#include "main.h"


SystemInfo::SystemInfo() : updateInterval(1000) { // ���������� �������� �� ��������� � 1000 ��
    CollectCPUInfo();        
    CollectInternetStatus();
    lastUpdate = std::chrono::steady_clock::now();
}

std::string SystemInfo::GetCPUInfo() {
    return u8"{FFFF00}CPU info: " + cpuInfo;
}
static bool check_disk = false;

void SystemInfo::GetDiskInfo() {
    /*if(!check_disk)
    {*/
        int k = 0;
        int sz = GetLogicalDriveStrings(NULL, 0);
        TCHAR* szLogicalDrives = new TCHAR[sz];
        GetLogicalDriveStrings(sz, szLogicalDrives);
        while (*szLogicalDrives)
        {
            TCHAR szDisk[80];
            lstrcpy(szDisk, szLogicalDrives);
            UINT uDriveType = GetDriveType(szDisk);
            if (uDriveType == DRIVE_FIXED) // ������� ����
            {
                k = k + 1; // ������� ���-�� ������� ������
                //sn->con.AddLog(szDisk); // ���������� ��������
                __int64 Free, Total;
                Free = 0;
                Total = 0;
                GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free); // ���������� �����    
                unsigned int  s_total = Total / (1024 * 1024 * 1024);
                unsigned int  s_free = Free / (1024 * 1024 * 1024);
                unsigned int  s_used = (Total - Free) / (1024 * 1024 * 1024);
                char c[0x1000] = {0};
                
                //sn->con.AddLog("%s ����� ����� : %u ��, �������� : %u ��, ������ : %u ��", szDisk, s_total, s_free, s_used);
                //sn->con.AddLog("�������� : %i ��", );
                //sn->con.AddLog("������ : %i ��", );
                sprintf(c, u8"%s ����� ����� : %u ��, �������� : %u ��, ������ : %u ��", szDisk, s_total, s_free, s_used);
                std::string diskinfo = c;
                //ImFuncs::GlitchText(diskinfo.c_str());
                //ImFuncs::GlitchText2(diskinfo.c_str());
                //ImFuncs::GlitchText3(diskinfo.c_str());
                ImGui::TextWithColors(diskinfo.c_str());
            }
            while (*szLogicalDrives) szLogicalDrives++;
            szLogicalDrives++;
            //sn->con.AddLog("���-�� ������: %i \t", k);
        }
        //check_disk = 1;        
    //}
    //return "{FFFF00}Drives: " + diskinfo;
}

std::string SystemInfo::GetInternetStatus() {
    return u8"{FFFF00}Network Status: " + internetStatus + " ";
}

void SystemInfo::UpdateInfo() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

    if (duration >= updateInterval) {
        CollectCPUInfo();        
        CollectInternetStatus();
        lastUpdate = now; // �������� ����� ���������� ����������
    }
}

void SystemInfo::SetUpdateInterval(int interval) {
    updateInterval = interval;
}

void SystemInfo::CollectCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);

    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        char cpuName[256];
        DWORD cpuNameSize = sizeof(cpuName);
        RegQueryValueExA(hKey, "ProcessorNameString", nullptr, nullptr, (LPBYTE)cpuName, &cpuNameSize);
        RegCloseKey(hKey);
        cpuInfo = "P Type: " + std::string(cpuName) + " ";
    }
    DWORD cores = 32;
    cpuInfo += "N Cores: " + std::to_string(sysInfo.dwNumberOfProcessors/*cores*/) + " ";
}

void SystemInfo::CollectInternetStatus() {
    if (InternetCheckConnection("http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0)) {
        internetStatus = "{00FF00}Connected";
    }
    else {
        internetStatus = "{FF0000}Not Connected";
    }
}



SystemInfo* sysi = new SystemInfo();


string BSTRToString(VARIANT vtProp) {
    // ���������, ��� vtProp �������� ������
    if (vtProp.vt == VT_BSTR) {
        // �������� ����� ������ � ��������
        int len = SysStringLen(vtProp.bstrVal);

        // �������� ������ ��� ������������� ������
        int bufferSize = WideCharToMultiByte(CP_UTF8, 0, vtProp.bstrVal, len, NULL, 0, NULL, NULL);
        char* buffer = new char[bufferSize + 1]; // +1 ��� ����-�����������

        // ����������� BSTR � ������������� ������
        WideCharToMultiByte(CP_UTF8, 0, vtProp.bstrVal, len, buffer, bufferSize, NULL, NULL);
        buffer[bufferSize] = '\0'; // ��������� ����-����������

        // ������� std::string �� ������
        string result(buffer);

        // ����������� ���������� ������
        delete[] buffer;

        return result; // ���������� ��������������� ������
    }
    else {
        throw invalid_argument("Provided VARIANT does not contain a BSTR.");
    }
}

static bool sysinfo_init = true;
        
void sysinfotoconsole() 
{
    if (sysinfo_init)
    {
        sn->con.AddLog("���������� � ������ : ");
        int k = 0;
        int sz = GetLogicalDriveStrings(NULL, 0);
        TCHAR* szLogicalDrives = new TCHAR[sz];
        GetLogicalDriveStrings(sz, szLogicalDrives);
        while (*szLogicalDrives)
        {
            TCHAR szDisk[80];
            lstrcpy(szDisk, szLogicalDrives);
            UINT uDriveType = GetDriveType(szDisk);
            if (uDriveType == DRIVE_FIXED) // ������� ����
            {
                k = k + 1; // ������� ���-�� ������� ������
                //sn->con.AddLog(szDisk); // ���������� ��������
                __int64 Free, Total;
                Free = 0;
                Total = 0;
                GetDiskFreeSpaceEx(szDisk, NULL, (PULARGE_INTEGER)&Total, (PULARGE_INTEGER)&Free); // ���������� �����    
                unsigned int  s_total = Total / (1024 * 1024 * 1024);
                unsigned int  s_free = Free / (1024 * 1024 * 1024);
                unsigned int  s_used = (Total - Free) / (1024 * 1024 * 1024);
                sn->con.AddLog("%s ����� ����� : %u ��, �������� : %u ��, ������ : %u ��", szDisk, s_total, s_free, s_used);
                //sn->con.AddLog("�������� : %i ��", );
                //sn->con.AddLog("������ : %i ��", );
            }
            while (*szLogicalDrives) szLogicalDrives++;
            szLogicalDrives++;
        }
        sn->con.AddLog("���-�� ������: %i \t",k); // �������� �����    

        HRESULT hres;

        // ������������� COM
        hres = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hres))
        {
            /*cout << "Failed to initialize COM library. Error code = 0x"
                << hex << hres << endl;*/
            return; // ��������� ����������� � �������.
        }

        // ��������� ������� ������������ COM
        hres = CoInitializeSecurity(
            NULL,
            -1,                          // �������������� COM
            NULL,                        // ������ ��������������
            NULL,                        // ���������������
            RPC_C_AUTHN_LEVEL_DEFAULT,   // ������� �������������� �� ���������
            RPC_C_IMP_LEVEL_IMPERSONATE, // ������� ������������ �� ���������  
            NULL,                        // ���������� �� ��������������
            EOAC_NONE,                   // �������������� ����������� 
            NULL                         // ���������������
        );

        if (FAILED(hres))
        {
           /* cout << "Failed to initialize security. Error code = 0x"
                << hex << hres << endl;*/
            CoUninitialize();
            return; // ��������� ����������� � �������.
        }

        // ��������� ���������� �������� ��� WMI
        IWbemLocator* pLoc = NULL;
        hres = CoCreateInstance(
            CLSID_WbemLocator,
            0,
            CLSCTX_INPROC_SERVER,
            IID_IWbemLocator, (LPVOID*)&pLoc);

        if (FAILED(hres))
        {
           /* cout << "Failed to create IWbemLocator object."
                << " Err code = 0x"
                << hex << hres << endl;*/
            CoUninitialize();
            return; // ��������� ����������� � �������.
        }

        // ����������� � WMI ����� IWbemLocator::ConnectServer
        IWbemServices* pSvc = NULL;
        hres = pLoc->ConnectServer(
            _bstr_t(L"ROOT\\CIMV2"), // ���� � ������������ ���� WMI
            NULL,                    //
            // ��� ������������. NULL = ������� ������������
            NULL,                    // ������ ������������. NULL = �������
            0,                       // ������. NULL ��������� �� �������
            NULL,                    // ����� ������������.
            0,                       // ��������� (��������, Kerberos)
            0,                       // ����������� ������ 
            &pSvc                    // ��������� �� ������ IWbemServices
        );

        if (FAILED(hres))
        {
            /*cout << "Could not connect. Error code = 0x"
                << hex << hres << endl;*/
            pLoc->Release();
            CoUninitialize();
            return; // ��������� ����������� � �������.
        }

        sn->con.AddLog("����������� �������� ������ � ����������� ����������...");

        // ������ ���������� � ����������
        IEnumWbemClassObject* pEnumerator = NULL;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_Processor"),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pEnumerator);

        if (FAILED(hres))
        {
            /*cout << "Query for processor failed. Error code = 0x"
                << hex << hres << endl;*/
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return; // ��������� ����������� � �������.
        }

        // ��������� ������ � ����������
        IWbemClassObject* pclsObj;
        ULONG uReturn = 0;

        SYSTEM_INFO siSysInfo;
        GetSystemInfo(&siSysInfo);

        while (pEnumerator)
        {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
            if (0 == uReturn)
            {
                break;
            }


            VARIANT vtProp;
            // �������� �������� �������� Name
            sn->con.AddLog("���������� � ����������:");
            sn->con.AddLog("��� ���������� : %d", siSysInfo.dwProcessorType);

            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            sn->con.AddLog("��� ���������� : %s",BSTRToString(vtProp));

            hr = pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
            sn->con.AddLog("���������� ���������� ���� : %u",vtProp.uintVal);

            sn->con.AddLog("���-�� ���������� ���� : %d", siSysInfo.dwNumberOfProcessors);

            hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
            sn->con.AddLog("������������ �������� ������� : %u ���", vtProp.uintVal);

            //hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
            //sn->con.AddLog("������������� : %s", BSTRToString(vtProp));

            hr = pclsObj->Get(L"Architecture", 0, &vtProp, 0, 0);
            sn->con.AddLog("����������� : %u", vtProp.uintVal);

            pclsObj->Release();
        }

        // ������ ���������� � ������� ���������
        IEnumWbemClassObject* pEnumerator1 = NULL;
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_NetworkAdapter"),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pEnumerator1);

        if (FAILED(hres))
        {
            /*cout << "Query for network adapters failed. Error code = 0x"
                << hex << hres << endl;*/
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return; // ��������� ����������� � �������.
        }

        sn->con.AddLog("������� ��������:");

        while (pEnumerator1)
        {
            HRESULT hr = pEnumerator1->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
            if (0 == uReturn)
            {
                break;
            }

            VARIANT vtProp;
            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);            

            string NameAdapter = BSTRToString(vtProp);

            hr = pclsObj->Get(L"NetConnectionStatus", 0, &vtProp, 0, 0);
            if (vtProp.uintVal == 2)
            {                
                sn->con.AddLog("���: %s   ������: ���������", NameAdapter);
            }
            else
            {                                
                sn->con.AddLog("���: %s   ������: ��������", NameAdapter);
            }

            pclsObj->Release();
        }

        // ������������ ��������
        pSvc->Release();
        pLoc->Release();
        pEnumerator->Release();
        pEnumerator1->Release();
        CoUninitialize();

        // �������� ����������� � ���������
       /* BOOL bl = InternetCheckConnection("http://google.com/", 1, 0);
        if (bl == TRUE)
        {
            cout << "���������� � ���������" << endl;
        }
        else
        {
            cout << "��� ����������� � ���������" << endl;
        }*/
        sysinfo_init = 0;
    }
}

#include <atomic>

std::atomic<unsigned long long> fileCount(0);
std::atomic<unsigned long long> dirCount(0);
std::atomic<bool> running(true);
//#include <iostream>
//#include <windows.h>
//#include <string>

void CountFilesAndDirectories(const std::string& path) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    std::string searchPath = path + "\\*";

    hFind = FindFirstFile(searchPath.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return; // ���� �� ������� �������, �������
    }

    do {
        if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                dirCount++;
                CountFilesAndDirectories(path + "\\" + findFileData.cFileName);
            }
            else {
                fileCount++;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
}

void DisplayCounts() {
    while (running) {
        //system("cls"); // ������� �������
        sn->con.AddLog("Total files: %u", fileCount.load());
        sn->con.AddLog("Total directories: %u", dirCount.load());
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ���������� ������ �������
    }
}

void count_dirs_and_files() {
    // ������� ����, � �������� ������ ������ (��������, "C:\\")
    std::string startPath = "C:\\";
    auto thw = ThreadWrapper::create();
    
    // ��������� ����� ��� ����������� ���������
    //thw->beginThread(DisplayCounts);
    //sleep(60);
    // �������� ������� ������ � ����������
    thw->beginThreadex(CountFilesAndDirectories,startPath);

    // ��������� ����� �����������
    running = false;    

    sn->con.AddLog("Final count:");
    sn->con.AddLog("Total files: %u", fileCount.load());
    sn->con.AddLog("Total directories: %u", dirCount.load());
}
