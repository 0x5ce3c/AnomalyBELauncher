#pragma once



class SystemInfo
{
public:
    SystemInfo();
    std::string GetCPUInfo();        
    std::string GetInternetStatus();
    void UpdateInfo(); // ����� ��� ���������� ����������
    void SetUpdateInterval(int interval); // ���������� �������� ����������

    void GetDiskInfo();

private:
    void CollectCPUInfo();        
    void CollectInternetStatus();

    std::string cpuInfo;        
    std::string internetStatus;
    int updateInterval; // �������� ���������� � �������������
    std::chrono::steady_clock::time_point lastUpdate; // ����� ���������� ����������
};

extern SystemInfo* sysi;

void sysinfotoconsole();

void count_dirs_and_files();
