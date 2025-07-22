#pragma once



class SystemInfo
{
public:
    SystemInfo();
    std::string GetCPUInfo();        
    std::string GetInternetStatus();
    void UpdateInfo(); // Метод для обновления информации
    void SetUpdateInterval(int interval); // Установить интервал обновления

    void GetDiskInfo();

private:
    void CollectCPUInfo();        
    void CollectInternetStatus();

    std::string cpuInfo;        
    std::string internetStatus;
    int updateInterval; // Интервал обновления в миллисекундах
    std::chrono::steady_clock::time_point lastUpdate; // Время последнего обновления
};

extern SystemInfo* sysi;

void sysinfotoconsole();

void count_dirs_and_files();
