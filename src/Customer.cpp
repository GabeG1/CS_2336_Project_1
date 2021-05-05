//Gabriel Goldstein
//gjg180000
#include "Customer.h"
Customer::Customer(std::string fn, std::string ln, std::string gid, float as)
{
    firstName = fn;
    lastName = ln;
    guestID = gid;
    amountSpent = as;
}

Customer::Customer()
{
    firstName = "";
    lastName = "";
    guestID = "";
    amountSpent = 0.00;
}
Customer::Customer(const Customer &C2)
{
    firstName = C2.firstName;
    lastName = C2.lastName;
    guestID =   C2.guestID;
    amountSpent = C2.amountSpent;

}


