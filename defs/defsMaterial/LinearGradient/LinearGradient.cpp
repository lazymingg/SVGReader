#include "LinearGradient.h"

LinearGradient::LinearGradient(rapidxml::xml_node<> *constructorData) : DefsTag(constructorData)
{
    rapidxml::xml_node<> *stopNode = constructorData->first_node("stop");
    while (stopNode != nullptr)
    {
        stops.push_back(new Stop(stopNode));
        stopNode = stopNode->next_sibling("stop");
    }
}

DefsTag *LinearGradient::clone()
{
    return new LinearGradient();
}

DefsTag *LinearGradient::clone(rapidxml::xml_node<> *constructorData)
{
    return new LinearGradient(constructorData);
}

LinearGradient::~LinearGradient()
{
    
}
