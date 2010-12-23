#include "xEngine.h"

xLogManager xLog;
xString xEndl("\r\n");

xLogManager::Listener::Listener()
{
}

xLogManager::Listener::~Listener()
{
}

xLogManager::xLogManager()
{
}

xLogManager::~xLogManager()
{
}

void xLogManager::AddListener(Listener* listener)
{
	mListeners.AddBack(listener);
}

void xLogManager::RemoveListener(Listener* listener)
{
	ListenerList::Iterator it = mListeners.Find(listener);
	if (it != mListeners.End())
		mListeners.Remove(it);
}

void xLogManager::Write(const xString& string)
{
	for (ListenerList::Iterator it = mListeners.Begin(); it != mListeners.End(); ++it)
		(*it)->Write(string);
}

xLogManager& operator << (xLogManager& log, const xString& string)
{
	log.Write(string);
	return log;
}