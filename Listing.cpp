#include "Listing.h"
#include <iostream>

Listing::Listing() { //default
    listingId = 0;
    price = 0.0;
    isActive = true;
    sellerUsername = "";
    itemPtr = new Item();
}

Listing::Listing(int id, double p, string seller, const Item& item) {
    listingId = id;
    price = p;
    isActive = true;
    sellerUsername = seller;
    itemPtr = new Item(item); // create new item on the heap thats a copy
}

// copy constructor - deep Copy
//vector makes copy  when we run listings.pushback(listing)
Listing::Listing(const Listing& other) {
    //cout << "copy constructor called" << endl;
    listingId = other.listingId; //shallow copy of members
    price = other.price;
    isActive = other.isActive;
    sellerUsername = other.sellerUsername;
    if (other.itemPtr) {
        itemPtr = new Item();
        *itemPtr = *(other.itemPtr);
    } else {
        itemPtr = nullptr; //make sure other listing has an item and allocate new memory (deep copy)
    }
}

// destructor called automatically when object out of scope
Listing::~Listing() {
    if (itemPtr) { //check that its not null
        delete itemPtr; 
        itemPtr = nullptr; //make null so its not used again
    }
}

// assignment operator - deep copy, for listingA = ListingB
//returns reference listing
Listing& Listing::operator=(const Listing& other) {
    if (this == &other)
        return *this;

    listingId = other.listingId; //shallow copy
    price = other.price;
    isActive = other.isActive;
    sellerUsername = other.sellerUsername;

    if (other.itemPtr) { //deep copy of the ptr
        if (!itemPtr)
            itemPtr = new Item();
        *itemPtr = *(other.itemPtr);
    } else {
        if (itemPtr)
            delete itemPtr;
        itemPtr = nullptr;
    }
    return *this;
}

string Listing::getItemTitle() const {
    if (itemPtr) return itemPtr->getTitle();
    return "N/A"; // return N/A if pointer is null
}

string Listing::getItemBrand() const {
    if (itemPtr) return itemPtr->getBrand();
    return "N/A";
}

string Listing::getItemCategory() const {
    if (itemPtr) return itemPtr->getCategory();
    return "N/A";
}

string Listing::getItemDescription() const {
    if (itemPtr) return itemPtr->getDescription();
    return "N/A";
}

void Listing::displayDetails() {
    cout << "Listing #" << getListingId() << " | EUR" << getPrice()
         << " | Seller: " << getSellerUsername() << endl;
    if (itemPtr)
        itemPtr->displayDetails(); //call display using ptr
}

// for STL sort by price, overloaded < operator
bool operator<(const Listing& a, const Listing& b) {
    return (a.price < b.price); 
}
