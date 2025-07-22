#include "main.h"

CFile::CFile(const std::string& Path, bool bRead): m_Read(bRead)
{
	m_path.assign(Path);
	if (m_Read)
	{
		m_read.open(m_path.c_str());
		m_Exists = m_read.is_open();

		if (m_Exists)
		{
			std::string line;
			while (std::getline(m_read, line))
			{
				m_lines.push_back(line);
			}
		}
	}
	else
	{
		m_write.open(m_path.c_str());
		m_Exists = m_write.good();
	}
}


CFile::~CFile()
{
	m_Read ? m_read.close() : m_write.close();
}

bool CFile::Exists()
{
	return m_Exists;
}

bool CFile::Remove()
{
	m_Read ? m_read.close() : m_write.close();
	return std::remove(m_path.c_str());
}

void CFile::Close()
{
	m_Read ? m_read.close() : m_write.close();
}

int CFile::GetLinesNum()
{
	return m_Read ? m_lines.size() : 0;
}

void CFile::WriteContent(std::string Input)
{
	if (!m_Read)
	{
		m_write << Input;
	}
}

void CFile::WriteLines(std::vector<std::string> Input)
{
	if (!m_Read)
	{
		for (std::string line : Input)
		{
			m_write << line;
		}
	}
}

std::vector<std::string> CFile::GetLines()
{
	return m_Read ? m_lines : (std::vector<std::string>)NULL;
}
