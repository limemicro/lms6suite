#ifndef LMS_PROTOCOLS_H
#define LMS_PROTOCOLS_H

#include "LMS_Commands.h"
#include "string.h"

class ConnectionManager;

enum eLMS_PROTOCOL
{
    LMS_PROTOCOL_UNDEFINED = 0,
    LMS_PROTOCOL_DIGIC,
    LMS_PROTOCOL_LMS64C,
    LMS_PROTOCOL_NOVENA,
};

struct ProtocolDIGIC
{
    static const int pktLength = 64;
    static const int maxDataLength = 60;
    ProtocolDIGIC() : cmd(0), i2cAddr(0), blockCount(0) {};
    unsigned char cmd;
    unsigned char i2cAddr;
    unsigned char blockCount;
    unsigned char reserved;
    unsigned char data[maxDataLength];
};

struct ProtocolLMS64C
{
    static const int pktLength = 64;
    static const int maxDataLength = 56;
    ProtocolLMS64C() :cmd(0),status(0),blockCount(0) {memset(reserved, 0, 5);};
    unsigned char cmd;
    unsigned char status;
    unsigned char blockCount;
    unsigned char reserved[5];
    unsigned char data[maxDataLength];
};

struct ProtocolNovena
{
    static const int pktLength = 128;
    static const int maxDataLength = 128;
    ProtocolNovena() :cmd(0),status(0){};
    unsigned char cmd;
    unsigned char status;
    unsigned char blockCount;
    unsigned char data[maxDataLength];
};

struct GenericPacket
{
    static const int maxDataLength = 1024;
    GenericPacket()
    {
        cmd = CMD_GET_INFO;
        status = STATUS_UNDEFINED;
        outLen = 0;
        inLen = 0;
        memset(outBuffer, 0, maxDataLength);
        memset(inBuffer, 0, maxDataLength);
    }

    eCMD_LMS cmd;
    eCMD_STATUS status;
    unsigned char outBuffer[maxDataLength];
    int outLen;
    unsigned char inBuffer[maxDataLength];
    int inLen;
};

unsigned char* PreparePacket(const GenericPacket &pkt, int &length, const eLMS_PROTOCOL protocol, ConnectionManager* pSerPort = NULL);
int ParsePacket(GenericPacket &pkt, const unsigned char* buffer, const int length, const eLMS_PROTOCOL protocol);

#endif // LMS_PROTOCOLS_H

