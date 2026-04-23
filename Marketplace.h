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

public:
    Marketplace(); //default
    ~Marketplace(); // destructor


    // users
    User* registerUser(string username, string password, string email, string role); //new user
    User* loginUser(string username, string password); //login 
    void displayAllUsers(); //privledges for admin
    bool usernameExists(string username); 



    // listings
    void addListing(Listing& listing);
    void removeListing(int listingId);
    void displayAllListings();
    void sortByPrice();
    void sortByTitle(); //alphabetically by title
    int searchByTitle(string title);



    // file I/O
    void saveToFile();
    void loadFromFile();
};

#endif
