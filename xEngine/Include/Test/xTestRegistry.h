#pragma once

class xEXPORT xTestRegistry
{
	typedef xList<xTest*> TestList;
private:
    xTestRegistry();
public:
    static xTestRegistry& Instance();
    
    void Add(xTest* test);
    void Run(xTestListener* listener);        
protected:
    TestList mTests;
};