#ifndef _ADMIN_
#define _ADMIN_
#include "User.h"

class Admin : public User { // defines admin as a class that inherits from User
private:
    string adminLevel;

public:
    Admin(); // Default constructor
    Admin(int id, string username, string password, string email, string level); // Parameterized constructor

    void setAdminLevel(string l) { adminLevel = l; }
    string getAdminLevel() const { return adminLevel; }

    void displayDetails() override;
    string getRole() const override { return "Admin"; }
};

#endif
