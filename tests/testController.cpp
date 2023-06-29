#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>

using namespace StockSafari;

TEST(TestController, CreateAccountTest) {
    Controller c;
    Account account = c.create_account("Alice", "qwerty123");

    EXPECT_EQ(account.get_username(), "Alice");
    EXPECT_EQ(account.get_password(), "qwerty123");
    EXPECT_THROW(c.create_account("Alice", "asdf"), invalid_argument);
}

TEST(TestController, GetAccountTest) {
    Controller c;
    Account account = c.create_account("Alice", "qwerty123");
    Account user = c.get_account("Alice");

    EXPECT_EQ(user.get_username(), "Alice");
    EXPECT_EQ(user.get_password(), "qwerty123");
    EXPECT_THROW(c.get_account("Bob"), invalid_argument);
}