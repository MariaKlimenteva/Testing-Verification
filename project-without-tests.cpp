#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

class OrderManager {
public:
    double calculateFinalPrice(double basePrice, int customerAge, bool hasCoupon) {
        if (basePrice < 0) {
            throw std::invalid_argument("Price cannot be negative");
        }

        double discount = 0.0;

        if (customerAge >= 60) {
            discount = 0.20;
        } else if (hasCoupon) {
            discount = 0.10;
        }

        return basePrice * (1.0 - discount);
    }

    bool isValidUsername(const std::string& username) {
        if (username.empty() || username.length() < 3) {
            return false;
        }

        for (char c : username) {
            if (!isalnum(c)) {
                return false;
            }
        }

        return true;
    }

    int safeDivide(int a, int b) {
        if (b == 0) {
            return -999;
        }
        return a / b;
    }
};

int main() {
    OrderManager manager;
    std::cout << manager.calculateFinalPrice(100, 65, false) << std::endl;
    return 0;
}