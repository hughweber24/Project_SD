#include "Marketplace.h"

int main() {
    Marketplace marketplace; // Create marketplace instance
    marketplace.loadFromFile(); // Load existing data if available

    cout << "\n=============================" << endl;
    cout << "   Online Marketplace" << endl;
    cout << "=============================" << endl;

    int choice;
    bool running = true;
    User* currentUser = nullptr; // Track logged-in user

    while (running) {
        // main menu - not logged in
        if (currentUser == nullptr) {
            cout << "\n--- Main Menu ---" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string username, password, email, role;
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                cout << "Email: ";
                getline(cin, email);
                cout << "Role (User/Admin): ";
                getline(cin, role);

                try {
                    marketplace.registerUser(username, password, email, role);
                } catch (const MarketplaceException& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if (choice == 2) {
                string username, password;
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);

                try {
                    currentUser = marketplace.loginUser(username, password);
                } catch (const MarketplaceException& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if (choice == 3) {
                running = false;
            }
        }
        // admin menu
        else if (currentUser->getRole() == "Admin") {
            cout << "\n--- Admin Menu (" << currentUser->getUsername() << ") ---" << endl;
            cout << "1. Browse Listings" << endl;
            cout << "2. Search by Title" << endl;
            cout << "3. Sort by Price" << endl;
            cout << "4. Sort by Title" << endl;
            cout << "5. View All Users" << endl;
            cout << "6. Remove Listing" << endl;
            cout << "7. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                marketplace.displayAllListings();
            }
            else if (choice == 2) {
                string title;
                cout << "Enter title: ";
                getline(cin, title);
                marketplace.searchByTitle(title);
            }
            else if (choice == 3) {
                marketplace.sortByPrice();
                marketplace.displayAllListings();
            }
            else if (choice == 4) {
                marketplace.sortByTitle();
                marketplace.displayAllListings();
            }
            else if (choice == 5) {
                marketplace.displayAllUsers();
            }
            else if (choice == 6) {
                int id;
                cout << "Listing ID to remove: ";
                cin >> id;
                cin.ignore();
                try {
                    marketplace.removeListing(id);
                } catch (const MarketplaceException& e) {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if (choice == 7) {
                currentUser = nullptr;
                cout << "Logged out." << endl;
            }
        }
        // regular user menu
        else {
            cout << "\n--- Menu (" << currentUser->getUsername() << ") ---" << endl;
            cout << "1. Browse Listings" << endl;
            cout << "2. Search by Title" << endl;
            cout << "3. Sort by Price" << endl;
            cout << "4. Sort by Title" << endl;
            cout << "5. Create Listing" << endl;
            cout << "6. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                marketplace.displayAllListings();
            }
            else if (choice == 2) {
                string title;
                cout << "Enter title: ";
                getline(cin, title);
                marketplace.searchByTitle(title);
            }
            else if (choice == 3) {
                marketplace.sortByPrice();
                marketplace.displayAllListings();
            }
            else if (choice == 4) {
                marketplace.sortByTitle();
                marketplace.displayAllListings();
            }
            else if (choice == 5) {
                string title, desc, brand, category;
                double price;
                cout << "Item title: ";
                getline(cin, title);
                cout << "Description: ";
                getline(cin, desc);
                cout << "Brand: ";
                getline(cin, brand);
                cout << "Category: ";
                getline(cin, category);
                cout << "Price (EUR): ";
                cin >> price;
                cin.ignore();

                try {
                    if (price < 0)
                        throw MarketplaceException("Price cannot be negative.");

                    Item item(title, desc, brand, category);
                    Listing listing(0, price, currentUser->getUsername(), item);
                    marketplace.addListing(listing);
                } catch (const MarketplaceException& e) { 
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if (choice == 6) {
                currentUser = nullptr;
                cout << "Logged out." << endl;
            }
        }
    }

    marketplace.saveToFile();
    cout << "Goodbye!" << endl;
    return 0;
}
