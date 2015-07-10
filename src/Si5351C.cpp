/**
@file   Si5351C.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Configuring of Si5351C synthesizer
*/

#include "Si5351C.h"
#include "ConnectionManager.h"
#include <math.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;
#include "CommonUtilities.h"
#include "MessageLog.h"

/// Splits float into fraction integers A + B/C
void realToFrac(const float real, int &A, int &B, int &C)
{
    A = (int)real;
    B = (int)((real - A) * 1048576 + 0.5);
    C = 1048576;

    int a = B;
    int b = C;
    int temp;
    while( b!= 0) // greatest common divider
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    B = B/a;
    C = C/a;
}

/// Default configuration for Si5351C
const unsigned char Si5351C::m_defaultConfiguration[] =
{ 0,0x00,
  1,0x00,
  2,0x08,
  3,0x00,
  4,0x00,
  5,0x00,
  6,0x00,
  7,0x00,
  8,0x00,
  9,0x00,
 10,0x00,
 11,0x00,
 12,0x00,
 13,0x00,
 14,0x00,
 15,0x04,
 16,0x4F,
 17,0x4F,
 18,0x4F,
 19,0x4F,
 20,0x4F,
 21,0x4F,
 22,0x0F,
 23,0x0F,
 24,0x00,
 25,0x00,
 26,0x00,
 27,0x80,
 28,0x00,
 29,0x0B,
 30,0x2F,
 31,0x00,
 32,0x00,
 33,0x00,
 34,0x00,
 35,0x00,
 36,0x00,
 37,0x00,
 38,0x00,
 39,0x00,
 40,0x00,
 41,0x00,
 42,0x00,
 43,0x01,
 44,0x00,
 45,0x0D,
 46,0x00,
 47,0x00,
 48,0x00,
 49,0x00,
 50,0x00,
 51,0x01,
 52,0x00,
 53,0x0D,
 54,0x00,
 55,0x00,
 56,0x00,
 57,0x00,
 58,0x00,
 59,0x01,
 60,0x00,
 61,0x0D,
 62,0x00,
 63,0x00,
 64,0x00,
 65,0x00,
 66,0x00,
 67,0x01,
 68,0x00,
 69,0x0D,
 70,0x00,
 71,0x00,
 72,0x00,
 73,0x00,
 74,0x00,
 75,0x01,
 76,0x00,
 77,0x0D,
 78,0x00,
 79,0x00,
 80,0x00,
 81,0x00,
 82,0x00,
 83,0x01,
 84,0x00,
 85,0x0D,
 86,0x00,
 87,0x00,
 88,0x00,
 89,0x00,
 90,0x1E,
 91,0x1E,
 92,0x00,
 93,0x00,
 94,0x00,
 95,0x00,
 96,0x00,
 97,0x00,
 98,0x00,
 99,0x00,
100,0x00,
101,0x00,
102,0x00,
103,0x00,
104,0x00,
105,0x00,
106,0x00,
107,0x00,
108,0x00,
109,0x00,
110,0x00,
111,0x00,
112,0x00,
113,0x00,
114,0x00,
115,0x00,
116,0x00,
117,0x00,
118,0x00,
119,0x00,
120,0x00,
121,0x00,
122,0x00,
123,0x00,
124,0x00,
125,0x00,
126,0x00,
127,0x00,
128,0x00,
129,0x00,
130,0x00,
131,0x00,
132,0x00,
133,0x00,
134,0x00,
135,0x00,
136,0x00,
137,0x00,
138,0x00,
139,0x00,
140,0x00,
141,0x00,
142,0x00,
143,0x00,
144,0x00,
145,0x00,
146,0x00,
147,0x00,
148,0x00,
149,0x00,
150,0x00,
151,0x00,
152,0x00,
153,0x00,
154,0x00,
155,0x00,
156,0x00,
157,0x00,
158,0x00,
159,0x00,
160,0x00,
161,0x00,
162,0x00,
163,0x00,
164,0x00,
165,0x00,
166,0x00,
167,0x00,
168,0x00,
169,0x00,
170,0x00,
171,0x00,
172,0x00,
173,0x00,
174,0x00,
175,0x00,
176,0x00,
177,0x00,
178,0x00,
179,0x00,
180,0x00,
181,0x30,
182,0x00,
183,0xD2,
184,0x60,
185,0x60,
186,0x00,
187,0xC0,
188,0x00,
189,0x00,
190,0x00,
191,0x00,
192,0x00,
193,0x00,
194,0x00,
195,0x00,
196,0x00,
197,0x00,
198,0x00,
199,0x00,
200,0x00,
201,0x00,
202,0x00,
203,0x00,
204,0x00,
205,0x00,
206,0x00,
207,0x00,
208,0x00,
209,0x00,
210,0x00,
211,0x00,
212,0x00,
213,0x00,
214,0x00,
215,0x00,
216,0x00,
217,0x00,
218,0x00,
219,0x00,
220,0x00,
221,0x0D,
222,0x00,
223,0x00,
224,0x00,
225,0x00,
226,0x00,
227,0x00,
228,0x00,
229,0x00,
230,0x00,
231,0x00,
232,0x00};

/** Creates configuration module for Si5351C and initializes default values
*/
Si5351C::Si5351C()
{
    memset(m_newConfiguration, 0, 255);
    for(unsigned int i=0; i<sizeof(m_defaultConfiguration); i+=2)
    {
        m_newConfiguration[m_defaultConfiguration[i]] = m_defaultConfiguration[i+1];
    }
	device = NULL;
}
// ---------------------------------------------------------------------------

Si5351C::~Si5351C()
{
}

/** @brief Sends Configuration to Si5351C
*/
void Si5351C::UploadConfiguration()
{
    vector<unsigned char> out;
	if (!device)
    {
        MessageLog::getInstance()->write("Si5351C - connection manager not set. Configuring aborted.\n", LOG_ERROR);
		return;
    }
    //Disable outputs
	out.push_back(3);
	out.push_back(0xFF);
	//Power down all output drivers
	for(int i=0; i<8; ++i)
    {
        out.push_back(16+i);
        out.push_back(0x84);
    }
	//write new configuration
	for (int i = 15; i <= 92; ++i)
	{
        out.push_back(i);
        out.push_back(m_newConfiguration[i]);
	}
	for (int i = 149; i <= 170; ++i)
	{
        out.push_back(i);
        out.push_back(m_newConfiguration[i]);
	}
	//apply soft reset
	out.push_back(177);
	out.push_back(0xAC);
    //Enabe desired outputs
	out.push_back(3);
	out.push_back(m_newConfiguration[3]);

	if( !device->IsOpen() )
	{
        MessageLog::getInstance()->write("Si5351C - Configuration upload FAILED: control port not connected\n", LOG_WARNING);
        return;
	}

	GenericPacket pkt;
	pkt.cmd = CMD_SI5351_WR;
	pkt.outLen = out.size();
	memcpy(pkt.outBuffer, &out[0], pkt.outLen);

	if( device->TransferPacket(pkt) == STATUS_COMPLETED_CMD )
        MessageLog::getInstance()->write("Si5351C - Configuration upload completed.\n", LOG_INFO);
    else
        MessageLog::getInstance()->write("Si5351C - Configuration upload FAILED.\n", LOG_WARNING);
}

// ---------------------------------------------------------------------------
/**
    @brief Sets connection manager to use for data transferring and configures Si5351C
    @param mng connection manager for data transferring
*/
void Si5351C::Initialize(ConnectionManager *mng)
{
	device = mng;
	if (device == NULL)
        MessageLog::getInstance()->write("Si5351C - Initializing without connection manager.\n", LOG_WARNING);
}

/**
    @brief Loads register values for Si5356A from file
    @param FName input filename
*/
bool Si5351C::LoadRegValuesFromFile(const char *FName)
{
    fstream fin;
    fin.open(FName, ios::in);

    const int len = 1024;
    char line[len];

    int addr;
    unsigned int value;

    while(!fin.eof())
    {
        fin.getline(line, len);
        if( line[0] == '#')
            continue;
        if( strcmp(line, "#END_PROFILE") == 0)
            break;
        sscanf(line, "%i,%x",&addr,&value);
        m_newConfiguration[addr] = value;
    }

    fin.close();
	return false;
}

/** @brief Calculates multisynth dividers and VCO frequencies
    @param clocks output clocks configuration
    @param plls plls configurations
    @param Fmin lowest VCO frequency
    @param Fmax highest VCO frequency
*/
void Si5351C::FindVCO(Si5351_Channel *clocks, Si5351_PLL *plls, const unsigned long Fmin, const unsigned long Fmax)
{
    int clockCount = 8;
    //reset output parameters
    for(int i=0; i<clockCount; i++)
    {
        clocks[i].pllSource = 0;
        clocks[i].int_mode = 0;
        clocks[i].multisynthDivider = 0;
    }

    bool clk6satisfied = !clocks[6].powered;
    bool clk7satisfied = !clocks[7].powered;

    bool pllAused = false;
    bool pllBused = false;

    map< unsigned long, int> availableFrequenciesPLLA; //all available frequencies for VCO
    map< unsigned long, int> availableFrequenciesPLLB; //all available frequencies for VCO

    //if clk6 or clk7 is used make available frequencies according to them
    if(clocks[6].powered || clocks[7].powered)
    {
        set<unsigned long> clk6freqs;
        set<unsigned long> clk7freqs;
        set<unsigned long> sharedFreqs;
        unsigned int mult = 6;
        if(!clk6satisfied)
        {
            unsigned long freq = clocks[6].outputFreqHz;
            while(freq <= Fmax && mult <= 254)
            {
                freq = clocks[6].outputFreqHz*mult;
                if(freq >= Fmin && freq <= Fmax)
                {
                    clk6freqs.insert(freq);
                }
                mult += 2;
            }
        }
        mult = 6;
        if(!clk7satisfied)
        {
            unsigned long freq = clocks[7].outputFreqHz;
            while(freq <= Fmax && mult <= 254)
            {
                freq = clocks[7].outputFreqHz*mult;
                if(freq >= Fmin && freq <= Fmax)
                {
                    clk7freqs.insert(freq);
                }
                mult += 2;
            }
        }
        bool canShare = false;
        //find if clk6 and clk7 can share the same pll
        for (set<unsigned long>::iterator it6=clk6freqs.begin(); it6!=clk6freqs.end(); ++it6)
        {
            for (set<unsigned long>::iterator it7=clk7freqs.begin(); it7!=clk7freqs.end(); ++it7)
            {
                if(*it6 == *it7)
                {
                    canShare = true;
                    sharedFreqs.insert(*it6);
                }
            }
        }
        cout << endl;
        if(canShare) //assign PLLA for both clocks
        {
            clocks[6].pllSource = 0;
            clocks[7].pllSource = 0;
            pllAused = true;
            for (set<unsigned long>::iterator it=sharedFreqs.begin(); it!=sharedFreqs.end(); ++it)
            {
                availableFrequenciesPLLA.insert( pair<unsigned long, int> (*it, 0) );
            }
            clk6satisfied = true;
            clk7satisfied = true;
        }
        else //if clocks 6 and 7 can't share pll, assign pllA to clk6 and pllB to clk7
        {
            if(!clk6satisfied)
            {
                clocks[6].pllSource = 0;
                clk6satisfied = true;
                pllAused = true;
                for (set<unsigned long>::iterator it6=clk6freqs.begin(); it6!=clk6freqs.end(); ++it6)
                {
                    availableFrequenciesPLLA.insert( pair<unsigned long, int>(*it6, 0) );
                }
            }
            if(!clk7satisfied)
            {
                clocks[7].pllSource = 1;
                clk7satisfied = true;
                pllBused = true;
                for (set<unsigned long>::iterator it7=clk7freqs.begin(); it7!=clk7freqs.end(); ++it7)
                {
                    availableFrequenciesPLLB.insert( pair<unsigned long, int> (*it7, 0) );
                }
            }
        }
    }

    //PLLA stage, find  all clocks that have integer coefficients with PLLA
    //if pllA is not used by clk6 or clk7, fill available frequencies according to clk1-clk5 clocks
    if( availableFrequenciesPLLA.size() == 0 && !pllAused)
    {
        for(int i=0; i<6; ++i)
        {
            unsigned long freq = clocks[i].outputFreqHz > Fmin ? clocks[i].outputFreqHz : (clocks[i].outputFreqHz*((Fmin/clocks[i].outputFreqHz) + ((Fmin%clocks[i].outputFreqHz)!=0)));
            while(freq >= Fmin && freq <= Fmax)
            {
                //add all output frequency multiples that are in VCO interval
                availableFrequenciesPLLA.insert( pair<unsigned long, int> (freq, 0));
                freq += clocks[i].outputFreqHz;
            }
        }
    }

    int bestScore = 0; //score shows how many outputs have integer dividers
    //calculate scores for all available frequencies
    unsigned long bestVCOA = 0;
    for (map<unsigned long, int>::iterator it=availableFrequenciesPLLA.begin(); it!=availableFrequenciesPLLA.end(); ++it)
    {
        for(int i=0; i<8; ++i)
        {
            if(clocks[i].outputFreqHz == 0 || !clocks[i].powered)
                continue;

            if( (it->first % clocks[i].outputFreqHz) == 0)
            {
                it->second = it->second+1;
            }
        }
        if(it->second >= bestScore)
        {
            bestScore = it->second;
            bestVCOA = it->first;
        }
    }

    plls[0].VCO_Hz = bestVCOA;
    plls[0].feedbackDivider = (double)bestVCOA/plls[0].inputFreqHz;

    for(int i=0; i<clockCount; ++i)
    {
        if(clocks[i].outputFreqHz == 0 || !clocks[i].powered)
            continue;

        clocks[i].multisynthDivider = bestVCOA/clocks[i].outputFreqHz;
        if(bestVCOA%clocks[i].outputFreqHz == 0)
        {
            clocks[i].int_mode = true;
            clocks[i].multisynthDivider = bestVCOA/clocks[i].outputFreqHz;
        }
        else
        {
            clocks[i].int_mode = false;
            clocks[i].multisynthDivider = (double)bestVCOA/clocks[i].outputFreqHz;
        }
        clocks[i].pllSource = 0;
    }


    //PLLB stage, find  all clocks that have integer coefficients with PLLB
    //if pllB is not used by clk6 or clk7, fill available frequencies according to clk1-clk5 clocks, that don't have integer dividers
    if( availableFrequenciesPLLB.size() == 0 && !pllBused)
    {
        for(int i=0; i<6; ++i)
        {
            if(clocks[i].outputFreqHz == 0 || !clocks[i].powered)
                continue;

            if(clocks[i].int_mode) //skip clocks with integer dividers
                continue;
            unsigned long freq = clocks[i].outputFreqHz > Fmin ? clocks[i].outputFreqHz : (clocks[i].outputFreqHz*((Fmin/clocks[i].outputFreqHz) + ((Fmin%clocks[i].outputFreqHz)!=0)));
            while(freq >= Fmin && freq <= Fmax)
            {
                availableFrequenciesPLLB.insert( pair<unsigned long, int> (freq, 0));
                freq += clocks[i].outputFreqHz;
            }
        }
    }

    bestScore = 0;
    //calculate scores for all available frequencies
    unsigned long bestVCOB = 0;
    for (map<unsigned long, int>::iterator it=availableFrequenciesPLLB.begin(); it!=availableFrequenciesPLLB.end(); ++it)
    {
        for(int i=0; i<8; ++i)
        {
            if(clocks[i].outputFreqHz == 0 || !clocks[i].powered)
                continue;

            if( (it->first % clocks[i].outputFreqHz) == 0)
            {
                it->second = it->second+1;
            }
        }
        if(it->second >= bestScore)
        {
            bestScore = it->second;
            bestVCOB = it->first;
        }
    }

    if(bestVCOB == 0) //just in case if pllb is not used make it the same frequency as plla
        bestVCOB = bestVCOA;
    plls[1].VCO_Hz = bestVCOB;
    plls[1].feedbackDivider = (double)bestVCOB/plls[0].inputFreqHz;
    for(int i=0; i<clockCount; ++i)
    {
        if(clocks[i].outputFreqHz == 0 || !clocks[i].powered)
                continue;

        if(clocks[i].int_mode)
            continue;
        clocks[i].multisynthDivider = bestVCOB/clocks[i].outputFreqHz;
        if(bestVCOB%clocks[i].outputFreqHz == 0)
        {
            clocks[i].int_mode = true;
            clocks[i].multisynthDivider = bestVCOB/clocks[i].outputFreqHz;
        }
        else
        {
            clocks[i].int_mode = false;
            clocks[i].multisynthDivider = (double)bestVCOB/clocks[i].outputFreqHz;
        }
        clocks[i].pllSource = 1;
    }
}


/** @brief Modifies register map with clock settings
    @return true if success
*/
bool Si5351C::ConfigureClocks()
{
    FindVCO(CLK, PLL, 600000000, 900000000);
    stringstream ss;
    int addr;
    m_newConfiguration[3] = 0;
    for(int i=0; i<8; ++i)
    {
        m_newConfiguration[3] |= (!CLK[i].powered) << i; //enabled
        m_newConfiguration[16+i] |= !CLK[i].powered << 7; // powered
        m_newConfiguration[16+i] = 0;
        if(CLK[i].int_mode)
        {
            m_newConfiguration[16+i] |= 1 << 6; //integer mode
        }
        else
            m_newConfiguration[16+i] |= 0 << 6;

        m_newConfiguration[16+i] |= CLK[i].pllSource << 5; //PLL source
        m_newConfiguration[16+i] |= CLK[i].inverted << 4; // invert
        m_newConfiguration[16+i] |= 3 << 2;
        m_newConfiguration[16+i] |= 3;

        addr = 42+i*8;
        ss.clear();
        ss.str( string() );
        ss << "CLK" << i << " fOut = " << CLK[i].outputFreqHz/1000000.0 << " MHz";
        int DivA;
        int DivB;
        int DivC;

        realToFrac(CLK[i].multisynthDivider, DivA, DivB, DivC);
        ss << "  Multisynth Divider " << DivA << " " << DivB << "/" << DivC;
        ss << "  R divider = " << CLK[i].outputDivider << " source = " << (CLK[i].pllSource == 0 ? "PLLA" : "PLLB") << endl;

        MessageLog::getInstance()->write(ss.str(), LOG_INFO);

        if(( CLK[i].multisynthDivider < 8 || 900 < CLK[i].multisynthDivider)&& CLK[i].powered == true)
        {
            MessageLog::getInstance()->write("Si5351C - Output multisynth divider is outside [8;900] interval.\n", LOG_ERROR);
            return false;
        }

        if(CLK[i].outputFreqHz <= 150000000)
        {
            if(i>5)
            {
                m_newConfiguration[90+i-6] = CLK[i].multisynthDivider;
            }
            else
            {
                unsigned MSX_P1 = 128 * DivA + floor(128 * ( (float)DivB/DivC)) - 512;
                unsigned MSX_P2 = 128 * DivB - DivC * floor( 128 * DivB/DivC );
                unsigned MSX_P3 = DivC;

                m_newConfiguration[addr] = MSX_P3 >> 8;
                m_newConfiguration[addr+1] = MSX_P3;

                m_newConfiguration[addr+2] = 0;
                m_newConfiguration[addr+2] |= (MSX_P1 >> 16 ) & 0x03;
                m_newConfiguration[addr+3] = MSX_P1 >> 8;
                m_newConfiguration[addr+4] = MSX_P1;

                m_newConfiguration[addr+5] = 0;
                m_newConfiguration[addr+5] = (MSX_P2 >> 16) & 0x0F;
                m_newConfiguration[addr+5] |= (MSX_P3 >> 16) << 4;

                m_newConfiguration[addr+6] = MSX_P2;
                m_newConfiguration[addr+7] = MSX_P2 >> 8;
            }
        }
        else if( CLK[i].outputFreqHz <= 160000000) // AVAILABLE ONLY ON 0-5 MULTISYNTHS
        {
            MessageLog::getInstance()->write("Si5351C - clock configuring for more than 150 MHz not implemented\n", LOG_ERROR);
            return false;
        }
    }

    //configure pll
    for(int i=0; i<2; ++i)
    {
        addr = 26+i*8;
        if(PLL[i].feedbackDivider < 15 || PLL[i].feedbackDivider > 90)
        {
            MessageLog::getInstance()->write("Si5351C - VCO frequency divider out of range [15:90].\n", LOG_ERROR); return false;
        }
        if( PLL[i].VCO_Hz < 600000000 || PLL[i].VCO_Hz > 900000000)
        {
            MessageLog::getInstance()->write("Si5351C - Can't calculate valid VCO frequency.\n", LOG_ERROR); return false;
        }
        ss.clear();
        ss.str(string());
        ss << "Si5351C : VCO" << (i==0 ? "A" : "B") << " = " << PLL[i].VCO_Hz/1000000.0 << " MHz";

        //calculate MSNx_P1, MSNx_P2, MSNx_P3
        int MSNx_P1;
        int MSNx_P2;
        int MSNx_P3;

        int DivA;
        int DivB;
        int DivC;
        realToFrac(PLL[i].feedbackDivider, DivA, DivB, DivC);
        ss << "  Feedback Divider " << DivA << " " << DivB << "/" << DivC << endl;
        MessageLog::getInstance()->write(ss.str(), LOG_INFO);

        MSNx_P1 = 128 * DivA + floor(128 * ( (float)DivB/DivC)) - 512;
        MSNx_P2 = 128 * DivB - DivC * floor( 128 * DivB/DivC );
        MSNx_P3 = DivC;

        m_newConfiguration[addr+4] = MSNx_P1;
        m_newConfiguration[addr+3] = MSNx_P1 >> 8;
        m_newConfiguration[addr+2] = MSNx_P1 >> 16;

        m_newConfiguration[addr+7] = MSNx_P2;
        m_newConfiguration[addr+6] = MSNx_P2 >> 8;
        m_newConfiguration[addr+5] = 0;
        m_newConfiguration[addr+5] = (MSNx_P2 >> 16) & 0x0F;

        m_newConfiguration[addr+5] |= (MSNx_P3 >> 16) << 4;
        m_newConfiguration[addr+1] |= MSNx_P3;
        m_newConfiguration[addr] |= MSNx_P3 >> 8;
    }
    //CLK input divider
    unsigned char cbyte = 0;
    cbyte = (m_newConfiguration[15] & 0x3F) | ((int)log2(PLL[0].feedbackDivider) << 6);
    //PLLA source
    cbyte |= 0x04;
    cbyte |= 0x08;
    m_newConfiguration[15] = cbyte;

    return true;
}

/** @brief Sets output clock parameters
    @param id clock id 0-CLK0 1-CLK1 ...
    @param fOut_Hz output frequency in Hz
    @param enabled is this output powered
    @param inverted invert clock
*/
void Si5351C::SetClock(unsigned char id, unsigned long fOut_Hz, bool enabled, bool inverted)
{
    if( id < 8)
    {
        if(fOut_Hz < 8000 || fOut_Hz > 160000000)
        {
            stringstream ss;
            ss << "Si5351C - CLK" << (int)id << " output frequency must be between 8kHz and 160MHz. fOut_MHz = " << fOut_Hz/1000000.0 << endl;
            MessageLog::getInstance()->write(ss.str(), LOG_ERROR);
            //return;
        }
        CLK[id].outputFreqHz = fOut_Hz;
        if(fOut_Hz == 0)
        {
            CLK[id].powered = false;
            CLK[id].outputFreqHz = 1;
        }
        else
            CLK[id].powered = enabled;
        CLK[id].inverted = inverted;
    }
}

/** @brief Sets PLL input frequency
    @param id PLL id 0-PLLA 1-PLLB
    @param CLKIN_Hz clock input in Hz
*/
void Si5351C::SetPLL(unsigned char id, unsigned long CLKIN_Hz)
{
    if(id < 2)
        PLL[id].inputFreqHz = CLKIN_Hz;
}

/** @brief Resets configuration registers to default values
*/
void Si5351C::Reset()
{
    memset(m_newConfiguration, 0, 255);
    for(unsigned int i=0; i<sizeof(m_defaultConfiguration); i+=2)
    {
        m_newConfiguration[m_defaultConfiguration[i]] = m_defaultConfiguration[i+1];
    }
}

ConnectionManager* Si5351C::getDeviceManager()
{
    return device;
}
