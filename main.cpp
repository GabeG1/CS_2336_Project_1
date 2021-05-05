//Gabriel Goldstein
//gjg180000
#include "Customer.h"
#include "GoldCustomer.h"
#include "PlatinumCustomer.h"
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

float processOrder(Customer**, int, char, string, float, int);
Customer* promoteCustomer(Customer**, int, float);
const float SMALL_SURFACE_AREA = (float)(3.142 * 2.00 * 4.5);
const float MEDIUM_SURFACE_AREA = (float)(3.142 * 2.25 * 5.75);
const float LARGE_SURFACE_AREA = (float)(3.142 * 2.75 * 7);
const float SODA_COST_PER_OUNCE = (float)0.20;
const float TEA_COST_PER_OUNCE = (float)0.12;
const float FRUITPUNCH_COST_PER_OUNCE = (float)0.15;

int main()
{

    Customer **regCustArr = NULL;
    Customer **prefCustArr = NULL;
    ifstream regCustomerFile("customer4.dat");
    int numRegCust = 0;
    int startingNumRegCust = 0;
    int numPrefCust = 0;
    string line = "";
    string firstName = "";
    string lastName = "";
    string id = "";
    float amountSpent;
    if (regCustomerFile.is_open())
    {
        //Determine number of Regular Customers to be stored in Array
        while(!(regCustomerFile.eof()))
        {
            getline(regCustomerFile, line);

            //In case there are any extra lines in file
            if(line == "")
            {
                continue;
            }
            numRegCust++;
        }
        startingNumRegCust = numRegCust;

        //Since file has been read, it needs to be sent back to the beginning to be read again to store regular customers into array
        regCustomerFile.clear();
        regCustomerFile.seekg(0);

        if (numRegCust != 0)
        {

            regCustArr = new Customer*[numRegCust];

            //Save information from Regular Customers File to Regular Customers Array
            for(int i = 0; i < numRegCust; i++)
            {
                regCustomerFile >> id >> firstName >> lastName >> amountSpent;
                regCustArr[i] = new Customer(firstName, lastName, id, amountSpent);
            }
        }
        regCustomerFile.close();

    }

    ifstream prefCustomerFile("preferred4.dat");

    //Make sure Preferred Customer File Exists
    if(prefCustomerFile.is_open())
    {

        //Count number of preferred customers in the file
        while(!(prefCustomerFile.eof()))
        {
            getline(prefCustomerFile, line);

            //In case there are any extra lines in file
            if(line == "")
            {

                continue;
            }
            numPrefCust++;

        }

        //Now that number of preferred customers has been counted, return file back to beginning to store preferred customer data into array
        prefCustomerFile.clear();
        prefCustomerFile.seekg(0);

        string discountTemp = "0";
        int pos = 0;
        float discount = 0.0;
        int bonusBucks = 0;

        if (numPrefCust != 0)
        {
            prefCustArr = new Customer*[numPrefCust];
            for(int i = 0; i < numPrefCust; i++)
            {

                prefCustomerFile >> id >> firstName >> lastName >> amountSpent >> discountTemp;

                pos = (int)discountTemp.find("%");

                //If the percentage sign has been found, store customer as a gold customer
                if(pos != (signed)string::npos)
                {
                    discount = stof(discountTemp.substr(0, discountTemp.length() - 1)) / 100;


                    prefCustArr[i] = new GoldCustomer(firstName, lastName, id, amountSpent, discount);
                }

                //Otherwise, since percentage sign not found, store customer as a platinum customer
                else
                {

                    bonusBucks = stoi(discountTemp);

                    prefCustArr[i] =  new PlatinumCustomer(firstName, lastName, id, amountSpent, bonusBucks);

                }

            }

        }

        prefCustomerFile.close();

    }

    ifstream ordersFile("orders4.dat");

    //Make sure order file exists
    if (ordersFile.is_open())
    {


        while(!(ordersFile.eof()))
        {


            getline(ordersFile, line);

            string temp;
            char drinkSize;
            string drinkType = "";
            float costPerSquareInch = 0.0;
            int drinkQuantity = 0;

            id = line.substr(0, line.find_first_of(" "));

            int posOfCustomer = -1;
            bool isRegCust = false;
            if(numRegCust > 0)
            {
                //Check to see if id in orders file matches that of a regular customer
                for (int i = 0; i < numRegCust; i++)
                {

                    if(id == regCustArr[i]->getguestID())
                    {

                        posOfCustomer = i;
                        isRegCust = true;

                        break;
                    }
                }
            }

            //If id does not match a regular customer's id, check to see if it matches that of a preferred customer
            if (numPrefCust > 0 && posOfCustomer == -1)
            {
                for (int i = 0; i < numPrefCust; i++)
                {
                    if(id == prefCustArr[i]->getguestID())
                    {

                        posOfCustomer = i;
                        break;
                    }
                }
            }

            //If the id matches no customer, skip this order
            if (posOfCustomer == -1)
            {

                continue;
            }

            temp = line.substr(line.find_first_of(" ") + 1, line.length());

            try
            {
                //Since the drink size is only one letter, make sure that the file only presents one letter for that data type. Otherwise, skip the order.
                if((temp.substr(0, temp.find_first_of(" "))).length() == 1)
                {

                    drinkSize = *(temp.substr(0, temp.find_first_of(" "))).c_str();

                    //Make sure the drink size specifically matches one of three drink size. Can only be uppercase. Skip order if not.
                    if(drinkSize != 'L' && drinkSize != 'M' && drinkSize!= 'S')
                    {
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
            catch(exception e)
            {

                continue;

            }

            temp = temp.substr(temp.find_first_of(" ") + 1, temp.length());
            try
            {
                drinkType = temp.substr(0, temp.find_first_of(" "));

                //Make sure the type of drink matches one of the three drinks. Can only be lowercase. Otherwise, skip order
                if(drinkType != "punch" && drinkType != "tea" && drinkType != "soda")
                {
                    continue;
                }
            }
            catch(exception e)
            {

                continue;
            }

            temp = temp.substr(temp.find_first_of(" ") + 1, temp.length());

            //If the cost per square inch is anything other than a float, the order will be discarded
            try
            {
                costPerSquareInch = stof(temp.substr(0, temp.find_first_of(" ")));
                if(temp.substr(0, temp.find_first_of(" ")) != "0")
                {

                    if(temp.find_first_of(".") == string::npos)
                    {
                        continue;
                    }

                    else if((temp.substr(1, temp.find_first_of(" ") - 1)).length() != 3)
                    {
                        continue;
                    }
                }
            }

            catch(exception e)
            {
                continue;
            }

            temp = temp.substr(temp.find_first_of(" ") + 1, temp.length());

            //If the drink quantity is anything other than an integer, the order will be discarded
            try
            {
                if(temp.find_first_of(".") != string::npos)
                {
                    continue;
                }
                drinkQuantity = stoi(temp.substr(0, temp.find_first_of(" ")));
            }
            catch(exception e)
            {

                continue;
            }


            int pos = 0;
            int numberOfFields = 1;

            //Determines how many fields there are in the order
            while(line.find(" ", pos) != string::npos)
            {

                pos = (int)line.find(" ", pos) + 1;
                numberOfFields++;
            }

            //Proceed with the order if there are exactly five fields
            if(numberOfFields == 5)
            {
                float costOfCurrentPurchase = 0.00;

                //If the customer is regular
                if(isRegCust == true)
                {
                    Customer** tempPrefCustArr;

                    costOfCurrentPurchase = processOrder(regCustArr, posOfCustomer, drinkSize, drinkType, costPerSquareInch, drinkQuantity);

                    //Since this customer is regular, check to see if customer spent over $50
                    if ((regCustArr[posOfCustomer]->getamountSpent() + costOfCurrentPurchase) >= 50)
                    {

                        Customer** tempRegCustArr;
                        tempRegCustArr = new Customer*[numRegCust - 1];

                        //Checking to see if the preferred customer array exists (by seeing how many preferred customers there are) to determine if the preferred customers array must be resized
                        if(numPrefCust != 0)
                        {
                            tempPrefCustArr = new Customer*[numPrefCust];

                            //Copy the contents of preferred customers array to a temporary array to be used later
                            for (int i = 0; i < numPrefCust; i++)
                            {

                                tempPrefCustArr[i] = prefCustArr[i];

                            }
                            //delete the content of the preferred customer array
                            for(int i = 0; i < numPrefCust; i++)
                            {
                                prefCustArr[i] = NULL;
                                delete[] prefCustArr[i];
                            }
                            prefCustArr = NULL;
                            delete[] prefCustArr;

                            numPrefCust++;

                            //Resizing the preferred customer array so that it can fit one more customer
                            prefCustArr = new Customer*[numPrefCust];

                            //Copying back the contents from the temporary array to the preferred customers array
                            for(int i = 0; i < numPrefCust - 1; i++)
                            {

                                prefCustArr[i] =  tempPrefCustArr[i];
                            }
                        }

                        //Since the preferred array has not been created, make it here
                        else
                        {
                            numPrefCust++;
                            prefCustArr = new Customer*[numPrefCust];
                        }

                        int tempRegArrPos = 0;
                        for (int i = 0; i < numRegCust; i++)
                        {
                            //This makes sure that the customer who was moved up to the preferred array does not get
                            //copied into the temporary regular array, which will be used again to copy elements back to the regular customer array
                            if(i == posOfCustomer)
                            {

                                continue;
                            }

                            tempRegCustArr[tempRegArrPos] = regCustArr[i];
                            tempRegArrPos++;

                        }

                        //Now its time to promote the customer to gold status
                        prefCustArr[numPrefCust - 1] = promoteCustomer(regCustArr, posOfCustomer, (costOfCurrentPurchase + regCustArr[posOfCustomer]->getamountSpent()));
                        numRegCust -= 1;

                        for (int i = 0; i < numRegCust; i++)
                        {

                            regCustArr[i] = tempRegCustArr[i];
                        }



                        //Checks to see if the purchase with no discount + amount previously spent  applied is greater than $200
                        if (prefCustArr[numPrefCust - 1]->getamountSpent() + costOfCurrentPurchase >= (float)200)
                        {
                            //Calculates the the purchase with a 15% discount applied
                            costOfCurrentPurchase = processOrder(prefCustArr, numPrefCust - 1, drinkSize, drinkType, costPerSquareInch, drinkQuantity);

                            //Checks to see if the purchase with 15% discount + the amount previously spent is greater than $200
                            if(prefCustArr[numPrefCust - 1]->getamountSpent() + costOfCurrentPurchase >= (float)200)
                            {
                                //Promote customer to platinum status
                                prefCustArr[numPrefCust - 1] = promoteCustomer(prefCustArr, numPrefCust - 1, prefCustArr[numPrefCust - 1]->getamountSpent() + costOfCurrentPurchase);
                            }

                        }

                        //Checks the cases in which the purchase + the amount previously spent is less than 200 to
                        //determine the appropriate discount to apply to the gold customer
                        else
                        {
                            //Calculates the order with a 5& discount applied
                            costOfCurrentPurchase = processOrder(prefCustArr, numPrefCust - 1, drinkSize, drinkType, costPerSquareInch, drinkQuantity);

                            //Checks if current purchase with 5% discount + amount previously spent puts customer over $100
                            if (prefCustArr[numPrefCust - 1]->getamountSpent() + costOfCurrentPurchase >= (float)100)
                            {
                                //Give customer 10% order and reprocess the order
                                prefCustArr[numPrefCust - 1]->setDiscount((float).10);
                                costOfCurrentPurchase = processOrder(prefCustArr, numPrefCust - 1, drinkSize, drinkType, costPerSquareInch, drinkQuantity);
                            }

                            //Checks if current purchase with 10% discount + amount previously spent puts customer over $150
                            if (prefCustArr[numPrefCust - 1]->getamountSpent() + costOfCurrentPurchase >= (float)150)
                            {
                                //Give customer 15% order and reprocess the order
                                prefCustArr[numPrefCust - 1]->setDiscount((float).15);
                                costOfCurrentPurchase = processOrder(prefCustArr, numPrefCust - 1, drinkSize, drinkType, costPerSquareInch, drinkQuantity);
                            }
                        }

                        //Change the total amount the customer has spent to include the current order
                        prefCustArr[numPrefCust - 1]->setAmountSpent(costOfCurrentPurchase);

                        //delete both temporary arrays created above
                        for(int i = 0; i < numRegCust; i++)
                        {
                            tempRegCustArr[i] = NULL;
                            delete[] tempRegCustArr[i];
                        }
                        tempRegCustArr = NULL;
                        delete[] tempRegCustArr;

                        for(int i = 0; i < numPrefCust - 1; i++)
                        {
                            tempPrefCustArr[i] = NULL;
                            delete[] tempPrefCustArr[i];
                        }
                        tempPrefCustArr = NULL;
                        delete[] tempPrefCustArr;
                    }

                    //If the customer remains a regular customer
                    else
                    {
                        //Change the total amount the customer has spent to include the current order
                        regCustArr[posOfCustomer]->setAmountSpent(costOfCurrentPurchase);

                    }
                }

                //If the customer is a preferred customer
                else
                {
                    //Calculate cost of order using appropriate discounts or bonus bucks
                    costOfCurrentPurchase = processOrder(prefCustArr, posOfCustomer, drinkSize, drinkType, costPerSquareInch, drinkQuantity);

                    //Promote customer to 10% discount if they originally had 5% discount and their purchase puts them over $100
                    if(((prefCustArr[posOfCustomer]->getamountSpent() + costOfCurrentPurchase) >= (float)100) && ((prefCustArr[posOfCustomer]->getDiscount()) == (float)0.05))
                    {

                        prefCustArr[posOfCustomer]->setDiscount((float).10);
                        costOfCurrentPurchase = processOrder(prefCustArr, posOfCustomer, drinkSize, drinkType, costPerSquareInch, drinkQuantity);
                    }
                    //Promote customer to 15% discount if they have 10% discount and their purchase puts them over $150
                    if(((prefCustArr[posOfCustomer]->getamountSpent() + costOfCurrentPurchase) >= 150) && ((prefCustArr[posOfCustomer]->getDiscount()) == (float)0.10))
                    {

                        prefCustArr[posOfCustomer]->setDiscount((float).15);
                        costOfCurrentPurchase = processOrder(prefCustArr, posOfCustomer, drinkSize, drinkType, costPerSquareInch, drinkQuantity);
                    }
                    //Promote customer to Platinum if their purchase puts them over $200 and they were previously under $200
                    if(((prefCustArr[posOfCustomer]->getamountSpent() + costOfCurrentPurchase) >= (float)200) && prefCustArr[posOfCustomer]->getamountSpent() < (float)200)
                    {


                        prefCustArr[posOfCustomer] = promoteCustomer(prefCustArr, posOfCustomer, (costOfCurrentPurchase + prefCustArr[posOfCustomer]->getamountSpent()));

                    }

                    prefCustArr[posOfCustomer]->setAmountSpent(costOfCurrentPurchase);

                }


            }



        }

    }
    ordersFile.close();

//Make sure the Regular Customer File exists
    if(startingNumRegCust != 0)
    {
        ofstream regCustOutFile("customer4.dat");

        //Print out regular customers to "customer4.dat"
        for(int i = 0; i < numRegCust; i++)
        {
            regCustOutFile << regCustArr[i]->getguestID() << " " << regCustArr[i]->getFirstName() << " " << regCustArr[i]->getLastName() << " " << fixed << setprecision(2) << regCustArr[i]->getamountSpent();
            if(i != numRegCust - 1)
            {
                regCustOutFile << "\n";
            }
        }
        regCustOutFile.close();
    }

    //make sure there are preferred customers. This implies that a preferred customer file exists
    if(numPrefCust != 0)
    {


        ofstream prefCustOutFile("preferred4.dat");

        //Print out preferred customers to "preferred4.dat"
        for (int i = 0; i < numPrefCust; i++)
        {
            //Printing out platinum customer
            if (prefCustArr[i]->getamountSpent() >= (float)200)
            {

                prefCustOutFile << prefCustArr[i]->getguestID() << " " << prefCustArr[i]->getFirstName() << " " << prefCustArr[i]->getLastName() << " " << fixed << setprecision(2) << prefCustArr[i]->getamountSpent() << " ";
                prefCustOutFile << setprecision(0) << prefCustArr[i]->getBonusBucks();
                if(i != numPrefCust - 1)
                {
                    prefCustOutFile << "\n";
                }

            }

            //Printing out gold customer
            else
            {

                prefCustOutFile << prefCustArr[i]->getguestID() << " " << prefCustArr[i]->getFirstName() << " " << prefCustArr[i]->getLastName() << " " << fixed << setprecision(2) << prefCustArr[i]->getamountSpent() << " ";
                prefCustOutFile << setprecision(0) << prefCustArr[i]->getDiscount() *100 << "%";
                if(i != numPrefCust - 1)
                {
                    prefCustOutFile << "\n";
                }
            }

        }

        prefCustOutFile.close();
    }

    //Deleting both the regular customer array and the preferred customer array
    for(int i = 0; i < numRegCust; i++)
    {
        regCustArr[i] = NULL;
        delete[] regCustArr[i];

    }
    regCustArr = NULL;
    delete[] regCustArr;
    for(int i = 0; i < numPrefCust; i++)
    {
        prefCustArr[i] = NULL;
        delete[]  prefCustArr[i];

    }
    prefCustArr = NULL;
    delete[]  prefCustArr;
    return 0;
}

//Calculates the cost of the current order
float processOrder(Customer **custArr, int posOfCust, char drinkSize, string drinkType, float costPerSquareInch, int quantity)
{

    float personalizedCost = 0.00;
    float numOunces = 0.00;

    //Figure out drink size in order to get correct number of ounces
    if(drinkSize == 'S')
    {
        personalizedCost = costPerSquareInch * SMALL_SURFACE_AREA;
        numOunces = 12;
    }
    else if(drinkSize == 'M')
    {
        personalizedCost = costPerSquareInch * MEDIUM_SURFACE_AREA;
        numOunces = 20;
    }
    else
    {
        personalizedCost = costPerSquareInch * LARGE_SURFACE_AREA;
        numOunces = 32;
    }

    float costOfDrink = 0.0;

    //Figure out the drink ordered to get correct price of drink
    if(drinkType == "punch")
    {

        costOfDrink = FRUITPUNCH_COST_PER_OUNCE * numOunces;
    }
    else if(drinkType == "tea")
    {

        costOfDrink = TEA_COST_PER_OUNCE * numOunces;
    }
    else
    {
        costOfDrink = SODA_COST_PER_OUNCE * numOunces;
    }
    float totalCost = (costOfDrink + personalizedCost) * (float)(quantity);

    //If gold customer, apply appropriate discount
    if(custArr[posOfCust]->getDiscount() != 0.0)
    {

        totalCost = totalCost - (totalCost * custArr[posOfCust]->getDiscount());
    }

    //If a platinum customer, use bonus bucks
    else if(custArr[posOfCust]->getamountSpent() >= 200)
    {

        int bonusBucksUsed = 0;

        //The if else statement makes sure that the number of bonus bucks used does not exceed the cost of the current purchase
        if (custArr[posOfCust]->getBonusBucks() > (int)totalCost)
        {

            int bonuBuckstoUse = (int)totalCost;
            totalCost = totalCost - (float) bonuBuckstoUse;
            bonusBucksUsed = bonuBuckstoUse;
        }
        else
        {

            totalCost = totalCost - (float)custArr[posOfCust]->getBonusBucks();
            bonusBucksUsed = custArr[posOfCust]->getBonusBucks();
        }

        //calculate the number of bonus bucks the platinum customer now has
        int numBonusBucks = custArr[posOfCust]->getBonusBucks() - bonusBucksUsed + (int)((totalCost + custArr[posOfCust]->getamountSpent()) / 10) - (int)(custArr[posOfCust]->getamountSpent() / 10);
        custArr[posOfCust]->setBonusBucks(numBonusBucks);
    }


    return totalCost;
}

//Promote Customer from Regular Customer Array to Preferred Customer Array
Customer* promoteCustomer(Customer **custArr, int posOfCust, float amountSpentTotal)
{


    if(amountSpentTotal >= (float)200)

    {
        //If customer is already gold
        if(custArr[posOfCust]->getDiscount() != (float)0.0)
        {
            return  new PlatinumCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (int)((amountSpentTotal - 200) / 10));

        }

        //Customer is regular
        else
        {

            return new GoldCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (float).15);
        }
    }

    //If customer is regular and their purchase + amount previously spent does not exceed $200, give them a 5% discount
    if(custArr[posOfCust]->getDiscount() == (float)0.00)
    {
        return new GoldCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (float).05);

    }
//If gold customer's purchase + amount previously spent exceeds $150, give them a 15% discount.
    if (amountSpentTotal >= (float)150)
    {
        return new GoldCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (float).15);
    }

    //If gold customer's purchase + amount previously spent exceeds $100, give them a 10% discount.
    if (amountSpentTotal >= (float)100)
    {
        return  new GoldCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (float).10);
    }
//By default, promote customer to gold status with 5% discount
    return new GoldCustomer(custArr[posOfCust]->getFirstName(), custArr[posOfCust]->getLastName(), custArr[posOfCust]->getguestID(), custArr[posOfCust]->getamountSpent(), (float).05);



}





