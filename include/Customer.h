//Gabriel Goldstein
//gjg180000
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

class Customer
{
public:
    Customer();
    Customer(std::string, std::string, std::string, float);

    //Copy Constructor
    Customer(const Customer&);

    virtual float getDiscount()
    {
        return 0.0;
    }
    virtual void setDiscount(float discount)
    {
        discount = discount;
    }
    virtual int getBonusBucks()
    {
        return 0;
    }
    virtual void setBonusBucks(int bonusBucks)
    {
        bonusBucks = bonusBucks;
    }
    std::string getFirstName()
    {
        return firstName;
    }


    std::string getLastName()
    {
        return lastName;
    }
    std::string getguestID()
    {
        return guestID;
    }
    float  getamountSpent()
    {
        return amountSpent;
    }
    void setAmountSpent(float as)
    {
        amountSpent += as;
    }

protected:

private:
    std::string firstName;
    std::string lastName;
    std::string guestID;
    float amountSpent;
};

#endif // CUSTOMER_H
