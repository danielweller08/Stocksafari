#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>

using namespace StockSafari;

// Test that quantity is too high
TEST(ControllerTest, Buy_Stock) {
    // Account person1 = Account("Daniel", "1234566");

    // Controller c;
    // c.createaccount();
    // c.deposit(100);
    // c.set_stockValue("APPL", 10);
}

TEST(ControllerTest, CreateAccountTest) {
    Controller c;
    Account& account = c.create_account("Alice", "qwerty123");

    EXPECT_EQ(account.get_username(), "Alice");
    EXPECT_EQ(account.get_password(), "qwerty123");
    EXPECT_THROW(c.create_account("Alice", "asdf"), invalid_argument);
}

TEST(ControllerTest, GetAccountTest) {
    Controller c;
    Account& account = c.create_account("Alice", "qwerty123");
    Account& user = c.get_account("Alice");

    EXPECT_EQ(user.get_username(), "Alice");
    EXPECT_EQ(user.get_password(), "qwerty123");
    EXPECT_THROW(c.get_account("Bob"), invalid_argument);
}

TEST(ControllerTest, Authentication_Works) {
    Controller c;
    auto token = c.generate_token("TEST");
    auto result = c.decode_token(token);
    ASSERT_EQ("TEST", result);
}