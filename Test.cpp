#include <iostream>
#include <fstream>
#include "Marketplace.h"

using namespace std;

int passed = 0;
int failed = 0;

void check(string name, bool condition){
    if(condition){ cout << "  PASS: " << name << endl; passed++; }
    else { cout << "  FAIL: " << name << endl; failed++; }
}

// ============================================================
// UNIT TESTS - testing individual classes in isolation
// ============================================================


void unitTests(){
    cout << "\n=== UNIT TESTS ===" << endl;



    // --- User ---
    cout << "\n-- User --" << endl;
    User u;
    check("Default constructor", u.getUsername() == "unknown" && u.getUserId() == 0);
    User u2(1, "dave", "pass", "dave@email.com");
    check("Param constructor", u2.getUsername() == "dave" && u2.getEmail() == "dave@email.com");
    check("getRole returns User", u2.getRole() == "User");
    User u3(2, "dave", "other", "other@email.com");
    check("== operator same username", u2 == u3);




    // --- Admin ---
    cout << "\n-- Admin --" << endl;
    Admin a(1, "admin1", "pass", "admin@test.com", "super");
    check("Param constructor", a.getUsername() == "admin1" && a.getAdminLevel() == "super");
    check("getRole returns Admin", a.getRole() == "Admin");
    User* ptr = new Admin(2, "adm", "p", "a@a.com", "basic");
    check("Polymorphism - User* to Admin", ptr->getRole() == "Admin");
    delete ptr;




    // --- Item ---
    cout << "\n-- Item --" << endl;
    Item i;
    check("Default constructor", i.getTitle() == "untitled");
    Item i2("Shoes", "Nice shoes", "Nike", "Footwear");
    check("Param constructor", i2.getTitle() == "Shoes" && i2.getBrand() == "Nike");





    // --- Listing ---
    cout << "\n-- Listing --" << endl;
    Item item("Shoes", "Nice", "Nike", "Footwear");
    Listing l(1, 99.99, "seller1", item);
    check("Param constructor", l.getItemTitle() == "Shoes" && l.getPrice() == 99.99);

    Listing copy(l);
    copy.setPrice(50.0);
    check("Copy constructor - deep copy", l.getPrice() == 99.99 && copy.getPrice() == 50.0);

    Listing l2(2, 20.0, "s", Item("Hat", "d", "Adidas", "Acc"));
    l2 = l;
    l2.setPrice(10.0);
    check("Assignment operator - deep copy", l.getPrice() == 99.99 && l2.getPrice() == 10.0);

    l = l;
    check("Self assignment safe", l.getItemTitle() == "Shoes");

    Listing cheap(1, 10.0, "s", Item("A","d","b","c"));
    Listing expensive(2, 100.0, "s", Item("B","d","b","c"));
    check("< operator", cheap < expensive);




    // --- MarketplaceException ---
    cout << "\n-- MarketplaceException --" << endl;
    MarketplaceException e("Test error");
    check("what() returns message", string(e.what()) == "Test error");
    bool caught = false;
    try { throw MarketplaceException("test"); }
    catch(const exception& e){ caught = true; }
    check("Caught as std::exception", caught);

   
   
   
   
   
    // --- Marketplace ---
    cout << "\n-- Marketplace --" << endl;
    Marketplace mp;
    User* reg = mp.registerUser("dave", "pass", "d@d.com", "user");
    check("Register works", reg != nullptr && reg->getUsername() == "dave");

    bool threw = false;
    try { mp.registerUser("dave", "p", "x@x.com", "user"); }
    catch(const MarketplaceException& e){ threw = true; }
    check("Duplicate username throws", threw);

    User* log = mp.loginUser("dave", "pass");
    check("Login works", log->getUsername() == "dave");

    threw = false;
    try { mp.loginUser("dave", "wrong"); }
    catch(const MarketplaceException& e){ threw = true; }
    check("Wrong password throws", threw);

    Item shoe("Shoe", "d", "Nike", "Footwear");
    Listing listing(0, 85.0, "dave", shoe);
    mp.addListing(listing);
    check("Search finds listing", mp.searchByTitle("Shoe") != -1);
    check("Search misses non-existent", mp.searchByTitle("Nope") == -1);
}





// ============================================================
// FUNCTIONAL TESTS - testing workflows across multiple classes
// ============================================================

void functionalTests(){
    cout << "\n=== FUNCTIONAL TESTS ===" << endl;



    // register then login
    cout << "\n-- Register and Login --" << endl;
    Marketplace mp;
    mp.registerUser("alice", "pass1", "alice@test.com", "user");
    User* u = mp.loginUser("alice", "pass1");
    check("Register then login works", u->getUsername() == "alice");



    // create then search
    cout << "\n-- Create and Search --" << endl;
    Item item("Watch", "Vintage", "Omega", "Watches");
    Listing listing(0, 250.0, "alice", item);
    mp.addListing(listing);
    check("Found after creation", mp.searchByTitle("Watch") != -1);



    // sort then search
    cout << "\n-- Sort --" << endl;
    mp.sortByPrice();
    check("Search works after sort", mp.searchByTitle("Watch") != -1);



    // save and reload
    cout << "\n-- Save and Load --" << endl;
    {
        Marketplace m("test_tmp.txt");
        m.registerUser("bob", "pass", "bob@test.com", "user");
        Item it("Jacket", "Leather", "Zara", "Clothing");
        Listing ls(0, 120.0, "bob", it);
        m.addListing(ls);
        m.saveToFile();
    }

    Marketplace m2("test_tmp.txt");
    m2.loadFromFile();
    check("User persists", m2.usernameExists("bob"));
    check("Listing persists", m2.searchByTitle("Jacket") != -1);
    remove("test_tmp.txt");


    // max listings
    cout << "\n-- Max Listings --" << endl;
    Marketplace mp3;
    for(int i = 0; i < mp3.getMaxListing(); i++){
        Item it("Item" + to_string(i), "d", "b", "c");
        Listing ls(0, 10.0, "s", it);
        mp3.addListing(ls);
    }


    Item extra("Extra", "d", "b", "c");
    Listing extraL(0, 10.0, "s", extra);
    mp3.addListing(extraL);
    check("Rejected when full", mp3.searchByTitle("Extra") == -1);



    // delete own listing
    cout << "\n-- Delete Listing --" << endl;
    Marketplace mp4;
    Item it("MyItem", "d", "b", "c");
    Listing ls(0, 10.0, "dave", it);
    mp4.addListing(ls);
    mp4.removeListingUser(1, "dave");
    check("Owner can delete own", mp4.searchByTitle("MyItem") == -1);



    bool threw = false;
    Item it2("Other", "d", "b", "c");
    Listing ls2(0, 10.0, "sarah", it2);
    mp4.addListing(ls2);
    try { mp4.removeListingUser(2, "dave"); }
    catch(const MarketplaceException& e){ threw = true; }
    check("Cannot delete others listing", threw);
}




int main(){
    unitTests();
    functionalTests();
    cout << "\n================================" << endl;
    cout << "Results: " << passed << " passed, " << failed << " failed" << endl;
    cout << "================================" << endl;
    cin.get();
    return 0;
} 
