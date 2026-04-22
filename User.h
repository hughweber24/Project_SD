#ifndef _USER_
#define _USER_
#include <string>
#include <iostream>
using namespace std;

class User {
private:
    int userId;
    string username;
    string password;
    string email;

public:
    User();   // Default constructor
    User(int id, string username, string password, string email);  // Parameterized constructor
    virtual ~User(); // Virtual destructor

    void setUserId(int id) { userId = id; }
    int getUserId() const { return userId; }
    void setUsername(string u) { username = u; }
    string getUsername() const { return username; }
    void setPassword(string p) { password = p; }
    string getPassword() const { return password; }
    void setEmail(string e) { email = e; }
    string getEmail() const { return email; }

    virtual void displayDetails();  // virtual void to display details
    virtual string getRole() const { return "User"; } //virtual function to return the role of the object

    friend bool operator==(const User& a, const User& b); // declares an overloaded operator as a friend function
};

#endif
