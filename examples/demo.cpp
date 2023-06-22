#include <stocksafari/StockValue.hpp>
#include <stocksafari/Stock.hpp>
#include <stocksafari/AccountStock.hpp>
#include <stocksafari/Account.hpp>

using namespace StockSafari;

int main() {
    StockValue value = StockValue(10);

    Stock stock = Stock("APPL", "Snapple", 20);

    AccountStock as = AccountStock(stock, 10);

    Account a = Account("Daniel", "Damyan");
}