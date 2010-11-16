#pragma once

template <typename F>
class xEvent;

template <typename R>
class xEvent< R() >
{
public:
	typedef xDelegate<R()> Handler;

	void operator += (Handler* delegate)
	{
		mDelegates.AddBack(delegate);
	}

	void operator -= (Handler* delegate)
	{
		typename DelegateList::Iterator it = mDelegates.Begin();
		while (it != mDelegates.End())
		{
			typename DelegateList::Iterator t = it++;
			if (*(Handler*)*t == *delegate)
				mDelegates.Remove(t);
		}
	}

	void operator ()()
	{
		for (typename DelegateList::Iterator it = mDelegates.Begin(); it != mDelegates.End(); ++it)
			(*it)->operator()();
	}
protected:
	typedef xList< xSharedPtr<Handler> > DelegateList;
	DelegateList	mDelegates;
};

template <typename R, typename A1>
class xEvent< R(A1) >
{
public:
	typedef xDelegate<R(A1)> Handler;

	void operator += (Handler* delegate)
	{
		mDelegates.AddBack(delegate);
	}

	void operator -= (Handler* delegate)
	{
		typename DelegateList::Iterator it = mDelegates.Begin();
		while (it != mDelegates.End())
		{
			typename DelegateList::Iterator t = it++;
			if (*(Handler*)*t == *delegate)
				mDelegates.Remove(t);
		}
	}

	void operator ()(A1 a1)
	{
		for (typename DelegateList::Iterator it = mDelegates.Begin(); it != mDelegates.End(); ++it)
			(*it)->operator()(a1);
	}
protected:
	typedef xList< xSharedPtr<Handler> > DelegateList;
	DelegateList	mDelegates;
};

template <typename R, typename A1, typename A2>
class xEvent< R(A1, A2) >
{
public:
	typedef xDelegate<R(A1, A2)> Handler;

	void operator += (Handler* delegate)
	{
		mDelegates.AddBack(delegate);
	}

	void operator -= (Handler* delegate)
	{
		typename DelegateList::Iterator it = mDelegates.Begin();
		while (it != mDelegates.End())
		{
			typename DelegateList::Iterator t = it++;
			if (*(Handler*)*t == *delegate)
				mDelegates.Remove(t);
		}
	}

	void operator ()(A1 a1, A2 a2)
	{
		for (typename DelegateList::Iterator it = mDelegates.Begin(); it != mDelegates.End(); ++it)
			(*it)->operator()(a1, a2);
	}
protected:
	typedef xList< xSharedPtr<Handler> > DelegateList;
	DelegateList	mDelegates;
};

template <typename R, typename A1, typename A2, typename A3>
class xEvent< R(A1, A2, A3) >
{
public:
	typedef xDelegate<R(A1, A2, A3)> Handler;

	void operator += (Handler* delegate)
	{
		mDelegates.AddBack(delegate);
	}

	void operator -= (Handler* delegate)
	{
		typename DelegateList::Iterator it = mDelegates.Begin();
		while (it != mDelegates.End())
		{
			typename DelegateList::Iterator t = it++;
			if (*(Handler*)*t == *delegate)
				mDelegates.Remove(t);
		}
	}

	void operator ()(A1 a1, A2 a2, A3 a3)
	{
		for (typename DelegateList::Iterator it = mDelegates.Begin(); it != mDelegates.End(); ++it)
			(*it)->operator()(a1, a2, a3);
	}
protected:
	typedef xList< xSharedPtr<Handler> > DelegateList;
	DelegateList	mDelegates;
};
