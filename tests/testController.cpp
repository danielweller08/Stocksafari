#include <gtest/gtest.h>
#include <stocksafari/Controller.hpp>

using namespace StockSafari;

TEST(ControllerTest, Authentication_Works) {
    Controller c;
    auto token = c.generate_token("TEST");
    auto result = c.decode_token(token);
    ASSERT_EQ("TEST", result);
}