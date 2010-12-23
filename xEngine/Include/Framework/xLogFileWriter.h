#pragma once

class xLogFileWriter : public xLogManager::Listener
{
public:
	xLogFileWriter(const xString& path);
	~xLogFileWriter();

	void Write(const xString& string);
protected:
	xFileStream*	mStream;
};