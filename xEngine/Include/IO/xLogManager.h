#pragma once

class xEXPORT xLogManager
{
public:
	class Listener
	{
	public:
		Listener();
		virtual ~Listener();

		virtual void Write(const xString& string) = 0;
	};
	xLogManager();
	~xLogManager();

	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);

	void Write(const xString& string);
protected:
	typedef xList<Listener*> ListenerList;

	ListenerList	mListeners;
};

xEXPORT
xLogManager& operator << (xLogManager& log, const xString& string);

extern xEXPORT xLogManager xLog;
extern xEXPORT xString xEndl;