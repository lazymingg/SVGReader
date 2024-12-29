#include "Id.h"

Id::Id()
{
    id = "";
}

Id::Id(std::string value)
{
    id = value;
}

std::string Id::getId()
{
    return id;
}

Attribute *Id::clone()
{
    return new Id(*this);
}

void Id::mergeData(Attribute *attribute)
{
    //nothing to do
}

Id::~Id()
{
    //nothing
}

Attribute *Id::clone(std::string value)
{
    return new Id(value);
}
