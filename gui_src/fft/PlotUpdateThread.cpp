#include "PlotUpdateThread.h"
#include <stdio.h>
#include "pnlFFTviewer.h"
#include "CommonUtilities.h"
#include "SamplesCollector.h"
#include <vector>
#include <wx/time.h>
using namespace std;

const int CHANNEL_COUNT = 2;

PlotUpdateThread::PlotUpdateThread(pnlFFTviewer* mainFrame) : wxThread(wxTHREAD_JOINABLE)
{
    m_mainframe = mainFrame;
    m_running = false;
    m_FFTsize = 0;
    m_samplingFreq = 1000;
}

PlotUpdateThread::~PlotUpdateThread()
{

}

/** @brief Plots drawing procedure
*/
void* PlotUpdateThread::Entry()
{
    CalculationResults measurements;
    float *amplitudes = new float[m_FFTsize];
    FFTPacket *results = new FFTPacket(2*m_FFTsize);
    memset(results->iqsamples, 0, sizeof(float)*results->samplesCount);
    memset(results->amplitudes, 0, sizeof(float)*results->amplitudesCount);
    float *ftempI = new float[m_FFTsize];
    float *ftempQ = new float[m_FFTsize];
    memset(ftempI, 0, sizeof(float)*m_FFTsize);
    memset(ftempQ, 0, sizeof(float)*m_FFTsize);
    m_running = true;

    vector<float> timeVector;
    timeVector.reserve(m_FFTsize);
    for(int i=0; i<m_FFTsize; ++i)
    {
        timeVector.push_back(i);
    }
    vector<float> freqVector;
    freqVector.resize(m_FFTsize);
    for(int i=0; i<m_FFTsize; ++i)
    {
        float freq = i*(m_samplingFreq/m_FFTsize);
        int output_index = i+m_FFTsize/2-1;
        if(output_index >= m_FFTsize)
        {
            output_index -= m_FFTsize;
            freq -= m_samplingFreq;
        }
        freqVector[output_index] = freq;
    }

    long t1, t2;
    t2 = t1 = getMilis();
    long minUpdateIntervalMs = 50;

    int ch = 0;
    //reset plots to default data
    for(int i = 0; i<CHANNEL_COUNT; ++i)
    {
        wxCriticalSectionLocker lock(m_mainframe->m_dataCS);
        m_mainframe->m_gltimePlot->series[2*i+0]->AssignValues(&timeVector[0], ftempI, m_FFTsize);
        m_mainframe->m_gltimePlot->series[2*i+1]->AssignValues(&timeVector[0], ftempQ, m_FFTsize);
        m_mainframe->m_glconstellationPlot->series[i]->AssignValues(results->iqsamples, results->samplesCount);
        m_mainframe->m_glFFTplot->series[i]->AssignValues(&freqVector[0], results->amplitudes, results->amplitudesCount-1);
        m_mainframe->m_glFFTplot->Refresh();
        m_mainframe->m_gltimePlot->Refresh();
        m_mainframe->m_glconstellationPlot->Refresh();
        m_mainframe->mPowerMeasurements = measurements;
        wxThreadEvent tevt(wxEVT_THREAD, wxEVT_COMMAND_THREAD_UPDATE);        
        m_mainframe->GetEventHandler()->AddPendingEvent(tevt); //post event for gui thread to update
    }

    while(m_running)
    {
        t2 = getMilis();
        if(t2 - t1 >= minUpdateIntervalMs)
        {
            t1 = t2;
            memset(amplitudes, 0, sizeof(float)*m_FFTsize);
            bool newData = m_mainframe->m_fftOutputs->pop_front(results, 100);
            if( newData == true)
            {
                ch = results->channel;
                int i=0;
                int j=0;
                while(i<results->samplesCount)
                {
                    ftempI[j] = results->iqsamples[i];
                    ++i;
                    ftempQ[j] = results->iqsamples[i];
                    ++i;
                    ++j;
                }

                //calculate power measurements
                float sumI = 0;
                float sumQ = 0;
                for (int i = 0; i<m_FFTsize; ++i)
                {
                    sumI += ftempI[i];
                    sumQ += ftempQ[i];
                }
                float meanI = sumI / m_FFTsize;
                float meanQ = sumQ / m_FFTsize;

                float tempMag = 0;
                float averageMag = 0;
                float peakMag = sqrt((ftempI[0] - meanI)*(ftempI[0] - meanI) + (ftempQ[0] - meanQ)*(ftempQ[0] - meanQ));
                for (int i = 0; i<m_FFTsize; ++i)
                {
                    tempMag = sqrt((ftempI[i] - meanI)*(ftempI[i] - meanI) + (ftempQ[i] - meanQ)*(ftempQ[i] - meanQ));
                    averageMag += tempMag*tempMag;
                    if (tempMag  > peakMag)
                        peakMag = tempMag;
                }
                averageMag = sqrt(averageMag / m_FFTsize);
                if (averageMag != 0)
                {
                    measurements.iqPeakToAvgRatio = 20 * log10(peakMag / averageMag);
                }
                else
                    measurements.iqPeakToAvgRatio = 0;

            }

            if(m_mainframe->chkFreezeDrawing->IsChecked() == false && newData)
            {
                wxCriticalSectionLocker lock(m_mainframe->m_dataCS);

                float chPwr[2];
                double cFreq[2] = { 0, 2000000 };
                m_mainframe->txtCFreq1->GetValue().ToDouble(&cFreq[0]);
                cFreq[0] *= 1000000;
                m_mainframe->txtCFreq2->GetValue().ToDouble(&cFreq[1]);
                cFreq[1] *= 1000000;
                double bw[2] = { 2000000, 3000000 };
                m_mainframe->txtBW1->GetValue().ToDouble(&bw[0]);
                bw[0] *= 1000000;
                m_mainframe->txtBW2->GetValue().ToDouble(&bw[1]);
                bw[1] *= 1000000;
                char ctemp[512];
                for (int c = 0; c<2; ++c)
                {
                    float f0 = cFreq[c] - bw[c] / 2;
                    float fn = cFreq[c] + bw[c] / 2;
                    float sum = 0;
                    int bins = 0;
                    for (int i = 0; i<results->amplitudesCount; ++i)
                        if (f0 <= freqVector[i] && freqVector[i] <= fn)
                        {
                            sum += pow(10, results->amplitudes[i] / 10);
                            ++bins;
                        }
                    chPwr[c] = sum;
                }
                measurements.pwrCh1 = 10 * log10(chPwr[0]);
                measurements.pwrCh2 = 10 * log10(chPwr[1]);
                measurements.dbc = 10 * log10(chPwr[1] / chPwr[0]);

                m_mainframe->mPowerMeasurements = measurements;

                m_mainframe->m_gltimePlot->series[2*ch+0]->AssignValues(&timeVector[0], ftempI, m_FFTsize);
                m_mainframe->m_gltimePlot->series[2*ch+1]->AssignValues(&timeVector[0], ftempQ, m_FFTsize);
                m_mainframe->m_glconstellationPlot->series[ch]->AssignValues(results->iqsamples, results->samplesCount);
                m_mainframe->m_glFFTplot->series[ch]->AssignValues(&freqVector[0], results->amplitudes, results->amplitudesCount);
                m_mainframe->m_glFFTplot->Refresh();
                m_mainframe->m_gltimePlot->Refresh();
                m_mainframe->m_glconstellationPlot->Refresh();
                m_mainframe->m_redrawsDone++;
            }
            wxThreadEvent tevt(wxEVT_THREAD, wxEVT_COMMAND_THREAD_UPDATE);
            //tevt.SetPayload<CalculationResults>(measurements); //can't use, it causes antivirus to report as false positive
            m_mainframe->GetEventHandler()->AddPendingEvent(tevt); //post event for gui thread to update
        }
        else
            milSleep(minUpdateIntervalMs-(t2-t1));
    }
    delete []ftempI;
    delete []ftempQ;
    delete results;
    delete []amplitudes;
    printf("plot thread stopped\n");
    return 0;
}

/** @brief Stops plot updating
*/
void PlotUpdateThread::Stop()
{
    m_running = false;
    Wait();
}

/**
*/
bool PlotUpdateThread::SetFFTsize(int size)
{
    if(m_running)
        return false;
    m_FFTsize = size;
    return true;
}

/** @brief Sets sampling frequency for display
    @param freq sampling frequency in Hz
*/
bool PlotUpdateThread::SetSamplingFrequency(double freq)
{
    m_samplingFreq = freq;
    return true;
}
