#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>

using namespace StockSafari;

TEST(ControllerTest, Buy_Stock) {
    Controller c;
    std::string token = c.registerAccount("Daniel", "123456");
    Account& person1 = c.get_account("Daniel", token);

    c.set_stockValue("APPL", 10);

    c.deposit(person1.get_username(), 10, token);
    EXPECT_THROW(c.buy_stock("APPL", 2, person1.get_username(), token) , invalid_argument);

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
    Account& account = c.registerAccount("Alice", "qwerty123");

    EXPECT_EQ(account.get_username(), "Alice");
    EXPECT_EQ(account.get_password(), "qwerty123");
    EXPECT_THROW(c.registerAccount("Alice", "asdf"), invalid_argument);
}

TEST(ControllerTest, GetAccountTest) {
    Controller c;
    Account& account = c.registerAccount("Alice", "qwerty123");
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