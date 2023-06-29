#include <vector>
#include <string>
#include <stdexcept>
#include <stocksafari/Account.hpp>
#include <stocksafari/Stock.hpp>

#pragma once

using namespace std;

namespace StockSafari {
    class Controller {
        public:
            Controller();

            const vector<Stock> get_stocks();

            const Stock get_stock(string stockId);

            Stock set_stockValue(string stockId, double value);

            // 1. Checkt Balance
            // 2. Legt AccountStock an
            // 3. Reduziert Balance
            Account buy_stock(string stockId, double quantity);

            // - Nur einen Teil verkaufen?
            // 	1. Neuen AccountStock anlegen
            // 		- Bekommt verkaufte Quantity mit aktueller Value als SellValue
            // 	2. Alter AccountStock bekommt reduzierte Quantity
            // 	3. Balance erhöhen
            // - Alles verkaufen?
            // 	1. AccountStock Sold auf true setzen, SellValue, SellDate usw.
            // 	2. Balance erhöhen
            Account sell_stock(string stockId, double quantity);

            Account get_account(string username);

            Account create_account(string username, string password);

            // Balance erhöhen
            Account deposit(string username, double amount);

            // Balance prüfen und dann reduzieren
            Account withdraw(string username, double amount);

        private:
            vector<Account> _accounts;

            vector<Stock> _stocks;
    };
}