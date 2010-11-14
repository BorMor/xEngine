#include "Prerequisites.h"

xTEST(TypeTraits)
{
	xCHECK(xIsIntegral<int>::Value == true);
	xCHECK(xIsIntegral<float>::Value == false);
	xCHECK(xIsFloatingPoint<int>::Value == false);
	xCHECK(xIsFloatingPoint<float>::Value == true);

	xCHECK(xIsPointer<float>::Value == false);
	xCHECK(xIsPointer<float*>::Value == true);
	xCHECK(xIsPointer<float**>::Value == true);

	xCHECK(xIsFundamental<char>::Value == true);
	xCHECK(xIsFundamental<xString>::Value == false);
}