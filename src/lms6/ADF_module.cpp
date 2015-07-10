/**
@file   ADF_module.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  ADF4002 module configuring
*/

#include "ADF_module.h"
#include <cmath>
#include "ConnectionManager.h"
#include "CommonUtilities.h"
#include "MessageLog.h"

/** @brief Creates ADF4002 control module and sets default control values
*/
ADF_module::ADF_module()
{
    SetDefaults();
}

ADF_module::~ADF_module()
{
}

/** @brief Sets default control values
*/
void ADF_module::SetDefaults()
{
    //Reference Counter Latch
    cmbLDP = 0;
    cmbABW = 0;
    txtRCnt = 125;

    //N Counter Latch
    cmbCPG = 0;
    txtNCnt = 384;

    //Function Latch
    rgrPD2_f = 0;
    cmbCS2_f = 7;
    cmbCS1_f = 7;
    cmbTC_f = 0;
    cmbFL_f = 0;
    rgrCPS_f = 0;
    rgrPDP_f = 1;
    cmbMOC_f = 1;
    rgrPD1_f = 0;
    rgrCR_f = 0;

    //Initialization Latch
    rgrPD2_i = 0;
    cmbCS2_i = 7;
    cmbCS1_i = 7;
    cmbTC_i = 0;
    cmbFL_i = 0;
    rgrCPS_i = 0;
    rgrPDP_i = 1;
    cmbMOC_i = 1;
    rgrPD1_i = 0;
    rgrCR_i = 0;

    txtFref = 10;
    txtFvco = 30.72;

    CalculateRN();
}

/** @brief Assigns connection manager for data writing
    @param pSerPort Serial port manager which will be used for data transfering
*/
void ADF_module::Initialize(ConnectionManager* pSerPort)
{
    m_serPort = pSerPort;
}

/** @brief Forms data buffer to configure ADF4002
*/
void ADF_module::MakeData()
{
    memset(m_registers, 0, 12);
    char btmp;
    unsigned int itmp;

    //======= register addr 0x00 =======
    m_registers[0x00] = 0x00;
    //R Value LSB
    itmp = txtRCnt;
    btmp = (char)itmp;
    btmp = btmp << 2;
    m_registers[0x00] |= btmp;
    //Addr
    btmp = 0x00;
    btmp = btmp << 0;
    m_registers[0x00] |= btmp;

    //======= register addr 0x01 =======
    m_registers[0x01] = 0x00;
    //R Value MSB
    btmp = (char)(itmp >> 6);
    btmp = btmp << 0;
    m_registers[0x01] |= btmp;

    //======= register addr 0x02 =======
    m_registers[0x02] = 0x00;
    //Anti-Backlash
    btmp = (char)cmbABW;
    if(btmp > 0) btmp++;
    btmp = btmp << 0;
    m_registers[0x02] |= btmp;
    //Lock Detact Precision
    btmp = (char)cmbLDP;
    btmp = btmp << 4;
    m_registers[0x02] |= btmp;

    //======= register addr 0x03 =======
    m_registers[0x03] = 0x00;
    //Addr
    btmp = 0x01;
    btmp = btmp << 0;
    m_registers[0x03] |= btmp;

    //======= register addr 0x04 =======
    m_registers[0x04] = 0x00;
    //N Value LSB
    itmp = txtNCnt;
    btmp = (char)itmp;
    btmp = btmp << 0;
    m_registers[0x04] |= btmp;

    //======= register addr 0x05 =======
    m_registers[0x05] = 0x00;
    //N Value MSB
    itmp = txtNCnt;
    btmp = (char)(itmp >> 8);
    btmp = btmp << 0;
    m_registers[0x05] |= btmp;
    //CP Gain
    btmp = (char)cmbCPG;
    btmp = btmp << 5;
    m_registers[0x05] |= btmp;

    //======= register addr 0x06 =======
    m_registers[0x06] = 0x00;
    //Addr
    btmp = 0x02;
    btmp = btmp << 0;
    m_registers[0x06] |= btmp;
    //Counter Reset
    btmp = (char)rgrCR_f;
    btmp = btmp << 2;
    m_registers[0x06] |= btmp;
    //PD 1
    btmp = (char)rgrPD1_f;
    btmp = btmp << 3;
    m_registers[0x06] |= btmp;
    //Muxout Control
    btmp = (char)cmbMOC_f;
    btmp = btmp << 4;
    m_registers[0x06] |= btmp;
    //PD Polarity
    btmp = (char)rgrPDP_f;
    btmp = btmp << 7;
    m_registers[0x06] |= btmp;

    //======= register addr 0x07 =======
    m_registers[0x07] = 0x00;
    //CP State
    btmp = (char)rgrCPS_f;
    btmp = btmp << 0;
    m_registers[0x07] |= btmp;
    //Fastlock
    btmp = (char)cmbFL_f;
    if(btmp > 0) btmp++;
    btmp = btmp << 1;
    m_registers[0x07] |= btmp;
    //Timer Counter
    btmp = (char)cmbTC_f;
    btmp = btmp << 3;
    m_registers[0x07] |= btmp;
    //Current Setting 1 MSB
    btmp = (char)cmbCS1_f;
    btmp = btmp << 7;
    m_registers[0x07] |= btmp;

    //======= register addr 0x08 =======
    m_registers[0x08] = 0x00;
    //Current Setting 1 LSB
    btmp = (char)cmbCS1_f;
    btmp = btmp >> 1;
    m_registers[0x08] |= btmp;
    //Current Setting 2
    btmp = (char)cmbCS2_f;
    btmp = btmp << 2;
    m_registers[0x08] |= btmp;
    //PD 2
    btmp = (char)rgrPD2_f;
    btmp = btmp << 5;
    m_registers[0x08] |= btmp;

    //======= register addr 0x09 =======
    m_registers[0x09] = 0x00;
    //Addr
    btmp = 0x03;
    btmp = btmp << 0;
    m_registers[0x09] |= btmp;
    //Counter Reset
    btmp = (char)rgrCR_i;
    btmp = btmp << 2;
    m_registers[0x09] |= btmp;
    //PD 1
    btmp = (char)rgrPD1_i;
    btmp = btmp << 3;
    m_registers[0x09] |= btmp;
    //Muxout Control
    btmp = (char)cmbMOC_i;
    btmp = btmp << 4;
    m_registers[0x09] |= btmp;
    //PD Polarity
    btmp = (char)rgrPDP_i;
    btmp = btmp << 7;
    m_registers[0x09] |= btmp;

    //======= register addr 0x0A =======
    m_registers[0x0A] = 0x00;
    //CP State
    btmp = (char)rgrCPS_i;
    btmp = btmp << 0;
    m_registers[0x0A] |= btmp;
    //Fastlock
    btmp = (char)cmbFL_i;
    if(btmp > 0) btmp++;
    btmp = btmp << 1;
    m_registers[0x0A] |= btmp;
    //Timer Counter
    btmp = (char)cmbTC_i;
    btmp = btmp << 3;
    m_registers[0x0A] |= btmp;
    //Current Setting 1 MSB
    btmp = (char)cmbCS1_i;
    btmp = btmp << 7;
    m_registers[0x0A] |= btmp;

    //======= register addr 0x0B =======
    m_registers[0x0B] = 0x00;
    //Current Setting 1 LSB
    btmp = (char)cmbCS1_i;
    btmp = btmp >> 1;
    m_registers[0x0B] |= btmp;
    //Current Setting 2
    btmp = (char)cmbCS2_i;
    btmp = btmp << 2;
    m_registers[0x0B] |= btmp;
    //PD 2
    btmp = (char)rgrPD2_i;
    btmp = btmp << 5;
    m_registers[0x0B] |= btmp;

    //change array order
    unsigned char ctemp = m_registers[0];
    m_registers[0] = m_registers[2];
    m_registers[1] = m_registers[1];
    m_registers[2] = ctemp;

    ctemp = m_registers[3];
    m_registers[3] = m_registers[5];
    m_registers[4] = m_registers[4];
    m_registers[5] = ctemp;

    ctemp = m_registers[6];
    m_registers[6] = m_registers[8];
    m_registers[7] = m_registers[7];
    m_registers[8] = ctemp;

    ctemp = m_registers[9];
    m_registers[9] = m_registers[11];
    m_registers[10] = m_registers[10];
    m_registers[11] = ctemp;
}

/** @brief Calculates and sets R & N values according to given frequencies
*/
void ADF_module::CalculateRN()
{
    double x = txtFref*1000000;
    double y = txtFvco*1000000;
    double Fcomp;
    while((x!=0) && (y!=0))
    {
        if(x >= y)
        {
            x = fmod(x, y);
        }
        else
        {
            y = fmod(y, x);
        };
    };

    Fcomp = (x + y)/1000000.0;
    int R = (txtFref/Fcomp)+0.5;
    int N = (txtFvco/Fcomp)+0.5;

    txtRCnt = R;
    txtNCnt = N;

    lblFcomp = Fcomp;
    double dFvco = 0;
    if(txtRCnt != 0)
        dFvco = txtNCnt * (txtFref)/txtRCnt;
    lblFvco = dFvco;
}

/** @brief Writes configuration to chip
    @return 0:success
            -1: failed
            -2: control port not connected
            -3: control manager not initialized
*/
int ADF_module::SendConfig()
{
    MakeData();
    GenericPacket pkt;
    pkt.cmd = CMD_ADF4002_WR;
    pkt.outLen = 12;

    memset(pkt.outBuffer, 0, 12);
    memcpy(&pkt.outBuffer[0], &m_registers[9], 3);
    memcpy(&pkt.outBuffer[3], &m_registers[6], 3);
    memcpy(&pkt.outBuffer[6], &m_registers[0], 3);
    memcpy(&pkt.outBuffer[9], &m_registers[3], 3);

    if(m_serPort == NULL)
    {
        MessageLog::getInstance()->write("ADF4002 configuration failed: module not initialized with serial port\n");
        return -3;
    }
    if(!m_serPort->IsOpen())
    {
        MessageLog::getInstance()->write("ADF4002 configuration failed: control port not connected\n");
        return -2;
    }
    if( m_serPort->TransferPacket(pkt) == STATUS_COMPLETED_CMD)
    {
        MessageLog::getInstance()->write("ADF4002 configured.\n");
        return 0;
    }
    else
    {
        MessageLog::getInstance()->write("ADF4002 configuration failed.\n");
        return -1;
    }
}

/** @brief Sets reference and VCO frequencies, returns R&N counts
    @param Fref reference frequency in MHz
    @param Fvco VCO frequency in MHz
    @param rcount Reference counter
    @param ncount N counter
*/
void ADF_module::SetFrefFvco(double Fref_MHz, double Fvco_MHz, int &rcount, int &ncount)
{
    txtFref = Fref_MHz;
    txtFvco = Fvco_MHz;
    CalculateRN();
    rcount = txtRCnt;
    ncount = txtNCnt;
}

void ADF_module::SetReferenceCounterLatch(int Ldp, int Abw, int refCounter)
{
    cmbLDP = Ldp;
    cmbABW = Abw;
    txtRCnt = refCounter;
}

void ADF_module::SetNCounterLatch(int CPgain, int NCounter)
{
    cmbCPG = CPgain;
    txtNCnt = NCounter;
}

void ADF_module::SetFunctionLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl)
{
    cmbCS1_f = currentSetting1;
    cmbCS2_f = currentSetting2;
    cmbTC_f = timerCounter;
    cmbFL_f = fastLock;
    cmbMOC_f = muxoutControl;
}
void ADF_module::SetFunctionLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState)
{
    rgrPD1_f = pd1;
    rgrPD2_f = pd2;
    rgrPDP_f = pdPol;
    rgrCR_f = counterReset;
    rgrCPS_f = cpState;
}
void ADF_module::SetInitializationLatch(int currentSetting1, int currentSetting2, int timerCounter, int fastLock, int muxoutControl)
{
    cmbCS1_i = currentSetting1;
    cmbCS2_i = currentSetting2;
    cmbTC_i = timerCounter;
    cmbFL_i = fastLock;
    cmbMOC_i = muxoutControl;
}
void ADF_module::SetInitializationLatchRgr(int pdPol, int pd1, int pd2, int counterReset, int cpState)
{
    rgrPD1_i = pd1;
    rgrPD2_i = pd2;
    rgrPDP_i = pdPol;
    rgrCR_i = counterReset;
    rgrCPS_i = cpState;
}

void ADF_module::HandleMessage(const LMS_Message &msg)
{
}
