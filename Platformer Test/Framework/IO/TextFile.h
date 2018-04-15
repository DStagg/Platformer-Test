#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include "BaseFile.h"

class TextFile : public BaseFile
{
public:

	TextFile(std::string filename = "", int mode = IOMode::IO_In, bool over = false);
	~TextFile();

	bool Open(std::string filename, int mode, bool overwrite);
	void Close();
	bool IsOpen();

	std::string Read();
	void Write(std::string line);
};

#endif