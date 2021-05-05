//Gabriel Goldstein
//gjg180000
#ifndef PLATINUMCUSTOMER_H
#define PLATINUMCUSTOMER_H
#include "Customer.h"

class PlatinumCustomer: public Customer
{
public:
    PlatinumCustomer();
    PlatinumCustomer(std::string, std::string, std::string, float, int);
    PlatinumCustomer(const PlatinumCustomer&);

    int getBonusBucks()
    {
        return bonusBucks;
    }
    void setBonusBucks(int bb)
    {
        bonusBucks = bb;
    }

protected:

private:
    int bonusBucks;
};

#endif // PLATINUMCUSTOMER_H
