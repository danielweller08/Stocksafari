#include <string>
#include <vector>
#include <stocksafari/PortfolioEntry.hpp>

#pragma once

namespace StockSafari {
    /// @brief Account.
    class Account {
        public:
            /// @brief Constructor.
            Account(std::string username, std::string password) :
                _username(username),
                _password(password),
                _balance(0),
                _portfolio({})
            { }

            /// @brief Gets username.
            /// @return The username.
            const std::string get_username() { return _username; }

            /// @brief Gets the password.
            /// @return The password in clear text, this should not be done in any production environment.
            const std::string get_password() { return _password; }

            /// @brief Gets the accounts balance.
            /// @return The balance.
            const double get_balance() { return _balance; }

            /// @brief Sets the accounts balance.
            /// @param value The new balance value.
            void set_balance(double value) { _balance = value; }

            /// @brief Gets the portfolio.
            /// @return A reference to the portfolio entries list.
            std::vector<PortfolioEntry>& get_portfolio() { return _portfolio; }

            /// @brief Adds a portfolio entry.
            /// @param stock The bought stock.
            /// @param quantity The bought quantity.
            void add_portfolioEntry(Stock& stock, double quantity) { _portfolio.push_back(PortfolioEntry(stock, quantity)); }

        private:
            /// @brief Username
            std::string _username;

            /// @brief Password
            std::string _password;

            /// @brief Account balance.
            double _balance;

            /// @brief Portfolio.
            std::vector<PortfolioEntry> _portfolio;

    };
}