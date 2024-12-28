#include "Defs.h"



Defs * Defs::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Defs();
    }
    return instance;
}