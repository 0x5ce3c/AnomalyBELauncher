#pragma once

class CFile
{
public:
	CFile(const std::string& Path, bool bRead = true);
	~CFile();
	
	void	Close();
	bool	Exists();
	bool	Remove();
	int		GetLinesNum();
	
	std::vector<std::string> GetLines();

	void WriteContent(std::string Input);
	void WriteLines(std::vector<std::string> Input);

private:
	std::string m_path;
	std::ifstream m_read;
	std::ofstream m_write;

	std::vector<std::string> m_lines;

	bool m_Exists;
	bool m_Read;
};
