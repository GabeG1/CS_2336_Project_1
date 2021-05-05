//Gabriel Goldstein
//gjg180000
#ifndef GOLDCUSTOMER_H
#define GOLDCUSTOMER_H
#include "Customer.h"

class GoldCustomer: public Customer
{
public:
    GoldCustomer();
    GoldCustomer(std::string, std::string, std::string, float, float);

    //Copy Constructor
    GoldCustomer(const GoldCustomer&);

    float getDiscount();
    void setDiscount(float discount)
    {
        discountPercentage = discount;
    }
protected:

private:
    float discountPercentage;
};

#endif // GOLDCUSTOMER_H
