/*
 * Name:Connie Wang
 * EID:cw39276
 * Project 7, CRM part 2
 * EE 312, Fall 2019
 */

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

using namespace std;

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    UTString name;
    readString(name);
    UTString prod;
    readString(prod);
    int num;
    readNum(num);

    if (num > 0) {
        if (num <= *selectInventItem(prod)) {
            Customer cust = database[name];
            int* items = (selectInventItem(prod, cust));
            *items += num;
            database[name] = cust;

            *(selectInventItem(prod)) -= num;
        } else {
            cout << "Sorry " << name.c_str() << ", we only have " << *(selectInventItem(prod)) << " " << prod.c_str() << endl;
        }
    }
    // not done, your effort goes here
}

void processSummarize() {
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;

    Customer* bMax = findMax(UTString("Bottles"));
    Customer* dMax = findMax(UTString("Diapers"));
    Customer* rMax = findMax(UTString("Rattles"));

    if (bMax != 0 && bMax->bottles != 0) {
        cout << bMax->name.c_str() << " has purchased the most Bottles (" << bMax->bottles << ")" << endl;
    } else {
        cout << "no one has purchased any Bottles" << endl;
    }

    if (dMax != 0 && dMax->diapers != 0) {
        cout << dMax->name.c_str() << " has purchased the most Diapers (" << dMax->diapers << ")" << endl;
    } else {
        cout << "no one has purchased any Diapers" << endl;
    }

    if (rMax != 0 && rMax->rattles != 0) {
        cout << rMax->name.c_str() << " has purchased the most Rattles (" << rMax->rattles << ")" << endl;
    } else {
        cout << "no one has purchased any Rattles" << endl;
    }
    // not done, your effort goes here
}

void processInventory() {
    UTString prod;
    int num;
    readString(prod);
    readNum(num);
    int *temp = selectInventItem(prod);
    *temp += num;
    // not done, your effort goes here
}
