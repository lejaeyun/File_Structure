//Recording.cpp
#include "recfile.h"
#include "Student.h"
#include "CourseRegistration.h"
template class RecordFile<Student>;
template class RecordFile<CourseRegistration>;

// template method bodies
template <class RecType>
int RecordFile<RecType>::Read(RecType & record, int recaddr)
{
	int readAddr, result;
	readAddr = BufferFile::Read (recaddr);
	if (readAddr==-1) return -1;
	result = record . Unpack (Buffer);
	if (!result) return -1;
	return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write(const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Write (recaddr);
}

template <class RecType>
int RecordFile<RecType>::Append(const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Append ();
}
