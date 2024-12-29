#ifndef _LINEAR_GRADIENT_H_
#define _LINEAR_GRADIENT_H_
#include "../DefsTag.h"
#include "Stop/Stop.h"
#include <vector>
class LinearGradient : public DefsTag
{
    private:
        std::vector<Stop*> stops;
    public:
        LinearGradient();
        LinearGradient(rapidxml::xml_node<> *constructorData);
        DefsTag* clone() override;
        DefsTag* clone(rapidxml::xml_node<> *constructorData) override;
        ~LinearGradient();
};

#endif