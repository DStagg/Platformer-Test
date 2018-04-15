#include "BinaryFile.h"

BinaryFile::BinaryFile(std::string filename, int mode, bool overwrite)
{
	if (filename != "")
		Open(filename, mode, overwrite);
};

BinaryFile::~BinaryFile()
{
	if (IsOpen())
		Close();
};

bool BinaryFile::Open(std::string filename, int mode, bool overwrite)
{
	if (filename == "")
		return false;

	if (IsOpen())
		Close();

	SetFilename(filename);
	SetMode(mode);
	SetOverwrite(overwrite);

	if (GetMode() == BinaryFile::IOMode::IO_In)
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::in);									//	In
	else if (GetOverwrite())
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::out | std::ios::trunc);				//	Out, Append
	else
		_Stream.open(GetFilename().c_str(), std::ios::binary | std::ios::out | std::ios::app | std::ios::ate);	//	Out, Overwrite

	return IsOpen();
};

void BinaryFile::Close()
{
	_Stream.close();
};

bool BinaryFile::IsOpen()
{
	return _Stream.is_open();
};

//	Explicit implementations	//

//std::string
template <>
void BinaryFile::Write<std::string>(std::string s)
{
	Write<int>(s.size());
	for (int i = 0; i < (int)s.length(); i++)
		Write<char>(s[i]);
};
template <>
std::string BinaryFile::Read<std::string>()
{
	int Size = Read<int>();
	std::string Temp = "";

	for (int i = 0; i < Size; i++)
		Temp += Read<char>();

	return Temp;
};

//bool

template<>
void BinaryFile::Write<bool>(bool b)
{
	if (b)
		Write<char>('1');
	else
		Write<char>('0');
};
template<>
bool BinaryFile::Read<bool>()
{
	return (Read<char>() == '1');
};