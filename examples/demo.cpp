#include <stocksafari/StockValue.hpp>
#include <stocksafari/Stock.hpp>
#include <stocksafari/AccountStock.hpp>
#include <stocksafari/Account.hpp>
#include <stocksafari/Controller.hpp>
#include <iostream>


using namespace StockSafari;

int main() {
    StockValue value = StockValue(10);

    Controller c;

    c.set_stockValue("APPL", 1);

    string token = c.registerAccount("Damyan", "1234");

    c.deposit("Damyan", 500, token);
    c.withdraw("Damyan", 1, token);

    // Token test.
    token = c.generate_token("Test_Username");
    std::cout << "Token: " << token << std::endl;
    std::cout << "Username after verification: " << c.try_decode_token(token) << std::endl;
}