#ifndef _MARKETPLACEEXCEPTION_
#define _MARKETPLACEEXCEPTION_
#include <exception>
#include <string>
using namespace std;

class MarketplaceException : public exception {
private:
    string message;

public:
    MarketplaceException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif
