#include "LinearGradient.h"

// LinearGradient::LinearGradient()
// {
//     // rapidxml::xml_node<> *stopNode = constructorData->first_node("stop");
//     // while (stopNode != nullptr)
//     // {
//     //     stops.push_back(new Stop(stopNode));
//     //     stopNode = stopNode->next_sibling("stop");
//     // }
// }

LinearGradient::LinearGradient(rapidxml::xml_node<> *constructorData) : DefsTag(constructorData)
{
    if (constructorData == nullptr)
    {
        return;
    }
    rapidxml::xml_node<> *stopNode = constructorData->first_node("stop");
    while (stopNode != nullptr)
    {
        cout << "=======push stop" << endl;
        stops.push_back(new Stop(stopNode));
        cout << "=======push stop done" << endl;
        stopNode = stopNode->next_sibling("stop");
    }
}

// DefsTag *LinearGradient::clone()
// {
//     return new LinearGradient();
// }

DefsTag *LinearGradient::clone(rapidxml::xml_node<> *constructorData)
{
    return new LinearGradient(constructorData);
}

std::string LinearGradient::toString()
{
    // print all stops
    std::string result = "LinearGradient\n";
    for (auto &stop : stops)
    {
        stop->printOffSet();
    }
    return result;
}

std::vector<Stop *> LinearGradient::getStops()
{
    return stops;
}

LinearGradient::~LinearGradient()
{
    
}