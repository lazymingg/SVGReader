#include "Defs.h"



Defs * Defs::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Defs();
    }
    return instance;
}

void Defs::read()
{
}

void Defs::print()
{
}
