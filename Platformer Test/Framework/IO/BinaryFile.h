#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include "BaseFile.h"

#include <fstream>

class BinaryFile : public BaseFile
{
public:

	BinaryFile(std::string filename = "", int mode = IOMode::IO_In, bool overwrite = false);
	~BinaryFile();

	bool Open(std::string filename, int mode, bool overwrite);
	void Close();
	bool IsOpen();

	template <class T>
	T Read();
	template <class T>
	void Write(T data);
};




//	Read and Write	//

template <class T>
void BinaryFile::Write( T data )	//	generic funtion for writing T into the stream, can be overwritten for non-standard data types
{
	if ( GetMode() != BinaryFile::IOMode::IO_Out )
		SetMode( BinaryFile::IOMode::IO_Out );

	_Stream.write( (char*)&data , sizeof( data ) );
};

template <class T>	
T BinaryFile::Read()	//	generic function for reading T from the stream, can be overwritten for non-standard data types
{
	if ( GetMode() != BinaryFile::IOMode::IO_In )
		SetMode( BinaryFile::IOMode::IO_In );

	T Data;
	_Stream.read( (char*)&Data , sizeof( Data ) );
	
	return Data;
};

//std::string
template <>
void BinaryFile::Write<std::string>(std::string s);
template <>
std::string BinaryFile::Read<std::string>();

//bool
template <>
void BinaryFile::Write<bool>(bool b);
template <>
bool BinaryFile::Read<bool>();

#endif