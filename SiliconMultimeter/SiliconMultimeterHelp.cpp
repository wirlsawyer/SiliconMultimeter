#include "StdAfx.h"
#include "SiliconMultimeterHelp.h"
#include "RS232c.h"
#include "Setupapi.h"
#include <string>
#include <iostream>
#pragma comment(lib, "Setupapi.lib")

RS232c *g_rs232 = NULL;
SiliconMultimeterHelp* SiliconMultimeterHelp::m_instance = NULL;
//=================================================================================================================================
SiliconMultimeterHelp* SiliconMultimeterHelp::Instance()
{
	if (m_instance == NULL){
		m_instance = new SiliconMultimeterHelp(); 
	}
	return m_instance;
}

SiliconMultimeterHelp::SiliconMultimeterHelp(void)
{
	g_rs232 = NULL;
}

SiliconMultimeterHelp::~SiliconMultimeterHelp(void)
{
	delete g_rs232;
}

char*SiliconMultimeterHelp::FindDevInMgrCom(GUID GUID_STR, LPWSTR lpszHWId)
{
	wchar_t wszHWId[256];
	wcscpy_s(wszHWId, lpszHWId);
	_wcslwr_s(wszHWId);


	BYTE DevHWID[512];
	memset(DevHWID, 0, 512);
	HDEVINFO hInfo = SetupDiGetClassDevsW(&GUID_STR,NULL,NULL,DIGCF_PRESENT);

	SP_DEVINFO_DATA data;
	data.cbSize = sizeof(SP_DEVINFO_DATA);

	int ItemCount = 0;
	BOOL ret=false,bEndFlag = false;
	while(!bEndFlag)
	{
		ret = SetupDiEnumDeviceInfo(hInfo,ItemCount,&data);
		if(!ret)
		{
			DWORD err = GetLastError();
			if(err != ERROR_NO_MORE_ITEMS)
				::MessageBoxW(NULL, L"Enumerate the USB device Fail !!", L"Message",MB_OK);

			bEndFlag = true;
			break;
		}		

		wchar_t ItemString[512];
		memset(ItemString, 0, 512*2);
		SetupDiGetDeviceRegistryPropertyW(hInfo,&data,SPDRP_HARDWAREID,NULL,DevHWID,512,NULL);
		swprintf_s(ItemString,L"%s",DevHWID);
		_wcslwr_s(ItemString);

		//OutputDebugStringW(ItemString);
		//OutputDebugStringW(L"\n");


		//if(wcscmp(ItemString, wszHWId)==0)
		//	return true;

		wchar_t *pdest = NULL;
		pdest = wcsstr( ItemString, wszHWId);
		if( pdest != NULL )
		{

			BYTE friendlyName[512];

			if(SetupDiGetDeviceRegistryPropertyA(hInfo, &data, SPDRP_FRIENDLYNAME, NULL, friendlyName, 512, NULL))
			{
				char szbuf[512];
				sprintf_s(szbuf,"%s",friendlyName);
				//_wcsupr_s(szbuf);

				OutputDebugStringA(szbuf);
				OutputDebugStringW(L"\n");


				std::string str = szbuf;

				std::size_t found1 = str.find("(");
				std::size_t found2 = str.find(")");
				if (found1 != std::string::npos && found2 != std::string::npos)
				{
					str = str.substr (found1+1, found2-found1-1);

					memset(szbuf, 0, sizeof(szbuf));
					sprintf(szbuf, "%s", str.c_str());
					return szbuf;
				}
			}

			return NULL;
		}

		ItemCount++;
	}
	return NULL;
}

bool SiliconMultimeterHelp::ConnectComPort(char *ComName)
{
	if (g_rs232) delete g_rs232;
	g_rs232 = new RS232c();

	return g_rs232->Connect(ComName, 9600);
}

bool SiliconMultimeterHelp::ConnetComAuto()
{
	DWORD requiredSize;
	// Get Class GUID for PORTS class
	GUID classGuid[1];
	if ( ! SetupDiClassGuidsFromName( _T("PORTS"), classGuid, 1, &requiredSize ) )
		return false;

	char *ComName = SiliconMultimeterHelp::Instance()->FindDevInMgrCom(classGuid[0], L"USB\\VID_10C4&PID_EA60&REV_0100");
	if ( ComName == NULL)
	{
		return false;
	}

	return ConnectComPort(ComName);
}

bool SiliconMultimeterHelp::sendCommand(char *cmd)
{
	if (g_rs232 == NULL) return false;

	if (g_rs232->isLink())
	{                 
		if (g_rs232->Send(cmd))
		{
			//OutputDebugString(L"Send CMD success\n");
		}
		else
		{
			OutputDebugString(L"Send CMD fault\n");
			return false;
		}
	}
	return true;
}



char *SiliconMultimeterHelp::SetContinueDump()
{
	memset(m_szBuf, 0, sizeof(m_szBuf));
	char cmd[2];
	cmd[0] = '\x3F';
	cmd[1] = '\0';
	bool bResult = sendCommand(cmd);

	if (bResult)
	{		
		g_rs232->Read(m_szBuf, sizeof(m_szBuf));
		return m_szBuf;
	}

	return NULL;
}

bool SiliconMultimeterHelp::SetStopDump()
{
	char cmd[2];
	cmd[0] = '\x2F';
	cmd[1] = '\0';
	return sendCommand(cmd);
}

char *SiliconMultimeterHelp::SetOneTimeDump()
{
	memset(m_szBuf, 0, sizeof(m_szBuf));
	bool bResult = sendCommand(" ");
	
	if (bResult)
	{		
		g_rs232->Read(m_szBuf, 64);
		return m_szBuf;
	}
	
	return NULL;
}

bool SiliconMultimeterHelp::SetManualMode()
{
	return sendCommand("R");
}

bool SiliconMultimeterHelp::SetAutoMode()
{
	return sendCommand("A");
}

bool SiliconMultimeterHelp::SetLockValue()
{
	return sendCommand("H");
}

bool SiliconMultimeterHelp::SetUnLockValue()
{
	return sendCommand("D");
}

bool SiliconMultimeterHelp::SetZeroTest()
{
	return sendCommand("Z");
}

bool SiliconMultimeterHelp::SetExitZeroTest()
{
	return sendCommand("O");
}

bool SiliconMultimeterHelp::SetStartREC()
{
	return sendCommand("M");
}

bool SiliconMultimeterHelp::SetStopREC()
{
	return sendCommand("L");
}

bool SiliconMultimeterHelp::SetSHIFTFunc()
{
	return sendCommand("F");
}

bool SiliconMultimeterHelp::SetHZFunc()
{
	return sendCommand("P");
}

bool SiliconMultimeterHelp::SetClearMemory()
{
	char cmd[2];
	cmd[0] = '\x03';
	cmd[1] = '\0';
	return sendCommand(cmd);
}

char *SiliconMultimeterHelp::SetDownload()
{	 
	memset(m_szBuf, 0, sizeof(m_szBuf));
	char cmd[2];
	cmd[0] = '\x04';
	cmd[1] = '\0';
	bool bResult = sendCommand(cmd);

	if (bResult)
	{		
		g_rs232->Read(m_szBuf, sizeof(m_szBuf));
		return m_szBuf;
	}

	return NULL;

}
