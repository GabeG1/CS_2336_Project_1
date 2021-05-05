//Gabriel Goldstein
//gjg180000
#include "Customer.h"
#include "PlatinumCustomer.h"

PlatinumCustomer::PlatinumCustomer()
{
    bonusBucks = 0;
}

PlatinumCustomer::PlatinumCustomer(std::string fn, std::string ln, std::string id, float as, int bb):Customer(fn, ln, id, as)
{


    bonusBucks = bb;
}
PlatinumCustomer::PlatinumCustomer(const PlatinumCustomer& PC2) : Customer::Customer(PC2)
{
    bonusBucks = PC2.bonusBucks;
}

