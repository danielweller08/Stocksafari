#include <stocksafari/Stock.hpp>
#include <stocksafari/Account.hpp>
#include <stocksafari/Controller.hpp>
#include <iostream>


using namespace StockSafari;

int main() {
    Controller c;

    string token = c.registerAccount("User", "passwort");

    c.deposit(1000, token);

    c.buy_stock("APPL", 1, token);
    c.sell_stock("APPL", 1, token);

    // Token test.
    token = c.generate_token("Test_Username");
    std::cout << "Token: " << token << std::endl;
    std::cout << "Username after verification: " << c.try_decode_token(token) << std::endl;
}