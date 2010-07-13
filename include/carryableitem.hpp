#ifndef __CARRYABLEITEM_H
#define __CARRYABLEITEM_H

#include "item.hpp"
#include <string>

namespace fur {
class CarryAbleItem : public Item
{
    public:
        CarryAbleItem();
        virtual ~CarryAbleItem();
        std::string getName();
    protected:
    private:
        float weight;
        std::string name;
};
}
#endif // __CARRYABLEITEM_H
