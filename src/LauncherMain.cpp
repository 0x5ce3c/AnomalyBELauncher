#include "main.h"

stsn * sn = 0;
stsn   sn_obj;

void sn_Thread()
{		

	while (true)
	{		
		//std::this_thread::yield();
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));		
			//sn->sn_log.AddLog("thread id: %i");		
		
	}	

}

bool createlauncherfolder = true;

void sn_init()
{				
	try
	{
		sn = new stsn();// &sn_obj;
		memset(sn, 0, sizeof(stsn*));
		registerAllCommands();						
	}
	catch (const std::exception& e) { Log("[ sn_init(); ] Error: %s !", e.what()); }
}

void ExtractRes(WORD wResId, LPCSTR ResType,LPSTR lpszOutputPath) {
	HRSRC hrsrc = FindResourceA(NULL, MAKEINTRESOURCE(wResId), ResType);
	HGLOBAL hLoaded = LoadResource(NULL, hrsrc);
	LPVOID lpLock = LockResource(hLoaded);
	DWORD dwSize = SizeofResource(NULL, hrsrc);
	HANDLE hFile = CreateFile(lpszOutputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByteWritten;
	WriteFile(hFile, lpLock, dwSize, &dwByteWritten, NULL);
	CloseHandle(hFile);
	FreeResource(hLoaded);
}

std::vector<std::string> GetFileList(const char* dir, const char* pattern) {
	std::vector<std::string> fileList;
	HANDLE hFind;
	WIN32_FIND_DATAA findData;

	char findStr[MAX_PATH];
	snprintf(findStr, MAX_PATH, "%s\\%s", dir, pattern);

	hFind = FindFirstFileA(findStr, &findData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!strcmp(findData.cFileName, ".") || !strcmp(findData.cFileName, "..")) continue;
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

			fileList.emplace_back(findData.cFileName);

		} while (FindNextFileA(hFind, &findData));
		FindClose(hFind);
	}
	return fileList;
}

std::vector<std::string> GetAllDirsList(const char* dir, const char* pattern) {
	std::vector<std::string> fileList;
	HANDLE hFind;
	WIN32_FIND_DATAA findData;

	char findStr[MAX_PATH];
	snprintf(findStr, MAX_PATH, "%s\\%s", dir, pattern);

	hFind = FindFirstFileA(findStr, &findData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!strcmp(findData.cFileName, ".") || !strcmp(findData.cFileName, "..")) continue;
			/*if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{	continue;	}*/

			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				fileList.emplace_back(findData.cFileName);
			}//continue;			
		} while (FindNextFileA(hFind, &findData));
		FindClose(hFind);
	}
	return fileList;
}

BOOL IsAppRunningAsAdminMode()
{
	BOOL fIsRunAsAdmin = FALSE;
	DWORD dwError = ERROR_SUCCESS;
	PSID pAdministratorsGroup = NULL;

	// Allocate and initialize a SID of the administrators group.

	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (!AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pAdministratorsGroup))
	{
		dwError = GetLastError();
		goto Cleanup;
	}

	// Determine whether the SID of administrators group is enabled in 

	// the primary access token of the process.

	if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
	{
		dwError = GetLastError();
		goto Cleanup;
	}

Cleanup:
	// Centralized cleanup for all allocated resources.

	if (pAdministratorsGroup)
	{
		FreeSid(pAdministratorsGroup);
		pAdministratorsGroup = NULL;
	}

	// Throw the error if something failed in the function.

	if (ERROR_SUCCESS != dwError)
	{
		throw dwError;
	}

	return fIsRunAsAdmin;
}