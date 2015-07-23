#include "FFTcalculator.h"

#include <vector>
#include "CommonUtilities.h"
#include <cmath>
#ifdef USE_FFTW
    #include "fftw3.h"
#else
    #include "kiss_fft.h"
#endif
using namespace std;

FFTcalculator::FFTcalculator(BlockingFIFO<SamplesPacket>* InChannels, BlockingFIFO<FFTPacket>* OutChannels, int outputChannels)
{
    mAmplitudeCorrectionCoef = 1;
    m_fftRate = 0;
    m_channelsEnable = 0x3; //first two channels enabled
    m_outputCount = outputChannels;
    windowFcoefs = NULL;
    m_windowFunction = 0;
    m_newWindowFunction = 0;
    m_fftLimit = 100;
    //fftw_init_threads();
    m_inChannels = InChannels;
    m_outChannels = OutChannels;
    m_fftsCalculated = 0;
    m_avgCount = 1;
    m_new_avgCount = m_avgCount;
    m_dccorr = false;
    m_running = false;
    m_FFTsize = 0;
    m_samplingFreq = 1000;
}

FFTcalculator::~FFTcalculator()
{
    if(windowFcoefs)
        delete []windowFcoefs;
}

/** @brief Starts FFT calculation procedures
*/
bool FFTcalculator::Start()
{
    if(m_inChannels == NULL)
    {
        fprintf(stderr, "FFT calculator has no assigned input buffers!\n");
        return false;
    }
    m_running = true;
    lmThread_create(m_thread, &CalculationsThread, this);
    return true;
}

/** @brief Signals to stop FFT calculations and blocks until calculations are finished
*/
void FFTcalculator::Stop()
{
    printf("Stopping FFT calc\n");
    m_running = false;
    lmThread_join(m_thread);
}

/** @brief Sets number of samples used in FFT calculations
    @param size number of samples
    @return true if success
*/
bool FFTcalculator::SetFFTsize(int size)
{
    if(m_running)
        return false;
    m_FFTsize = size;
    return true;
}

/** @brief Sets sampling frequency for display
    @param freq sampling frequency in Hz
    @return true if success
*/
bool FFTcalculator::SetSamplingFrequency(double freq)
{
    if(m_running)
        return false;
    m_samplingFreq = freq;
    return true;
}

/** @brief Sets number of FFT results to average for display
    @param count number of FFTs
    @param enabled enable averaging
    @return true if success
*/
bool FFTcalculator::SetAveragingCount(unsigned count, bool enabled)
{
    if(enabled)
        m_new_avgCount = count;
    else
        m_new_avgCount = 1;
    return true;
}

/** @brief Enables or disables DC correction
    @return true if success
*/
bool FFTcalculator::SetDCcorrection(bool enabled)
{
    m_dccorr = enabled;
    return true;
}

/** @brief FFT calculations procedure
    @param pFFTcalculator pointer to FFT calculations module
*/
void* FFTcalculator::CalculationsThread(void* pFFTcalculator)
{
    FFTcalculator *pthis;
    pthis = static_cast<FFTcalculator*>(pFFTcalculator);
    const int fftSize = pthis->m_FFTsize;

#ifdef USE_FFTW
    fftwf_complex* m_fftCalcOut;
    fftwf_complex* m_fftCalcIn;
    fftwf_plan m_fftCalcPlan;
    m_fftCalcOut = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * fftSize);
    m_fftCalcIn = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * fftSize);
    //same fft plan will be used for all channels
    m_fftCalcPlan = fftwf_plan_dft_1d(fftSize, m_fftCalcIn, m_fftCalcOut, FFTW_FORWARD, FFTW_MEASURE);
#else
    kiss_fft_cfg m_fftCalcPlan = kiss_fft_alloc(fftSize, 0, 0, 0);
    kiss_fft_cpx* m_fftCalcIn = new kiss_fft_cpx[fftSize];
    kiss_fft_cpx* m_fftCalcOut = new kiss_fft_cpx[fftSize];
#endif

    FFTPacket **output = new FFTPacket*[pthis->m_outputCount]; //fft outputs for each channel
    for (int i = 0; i<pthis->m_outputCount; ++i)
    {
        output[i] = new FFTPacket(2 * fftSize);
        memset(output[i]->amplitudes, 0, sizeof(float)*output[i]->amplitudesCount);
    }
    SamplesPacket *samples = new SamplesPacket(2 * fftSize);
    FFTPacket *pkt = output[0];




    double val0 = -100; // db value to write when log10(0)
    pthis->m_fftsCalculated = 0;
    pthis->m_avgCount = pthis->m_new_avgCount;

    double dcCorrI = 0;
    double dcCorrQ = 0;

    long t1, t2;
    t2 = t1 = getMilis();

    int fftDiscarded = 0;
    long fftsCalculated = 0;
    //generate coefficients for currently selected window function
    pthis->GenerateWindowCoefficients(pthis->m_newWindowFunction, fftSize);

    int* packetsCollected = new int[pthis->m_outputCount];
    memset(packetsCollected, 0, sizeof(int)*pthis->m_outputCount);
    while (pthis->m_running)
    {
        if (pthis->m_inChannels->pop_front(samples, 200))
        {
            pkt = output[samples->channel];
            pkt->channel = samples->channel;
            ++packetsCollected[pkt->channel];
            if (((pthis->m_channelsEnable >> pkt->channel) & 0x1) == false)
                continue; // skip disabled channel data
            memcpy(pkt->iqsamples, samples->iqdata, sizeof(float)*samples->samplesCount);

            dcCorrI = 0;
            dcCorrQ = 0;
            if (pthis->m_dccorr) // calculate DC correction for IQ
            {
                int index = 0;
                while (index<pkt->samplesCount)
                {
                    dcCorrI += pkt->iqsamples[index];
                    ++index;
                    dcCorrQ += pkt->iqsamples[index];
                    ++index;
                }
                dcCorrI = dcCorrI / fftSize;
                dcCorrQ = dcCorrQ / fftSize;
                index = 0;
                while (index<pkt->samplesCount)
                {
                    pkt->iqsamples[index] -= dcCorrI;
                    ++index;
                    pkt->iqsamples[index] -= dcCorrQ;
                    ++index;
                }
            }
            if (pthis->m_windowFunction > 0) //apply window function if it's selected
            {
                int index = 0; int c = 0;
                while (index<pkt->samplesCount)
                {
                    samples->iqdata[index] = pkt->iqsamples[index] * pthis->windowFcoefs[c];
                    ++index;
                    samples->iqdata[index] = pkt->iqsamples[index] * pthis->windowFcoefs[c];
                    ++index;
                    ++c;
                }
            }
#ifdef USE_FFTW
            memcpy(m_fftCalcIn, samples->iqdata, samples->samplesCount*sizeof(float));
            fftwf_execute(m_fftCalcPlan);
#else			
            for (int i = 0; i < samples->samplesCount / 2; ++i)
            {
                m_fftCalcIn[i].r = samples->iqdata[2 * i];
                m_fftCalcIn[i].i = samples->iqdata[2 * i + 1];
            }
            kiss_fft(m_fftCalcPlan, m_fftCalcIn, m_fftCalcOut);
#endif
            ++fftsCalculated;

            int output_index = 0;
            for (int i = 0; i<fftSize; ++i)
            {
                // normalize FFT results
#ifdef USE_FFTW
                m_fftCalcOut[i][0] /= fftSize;
                m_fftCalcOut[i][1] /= fftSize;
                m_fftCalcOut[i][0] *= pthis->mAmplitudeCorrectionCoef;
                m_fftCalcOut[i][1] *= pthis->mAmplitudeCorrectionCoef;

                output_index = i + fftSize / 2 - 1;
                if (output_index >= fftSize)
                    output_index -= fftSize;
                pkt->amplitudes[output_index] += sqrt(m_fftCalcOut[i][0] * m_fftCalcOut[i][0] + m_fftCalcOut[i][1] * m_fftCalcOut[i][1]);
#else
                m_fftCalcOut[i].r /= fftSize;
                m_fftCalcOut[i].i /= fftSize;
                m_fftCalcOut[i].r *= pthis->mAmplitudeCorrectionCoef;
                m_fftCalcOut[i].i *= pthis->mAmplitudeCorrectionCoef;

                output_index = i + fftSize / 2 - 1;
                if (output_index >= fftSize)
                    output_index -= fftSize;
                pkt->amplitudes[output_index] += sqrt(m_fftCalcOut[i].r * m_fftCalcOut[i].r + m_fftCalcOut[i].i * m_fftCalcOut[i].i);
#endif
            }

        }

        if (packetsCollected[pkt->channel] >= pthis->m_avgCount)
        {
            if (((pthis->m_channelsEnable >> pkt->channel) & 0x1) == true)
            {
                //convert to log

                for (int s = 0; s<fftSize; ++s)
                {
                    pkt->amplitudes[s] /= packetsCollected[pkt->channel];     
                    pkt->amplitudes[s] = pkt->amplitudes[s] != 0 ? (20 * log10(pkt->amplitudes[s])) - 69.2369 : val0;
                }
                if (pthis->m_dccorr) // remove dc component from spectrum
                {
                    int dcIndex = fftSize / 2 - 1;
                    pkt->amplitudes[dcIndex] = (pkt->amplitudes[dcIndex - 1] + pkt->amplitudes[dcIndex + 1]) / 2;                    
                }
                if (pthis->m_outChannels->push_back(pkt, 0) == false)
                    ++fftDiscarded;
                //reset amplitudes to zeros for each channel
                memset(pkt->amplitudes, 0, sizeof(float)*pkt->amplitudesCount);
                packetsCollected[pkt->channel] = 0;
            }
        }

        //change averaging count if it changed
        if (pthis->m_new_avgCount != pthis->m_avgCount)
            pthis->m_avgCount = pthis->m_new_avgCount;

        //recalculate window function coefficients if it changed
        if (pthis->m_newWindowFunction != pthis->m_windowFunction)
            pthis->GenerateWindowCoefficients(pthis->m_newWindowFunction, fftSize);

        t2 = getMilis();
        if (t2 - t1 >= 1000)
        {
            printf("FFT posted %li  discarded:%i\n", fftsCalculated, fftDiscarded);
            pthis->m_outChannels->status();
            pthis->m_fftRate = (1000.0*fftsCalculated) / (t2 - t1);
            fftsCalculated = 0;
            fftDiscarded = 0;
            t1 = t2;
        }
    }
    delete[]packetsCollected;
#ifdef USE_FFTW
    fftwf_free(m_fftCalcOut);
    fftwf_free(m_fftCalcIn);
#else
    delete[]m_fftCalcOut;
    delete[]m_fftCalcIn;
#endif
    for (int i = 0; i<pthis->m_outputCount; ++i)
        delete output[i];
    delete[]output;
    delete samples;

    printf("fft calc stopped\n");
    return 0;
}


/** @brief Selects window function for incoming samples
    @param index window function index, 0-window function disabled
*/
void FFTcalculator::SetWindowFunction(int index)
{
    m_newWindowFunction = index;
}

/** @brief Calculates selected window function coefficients
    @param func window function index
    @param fftsize number of samples for FFT calculations
*/
void FFTcalculator::GenerateWindowCoefficients(int func, int fftsize)
{
    if(windowFcoefs)
        delete []windowFcoefs;

    windowFcoefs = new float[fftsize];
    float a0 = 0.35875;
    float a1 = 0.48829;
    float a2 = 0.14128;
    float a3 = 0.01168;
    float a4 = 1;
    int N = fftsize;
    float PI = 3.141596;
    switch(func)
    {
    case 0:
        mAmplitudeCorrectionCoef = 1;
        break;
    case 1: //hamming
        mAmplitudeCorrectionCoef = 0;
        a0 = 0.54;
        for(int i=0; i<N; ++i)
        {
            windowFcoefs[i] = a0 -(1-a0)*cos((2*PI*i)/(N));
            mAmplitudeCorrectionCoef += windowFcoefs[i];
        }
        mAmplitudeCorrectionCoef = 1.0/(mAmplitudeCorrectionCoef/N);
        break;
    case 2: //hanning
        mAmplitudeCorrectionCoef = 0;
        for(int i=0; i<N; ++i)
        {
            windowFcoefs[i] = 0.5 *(1 - cos((2*PI*i)/(N)));
            mAmplitudeCorrectionCoef += windowFcoefs[i];
        }
        mAmplitudeCorrectionCoef = 1.0/(mAmplitudeCorrectionCoef/N);
        break;
    default:
        mAmplitudeCorrectionCoef = 1;
    }
    m_windowFunction = func;
}

/** @brief Sets mask to enable channel calculations
    @param hexFlags channel enable bits, LSB-channel 0,
*/
void FFTcalculator::EnableChannels(int hexFlags)
{
    m_channelsEnable = hexFlags;
}
