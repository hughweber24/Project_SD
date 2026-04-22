#ifndef _ITEM_
#define _ITEM_
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string title;
    string description;
    string brand;
    string category;

public:
    Item(); //default 
    Item(string title, string description, string brand, string category); //4 parameter constructr

    void setTitle(string t) { title = t; }
    string getTitle() const { return title; }
    void setDescription(string d) { description = d; }
    string getDescription() const { return description; }
    void setBrand(string b) { brand = b; }
    string getBrand() const { return brand; }
    void setCategory(string c) { category = c; }
    string getCategory() const { return category; }

    void displayDetails();
};

#endif
