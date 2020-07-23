// iobuffer.cpp
#include "iobuffer.h"
#include <cstring>

IOBuffer::IOBuffer (int maxBytes)
// construct with a maximum of maxFields
{
	Init (maxBytes);
}

int IOBuffer::Init (int maxBytes)
{
	Initialized = FALSE;
	if (maxBytes < 0) maxBytes = 0;
	MaxBytes = maxBytes;
	Buffer = new char[MaxBytes];
	BufferSize = 0;
	Clear ();
	return 1;
}

int IOBuffer::Read (istream & stream)
{
	if (stream.eof()) return -1;
	int recaddr = stream.tellg ();
	Clear();
	unsigned short bufferSize;
	stream.read ((char *)&bufferSize, sizeof(bufferSize));
	memset(Buffer, 0, MaxBytes);
	if ( !stream.good() ) {stream.clear(); return -1;}
	BufferSize = bufferSize;
	if (BufferSize > MaxBytes) return -1; // buffer overflow
	stream.read (Buffer, BufferSize);
	if ( !stream.good() ) {stream.clear(); return -1;}
	return recaddr;
}


// write the length and buffer into the stream
int IOBuffer::Write(ostream & stream)
{
	int recaddr = stream.tellp();
	unsigned short bufferSize = BufferSize;
	stream.write((char *)&bufferSize, sizeof(bufferSize));
	if ( !stream ) return -1;
	stream.write(Buffer, BufferSize);
	if ( !stream.good() ) return -1;
	return recaddr;
}
// set the value of the next field of the buffer;
// if size = -1 (default) use strlen(field) as Delim of field
// return number of bytes packed, -1 if error
int IOBuffer :: Pack (const void * field, int size)
{
	// look for delimeter in field!
	short len; // length of string to be packed
	if (size >= 0) len = size;
	else len = strlen ((char*)field);
	if (len > (short)strlen((char*)field)) // field is too short!
		return -1;
	int start = NextByte; // first character to be packed
	NextByte += len + 1;
	if (NextByte > MaxBytes) return -1;
	memcpy (&Buffer[start], field, len);
	Buffer [start+len] = Delim; // add delimeter
	BufferSize = NextByte;
	return len;
}

// extract the value of the next field of the buffer
// return the number of bytes extracted, -1 if error
int IOBuffer :: Unpack (void * field, int maxBytes)
{
	int len = -1; // length of packed string
	int start = NextByte; // first character to be unpacked
	for (int i = start; i < BufferSize; i++) {
		if (Buffer[i] == Delim) 
			{len = i - start; break;}
			
	}
		
	if (len == -1) return -1; // delimeter not found
	NextByte += len + 1;
	if (NextByte > BufferSize) return -1;
	// check for maxBytes
	memcpy (field, &Buffer[start], len);
	if (maxBytes > len || maxBytes == -1)
		((char*)field) [len] = 0; // zero termination for string 
	return len;
}


int IOBuffer::DRead(istream & stream, int recref)
// read specified record
{
	stream.seekg(recref, ios::beg);
	if (stream.tellg() != recref) return -1;
	return Read (stream);
}

int IOBuffer::DWrite (ostream & stream, int recref) 
// write specified record
{
	stream.seekp(recref, ios::beg);
	if (stream.tellp() != recref) return -1;
	return Write (stream);
}

static const char * headerStr = "201624548_Leejaeyun";
static const int headerSize = strlen (headerStr);

int IOBuffer::ReadHeader(istream & stream) 
{
	char str[headerSize+1];
	stream.seekg(0, ios::beg);
	stream.read(str, headerSize);
	if (!stream. good() ) return -1;
	if (strncmp(str, headerStr, headerSize)==0) return headerSize;
	else return -1;
}

int IOBuffer::WriteHeader(ostream & stream) const
{
	stream.seekp(0, ios::beg);
	stream.write(headerStr, headerSize);
	if (! stream.good() ) return -1;
	return headerSize;
}

void IOBuffer::Clear ()
// clear field values from buffer
{
	NextByte = 0;
	Packing = TRUE;
}

void IOBuffer::Print (ostream & stream) const
{
	stream<<"MaxBytes "<<MaxBytes<<" BufferSize "<<BufferSize;
}


