#ifndef _LISTING_
#define _LISTING_
#include "Item.h"

class Listing {
private:
    int listingId; 
    double price;
    bool isActive;
    string sellerUsername;
    Item* itemPtr; // pointer to an item object

public:
    Listing(); //default
    Listing(int id, double price, string seller, const Item& item);
    Listing(const Listing& other);            // copy constructor
    ~Listing();                                // destructor called when object is out of scope
    Listing& operator=(const Listing& other);  // assignment operator

    void setListingId(int id) { listingId = id; }
    int getListingId() const { return listingId; }
    void setPrice(double p) { price = p; }
    double getPrice() const { return price; }
    void setIsActive(bool a) { isActive = a; }
    bool getIsActive() const { return isActive; }
    void setSellerUsername(string s) { sellerUsername = s; }
    string getSellerUsername() const { return sellerUsername; }

    string getItemTitle() const; //access item through the ptr, itemPtr is private
    string getItemBrand() const;
    string getItemCategory() const;
    string getItemDescription() const;

    void displayDetails(); //listing info

    // needed for STL sort so it can compare two listings by price, friend function
    friend bool operator<(const Listing& a, const Listing& b);
};

// comparator function for sorting different listings by there title
//
inline bool compareByTitle(const Listing& a, const Listing& b) {
    return (a.getItemTitle() < b.getItemTitle()); //compares it alphabetically
}

#endif
