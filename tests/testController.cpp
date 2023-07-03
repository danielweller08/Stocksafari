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

    EXPECT_NO_THROW(c.deposit(100, token));

    ASSERT_EQ(100, c.get_account(token).get_balance());
}

TEST(ControllerTest, Withdraw_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.deposit(100, token);
    EXPECT_NO_THROW(c.withdraw(50, token));

    ASSERT_EQ(50, c.get_account(token).get_balance());
}

TEST(ControllerTest, Withdraw_LowBalance_Throws) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.deposit(50, token);
    ASSERT_ANY_THROW(c.withdraw(100, token));
}

TEST(ControllerTest, BuyStock_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);
    ASSERT_NO_THROW(c.buy_stock("APPL", 10, token));

    ASSERT_EQ(0, c.get_account(token).get_balance());

    auto portfolio = c.get_account(token).get_portfolio();

    ASSERT_EQ(1, portfolio.size());
    ASSERT_EQ(1, portfolio[0].get_details().size());

    ASSERT_NE(std::chrono::time_point<std::chrono::system_clock>{}, portfolio[0].get_details()[0].get_buyDate());
    ASSERT_EQ(10, portfolio[0].get_details()[0].get_buyValue());
    ASSERT_EQ(10, portfolio[0].get_details()[0].get_quantity());
    ASSERT_EQ(false, portfolio[0].get_details()[0].get_sold());
    ASSERT_EQ("APPL", portfolio[0].get_stock().get_stockId());
}

TEST(ControllerTest, BuyStock_Multiple_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);
    ASSERT_NO_THROW(c.buy_stock("APPL", 5, token));
    ASSERT_NO_THROW(c.buy_stock("APPL", 5, token));

    auto portfolio = c.get_account(token).get_portfolio();

    ASSERT_EQ(1, portfolio.size());
    ASSERT_EQ(2, portfolio[0].get_details().size());
}

TEST(ControllerTest, BuyStock_LowBalance_Throws) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    ASSERT_ANY_THROW(c.buy_stock("APPL", 10, token));
}

TEST(ControllerTest, BuyStock_NegativeQuantity_Throws) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);
    ASSERT_ANY_THROW(c.buy_stock("APPL", -10, token));
}

TEST(ControllerTest, GetAccount_StockValueIncrease_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);
    c.buy_stock("APPL", 10, token);

    auto account = c.get_account(token);

    ASSERT_EQ(0, account.get_portfolio()[0].get_total_increase());
    ASSERT_EQ(0, account.get_portfolio()[0].get_percental_increase());

    c.set_stockValue("APPL", 20);

    ASSERT_EQ(100, account.get_portfolio()[0].get_total_increase());
    ASSERT_EQ(100, account.get_portfolio()[0].get_percental_increase());
}

TEST(ControllerTest, SellStock_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);

    c.buy_stock("APPL", 5, token);
    c.buy_stock("APPL", 5, token);

    ASSERT_NO_THROW(c.sell_stock("APPL", 10, token));

    ASSERT_EQ(100, c.get_account(token).get_balance());

    auto applePortfolio = c.get_account(token).get_portfolio()[0];

    ASSERT_EQ(2, applePortfolio.get_details().size());

    ASSERT_EQ(true, applePortfolio.get_details()[0].get_sold());
    ASSERT_EQ(true, applePortfolio.get_details()[1].get_sold());
    ASSERT_EQ(10, applePortfolio.get_details()[0].get_sellValue());
    ASSERT_EQ(10, applePortfolio.get_details()[1].get_sellValue());
    ASSERT_NE(std::chrono::time_point<std::chrono::system_clock>{}, applePortfolio.get_details()[0].get_sellDate());
    ASSERT_NE(std::chrono::time_point<std::chrono::system_clock>{}, applePortfolio.get_details()[1].get_sellDate());
}

TEST(ControllerTest, SellStock_Partially_Works) {
    Controller c;
    std::string token = c.registerAccount("User", "password");

    c.set_stockValue("APPL", 10);

    c.deposit(100, token);

    c.buy_stock("APPL", 3, token);
    c.buy_stock("APPL", 7, token);

    ASSERT_NO_THROW(c.sell_stock("APPL", 5, token));

    auto applePortfolio = c.get_account(token).get_portfolio()[0];

    ASSERT_EQ(3, applePortfolio.get_details().size());

    ASSERT_EQ(true, applePortfolio.get_details()[0].get_sold());
    ASSERT_EQ(false, applePortfolio.get_details()[1].get_sold());
    ASSERT_EQ(5, applePortfolio.get_details()[1].get_quantity());
    ASSERT_EQ(2, applePortfolio.get_details()[2].get_quantity());
    ASSERT_EQ(true, applePortfolio.get_details()[2].get_sold());
}

TEST(ControllerTest, Authentication_Works) {
    Controller c;
    auto token = c.generate_token("User");
    auto result = c.try_decode_token(token);
    ASSERT_EQ("User", result);
}