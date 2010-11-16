#include "xEngine.h"


xString xFile::ReadToString(const xString& path)
{
	xString result;

	xFileStream* stream = new xFileStream(path, xAccessMode::Read);	
	size_t size = stream->Size();
	result.Reserve(size+1);	
	stream->Read(result.Data(), size);
	result[size] = 0;
	delete stream;

	return result;
}