#pragma once

class SiliconMultimeterHelp
{
public:
	static SiliconMultimeterHelp *Instance(void);
	~SiliconMultimeterHelp(void);
	char *FindDevInMgrCom(GUID GUID_STR, LPWSTR lpszHWId);
	bool ConnectComPort(char *ComName);
	bool ConnetComAuto();

	char *SetContinueDump();
	bool SetStopDump();
	char *SetOneTimeDump();
	bool SetManualMode();	
	bool SetAutoMode();
	bool SetLockValue();
	bool SetUnLockValue();
	bool SetZeroTest();
	bool SetExitZeroTest();
	bool SetStartREC();
	bool SetStopREC();
	bool SetSHIFTFunc();
	bool SetHZFunc();
	bool SetClearMemory();
	char *SetDownload();
private:
	SiliconMultimeterHelp(void);
	bool sendCommand(char *cmd);
private:
	static SiliconMultimeterHelp	*m_instance;
	char m_szBuf[512];
};

