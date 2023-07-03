#include <vector>
#include <string>
#include <stdexcept>
#include <stocksafari/Account.hpp>
#include <stocksafari/Stock.hpp>

#pragma once

using namespace std;

namespace StockSafari {
    /// @brief API Controller used for user interaction. Also contains most of the logic.
    class Controller {
        public:
            /// @brief Default Constructor.
            Controller();

            /// @brief Gets all stocks.
            /// @return Reference to the list of stocks.
            vector<Stock>& get_stocks();

            /// @brief Gets a stock by id.
            /// @param stockId The id to be searched for.
            /// @return Reference to the stock.
            Stock& get_stock(string stockId);

            /// @brief Sets the stocks value. Should not be able to be called by the user.
            /// @param stockId The id of the stock to be updated.
            /// @param value The value to be inserted.
            /// @return Reference to the updated stock.
            Stock& set_stockValue(string stockId, double value);

            /// @brief Buys a stock on behalf of the user that is authenticated with the given token.
            /// @param stockId The id of the stock to be bought.
            /// @param quantity The quantity to be bought.
            /// @param token The authentication token.
            /// @return Reference to the account.
            Account& buy_stock(string stockId, double quantity, string token);

            /// @brief sells a stock on behalf of the user that is authenticated with the given token.
            /// @param stockId The id of the stock to be sold.
            /// @param quantity The quantity to be sold.
            /// @param token The authentication token.
            /// @return Reference to the account.
            Account& sell_stock(string stockId, double quantity, string token);

            /// @brief Gets the account associated with the authenticated user.
            /// @param token The authentication token.
            /// @return Reference to the account.
            Account& get_account(string token);

            /// @brief Adds to the balance of the account associated with the authenticated user.
            /// @param amount The amount of money to be added.
            /// @param token The authentication token.
            /// @return Reference to the account.
            Account& deposit(double amount, string token);

            /// @brief Removes from the balance of the account associated with the authenticated user.
            /// @param amount The amount of money to be removed.
            /// @param token The authentication token.
            /// @return Reference to the account.
            Account& withdraw(double amount, string token);

            /// @brief Registers a new account.
            /// @param username 
            /// @param password 
            /// @return An authentication token associated with the registered account.
            string registerAccount(string username, string password);

            /// @brief Gets an authentication token in exchange of correct account credentials.
            /// @param username 
            /// @param password 
            /// @return The authentication token.
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