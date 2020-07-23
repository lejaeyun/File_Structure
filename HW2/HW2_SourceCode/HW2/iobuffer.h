#ifndef IOBUFFER_H
#define IOBUFFER_H

#include <cstdlib>
#include <iostream>

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

using namespace std;

class IOBuffer
{
public:
    IOBuffer(int MaxBytes =1000);
    virtual void Clear(); // clear fields from buffer
    int Init(int MaxBytes);

    int Read(istream &); //read?a?buffer
    int Write(ostream &); //write?a?buffer

    int Pack(const void* field, int size=-1);
    int Unpack(void* field, int maxbytes = -1);

	// these are the direct access read and write operations
	int DRead(istream &, int recref); // read specified record
	int DWrite(ostream &, int recref); // write specified record

	// these header operations return the number of bytes in the header
	int ReadHeader(istream &); // write a buffer to the stream
	int WriteHeader(ostream &) const; // write a buffer to the stream    

    void Print(ostream &) const;
    
protected:
    int Initialized; // TRUE if buffer is initialized
    char *Buffer; //character?array?to?hold?field?values
    int BufferSize; //?sum?of?the?sizes?of?packed?fields
    int MaxBytes; //max?#?of?char?in?the?buffer
    int NextByte; // index of next byte to be packed/unpacked
    int Packing;  // TRUE if in packing mode, FALSE, if unpacking
    char Delim = '|';
};

#endif


