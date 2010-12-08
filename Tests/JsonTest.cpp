#include "Prerequisites.h"

xTEST(Json)
{
	xJsonValue	root;
	xString test1 = xFile::ReadToString("Tests/test1.json");
	xCHECK(xJson::Parse(test1, root))
	xCHECK(root["link"].Type() == xJsonType::Null)
	xCHECK(root["flag"].Type() == xJsonType::Boolean)
	xCHECK(root["number"].AsInt32() == -2000)
	xCHECK(root["address"]["city"].AsString() == "Ленинград");
	xCHECK(root["phoneNumbers"][1].AsString() == "916 123-4567");
}