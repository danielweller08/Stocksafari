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
            Controller() {
                // TODO: Initiale Stocks erstellen (Für initialValue erstmal 0 eintragen)
                // 1. Apple - Snapple - APPL
                // 2. Microsoft - Microhard - MSFT
                // 3. Amazon - Amazoo - AMZN
                // 4. Alphabet (Google) - Alphabutt -  GOOG
                // 5. Facebook - Facebark - META
                // 6. Berkshire Hathaway - Berkshire Hataway - BRK.A
                // 7. JPMorgan Chase - JPMoney Chase - JPM
                // 8. Procter & Gamble - Procter & Gamble With It - PG
                // 9. Visa - Vroom vroom - V
                // 10. Walmart - Wallyworld - WMT
                // 11. Mastercard - Masterlord - MA
                // 12. ExxonMobil - Exxtra money Mobil - XOM
                // 13. Nestle - Noodle - NESM
                // 14. AT&T - A-Team & T - T
                // 15. Pfizer - Pfeiffer - PFE
                // 16. Intel - Intellimouse - INTC
            }

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

            // Balance erhöhen
            Account deposit(string username, double amount);

            // Balance prüfen und dann reduzieren
            Account withdraw(string username, double amount);

        private:
            vector<Account> _accounts;

            vector<Stock> _stocks;
    };
}