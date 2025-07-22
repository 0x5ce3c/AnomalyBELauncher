#include "main.h"
#include "FileSystemManager.h"
FSManager* fsm;



void FSManager::FreeStringMemory(std::string& string)
{
	if (!string.empty())
		string.clear();
	if (string.empty())
		string.shrink_to_fit();
}

size_t FSManager::GetStringLenght(std::string& string)
{
	
	return string.length();
}

void FSManager::CreateThreadA(LPTHREAD_START_ROUTINE thread)
{

	DWORD threadID;
	HANDLE thread1 = CreateThread(NULL, NULL, thread, NULL, 0, &threadID);
	CloseHandle(thread1);
}


//D3DCOLOR FSManager::FLOAT4TOD3DCOLOR(float Col[])
//{
//	D3DCOLOR col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
//	float a = (col32_no_alpha >> 24) & 255;
//	float r = (col32_no_alpha >> 16) & 255;
//	float g = (col32_no_alpha >> 8) & 255;
//	float b = col32_no_alpha & 255;
//	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
//}

std::string FSManager::UTF8_to_CP1251(std::string const& utf8)
{
	if (!utf8.empty())
	{
		int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
		if (wchlen > 0 && wchlen != 0xFFFD)
		{
			std::vector<wchar_t> wbuf(wchlen);
			MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
			std::vector<char> buf(wchlen);
			WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);

			return std::string(&buf[0], wchlen);
		}
	}
	return std::string();
}

std::string FSManager::Ansii_to_UTF8(std::string const ansii)
{
	int size = MultiByteToWideChar(CP_ACP, 0/*MB_COMPOSITE*/, ansii.c_str(),
		ansii.length(), nullptr, 0);
	std::wstring utf16_str(size, '\0');
	MultiByteToWideChar(CP_ACP, 0/*MB_COMPOSITE*/, ansii.c_str(),
		ansii.length(), &utf16_str[0], size);

	int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
		utf16_str.length(), nullptr, 0,
		nullptr, nullptr);

	std::string utf8_str(utf8_size, '\0');
	WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
		utf16_str.length(), &utf8_str[0], utf8_size,
		nullptr, nullptr);

	return utf8_str;
}

//std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
#if _MSC_VER >= 1900
std::string FSManager::utf16_to_utf8(std::u16string utf16_string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t*>(utf16_string.data());
	return convert.to_bytes(p, p + utf16_string.size());
}
#else
std::string FSManager::utf16_to_utf8(std::u16string utf16_string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.to_bytes(utf16_string);
}
#endif

std::vector<std::string> FSManager::get_filenames(std::filesystem::path path)
{
	namespace stdfs = std::filesystem;

	std::vector<std::string> filenames;

	// http://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
	const stdfs::directory_iterator end{};

	for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
	{
		// http://en.cppreference.com/w/cpp/experimental/fs/is_regular_file 
		if (stdfs::is_regular_file(*iter)) // comment out if all names (names of directories tc.) are required
			filenames.push_back(iter->path().string());
	}

	return filenames;
}

BOOL FSManager::DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributesA(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void FSManager::CreatefolderRecursive(std::string path)
{
	signed int pos = 0;
	do
	{
		pos = path.find_first_of("\\/", pos + 1);
		CreateDirectoryA(path.substr(0, pos).c_str(), NULL);
	} while (pos != std::string::npos);
}

void FSManager::CreateFolder(const char* szFolderName)
{

	if (!std::filesystem::exists(szFolderName))
	{
		//cheat_state_text("Folder %s not found, creating folder %s", szFolderName, szFolderName);
		std::filesystem::create_directory(szFolderName);
	}
}

void FSManager::DeleteEmptyFolder(const char* szPath)
{
	RemoveDirectoryA(szPath);
}

// Функция для рекурсивного удаления файлов и папок
void FSManager::DeleteFolderWithFiles(const char* szPath) {
	std::filesystem::remove_all(szPath);
}

bool FSManager::FolderExist(const char* szFolderName)
{
	

	DWORD attribs = ::GetFileAttributesA(szFolderName);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	else return true;
}

const char* FSManager::GetPCUserNameF(void)
{
	

	static char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserNameA(username, &username_len);

	return username;
}

const char* FSManager::GetComputerNameF(void)
{
	

	static char cname[256];
	DWORD nameccc = UNLEN + 1;
	GetComputerNameA(cname, &nameccc);
	return cname;
}

const char* FSManager::GetNumberOfProcessorsF(void)
{
	

	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return this->SetText("%d", info.dwNumberOfProcessors);
}

bool FSManager::AreNumbersIdentical(const char* text_to_scan, const char* text_for_scan)
{
	int result = strspn(text_to_scan, text_for_scan);
	if (result > 0)
		return true;
	else return false;
	//if (g_SAMP && result > 0)
		////addMessageToChatWindow("Defined text has %d identical numbers", result);
}

//https://stackoverflow.com/users/87234/gmannickg
bool FSManager::IsFileEmpty(std::fstream& szFile)
{
	return szFile.peek() == std::ifstream::traits_type::eof();
}

void FSManager::IntDuplicate(int& dup_target, int duplicate_size)
{

	dup_target *= duplicate_size;
}

int FSManager::GetFilesCount(const char* szFolder)
{

	int files = 0;
	for (const auto& rfiles : std::filesystem::directory_iterator(szFolder))
		files++;

	return files;
}

int FSManager::GetFileItemsCount(const char* szFile)
{

	int file_iC = 0;
	std::fstream file;
	file.open(szFile, std::fstream::in);
	if (file.is_open())
	{
		for (std::string lines; std::getline(file, lines);)
		{
			if (!lines.empty())
				file_iC++;
		}
		file.close();
	}
	return file_iC;
}


void FSManager::FileDelete(const char* szFile)
{
	
	remove(szFile);
}

void FSManager::AddText_to_Text(const char* szDefineText, char szTextoAdd)
{
	

	std::string str = szDefineText;
	str.back() = szTextoAdd;
}

bool FSManager::TextInFileExists(const char* file_path, const char* szTextToCheck)
{
	std::fstream file;
	file.open(file_path, std::fstream::in);

	if (file.is_open())
	{
		std::string file_lines;
		std::getline(file, file_lines);
		if (!file_lines.empty())
		{
			if (this->IsTextIdentical(file_lines.c_str(), szTextToCheck))
				return true;
		}
		file.close();
	}
	return false;
}

bool FSManager::IsTextIdentical(const char* str1, const char* str2)
{
	if (strcmp(str1, str2) == 0)
		return true;

	return false;
}

const char* FSManager::SetText(const char* szText, ...)
{
	va_list ap;

	static char tmp[512];
	memset(tmp, 0, sizeof(tmp));

	va_start(ap, szText);
	vsnprintf(tmp, sizeof(tmp), szText, ap);
	va_end(ap);

	return tmp;
}

void FSManager::WriteToFile(const char* filename, const char* szText)
{
	std::fstream file;
	file.open(filename, std::fstream::out | std::fstream::app);
	if (file.is_open())
	{
		file << szText << std::endl;
		ZeroMemory(&szText, sizeof(szText));
		file.close();
	}
}

const char* FSManager::ReadFromFile(const char* szFile)
{
	std::string text;
	std::string npos;
	std::string out;
	std::fstream file(szFile);	
	if (!file.is_open()) file.open(szFile, std::fstream::in);
	if (file.is_open())
	{		
		while (std::getline(file, text))
		{						
			npos += text;
			npos.push_back('\n');				
			if (!file.eof()) continue;	
		}			
		//Log("%s", npos.c_str());
		out = npos;
		return out.c_str();				
		file.close();
	}

	return "N/A";
}

const char* FSManager::ReplaceText(const char* szText, const char* szTextToDelete)
{
	std::string text = szText;

	text.replace(text.find(szTextToDelete), strlen(szTextToDelete), "").c_str();
	return text.c_str();
}

const char* FSManager::ModifyText(const char* szText, const char* szTextToDelete, const char* szNewText)
{
	return std::string(szText).replace(std::string(szText).find(szTextToDelete), strlen(szTextToDelete), szNewText).c_str();
}

void FSManager::ImSpacing(int spaces)
{
	for (int spc = 0; spc < spaces; spc++)
		ImGui::Spacing();
}

void FSManager::ImAllingItem(float fpos)
{
	ImGui::Text("");
	ImGui::SameLine(fpos);
}



bool FSManager::FileExists(const char* fname)
{
	return access(fname, 0) != -1;
}

bool FSManager::DoesFileExist(const char* szFile, const char* szFileExt, const char* szPath)
{
	

	std::string	srcFile;
	srcFile += szPath;
	srcFile += szFile;
	srcFile += szFileExt;

	if (std::filesystem::exists(srcFile.c_str()))
		return true;
	else
		return false;
}

bool FSManager::FileExist(const char* fname) {
	

	/*std::string path;
	path = MOD_FOLDER_MP3;
	path += szFile;*/

	if (std::filesystem::exists(fname)) return true;
	 
	return false;
}

const char* FSManager::AddText(const char* toAdd, const char* location)
{
	

	return std::string(location).insert(0, toAdd).c_str();
}

std::string FSManager::ReplaceAllcharactersInString(std::string str, const std::string& from, const std::string& to) 
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void FSManager::ClearFile(const char* filename, const char* szMsg)
{
	

	std::fstream file; file.open(filename, std::fstream::out);
	if (file.is_open()) { file.clear(); file.close(); }

	//if (g_SAMP && g_Chat && strlen(szMsg))
		////addMessageToChatWindow(szMsg);
}



static float fCol;
static bool start = false;
static DWORD tick = 0;
ImVec4 FSManager::ColorOpacityPulse(ImVec4 ImColorID, float OpacityPower, float OpacityMax, float OpacityMin, int TimePulse)
{
	if (GetTickCount() - tick > TimePulse)
	{
		if (!start && fCol <= OpacityMin)
			start = true;
		else if (start && fCol >= OpacityMax)
			start = false;

		if (start)
			fCol += OpacityPower;
		else
			fCol -= OpacityPower;
		tick = GetTickCount();

	}
	return ImVec4(ImColorID.x, ImColorID.y, ImColorID.z, fCol);
}

ImColor FSManager::TotalRainbow(int speed)
{
	ImColor color; float misc; static float rainbow;
	rainbow += misc = 0.0001f * (int)speed;
	if (rainbow > 1.f)  rainbow = 0.0f;
	color = Color2::ToImColor(Color2::FromHSB(rainbow, 0.5f, 1.0f));
	return color;
}

//D3DCOLOR FSManager::CustomImVec4_D3DCOLOR(ImVec4 color) //use in ImGui::ColorEdit's
//{
//	return D3DCOLOR_RGBA((int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), (int)(color.w * 255));
//}


int FSManager::GetDirFileCount(const char* szDir)
{
	

	int count = 0;
	for (const auto& entry : std::filesystem::directory_iterator(szDir))
		count++;

	return count;
}

//By ThreadShakur
char* FSManager::BinToHex(BYTE* bin, size_t size, char* out)
{
	if (bin == nullptr || size == 0 || out == nullptr)
		return "";
	out[0] = '\0';

	char	b[4];
	for (size_t i = 0; i < size; i++)
	{
		_snprintf_s(b, sizeof(b) - 1, "%02X", bin[i]);
		strcat(out, b);
	}
	return out;
}

const char* FSManager::GetSystemUpTime(void)
{
	DWORD ticks = GetTickCount();
	//DWORD milliseconds = ticks % 1000;
	ticks /= 1000;
	static DWORD seconds = ticks % 60;
	ticks /= 60;
	static DWORD minutes = ticks % 60;
	ticks /= 60;
	static DWORD hours = ticks; // may exceed 24 hours.

	return this->SetText("%02d:%02d:%02d", hours, minutes, seconds - 2);
}


std::string FSManager::GetCurrentTimeA(void)
{
	SYSTEMTIME timeA;
	GetLocalTime(&timeA);
	return std::string(this->SetText("%02d:%02d:%02d", timeA.wHour, timeA.wMinute, timeA.wSecond));
}

std::string FSManager::GetCurrentDateA(void)
{
	SYSTEMTIME dateA;
	GetLocalTime(&dateA);
	return std::string(this->SetText("%02d.%02d.%02d", dateA.wDay, dateA.wMonth, dateA.wYear));
}

const char* FSManager::getTimeCounter(void)
{
	// hours, minutes, seconds of timer 
	static int hours = 0;
	static int minutes = 0;
	static int seconds = 0;
	static int ms = 0;

	static DWORD tickg = 0;
	DWORD tock = GetTickCount();

	if (tock - tickg >= 1000)
	{
		tickg = tock;
		ms += 1000;
	}

	if (ms == 1000)
	{
		ms = 0;
		seconds += 1;
	}
	// if seconds reaches 60 
	if (seconds == 60) {

		// increment minutes 
		minutes++;

		// if minutes reaches 60 
		if (minutes == 60) {

			// increment hours 
			hours++;
			minutes = 0;
		}
		seconds = 0;
	}

	std::string h, m, s;
	if (hours >= 10)
	{
		h.replace(0, strlen(h.c_str()), this->SetText("%s:", std::to_string(hours).c_str()));
	}
	else if (hours >= 0)
	{
		h.append(this->SetText("0%s:", std::to_string(hours).c_str()));
	}

	if (minutes >= 10)
	{
		m.replace(0, strlen(m.c_str()), this->SetText("%s:", std::to_string(minutes).c_str()));
	}
	else if (minutes >= 0)
	{
		m.append(this->SetText("0%s:", std::to_string(minutes).c_str()));
	}

	if (seconds >= 10)
	{
		s.replace(0, strlen(s.c_str()), std::to_string(seconds).c_str());
	}
	else if (seconds >= 0)
	{
		s.append(this->SetText("0%s", std::to_string(seconds).c_str()));
	}

	return this->SetText("%s%s%s", h.c_str(), m.c_str(), s.c_str());
}

static uint32_t protect(void* dest, size_t len, uint32_t protection)
{
	uint32_t old_protection;
	if (!VirtualProtectEx(GetCurrentProcess(), dest, len, protection, (PDWORD)&old_protection))
		return 0;
	return old_protection;
};

void* FSManager::MemoryRead(void* dest, const void* src, size_t len)
{
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	size_t psz = sinfo.dwPageSize;

	void* _src = const_cast<void*>(src);
	uint8_t* src_ptr = static_cast<uint8_t*>(_src);
	uint8_t* dst_ptr = static_cast<uint8_t*>(dest);
	size_t	read_len = 0, all_size = len;

	uint32_t prot = protect(_src, all_size, PAGE_EXECUTE_READWRITE);
	while ((src_ptr += read_len) && (dst_ptr += read_len) && (len -= read_len))
	{
		size_t pg_offs = (size_t)((uintptr_t)src_ptr % psz);
		size_t pg_remn = psz - pg_offs;
		read_len = len > pg_remn ? pg_remn : len;
		std::copy(src_ptr, src_ptr + read_len, dst_ptr);
	}
	protect(_src, all_size, prot);
	return dest;
};

void* FSManager::MemoryWrite(void* dest, const void* src, size_t len)
{
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	size_t psz = sinfo.dwPageSize;

	void* _src = const_cast<void*>(src);
	uint8_t* src_ptr = static_cast<uint8_t*>(_src);
	uint8_t* dst_ptr = static_cast<uint8_t*>(dest);
	size_t	read_len = 0, all_size = len;

	uint32_t prot = protect(dest, all_size, PAGE_EXECUTE_READWRITE);
	while ((src_ptr += read_len) && (dst_ptr += read_len) && (len -= read_len))
	{
		size_t pg_offs = (size_t)((uintptr_t)dst_ptr % psz);
		size_t pg_remn = psz - pg_offs;
		read_len = len > pg_remn ? pg_remn : len;
		std::copy(src_ptr, src_ptr + read_len, dst_ptr);
	}
	protect(dest, all_size, prot);
	return dest;
};

int FSManager::MemoryCompare(const void* orig, const void* comp, size_t len)
{
	int		retvalue = 1;
	void* _org = const_cast<void*>(orig);
	void* _cmp = const_cast<void*>(comp);
	uint8_t* org = static_cast<uint8_t*>(_org);
	uint8_t* cmp = static_cast<uint8_t*>(_cmp);

	size_t	nlen = len > 4096 ? 4096 : len;
	void* temp = malloc(nlen);
	memcpy(temp, org, nlen);

	for (size_t sz = len; sz; sz -= nlen, org += nlen, cmp += nlen)
	{
		nlen = sz > 4096 ? 4096 : sz;
		this->MemoryRead(temp, org, nlen);
		retvalue = memcmp(temp, comp, nlen);
	}
	free(temp);

	return retvalue;
};
void* FSManager::MemoryCopy(void* dest, const void* src, size_t len, bool cmp, const void* cmpdata)
{
	if (cmp && cmpdata != nullptr) {
		if (this->MemoryCompare(dest, cmpdata, len)) {
			return nullptr;
		}
	}
	void* _src = const_cast<void*>(src);
	uint8_t* sptr = static_cast<uint8_t*>(_src);
	uint8_t* dptr = static_cast<uint8_t*>(dest);
	size_t	nlen = len > 4096 ? 4096 : len;
	void* temp = malloc(nlen);

	for (size_t sz = len; sz; sz -= nlen,
		sptr += nlen, dptr += nlen)
	{
		nlen = sz > 4096 ? 4096 : sz;
		this->MemoryRead(temp, sptr, nlen);
		this->MemoryWrite(dptr, temp, nlen);
	}
	free(temp);

	return dest;
}

void FSManager::RenameFile(char const* OldFileName, char const* NewFileName)
{
	rename(OldFileName, NewFileName);
};


void FSManager::MoveTo(const char* filename, const char* directory)
{			
	string file = GetExePath() + "\\" + filename;
	string to = GetExePath() + "\\" + directory + "\\" + filename;
	string dir = GetExePath() + "\\" + directory;
	if(FileExist(file.c_str()) == true)
	{		
		if (!DirectoryExists(dir.c_str()))
		{
			CreatefolderRecursive(dir);
			sleep(60);
			MoveFileExA(file.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING);
		}
		if (DirectoryExists(dir.c_str()))
		{
			MoveFileExA(file.c_str(), to.c_str(), MOVEFILE_REPLACE_EXISTING);
		}
	}	
};