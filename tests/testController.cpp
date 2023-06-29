#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>
#include <iostream>

using namespace StockSafari;

TEST(ControllerTest, Buy_Stock) {
    Controller c;
    std::string token = c.registerAccount("Daniel", "123456");
    Account& person1 = c.get_account("Daniel", token);
    std::string token = c.registerAccount("Daniel", "123456");
    Account& person1 = c.get_account("Daniel", token);

    c.set_stockValue("APPL", 10);

    c.deposit(person1.get_username(), 10, token);
    EXPECT_THROW(c.buy_stock("APPL", 2, person1.get_username(), token) , invalid_argument);
    c.deposit(person1.get_username(), 10, token);
    EXPECT_THROW(c.buy_stock("APPL", 2, person1.get_username(), token) , invalid_argument);

    c.deposit(person1.get_username(), 10, token);
    Account& acc = c.buy_stock("APPL", 2, person1.get_username(), token);
    c.deposit(person1.get_username(), 10, token);
    Account& acc = c.buy_stock("APPL", 2, person1.get_username(), token);
    EXPECT_EQ(acc.get_balance(), 0);
}

TEST(ControllerTest, Sell_Stock) {
    Controller c;
    std::string token = c.registerAccount("Daniel", "123456");
    Account& person1 = c.get_account("Daniel", token);

    c.set_stockValue("APPL", 10);

    c.deposit(person1.get_username(), 10, token);

    EXPECT_THROW(c.sell_stock("APPL", 1, person1.get_username(), token) , invalid_argument);

    Account& acc = c.buy_stock("APPL", 1, person1.get_username(), token);
    EXPECT_EQ(acc.get_balance(), 0);
    acc = c.sell_stock("APPL", 1, person1.get_username(), token);
    EXPECT_EQ(acc.get_balance(), 10);
}

TEST(ControllerTest, CreateAccountTest) {
    Controller c;
    string token = c.registerAccount("Alice", "qwerty123");
    Account& account = c.get_account("Alice", token);
    EXPECT_EQ(account.get_username(), "Alice");
    EXPECT_EQ(account.get_password(), "qwerty123");
    EXPECT_THROW(c.registerAccount("Alice", token), invalid_argument);
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