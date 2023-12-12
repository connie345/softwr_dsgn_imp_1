/*
 * Name:Connie Wang
 * EID:cw39276
 * Project 7, CRM part 2
 * EE 312, Fall 2019
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
    if (isMember(name)) {
        for(int k = 0;k<this->length;k++){
            if (this->data[k].name == name) {
                return this->data[k];
            }
        }
    }
    else {
        if (this->length + 1 == this->capacity) {
            Customer *newData = new Customer[capacity * 2];
            for (int k = 0; k < this->length; k++) {
                newData[k] = this->data[k];
            }
            delete[] this->data;
            newData[length] = Customer(name);
            this->data = newData;
            this->capacity *= 2;
        }
        else {
            this->data[length] = Customer(name);
        }
        this->length++;
        return this->data[length -1];

    }
}

bool CustomerDB::isMember(UTString name) { // not done, your effort goes here
    for (int i = 0; i < this->length; i++) {
        if (this->data[i].name == name) {
            return true;
        }
    }
    return false;
}
