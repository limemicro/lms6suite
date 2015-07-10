/**
@file   ParameterDescription.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for defining control parameters
*/

#ifndef LMS_CONTROL_PARAMETER_DESCRIPTION_H
#define LMS_CONTROL_PARAMETER_DESCRIPTION_H

#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
class ControlParameter
{
public:
    struct RegPiece
    {
        unsigned int addr;
        unsigned int msb;
        unsigned int lsb;
    };

	ControlParameter()
	{
	    multipleChannels = false;
	    registers = NULL;
	    name = "Unnamed";
	    bitsCount = 0;
	    piecesCount = 0;
	    defaultValue = 0;
	    registers = NULL;
	    readonly = false;
	}
	ControlParameter(unsigned long addr, unsigned msb, unsigned lsb, unsigned long defVal, const char* nameID, const bool multiChannel = false)
	{
	    multipleChannels = multiChannel;
	    name = nameID;
	    bitsCount = msb-lsb+1;
	    if(msb > 15)
            printf("reg  outbound %s\n", nameID);
	    piecesCount = 1;
	    registers = new RegPiece[1];
        registers[0].addr = addr;
        registers[0].msb = msb;
        registers[0].lsb = lsb;
        defaultValue = defVal;
        readonly = false;
	}
	ControlParameter(const RegPiece *LSB, unsigned pCount, unsigned long defVal, const char* nameID, const bool multiChannel = false)
	{
	    multipleChannels = multiChannel;
	    defaultValue = defVal;
	    registers = NULL;
	    name = nameID;
	    bitsCount = 0;
	    piecesCount = pCount;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            for(int i=0; i<piecesCount; ++i)
            {
                registers[i] = LSB[i];
                bitsCount += LSB[i].msb-LSB[i].lsb+1;
            }
            //memcpy(registers, pieces, piecesCount*sizeof(RegPiece));
        }
        readonly = false;
	}
	ControlParameter(const ControlParameter &p2)
	{
	    defaultValue = p2.defaultValue;
	    registers = NULL;
	    name = p2.name;
	    bitsCount = p2.bitsCount;
	    piecesCount = p2.piecesCount;
	    readonly = p2.readonly;
	    multipleChannels = p2.multipleChannels;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            //memcpy(registers, p2.registers, p2.piecesCount*sizeof(RegPiece));
            for(int i=0; i<piecesCount; ++i)
                registers[i] = p2.registers[i];
        }
	}

	ControlParameter &operator=(const ControlParameter &p2)
	{
	    defaultValue = p2.defaultValue;
	    registers = NULL;
	    name = p2.name;
	    bitsCount = p2.bitsCount;
	    piecesCount = p2.piecesCount;
	    readonly = p2.readonly;
	    multipleChannels = p2.multipleChannels;
	    if(piecesCount > 0)
        {
            registers = new RegPiece[piecesCount];
            //memcpy(registers, p2.registers, p2.piecesCount*sizeof(RegPiece));
            for(int i=0; i<piecesCount; ++i)
                registers[i] = p2.registers[i];
        }
        return *this;
	}

	~ControlParameter()
	{
	    if(registers)
            delete []registers;
	}

    string name;
	unsigned char bitsCount;
	unsigned char piecesCount;
	unsigned long defaultValue;
	RegPiece *registers; //first index lsb, further msb
	bool multipleChannels;
	bool readonly;
};
#endif // LMS_CONTROL_PARAMETER_DESCRIPTION_H

