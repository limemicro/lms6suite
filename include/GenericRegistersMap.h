/**
    @file   GenericRegistersMap.h
    @author Lime Microsystems (www.limemicro.com)
    @brief  Template class for managing registers map values
*/

#ifndef LMS_GENERIC_REGISTERS_MAP_H
#define LMS_GENERIC_REGISTERS_MAP_H

#include "ControlParameter.h"
#include "ConnectionManager.h"
#include <sstream>
#include <iostream>
#include "CommonUtilities.h"

/** @brief Template for defining registers map
    Takes enumeration type for control parameters and Word type for handled data type
    Other classed should inherit this class and define default register values
    initialization
*/
template<class ParamEnum, class WordType>
class GenericRegistersMap
{
public:
    struct Register
    {
        Register() : value(0), defaultValue(0), mask(~0x0) {};
        WordType address;
        WordType value;
        WordType defaultValue;
        WordType mask;
    };

    /** @brief Returns mask from msb to lsb bits
    */
    WordType makeMask(unsigned msb, unsigned lsb)
    {
        unsigned long mask = ~0; // fill with ones
        mask = mask << (msb-lsb+1);
        mask = ~mask;
        mask = mask << lsb;
        return mask;
    }

    GenericRegistersMap()
    {
        mDevice = NULL;
        mCmdRead = CMD_LMS7002_RD;
        mCmdWrite = CMD_LMS7002_WR;
    }

    GenericRegistersMap(ConnectionManager* serPort)
    {
        mDevice = serPort;
        mCmdRead = CMD_LMS7002_RD;
        mCmdWrite = CMD_LMS7002_WR;
    }
    void SetComms(ConnectionManager* serPort)
    {
        mDevice = serPort;
    }

    virtual ~GenericRegistersMap()
    {};

/** @brief Sets selected register value
    @param address register address
    @param value register's new value
    @return true is success
*/
    virtual bool SetRegisterValue(const WordType address, const WordType value, const bool toChip = true, const bool updateLocal = true)
    {
        bool status = true;
        if(mDevice)
            if(mDevice->IsOpen() && toChip)
            {
                GenericPacket pkt;
                pkt.cmd = mCmdWrite;
                memcpy(&pkt.outBuffer[0], &address, sizeof(WordType));
                memcpy(&pkt.outBuffer[0]+sizeof(WordType), &value, sizeof(WordType));
                pkt.outLen = 2*sizeof(WordType);
                if(mDevice->TransferPacket(pkt) != 1)
                    status = false;
            }
        if(updateLocal || !toChip)
            m_registers[address].value = value;
        return status;
    }

/** @brief Return register value of selected address
    @param address register address
    @param fromChip read directly from chip
    @param updateLocal update local registers map with read value
    @return register value
*/
	virtual WordType GetRegisterValue(const WordType address, const bool fromChip = false, const bool updateLocal = true)
	{
	    WordType resultValue = 0;
	    if(mDevice && fromChip)
            if(mDevice->IsOpen())
            {
                GenericPacket pkt;
                pkt.cmd = mCmdRead;
                memcpy(&pkt.outBuffer[0], &address, sizeof(WordType));
                pkt.outLen = sizeof(WordType);
                mDevice->TransferPacket(pkt);
                memcpy(&resultValue, (&pkt.inBuffer[0])+sizeof(WordType), sizeof(WordType));
                if(updateLocal)
                    m_registers[address].value = resultValue;
                return resultValue;
            }
        return m_registers[address].value;
	}

/** @brief Sets selected parameter to given value
    @param param Control parameter enum
    @param value parameter value
    @return true if success
*/
	virtual bool SetParameterValue(const ParamEnum param_id, const unsigned long value, const bool toChip=true, const bool updateLocal=true)
	{
	    bool status = true;
        ControlParameter param = mParameterList[param_id];
        unsigned long residueVal = value;
        WordType tempVal = 0;
        WordType tempAddr = 0;
        WordType tempMask = 0;
        //start changing from LSB
        for(int i=0; i<param.piecesCount; ++i)
        {
            tempAddr = param.registers[i].addr;
            tempVal = m_registers[tempAddr].value;
            tempMask = makeMask(param.registers[i].msb, param.registers[i].lsb);
            tempVal = tempVal & ~tempMask;
            tempVal |= (residueVal << param.registers[i].lsb) & tempMask;
            status &= SetRegisterValue(tempAddr, tempVal, toChip, updateLocal);
            residueVal = residueVal >> (param.registers[i].msb-param.registers[i].lsb+1);
        }
        return status;
	}

/** @brief Returns selected parameter value
    @param param Control parameter enum
    @param fromChip read directly from chip
    @param updateLocal update local copy of registers with read value
    @return parameter value
*/
	virtual unsigned long GetParameterValue(const ParamEnum param_id, const bool fromChip = false, bool updateLocal = true)
	{
        ControlParameter param = mParameterList[param_id];
        WordType tempVal = 0;
        WordType tempAddr = 0;
        WordType tempMask = 0;
        unsigned long value = 0;
        //start collecting from MSB
        for(int i=param.piecesCount-1; i>=0; --i)
        {
            tempAddr = param.registers[i].addr;
            if(fromChip)
                tempVal = GetRegisterValue(tempAddr, fromChip, updateLocal);
            else
                tempVal = m_registers[tempAddr].value;
            tempMask = makeMask(param.registers[i].msb, param.registers[i].lsb);
            tempVal = (tempVal & tempMask) >> param.registers[i].lsb;
            value = value << (param.registers[i].msb-param.registers[i].lsb+1);
            value |= tempVal;
        }
        return value;
	}

    /** @brief Returns parameter description by enumeration
        @param param Control parameter enum
    */
	const ControlParameter GetParameterInfo(const ParamEnum param)
	{
	    return mParameterList[param];
	}

    /** @brief Downloads all registers from connected device
        @return 1:success, 0:failure
    */
	bool DownloadAll()
	{
        vector<WordType> addrToRead;
        typename map<WordType, Register>::iterator registers;
        for(registers = m_registers.begin(); registers!=m_registers.end(); ++registers)
            addrToRead.push_back(registers->first);

        GenericPacket pkt;
        pkt.cmd = mCmdRead;
        pkt.outLen = addrToRead.size()*sizeof(WordType);
        memcpy(pkt.outBuffer, &addrToRead[0], pkt.outLen);

        if(mDevice)
            mDevice->TransferPacket(pkt);
        else
            return 0;
        WordType* inData = (WordType*)pkt.inBuffer;
        if(pkt.status == STATUS_COMPLETED_CMD)
        {
            for(unsigned i=0; i<addrToRead.size() && 2*i < pkt.inLen; ++i)
                m_registers[addrToRead[i]].value = inData[2*i+1];
            return 1;
        }
        else
            return 0;
	}

	/** @brief Uploads all registers to connected device
        @return 1:success, 0:failure
    */
	int UploadAll()
	{
        vector<WordType> DataToWrite;
        typename map<WordType, Register>::iterator registers;
        for(registers = m_registers.begin(); registers!=m_registers.end(); ++registers)
        {
            DataToWrite.push_back( registers->first );
            DataToWrite.push_back( registers->second.value );
        }
        GenericPacket pkt;
        pkt.cmd = mCmdWrite;
        pkt.outLen = DataToWrite.size()*sizeof(WordType);
        memcpy(pkt.outBuffer, &DataToWrite[0], pkt.outLen);

        if(mDevice)
            mDevice->TransferPacket(pkt);
        else
            return 0;
        if(pkt.status == STATUS_COMPLETED_CMD)
            return 1;
        else
            return 0;
	}

	/** @brief Initializes all registers default values and masks
	*/
	void InitializeDefaultValuesAndMasks()
	{
	    typename map<ParamEnum, ControlParameter>::iterator iter;
        for(iter=mParameterList.begin(); iter!=mParameterList.end(); ++iter)
            if(iter->second.readonly)
                SetParameterValue(iter->first, 0);
            else
                SetParameterValue(iter->first, 0xFFFFFFFF);

        typename map<WordType, Register>::iterator regIter;
        for(regIter = m_registers.begin(); regIter!=m_registers.end(); ++regIter)
            regIter->second.mask = regIter->second.value;

        for(iter=mParameterList.begin(); iter!=mParameterList.end(); ++iter)
            SetParameterValue(iter->first, iter->second.defaultValue);
        //setup default register values
        for(regIter = m_registers.begin(); regIter!=m_registers.end(); ++regIter)
            regIter->second.defaultValue = regIter->second.value;
	}
	/** @brief Returns current registers map state
	*/
    map<WordType, Register> GetRegisters() const
    {
        return m_registers;
    }

    /** @brief Returns given address register mask
        @param addr register's address
        @return register mask
    */
    WordType GetRegisterMask(WordType addr) const
    {
        typename std::map<WordType, Register>::const_iterator iter;
        iter = m_registers.find(addr);
        if(iter != m_registers.end())
            return iter->second.mask;
        else
            return ~0;
    }

    /** @brief Performs simple registers test, writes and reads values from device then compares values
        @return 1:success, 0:failed, -1:error writing, -2:error reading
    */
    int RegistersTest(WordType startAddr, WordType endAddr, bool onlyUsed, WordType pattern)
    {
        if(mDevice == NULL)
            return 0;
        int testResult=1;
        //find registers within range
        vector<WordType> usedRegs;
        if(onlyUsed)
        {
            typename std::map<WordType, Register>::iterator iter;
            for (iter = m_registers.begin(); iter != m_registers.end(); ++iter)
            {
                if(iter->first > endAddr)
                    break;
                if(iter->first >= startAddr)
                    usedRegs.push_back(iter->first);
            }
        }
        else
        {
            for(int i=startAddr; i<=endAddr; ++i)
                usedRegs.push_back(i);
        }
        //write data
        vector<WordType> writtenBuffer;
        for(unsigned int i=0; i<usedRegs.size(); ++i)
        {
            writtenBuffer.push_back(usedRegs[i]);
            writtenBuffer.push_back(pattern & GetRegisterMask(usedRegs[i]));
        }
        unsigned long bytesToSend, bytesToRead;
        bytesToSend = writtenBuffer.size()*sizeof(WordType);
        bytesToRead = bytesToSend;

        GenericPacket pkt;
        pkt.cmd = mCmdWrite;
        pkt.outLen = bytesToSend;
        memcpy(pkt.outBuffer, &writtenBuffer[0], pkt.outLen);

        mDevice->TransferPacket(pkt);
        if(pkt.status != STATUS_COMPLETED_CMD)
            return -1;

        vector<WordType> outBuffer;
        for(unsigned i=0; i<usedRegs.size(); ++i)
            outBuffer.push_back(usedRegs[i]);
        bytesToSend = outBuffer.size()*sizeof(WordType);
        bytesToRead = 2*bytesToSend;

        pkt.cmd = mCmdRead;
        pkt.outLen = bytesToSend;
        memcpy(pkt.outBuffer, &outBuffer[0], bytesToSend);
        mDevice->TransferPacket(pkt);
        if(pkt.status != STATUS_COMPLETED_CMD)
            return -2;

        WordType *inBuffer = new WordType[usedRegs.size()*2];
        memset(inBuffer, 0, usedRegs.size()*2*sizeof(WordType));
        memcpy(inBuffer, pkt.inBuffer, bytesToRead);
        //compare results
        stringstream ssr;
        ssr.clear();
        ssr.str( string() );
        for(unsigned int i=0; i<outBuffer.size(); ++i)
        {
            if( (inBuffer[1+i*2] & m_registers[usedRegs[i]].mask) != writtenBuffer[1+i*2])
            {
                ssr << "address 0x" << int2hex(outBuffer[i],sizeof(WordType)) << " (write/read) : " << int2hex(writtenBuffer[1+i*2], sizeof(WordType)) << "/" << int2hex(inBuffer[1+i*2], sizeof(WordType))<<endl;
                testResult = 0;
            }
        }

        if(testResult == 1)
        {
            ssr.clear();
            ssr.str( string() );
            ssr << "Registers OK : (write/read) : " << int2hex(pattern, sizeof(WordType)) << "/" << int2hex(pattern, sizeof(WordType)) << endl;
            cout << ssr.str() << endl;
            //m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
        }
        else
        {
            cout << ssr.str() << endl;
            //m_serPort->Notify(LMS_Message(MSG_REGISTER_TEST, ssr.str(), 0, 0));
        }
        cout << ssr.rdbuf();

        delete inBuffer;
        return testResult;
    }

    void SetControlParameters(map<ParamEnum, ControlParameter> controlParameters)
    {
        mParameterList = controlParameters;
    }
    eCMD_LMS mCmdRead;
    eCMD_LMS mCmdWrite;
protected:
    map<ParamEnum, ControlParameter> mParameterList;
    map<WordType, Register> m_registers;
    ConnectionManager* mDevice;
};

#endif // LMS_GENERIC_REGISTERS_MAP_H
