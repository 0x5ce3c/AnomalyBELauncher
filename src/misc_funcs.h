#pragma once

/// Check Exist Anomaly
std::string GetAnomalybinFolder();
std::string GetAnomalydbFolder();
std::string GetAnomalygamedataFolder();
std::string GetAnomalyFolder();

/// Check MO2 if installed
std::string GetMO2Folder();

/// Check Blue Eclipse if installed
std::string GetBEFolder();

void funcs_enabler();

bool IsCheckAVXSupport();

void Createuserltxbtn();

void sleep(int ms);

void CheckUserltx();

void FindStringsForReplace();

//vector<string> paths;
//std::string path = GetExePath() + "\\appdata";
//GetAllFilesInDir(paths, path);
void GetListFiles(std::string path);


std::string getFileNameWithExtension(const std::string& s);
std::string getFileNameWithoutExtension(const std::string& s);