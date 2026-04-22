#include <iostream>
#include <vector>
#include "User.h"
#include "Item.h"
#include "Admin (1).h"

using namespace std;

int main() {
    cout << "=== Testing User class ===" << endl;
    User u1;
    User u2(101, "alice", "pass123", "alice@email.com");

    u1.displayDetails();
    u2.displayDetails();

    cout << "\nUpdating default user with setters..." << endl;
    u1.setUserId(102);
    u1.setUsername("bob");
    u1.setPassword("secret");
    u1.setEmail("bob@email.com");
    u1.displayDetails();

    cout << "\nComparing users with operator==" << endl;
    User u3(103, "alice", "differentPass", "another@email.com");
    cout << "u2 == u3 ? " << ((u2 == u3) ? "true" : "false") << endl;
    cout << "u1 == u2 ? " << ((u1 == u2) ? "true" : "false") << endl;

    cout << "\n=== Testing Admin class ===" << endl;
    Admin a1;
    Admin a2(201, "charlie", "adminpass", "charlie@site.com", "super");

    a1.displayDetails();
    a2.displayDetails();

    cout << "\nUpdating default admin with setters..." << endl;
    a1.setUserId(202);
    a1.setUsername("diana");
    a1.setPassword("dpass");
    a1.setEmail("diana@site.com");
    a1.setAdminLevel("manager");
    a1.displayDetails();

    cout << "\n=== Testing polymorphism ===" << endl;
    vector<User*> users;
    users.push_back(&u2);
    users.push_back(&a2);

    for (User* user : users) {
        user->displayDetails();
        cout << "Role from getRole(): " << user->getRole() << endl;
    }

    cout << "\n=== Testing Item class ===" << endl;
    Item item1;
    Item item2("Laptop", "15-inch laptop with 16GB RAM", "Lenovo", "Electronics");

    item1.displayDetails();
    item2.displayDetails();

    cout << "\nUpdating default item with setters..." << endl;
    item1.setTitle("Shoes");
    item1.setDescription("Running shoes with cushioned sole");
    item1.setBrand("Nike");
    item1.setCategory("Footwear");
    item1.displayDetails();

    cout << "\n=== All tests finished ===" << endl;
    return 0;
}
