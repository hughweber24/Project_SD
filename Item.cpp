#include "Item.h"

Item::Item() { // default
    title = "untitled";
    description = "";
    brand = "";
    category = "";
}

Item::Item(string t, string d, string b, string c) {
    title = t;
    description = d;
    brand = b;
    category = c;
}

void Item::displayDetails() { // item details
    cout << "Item: " << getTitle() << " | Brand: " << getBrand()
     << " | Category: " << getCategory() << endl;
    cout << "  Description: " << getDescription() << endl;
}
