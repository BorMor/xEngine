#include "Prerequisites.h"

class A
{
public:
	void Method(int& value)
	{
		value += 10;
	}
};

class B
{
public:
	void Method(int& value)
	{	
		value += 1;
	}
};

class C : public A, public B
{
};

void Func(int& value)
{
	value += 100;
}

xTEST(Event)
{
	int value = 0;
	C instance;

	typedef xEvent< void(int&) > Event;

	Event event;
	

	xCHECK(value == 0)
	event += new Event::Handler(Func);
	event(value);
	xCHECK(value == 100)
	event += new Event::Handler(&instance, &A::Method);
	event += new Event::Handler(&instance, &B::Method);
	event(value);
	xCHECK(value == 211)

	event -= new Event::Handler(&instance, &B::Method);
	event(value);
	xCHECK(value == 321)
	//@todo: automatic disconnect
}