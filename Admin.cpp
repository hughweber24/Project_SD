#include "Admin.h"

Admin::Admin() : User() { // defines default constructor
    adminLevel = "basic";
}

Admin::Admin(int id, string username, string password, string email, string level) // defines parameterized constructor
    : User(id, username, password, email) {
    adminLevel = level;
}

void Admin::displayDetails() { // defines method to display admin details, overrides User's displayDetails
    cout << "Admin: " << getUsername() << " | Email: " << getEmail()
         << " | Level: " << getAdminLevel() << endl;
}
