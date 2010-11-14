#include "Prerequisites.h"

class SharedObject
{
public:
	SharedObject(int value = 0)
		: mValue(value)
	{

		mCount++;
	}

	~SharedObject()
	{
		mCount--;
	}

	int mValue;
	static int mCount;
};

int SharedObject::mCount = 0;

xTEST(SharedPtr)
{
	xCHECK(SharedObject::mCount == 0);
	{
		xSharedPtr<SharedObject> ptr(new SharedObject());
		xCHECK(SharedObject::mCount == 1);
		xCHECK(ptr == true);
		xCHECK(!ptr == false);
		xCHECK((*ptr).mCount == 1);
		xCHECK(ptr->mCount == 1);
	}
	xCHECK(SharedObject::mCount == 0);
	{
		xSharedPtr<SharedObject> ptr(new SharedObject());
		xCHECK(SharedObject::mCount == 1);		
		ptr.Reset();
		xCHECK(ptr.UseCount() == 0);
		xCHECK(SharedObject::mCount == 0);
	}
	xCHECK(SharedObject::mCount == 0);
	{
		xSharedPtr<SharedObject> ptr1(new SharedObject());
		xCHECK(ptr1.UseCount() == 1);
		xSharedPtr<SharedObject> ptr2(ptr1);
		xCHECK(SharedObject::mCount == 1);
		xCHECK(ptr1.UseCount() == 2);
		xCHECK(ptr2.UseCount() == 2);
		xSharedPtr<SharedObject> ptr3(ptr2);
		xCHECK(ptr1.UseCount() == 3);
		xCHECK(ptr2.UseCount() == 3);
		xCHECK(ptr3.UseCount() == 3);
	}
	xCHECK(SharedObject::mCount == 0);
	{
		xSharedPtr<SharedObject> ptr1(new SharedObject(1));
		xSharedPtr<SharedObject> ptr2(new SharedObject(2));
		xSharedPtr<SharedObject> ptr3(new SharedObject(3));
		xCHECK(SharedObject::mCount == 3);
		ptr2 = ptr3;
		xCHECK(SharedObject::mCount == 2);
		xCHECK(ptr1->mValue == 1);
		xCHECK(ptr2->mValue == 3);
		xCHECK(ptr3->mValue == 3);	
		xCHECK(ptr1.UseCount() == 1);
		xCHECK(ptr2.UseCount() == 2);
		xCHECK(ptr3.UseCount() == 2);
	}
	xCHECK(SharedObject::mCount == 0);
}