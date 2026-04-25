#include "Marketplace.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;
 
int main(){
    Marketplace marketplace;
    marketplace.loadFromFile();
 
    cout << "\n=============================" << endl;
    cout << "   Online Marketplace" << endl;
    cout << "=============================" << endl;
 
    int choice;
    bool running = true;
    User* currentUser = nullptr;
    string input; // reuse this for string inputs
 
    while(running){
 
        if(currentUser == nullptr){ 
            // not logged in
            cout << "\n1. Register\n2. Login\n3. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;
 
            // fix for infinite loop when user types a letter instead of number
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, enter a number." << endl;
                continue;
            }
            cin.ignore();
 
            if(choice == 1){
                string username, password, email, role;
                cout << "Username: "; getline(cin, username);
                cout << "Password: "; getline(cin, password);
                cout << "Email: "; getline(cin, email);
                cout << "Role (User/Admin): "; getline(cin, role);
                try{
                    marketplace.registerUser(username, password, email, role);
                } catch(const MarketplaceException& e){
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if(choice == 2){
                string username, password;
                cout << "Username: "; getline(cin, username);
                cout << "Password: "; getline(cin, password);
                try{
                    currentUser = marketplace.loginUser(username, password);
                } catch(const MarketplaceException& e){
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if(choice == 3){
                running = false;
            }
        }
 
        else if(currentUser->getRole() == "Admin"){
            // admin menu
            cout << "\n--- Admin (" << currentUser->getUsername() << ") ---" << endl;
            cout << "1. Browse\n2. Search\n3. Sort Price\n4. Sort Title\n5. Users\n6. Remove Listing\n7. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
 
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, enter a number." << endl;
                continue;
            }
            cin.ignore();
 
            if(choice == 1){
                marketplace.displayAllListings();
            }
            else if(choice == 2){
                cout << "Title: "; getline(cin, input);
                marketplace.searchByTitle(input);
            }
            else if(choice == 3){
                marketplace.sortByPrice();
                marketplace.displayAllListings();
            }
            else if(choice == 4){
                marketplace.sortByTitle();
                marketplace.displayAllListings();
            }
            else if(choice == 5){
                marketplace.displayAllUsers();
            }
            else if(choice == 6){
                int id;
                cout << "Listing ID: "; cin >> id;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input." << endl;
                    continue;
                }
                cin.ignore();
                try{
                    marketplace.removeListing(id);
                } catch(const MarketplaceException& e){
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if(choice == 7){
                currentUser = nullptr;
                cout << "Logged out." << endl;
            }
        }
 
        else{
            // normal user menu
            cout << "\n--- Menu (" << currentUser->getUsername() << ") ---" << endl;
            cout << "1. Browse\n2. Search\n3. Sort Price\n4. Sort Title\n5. Create Listing\n6. Delete My Listing\n7. Logout" << endl;
            cout << "Choice: ";
            cin >> choice;
 
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, enter a number." << endl;
                continue;
            }
            cin.ignore();
 
            if(choice == 1){
                marketplace.displayAllListings();
            }
            else if(choice == 2){
                cout << "Title: "; getline(cin, input);
                marketplace.searchByTitle(input);
            }
            else if(choice == 3){
                marketplace.sortByPrice();
                marketplace.displayAllListings();
            }
            else if(choice == 4){
                marketplace.sortByTitle();
                marketplace.displayAllListings();
            }
            else if(choice == 5){
                string title, desc, brand, category;
                double price;
                cout << "Title: "; getline(cin, title);
                cout << "Description: "; getline(cin, desc);
                cout << "Brand: "; getline(cin, brand);
                cout << "Category: "; getline(cin, category);
                cout << "Price: "; cin >> price;
 
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid price." << endl;
                    continue;
                }
                cin.ignore();
 
                try{
                    if(price < 0)
                        throw MarketplaceException("Price cant be negative.");
                    Item item(title, desc, brand, category);
                    Listing listing(0, price, currentUser->getUsername(), item);
                    marketplace.addListing(listing);
                } catch(const MarketplaceException& e){
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if(choice == 6){
                int id;
                cout << "Listing ID: "; cin >> id;
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input." << endl;
                    continue;
                }
                cin.ignore();
                try{
                    marketplace.removeListingUser(id, currentUser->getUsername());
                } catch(const MarketplaceException& e){
                    cerr << "Error: " << e.what() << endl;
                }
            }
            else if(choice == 7){
                currentUser = nullptr;
                cout << "Logged out." << endl;
            }
        }
    }
 
    marketplace.saveToFile();
    cout << "Goodbye!" << endl;
    return 0;
}
