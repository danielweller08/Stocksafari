#include <stocksafari/StockValue.hpp>
#include <stocksafari/Stock.hpp>
#include <stocksafari/AccountStock.hpp>
#include <stocksafari/Account.hpp>
#include <stocksafari/Controller.hpp>
#include <iostream>


using namespace StockSafari;

int main() {
    StockValue value = StockValue(10);

    Stock stock = Stock("APPL", "Snapple", 20);

    AccountStock as = AccountStock(stock, 10);

    Controller c;

    c.set_stockValue("APPL", 1);

    Account& a = c.create_account("Damyan", "1234");

    a = c.deposit("Damyan", 500);
    a = c.withdraw("Damyan", 1);

    // Token test.
    auto token = c.generate_token("Test_Username");
    std::cout << "Token: " << token << std::endl;
    std::cout << "Username after verification: " << c.decode_token(token) << std::endl;
}