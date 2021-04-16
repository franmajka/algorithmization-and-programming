#include <iostream>
#include <exception>

#define PRINT_ERROR(reason) \
    std::cerr << "An error occured in file " << __FILE__ \
    << " in function " << __func__ << " on line " << __LINE__ << ". " \
    << "Reason is: " << (reason) << std::endl

using namespace std;

class ZeroDivisionError : public exception {
    virtual const char* what() const throw()
    {
        return "Division by zero";
    }
};

float divide(const int& dividable, const int& divisor) {
    if (!divisor) throw ZeroDivisionError();

    return (float)dividable / divisor;
}

int main()
{
   

    float a;

    try {
        a = divide(10, 0);
        cout << a;
    }
    catch (exception& e) {
        PRINT_ERROR(e.what());
    }

    return 0;
}
