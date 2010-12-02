#include "xEngine.h"

xException::xException(const xString& source, const xString& description, const char* file, long line)
	: mSource(source), mDescription(description), mFile(file), mLine(line)
{
}

xException::xException()
{
}

xString xException::Type() const
{
	return xString("xException");
}

const xString& xException::Message() const
{
	PrepareMessage();	
	return mFullDescription;
}

const char* xException::what() const throw()
{
	PrepareMessage();
	return mFullDescription.c_str();
}

void xException::PrepareMessage() const
{
	if (mFullDescription == "")
	{
		try
		{			
			if (mDescription != "")
				mFullDescription += xString::Format("\"%s\" ", mDescription.c_str());
			mFullDescription += Type();
			if (mSource != "")
				mFullDescription += xString::Format(" %s in %s at %s(line %d)", mSource.c_str(), mFile.c_str(), mLine);
		}
		catch(...)
		{
			mFullDescription = "Unknown Exception";
		}
	}
}

xIMPLEMENT_EXCEPTION(xFileNotFoundException, xException)
xIMPLEMENT_EXCEPTION(xInvalidOperationException, xException)