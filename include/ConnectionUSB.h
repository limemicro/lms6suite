/**
@file   ConnectionUSB.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for data writing and reading through USB port
*/

#ifndef USB_PORT_CONNECTION_H
#define USB_PORT_CONNECTION_H

#include "IConnection.h"
#include <string>
#include <vector>

#ifndef __unix__
#include "windows.h"
#include "CyAPI.h"
#else
#include <libusb-1.0/libusb.h>
#endif

#define USB_BUFFER_LENGTH = 64;
#define USB_MAX_CONTEXTS 64 //maximum number of contexts for asynchronous transfers

#include "lmSemaphore.h"

/** @brief Wrapper class for holding USB asynchronous transfers contexts
*/
class USBTransferContext
{
public:
	USBTransferContext() : used(false)
	{
		#ifndef __unix__
		inOvLap = new OVERLAPPED;
		memset(inOvLap, 0, sizeof(OVERLAPPED));
		inOvLap->hEvent = CreateEvent(NULL, false, false, NULL);
		context = NULL;
		#else
		transfer = libusb_alloc_transfer(0);
		bytesXfered = 0;
		bytesExpected = 0;
		done = 0;
		lmCreateSemaphore(m_lock, 1, 1);
		#endif
	}
	~USBTransferContext()
	{
		#ifndef __unix__
		CloseHandle(inOvLap->hEvent);
		delete inOvLap;
		#else
		libusb_free_transfer(transfer);
		lmDestroySemaphore(m_lock);
		#endif
	}
	bool reset()
	{
        if(used)
            return false;
        #ifndef __unix__
        CloseHandle(inOvLap->hEvent);
        memset(inOvLap, 0, sizeof(OVERLAPPED));
        inOvLap->hEvent = CreateEvent(NULL, false, false, NULL);
        #endif
        return true;
	}
	bool used;
	#ifndef __unix__
	PUCHAR context;
	OVERLAPPED *inOvLap;
	#else
	libusb_transfer* transfer;
	long bytesXfered;
	long bytesExpected;
	bool done;
	lmSemaphore m_lock;
	#endif
};

class ConnectionUSB : public IConnection
{
public:
	ConnectionUSB();
	~ConnectionUSB();

    void FindDevices();
	bool Open();
	bool Open(int index);
	void Close();
	bool IsOpen();

	int SendData(const unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 1000);
	int ReadData(unsigned char *buffer, unsigned long length, unsigned long timeout_ms = 1000);

	virtual int BeginDataReading(char *buffer, long length);
	virtual int WaitForReading(int contextHandle, unsigned int timeout_ms);
	virtual int FinishDataReading(char *buffer, long &length, int contextHandle);
	virtual void AbortReading();

	virtual int BeginDataSending(const char *buffer, long length);
	virtual int WaitForSending(int contextHandle, unsigned int timeout_ms);
	virtual int FinishDataSending(const char *buffer, long &length, int contextHandle);
	virtual void AbortSending();

	std::vector<std::string> GetDeviceNames() { return m_deviceNames; };
	void ClearComm();
	virtual eLMS_DEV ConnectedDeviceType();
private:
    std::string DeviceName();

    std::vector<std::string> m_deviceNames;
    int m_maxPacketSize;
    std::string m_hardwareName;
    int m_hardwareVer;

	USBTransferContext contexts[USB_MAX_CONTEXTS];
	USBTransferContext contextsToSend[USB_MAX_CONTEXTS];
	void Initialize();

	bool isConnected;
	int currentPortIndex;

	#ifndef __unix__
	CCyUSBDevice *USBDevicePrimary;
	//usb device for DigiRed transmitting
	CCyUSBDevice *USBDeviceSecondary;
	//control endpoints for DigiRed
	CCyControlEndPoint *InCtrlEndPt3;
	CCyControlEndPoint *OutCtrlEndPt3;

    //control endpoints for DigiGreen
	CCyUSBEndPoint *OutCtrEndPt;
	CCyUSBEndPoint *InCtrEndPt;

    //end points for samples reading and writing
	CCyUSBEndPoint *InEndPt;
	CCyUSBEndPoint *OutEndPt;

	#else
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx; //a libusb session
    std::vector<std::pair<int,int> > m_dev_pid_vid;
	#endif
};

#endif
