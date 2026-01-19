#include <gtest/gtest.h>
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

TEST(OrderManagerTest, CalculateFinalPriceNegativeBasePrice) {
    OrderManager manager;
    ASSERT_THROW(manager.calculateFinalPrice(-100, 65, false), std::invalid_argument);
}

TEST(OrderManagerTest, CalculateFinalPriceCustomerAge60OrGreater) {
    OrderManager manager;
    double result = manager.calculateFinalPrice(100, 65, false);
    ASSERT_DOUBLE_EQ(80, result);
}

TEST(OrderManagerTest, CalculateFinalPriceCustomerAgeLessThan60WithCoupon) {
    OrderManager manager;
    double result = manager.calculateFinalPrice(100, 20, true);
    ASSERT_DOUBLE_EQ(90, result);
}

TEST(OrderManagerTest, CalculateFinalPriceCustomerAgeLessThan60WithoutCoupon) {
    OrderManager manager;
    double result = manager.calculateFinalPrice(100, 20, false);
    ASSERT_DOUBLE_EQ(100, result);
}

TEST(OrderManagerTest, IsValidUsernameEmptyString) {
    OrderManager manager;
    bool result = manager.isValidUsername("");
    ASSERT_FALSE(result);
}

TEST(OrderManagerTest, IsValidUsernameTooShortString) {
    OrderManager manager;
    bool result = manager.isValidUsername("ab");
    ASSERT_FALSE(result);
}

TEST(OrderManagerTest, IsValidUsernameValidString) {
    OrderManager manager;
    bool result = manager.isValidUsername("abc");
    ASSERT_TRUE(result);
}

TEST(OrderManagerTest, IsValidUsernameStringWithNonAlphanumericCharacters) {
    OrderManager manager;
    bool result = manager.isValidUsername("ab!c");
    ASSERT_FALSE(result);
}

TEST(OrderManagerTest, SafeDivideDivideByZero) {
    OrderManager manager;
    int result = manager.safeDivide(10, 0);
    ASSERT_EQ(-999, result);
}

TEST(OrderManagerTest, SafeDivideValidDivision) {
    OrderManager manager;
    int result = manager.safeDivide(10, 2);
    ASSERT_EQ(5, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}