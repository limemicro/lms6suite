/**
@file   Si5351C.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for configuring Si5351C synthesizer
*/

#ifndef SI5351C_MODULE
#define SI5351C_MODULE

#include <stdio.h>
#include <string>

void realToFrac(const float real, int &A, int &B, int &C);
//---------------------------------------------------------------------------
/// Input clock type
enum eSi_CLOCK_INPUT
{
    Si_CLKIN,
    Si_XTAL,
    Si_CMOS
};

/// Output channel parameters
struct Si5351_Channel
{
    Si5351_Channel() : outputDivider(1), outputFreqHz(1), multisynthDivider(1), pllSource(0),
        phaseOffset(0), powered(true), inverted(false), int_mode(false) {};
    int outputDivider;
    unsigned long outputFreqHz;
    float multisynthDivider;
    int pllSource;
    float phaseOffset;
    bool powered;
    bool inverted;
    bool int_mode;
};

/// PLL parameters
struct Si5351_PLL
{
    Si5351_PLL() : inputFreqHz(0), VCO_Hz(0), feedbackDivider(0), CLKIN_DIV(1) {}
    unsigned long inputFreqHz;
    float VCO_Hz;
    float feedbackDivider;
    int CLKIN_DIV;
};

class ConnectionManager;
class Si5351C
{
public:
	Si5351C();
	~Si5351C();
	void Initialize(ConnectionManager *mng);
	bool LoadRegValuesFromFile(const char* FName);

    void SetPLL(unsigned char id, unsigned long CLKIN_Hz);
    void SetClock(unsigned char id, unsigned long fOut_Hz, bool enabled = true, bool inverted = false);

	void UploadConfiguration();
	bool ConfigureClocks();
	void Reset();
	ConnectionManager* getDeviceManager();
private:
    void FindVCO(Si5351_Channel *clocks, Si5351_PLL *plls, const unsigned long Fmin, const unsigned long Fmax);
    ConnectionManager *device;
    Si5351_PLL PLL[2];
    Si5351_Channel CLK[8];
	static const unsigned char m_defaultConfiguration[];
	unsigned char m_newConfiguration[255];
};
#endif // SI5351C_MODULE
