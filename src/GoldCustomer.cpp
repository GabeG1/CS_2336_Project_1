//Gabriel Goldstein
//gjg180000
#include "Customer.h"
#include "GoldCustomer.h"

GoldCustomer::GoldCustomer()
{
    discountPercentage = 0.00;
}
GoldCustomer::GoldCustomer(std::string fn, std::string ln, std::string id, float as, float dp):
    Customer::Customer(fn, ln, id, as)
{
    discountPercentage = dp;
}
GoldCustomer::GoldCustomer(const GoldCustomer& GC2) : Customer::Customer(GC2)
{

    discountPercentage = GC2.discountPercentage;
}

float GoldCustomer::getDiscount()
{
    return discountPercentage;
}

