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

            vector<Stock>& get_stocks();

            Stock& get_stock(string stockId);

            Stock& set_stockValue(string stockId, double value);

            Account& buy_stock(string stockId, double quantity, string token);

            Account& sell_stock(string stockId, double quantity, string token);

            Account& get_account(string token);

            Account& deposit(double amount, string token);

            Account& withdraw(double amount, string token);

            string registerAccount(string username, string password);

            string loginAccount(string username, string password);

            /// @brief Generates a jwt token on behalf of the given username.
            /// @return The JWT token.
            const string generate_token(string username);

            /// @brief Validates and decodes a jwt token and returns the username.
            /// @param token The JWT token.
            /// @return 
            const string try_decode_token(string token);

        private:
            /// @brief 64-byte secret string to encode and decode JWT tokens with.
            /// @return The secret string.
            static const string get_jwt_secret() { return "7a9fe8a26f2c56b89f25d0a642dc9ae47d6eaf1a5b88002b95a9e0dcb64d6e84"; }

            vector<Account> _accounts;

            vector<Stock> _stocks;
    };
}