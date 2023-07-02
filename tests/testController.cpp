#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>
#include <iostream>

using namespace StockSafari;

TEST(ControllerTest, Register_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    Account user = c.get_account(token);

    ASSERT_EQ("User", user.get_username());
}

TEST(ControllerTest, Register_ExistingUser_Throws) {
    Controller c;
    c.registerAccount("User", "password");

    ASSERT_ANY_THROW(c.registerAccount("User", "differentPassword"));
}

TEST(ControllerTest, Login_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    ASSERT_NO_THROW(c.loginAccount("User", "password"));
}

TEST(ControllerTest, GetAccount_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    ASSERT_NO_THROW(c.get_account(token));
}

TEST(ControllerTest, Deposit_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    EXPECT_NO_THROW(c.deposit("User", 100, token));

    ASSERT_EQ(100, c.get_account(token).get_balance());
}

TEST(ControllerTest, Withdraw_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.deposit("User", 100, token);
    EXPECT_NO_THROW(c.withdraw("User", 50, token));

    ASSERT_EQ(50, c.get_account(token).get_balance());
}

TEST(ControllerTest, Withdraw_LowBalance_Throws) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.deposit("User", 50, token);
    ASSERT_ANY_THROW(c.withdraw("User", 100, token));
}

TEST(ControllerTest, BuyStock_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit("User", 100, token);
    EXPECT_NO_THROW(c.buy_stock("APPL", 10, token));

    auto portfolio = c.get_account(token).get_portfolio();

    ASSERT_EQ(1, portfolio.size());

    EXPECT_NE(std::chrono::time_point<std::chrono::system_clock>{}, portfolio[0].get_buyDate());
    EXPECT_EQ(10, portfolio[0].get_buyValue());
    EXPECT_EQ(10, portfolio[0].get_quantity());
    EXPECT_EQ(false, portfolio[0].get_sold());
    EXPECT_EQ("APPL", portfolio[0].get_stock().get_stockId());
}

TEST(ControllerTest, BuyStock_DecreasesBalance) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit("User", 100, token);
    EXPECT_NO_THROW(c.buy_stock("APPL", 10, token));

    ASSERT_EQ(0, c.get_account(token).get_balance());
}

TEST(ControllerTest, BuyStock_LowBalance_Throws) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    ASSERT_ANY_THROW(c.buy_stock("APPL", 10, token));
}

TEST(ControllerTest, SellStock_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit("User", 100, token);

    c.buy_stock("APPL", 10, token);

    ASSERT_NO_THROW(c.sell_stock("APPL", 10, token));

    AccountStock accountStock = c.get_account(token).get_portfolio()[0];

    EXPECT_NE(std::chrono::time_point<std::chrono::system_clock>{}, accountStock.get_sellDate());
    EXPECT_EQ(10, accountStock.get_sellValue());
    EXPECT_EQ(true, accountStock.get_sold());
}

TEST(ControllerTest, SellStock_Partially_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit("User", 100, token);

    c.buy_stock("APPL", 10, token);

    c.set_stockValue("APPL", 5);

    ASSERT_NO_THROW(c.sell_stock("APPL", 5, token));

    auto portfolio = c.get_account(token).get_portfolio();

    ASSERT_EQ(2, portfolio.size());

    EXPECT_EQ(5, portfolio[0].get_quantity());
    EXPECT_EQ(5, portfolio[1].get_quantity());
    EXPECT_EQ(10, portfolio[1].get_buyValue());
    EXPECT_EQ(5, portfolio[1].get_sellValue());
    EXPECT_EQ("APPL", portfolio[1].get_stock().get_stockId());
    EXPECT_EQ(portfolio[0].get_buyDate(), portfolio[1].get_buyDate());
    EXPECT_NE(std::chrono::time_point<std::chrono::system_clock>{}, portfolio[1].get_sellDate());
    EXPECT_EQ(true, portfolio[1].get_sold());
}

TEST(ControllerTest, Authentication_Works) {
    Controller c;
    auto token = c.generate_token("User");
    auto result = c.try_decode_token(token);
    ASSERT_EQ("User", result);
}