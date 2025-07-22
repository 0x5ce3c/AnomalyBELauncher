#pragma once

class FSManager
{
public:

	void FreeStringMemory(std::string& string);
	size_t GetStringLenght(std::string& string);

	int getMiddleYWindowSize(void);
	int getMiddleXWindowSize(void);

	//D3DCOLOR FLOAT4TOD3DCOLOR(float Col[]);
	std::string UTF8_to_CP1251(std::string const& utf8); 
	std::string Ansii_to_UTF8(std::string const ansii); 
	std::string utf16_to_utf8(std::u16string utf16_string); 
	std::vector<std::string> get_filenames(std::filesystem::path path);
	char* BinToHex(BYTE* bin, size_t size, char* out);
	const char* GetSystemUpTime(void); //Task Manager -> Up Time

	void ImSpacing(int spaces);
	void ImAllingItem(float fpos);	
	bool FileExists(const char* fname);
	bool FileExist(const char* fname);
	bool DoesFileExist(const char* szFile, const char* szFileExt, const char* szPath); //for .txt, .ini, text files mostly
	bool AreNumbersIdentical(const char* text_to_scan, const char* text_for_scan);
	bool IsFileEmpty(std::fstream& szFile);
	int GetDirFileCount(const char* szDir = 0); // = 0 empty
	void CreateFolder(const char* szFolderName);
	BOOL DirectoryExists(LPCTSTR szPath);
	void CreatefolderRecursive(std::string path);
	void DeleteEmptyFolder(const char* szPath);
	void DeleteFolderWithFiles(const char* szPath);
	void RenameFile(char const* OldFileName, char const* NewFileName);
	void MoveTo(const char* filename, const char* directory);
	bool FolderExist(const char* szFolderName);
	const char* ReplaceText(const char* szText, const char* szTextToDelete);
	const char* ModifyText(const char* szText, const char* szTextToDelete, const char* szNewText);
	const char* AddText(const char* toAdd, const char* location);
	std::string ReplaceAllcharactersInString(std::string str, const std::string& from, const std::string& to);
	bool MP3FileExist(const char* szFile, bool bIncludePath = true); //only for music, szfile pass parameters path+file_name+file_extension(.mp3, .wav(supported bass ext. in this case))
	void FileDelete(const char* szFile);
	void AddText_to_Text(const char* szDefineText, char szTextoAdd); //adds szTextoAdd to the latest character of szDefineText
	bool TextInFileExists(const char* file_path, const char* szTextToCheck);
	bool IsTextIdentical(const char* str1, const char* str2);
	const char* SetText(const char* szText, ...);	
	void WriteToFile(const char* filename = "", const char* szText = "");
	const char* ReadFromFile(const char* szFile);
	void ClearFile(const char* filename, const char* szMsg = "");
	ImVec4 ColorOpacityPulse(ImVec4 ImColorID, float OpacityPower = 0.050f, float OpacityMax = 1.000f, float OpacityMin = 0.050f, int TimePulse = 80);
	ImColor TotalRainbow(int speed);
	
	//D3DCOLOR CustomImVec4_D3DCOLOR(ImVec4 color);

	void IntDuplicate(int& dup_target, int duplicate_size = 2);
	int GetFilesCount(const char* szFolder);
	int GetFileItemsCount(const char* szFile);	
	
	std::string GetCurrentTimeA(void);
	std::string GetCurrentDateA(void);
	const char* getTimeCounter(void);
	
	const char* GetPCUserNameF(void);
	const char* GetComputerNameF(void);
	const char* GetNumberOfProcessorsF(void);
	
	void CreateThreadA(LPTHREAD_START_ROUTINE thread);
	//Memory stuff
	void* MemoryRead(void* dest, const void* src, size_t len);
	void* MemoryWrite(void* dest, const void* src, size_t len);
	int MemoryCompare(const void* orig, const void* comp, size_t len);
	void* MemoryCopy(void* dest, const void* src, size_t len, bool cmp = false, const void* cmpdata = nullptr);

private:
};
extern FSManager* fsm;