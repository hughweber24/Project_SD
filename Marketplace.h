#ifndef _MARKETPLACE_
#define _MARKETPLACE_
#include "Admin.h"
#include "Listing.h"
#include "MarketplaceException.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class Marketplace {
private:
    vector<User*> users;       // polymorphic pointers
    vector<Listing> listings; //stores all listings 
    int nextUserId; //auto incremement IDs for new users and listings
    int nextListingId;
    string dataFile;
    const static int MaxListings = 5;

public:
    Marketplace(); //default
    Marketplace(string filename);
    ~Marketplace(); // destructor


    // users
    User* registerUser(string username, string password, string email, string role); //new user
    User* loginUser(string username, string password); //login 
    void displayAllUsers(); //privledges for admin
    bool usernameExists(string username); 



    // listings
    void addListing(Listing& listing);
    void removeListing(int listingId);
    void removeListingUser(int ListingId, string seller); //can only delete their own listings
    void displayAllListings();
    void sortByPrice();
    void sortByTitle(); //alphabetically by title
    int searchByTitle(string title);
    int getMaxListing() {return MaxListings; }



    // file I/O
    void saveToFile();
    void loadFromFile();
};

#endif
