#include "xEngine.h"

xLogFileWriter::xLogFileWriter(const xString& path)
{
	mStream = new xFileStream(path, xAccessMode::Write);
}

xLogFileWriter::~xLogFileWriter()
{
	delete mStream;
}

void xLogFileWriter::Write(const xString& string)
{
	mStream->Write((void*)string.Data(), string.Length());
}