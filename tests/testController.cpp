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
    string token = c.registerAccount("Alice", "qwerty123");
    Account& account = c.get_account("Alice", token);
    EXPECT_EQ(account.get_username(), "Alice");
    EXPECT_EQ(account.get_password(), "qwerty123");
    EXPECT_THROW(c.registerAccount("Alice", "asdf"), invalid_argument);
}

TEST(ControllerTest, GetAccountTest) {
    Controller c;
    string token = c.registerAccount("Alice", "qwerty123");
    Account& user = c.get_account("Alice", token);

    EXPECT_EQ(user.get_username(), "Alice");
    EXPECT_EQ(user.get_password(), "qwerty123");
    EXPECT_THROW(c.get_account("Bob", token), invalid_argument);
}

TEST(ControllerTest, DepositTest) {
    Controller c;
    string token = c.registerAccount("Alice", "qwerty123");
    Account& account = c.get_account("Alice", token);

    c.deposit("Alice", 100, token);
    EXPECT_EQ(100, account.get_balance());
    c.deposit("Alice", 42, token);
    EXPECT_EQ(142, account.get_balance());

    EXPECT_THROW(c.deposit("Bob", 999, token), invalid_argument);
}

TEST(ControllerTest, WithdrawTest) {
    Controller c;
    string token = c.registerAccount("Alice", "qwerty123");
    Account& account = c.get_account("Alice", token);
     
    EXPECT_THROW(c.withdraw("Alice", 100, token), invalid_argument);
    EXPECT_THROW(c.withdraw("Bob", 100, token), invalid_argument);
    
    c.deposit("Alice", 300, token);
    c.withdraw("Alice", 100, token);
    EXPECT_EQ(200, account.get_balance());
    c.withdraw("Alice", 200, token);
    EXPECT_EQ(0, account.get_balance());
}

TEST(ControllerTest, Authentication_Works) {
    Controller c;
    auto token = c.generate_token("TEST");
    auto result = c.try_decode_token(token);
    ASSERT_EQ("TEST", result);
}