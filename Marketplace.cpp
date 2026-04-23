#include "Marketplace.h"

Marketplace::Marketplace() { //default
    nextUserId = 1;
    nextListingId = 1;
    dataFile = "data.txt";
}

Marketplace::~Marketplace() { //destructor
    for (int i = 0; i < users.size(); i++) {
        delete users[i];
    }
    users.clear();
}

// ---- User functions ----

User* Marketplace::registerUser(string username, string password, string email, string role) {
    if (usernameExists(username)) {
        throw MarketplaceException("Username '" + username + "' already exists."); //throws exeption if its already on the system
    }

    User* newUser = nullptr;
    if (role == "Admin") { 
        newUser = new Admin(nextUserId, username, password, email, "basic");
    } else {
        newUser = new User(nextUserId, username, password, email);
    }

    nextUserId++;
    users.push_back(newUser);
    cout << "Registration successful! Welcome, " << username << "." << endl;
    return newUser;
}


User* Marketplace::loginUser(string username, string password) { //checks if username and password match
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getUsername() == username && users[i]->getPassword() == password) {
            cout << "Login successful! Welcome back, " << username << "." << endl;
            return users[i];
        }
    }
    throw MarketplaceException("Invalid username or password.");
}




void Marketplace::displayAllUsers() { //not neccessary
    if (users.empty()) {
        cout << "No users registered." << endl;
        return;
    }

    cout << "\n--- All Users (" << users.size() << ") ---" << endl;
    for (int i = 0; i < users.size(); i++) {
        users[i]->displayDetails(); // polymorphic display
    }
}



bool Marketplace::usernameExists(string username) { 
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getUsername() == username)
            return true;
    }
    return false;
}




// ----------------------------Listing functions -------------------------------------------------------

void Marketplace::addListing(Listing& listing) {
    listing.setListingId(nextListingId); //add new ID to listing
    nextListingId++;
    listings.push_back(listing);
    cout << "Listing added! (ID: " << listing.getListingId() << ")" << endl;
}



void Marketplace::removeListing(int listingId) { //admin privledge
    for (int i = 0; i < listings.size(); i++) {
        if (listings[i].getListingId() == listingId) {
            listings.erase(listings.begin() + i);
            cout << "Listing #" << listingId << " removed." << endl;
            return;
        }
    }
    throw MarketplaceException("Listing not found.");
}



void Marketplace::displayAllListings() { //admin privledge
    if (listings.empty()) {
        cout << "No listings available." << endl;
        return; //just in case
    }
    cout << "\n--- Listings (" << listings.size() << ") ---" << endl;
    for (int i = 0; i < listings.size(); i++) {
        listings[i].displayDetails();
        cout << endl;
    }
}


// STL sort - uses overloaded < operator
void Marketplace::sortByPrice() {
    sort(listings.begin(), listings.end());
    cout << "Sorted by price." << endl;
}

// STL sort - uses compareByTitle function from Listing.h
void Marketplace::sortByTitle() {
    sort(listings.begin(), listings.end(), compareByTitle);
    cout << "Sorted by title." << endl;
}

// search using STL find_if
int Marketplace::searchByTitle(string title) {
    for (int i = 0; i < listings.size(); i++) {
        if (listings[i].getItemTitle() == title) {
            cout << "Found:" << endl;
            listings[i].displayDetails();
            return listings[i].getListingId();
        }
    }
    cout << "No listing found with title: " << title << endl;
    return -1;
}

// ---- File I/O ----

void Marketplace::saveToFile() {
    try {
        ofstream outFile(dataFile);
        if (!outFile.is_open()) {
            throw runtime_error("Could not open file: " + dataFile);
        }
        
        //save users
        outFile << "[USERS]" << endl;
        for (int i = 0; i < users.size(); i++) {
            outFile << users[i]->getUserId() << "|"
                    << users[i]->getUsername() << "|"
                    << users[i]->getPassword() << "|"
                    << users[i]->getEmail() << "|"
                    << users[i]->getRole() << endl;
        }

        //save listings
        outFile << "[LISTINGS]" << endl;
        for (int i = 0; i < listings.size(); i++) {
            outFile << listings[i].getListingId() << "|"
                    << listings[i].getItemTitle() << "|"
                    << listings[i].getItemDescription() << "|"
                    << listings[i].getItemBrand() << "|"
                    << listings[i].getItemCategory() << "|"
                    << listings[i].getPrice() << "|"
                    << listings[i].getSellerUsername() << endl;
        }

        outFile.close();
        cout << "Data is saved." << endl;

    } catch (const runtime_error& e) {
        cerr << "File error: " << e.what() << endl;
    }
}





void Marketplace::loadFromFile() {
    try {
        ifstream inFile(dataFile);
        if (!inFile.is_open()) {
            cout << "No data file found. Starting new." << endl;
            return;
        }

        string line;
        string section = "";

        while (getline(inFile, line)) {
            if (line.empty()) continue;
            //headers
            if (line == "[USERS]") { section = "USERS"; continue; }
            if (line == "[LISTINGS]") { section = "LISTINGS"; continue; }

            // split line by | to make it neat
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            //assemble users
            if (section == "USERS" && tokens.size() >= 5) {
                int id = stoi(tokens[0]);
                User* u = nullptr;
                if (tokens[4] == "Admin")
                    u = new Admin(id, tokens[1], tokens[2], tokens[3], "basic");
                else
                    u = new User(id, tokens[1], tokens[2], tokens[3]);

                users.push_back(u);
                if (id >= nextUserId) nextUserId = id + 1;
            }

            //assemble listings
            else if (section == "LISTINGS" && tokens.size() >= 7) {
                int id = stoi(tokens[0]);
                Item item(tokens[1], tokens[2], tokens[3], tokens[4]);
                Listing listing(id, stod(tokens[5]), tokens[6], item);
                listings.push_back(listing);
                if (id >= nextListingId) nextListingId = id + 1;
            }
        }

        inFile.close();
        cout << "Loaded " << users.size() << " users, "
             << listings.size() << " listings." << endl;

    } catch (const exception& e) {
        cerr << "Error loading file: " << e.what() << endl;
    }
}
