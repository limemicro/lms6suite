#include "Programmer.h"
#include <fstream>

#include "ConnectionManager.h"
#include "LMS_Commands.h"
#include "CommonUtilities.h"
#include <sstream>
using namespace std;

Programmer::Programmer(ConnectionManager* pSerPort)
{
    m_serPort = pSerPort;
    m_data = NULL;
    m_data_size = 0;
}

Programmer::~Programmer()
{
    if(m_data)
        delete m_data;
}

/** @brief Loads program code from file
    @param filename file path
    @param type 0-binary, 1-hex
    @return 0:success, -1:failure, -2:file not found
*/
int Programmer::LoadFile(const char* filename, const int type)
{
    fstream fin;
    if(type == 0)
    {
        fin.open(filename, ios::in|ios::binary);
        if(!fin.good())
        {
            fin.close();
            return -2;
        }
        fin.seekg(0, ios_base::end);
        m_data_size = fin.tellg();
        if(m_data)
            delete[] m_data;
        m_data = new unsigned char[m_data_size];
        fin.seekg(0, ios_base::beg);
        fin.read((char*)m_data, m_data_size);
        if (fin.fail())
            return -1;
        fin.close();
        return 0;
    }
    return -1;
}

/** @brief Uploads program to controller
    @param device programmed device type 0:MyriadRF
    @param prog_mode programming mode
    @return 0:success, -1:failure, -2:program not loaded; -3:board not connected
*/
int Programmer::UploadProgram(const int device, const int prog_mode)
{
    if(m_data == NULL || m_data_size == 0)
        return -2;

    if(!m_serPort->IsOpen())
        return -3;

    int pktSize = 32;
    int data_left = m_data_size;
    unsigned char* data_src = m_data;
    // +1 programming end packet
    int portionsCount = m_data_size/pktSize + (m_data_size%pktSize > 0) + 1;
    int portionNumber;
    int status = 0;
    eCMD_LMS cmd;
    if(device == 0)
        cmd = CMD_MYRIAD_PROG;
    if(device == 1)
        cmd = CMD_ALTERA_FPGA_GW_WR;
    GenericPacket pkt;
    pkt.cmd = cmd;
    long updateInterval_ms = 1000;
    long t1, t2;
    t1 = getMilis();
    for(portionNumber=0; portionNumber<portionsCount; ++portionNumber)
    {
        memset(pkt.outBuffer, 0, 56);
        pkt.outBuffer[0] = prog_mode;
        pkt.outBuffer[1] = (portionNumber >> 24) & 0xFF;
        pkt.outBuffer[2] = (portionNumber >> 16) & 0xFF;
        pkt.outBuffer[3] = (portionNumber >> 8) & 0xFF;
        pkt.outBuffer[4] = portionNumber & 0xFF;
        unsigned char data_cnt = data_left > pktSize ? pktSize : data_left;
        pkt.outBuffer[5] = data_cnt;
        pkt.outLen = 56;
        memcpy(&pkt.outBuffer[24], data_src, data_cnt);
        data_src+=data_cnt;
        status = m_serPort->TransferPacket(pkt);
        data_left -= data_cnt;
        t2 = getMilis();
        if(status != STATUS_COMPLETED_CMD)
        {
            stringstream ss;
            ss << "Programming failed! Status: " << status2string(status) << endl;
            Notify( LMS_Message(MSG_ERROR, ss.str(), 0, 0));
            Notify( LMS_Message(MSG_PROGRAMMING_PACKET_SENT, "", portionsCount, portionsCount));
            return -1;
        }
        if(t2-t1>updateInterval_ms || portionNumber==portionsCount-1)
        {
            Notify( LMS_Message(MSG_PROGRAMMING_PACKET_SENT, "", portionNumber, portionsCount-1));
            t1 = t2;
        }
        if(device == 1 && prog_mode == 2)
            break;
    }
    Notify( LMS_Message(MSG_PROGRAMMING_PACKET_SENT, "", portionsCount, portionsCount));
    char ctemp[128];
    if((device == 1 && prog_mode == 2) == false)
    {
        sprintf(ctemp, "Programming finished, %li bytes sent!\n", m_data_size);
        Notify( LMS_Message(MSG_INFO, ctemp, 0, 0));
    }
    return 0;
}

void Programmer::HandleMessage(const LMS_Message &msg)
{
}
