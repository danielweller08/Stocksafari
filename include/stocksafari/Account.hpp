#include <string>
#include <vector>
#include <stocksafari/PortfolioEntry.hpp>

#pragma once

namespace StockSafari {
    class Account {
        public:
            Account(std::string username, std::string password) :
                _username(username),
                _password(password),
                _balance(0),
                _portfolio({})
            { }

            const std::string get_username() { return _username; }

            const std::string get_password() { return _password; }

            const double get_balance() { return _balance; }
            void set_balance(double value) { _balance = value; }

            std::vector<PortfolioEntry>& get_portfolio() { return _portfolio; }
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