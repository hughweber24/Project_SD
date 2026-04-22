#include "User.h"

User::User() {  // defines default constructor
    userId = 0;
    username = "unknown";
    password = "";
    email = "";
}

User::User(int id, string u, string p, string e) { // defines parameterized constructor
    userId = id;
    username = u;
    password = p;
    email = e;
}

User::~User() {} // defines virtual destructor

void User::displayDetails() { // defines method to display user details
    cout << "User: " << getUsername() << " | Email: " << getEmail()
         << " | Role: " << getRole() << endl; // getRole is virtual
}

bool operator==(const User& a, const User& b) {
    return (a.username == b.username);
}
