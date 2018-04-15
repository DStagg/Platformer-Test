#include "TextFile.h"

TextFile::TextFile(std::string filename, int mode, bool overwrite)
{
	if (filename != "")
		Open(filename, mode, overwrite);
};

TextFile::~TextFile()
{
	if (IsOpen())
		Close();
};

bool TextFile::Open(std::string filename, int mode, bool overwrite) 
{
	if (filename == "")
		return false;

	if (IsOpen())
		Close();

	if (filename.compare(filename.length() - 4, 4, ".txt") != 0)
		filename += ".txt";

	SetFilename(filename);
	SetMode(mode);
	SetOverwrite(overwrite);

	_Stream.open(filename, ((GetMode() == IOMode::IO_In) ? std::ios::in : std::ios::out) | (overwrite ? std::ios::trunc : std::ios::app | std::ios::ate));

	return IsOpen();
};

void TextFile::Close()
{
	_Stream.close();
};

bool TextFile::IsOpen()
{
	return _Stream.is_open();
};

std::string TextFile::Read()
{
	if (!IsOpen() || (GetMode() == IOMode::IO_Out))
		return "";
	std::string lineIn;
	std::getline(_Stream, lineIn);
	return lineIn;
};

void TextFile::Write(std::string line)
{
	if (!IsOpen() || (GetMode() == IOMode::IO_In))
		return;
	_Stream << line.c_str() << std::endl;
};
