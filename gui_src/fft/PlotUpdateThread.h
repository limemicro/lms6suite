#ifndef PLOT_UPDATE_THREAD_H
#define PLOT_UPDATE_THREAD_H

#include "wx/thread.h"

class pnlFFTviewer;

class PlotUpdateThread : public wxThread
{
public:
    struct CalculationResults
    {
        float iqPeakToAvgRatio;
        float pwrCh1;
        float pwrCh2;
        float dbc;
    };

    PlotUpdateThread(pnlFFTviewer *mainFrame);
    ~PlotUpdateThread();
    virtual void* Entry();
    void Stop();
    bool SetFFTsize(int size);
    bool SetSamplingFrequency(double freq);
private:
    int m_FFTsize;
    double m_samplingFreq;
    pnlFFTviewer *m_mainframe;
    bool m_running;
};

#endif // PLOT_UPDATE_THREAD_H

