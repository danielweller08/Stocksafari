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

    Account a = Account("Daniel", "Damyan");

    std::cout << a.get_username();

    Controller c;

    c.set_stockValue("APPL", 1);

}