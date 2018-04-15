#ifndef BASE_FILE_H
#define BASE_FILE_H

#include <string>
#include <fstream>

//	Unfortunately C++ does not allow virtual templated member functions so we cannot define a virtual Read() or Write() here.

class BaseFile
{
public:
	
	bool Open()
	{
		return Open(GetFilename(), IOMode::IO_In, false);
	};
	virtual bool Open(std::string filename, int mode, bool overwrite) = 0;
	virtual void Close() = 0;
	virtual bool IsOpen() = 0;

	void SetFilename(std::string filename)
	{
		if (IsOpen())
		{
			Close();
			_Filename = filename;
			Open(GetFilename(), GetMode(), GetOverwrite());
		}
		else
			_Filename = filename;
	};
	std::string GetFilename()
	{
		return _Filename;
	};

	void SetMode(int mode)
	{
		if (IsOpen())
		{
			Close();
			_Mode = mode;
			Open(GetFilename(), GetMode(), GetOverwrite());
		}
		else
			_Mode = mode;
	};
	int GetMode()
	{
		return _Mode;
	};

	void SetOverwrite(bool over)
	{
		if (IsOpen())
		{
			Close();
			_Overwrite = over;
			Open(GetFilename(), GetMode(), GetOverwrite());
		}
		else
			_Overwrite = over;
	};
	bool GetOverwrite()
	{
		return _Overwrite;
	};

	enum IOMode
	{
		IO_In = 0,
		IO_Out
	};

protected:

	int _Mode = 0;
	bool _Overwrite = false;
	std::string _Filename = "";
	std::fstream _Stream;

private:



};

#endif