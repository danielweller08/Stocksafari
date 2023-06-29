#include <vector>
#include <string>
#include <stdexcept>
#include <stocksafari/Account.hpp>
#include <stocksafari/Stock.hpp>
#include <stocksafari/StockValue.hpp>

#pragma once

using namespace std;

namespace StockSafari {
    class Controller {
        public:
            Controller();

            const vector<Stock> get_stocks();

            Stock get_stock(string stockId);

            Stock set_stockValue(string stockId, double value);

            Account buy_stock(string stockId, double quantity, string username);

            Account sell_stock(string stockId, double quantity, string username);

            Account get_account(string username);

            // Balance erhöhen
            Account deposit(string username, double amount);

            // Balance prüfen und dann reduzieren
            Account withdraw(string username, double amount);

        private:
            vector<Account> _accounts;

            vector<Stock> _stocks;
    };
}