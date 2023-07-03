#include <stocksafari/Stock.hpp>
#include <stocksafari/Account.hpp>
#include <stocksafari/Controller.hpp>
#include <iostream>


using namespace StockSafari;

int main() {
    Controller c;

    c.set_stockValue("APPL", 1);

    string token = c.registerAccount("Damyan", "1234");

    c.deposit(500, token);
    c.withdraw(1, token);

    // Token test.
    token = c.generate_token("Test_Username");
    std::cout << "Token: " << token << std::endl;
    std::cout << "Username after verification: " << c.try_decode_token(token) << std::endl;
}