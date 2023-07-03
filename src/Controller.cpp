#include <stocksafari/Controller.hpp>
#include <stdexcept>
#include <jwt-cpp/jwt.h>

using namespace std;

namespace StockSafari {

    Controller::Controller() { 
        _stocks.push_back(Stock("APPL", "Snapple", 193.97, 2.31));
        _stocks.push_back(Stock("MSFT", "Microhard", 340.54, 1.64));
        _stocks.push_back(Stock("AMZN", "Amazoo", 130.36, 1.92));
        _stocks.push_back(Stock("GOOG", "Alphabutt", 120.97, 0.8));
        _stocks.push_back(Stock("META", "Facebark", 286.98, 1.94));
        _stocks.push_back(Stock("BRK.A", "Berkshire Hataway", 517810.00, 1.08));
        _stocks.push_back(Stock("JPM", "JPMoney Chase", 145.44, 1.4));
        _stocks.push_back(Stock("PG", "Procter & Gamble With It", 151.74, 1.58));
        _stocks.push_back(Stock("V", "Vroom vroom", 237.48, 1.35));
        _stocks.push_back(Stock("WMT", "Wallyworld", 157.18, 1.88));
        _stocks.push_back(Stock("MA", "Masterlord", 393.30, 1.45));
        _stocks.push_back(Stock("XOM", "Exxtra money Mobil", 107.25, 0.52));
        _stocks.push_back(Stock("NESM", "Noodle", 109.50, -0.45));
        _stocks.push_back(Stock("T", "A-Team & T", 15.95, -0.19));
        _stocks.push_back(Stock("PFE", "Pfeiffer", 36.68, 1.55));
        _stocks.push_back(Stock("INTC", "Intellimouse", 33.44, 1.61));
    }

    vector<Stock>& Controller::get_stocks() {
        return _stocks;
    } 

    Stock& Controller::get_stock(string stockId) {
        // Looks for stocks with matching stockid
        for(Stock& s: _stocks) {
            if(s.get_stockId() == stockId) {
                // Returns Stock if it found the right one
                return s;
            }
        }
        throw invalid_argument("Kein passender Stock wurde gefunden.");
    }

    Stock& Controller::set_stockValue(string stockId, double value) {
        get_stock(stockId).add_value(value);
        return get_stock(stockId);
    }

    Account& Controller::buy_stock(string stockId, double quantity, string token) {
        string username = try_decode_token(token);

        // Check if quantity is negative.
        if (quantity <= 0) {
            throw invalid_argument("Die angebene Menge ist nicht zulässig");
        }

        // Get the account.
        Account& account = get_account(token);

        // Get the stock.
        Stock& stock = get_stock(stockId);

        // Check if accounts balance is sufficient.
        if (!(account.get_balance() >= (quantity * stock.get_value()))) {
            throw invalid_argument("Dein Guthaben reicht für diesen Kauf nicht aus.");
        }

        // Check if account already owns that stock.
        bool ownsStock = false;
        for (PortfolioEntry& portfolioEntry: account.get_portfolio()) {
            if (portfolioEntry.get_stock().get_stockId() == stockId) {
                // Account owns that stock.
                ownsStock = true;

                // Add a new detail.
                portfolioEntry.add_detail(PortfolioEntryDetail(stock.get_value(), quantity));

                break;
            }
        }

        if (!ownsStock) {
            // Account does not own the stock.
            account.add_portfolioEntry(stock, quantity);
        }

        // Adjust the accounts balance.
        account.set_balance(account.get_balance() - (stock.get_value() * quantity));

        return account;
    }

    Account& Controller::sell_stock(string stockId, double quantity, string token) {
        string username = try_decode_token(token);

        // Check if quantity is negative.
        if (quantity <= 0) {
            throw invalid_argument("Die angebene Menge ist nicht zulässig");
        }

        // Get the account.
        Account& account = get_account(token);

        // Get the stock.
        Stock& stock = get_stock(stockId);

        // Check if account owns the stock.
        for (PortfolioEntry& portfolioEntry : account.get_portfolio()) {
            if (portfolioEntry.get_stock().get_stockId() == stockId) {
                // Stock found.

                // Check if account stock quantity is sufficient.
                double total_quantity = 0;
                for (PortfolioEntryDetail detail : portfolioEntry.get_details()) {
                    if (!detail.get_sold()) {
                        total_quantity += detail.get_quantity();
                    }
                }

                if (total_quantity < quantity) {
                    throw invalid_argument("Die angegebene Menge liegt über der Menge, die sie besitzen.");
                }

                // Iterate through and sell as many details as needed.
                vector<PortfolioEntryDetail> entriesToAdd = {}; // This variable is needed since we are not allowed to modify the vector we are currently iterating.
                for (PortfolioEntryDetail& detail : portfolioEntry.get_details()) {
                    if (!detail.get_sold()) {
                        if (detail.get_quantity() <= quantity) {
                            detail.sell(stock.get_value());
                        }
                        else {
                            // Create a new sold detail.
                            PortfolioEntryDetail newDetail = PortfolioEntryDetail(detail.get_buyValue(), quantity);
                            newDetail.set_buyDate(detail.get_buyDate());
                            newDetail.sell(stock.get_value());
                            entriesToAdd.push_back(newDetail);

                            // Update quantity of the existing detail.
                            detail.set_quantity(detail.get_quantity() - quantity);
                        }

                        // Reduce the account balance.
                        account.set_balance(account.get_balance() + (stock.get_value() * detail.get_quantity()));

                        // Update the quantity.
                        quantity -= detail.get_quantity();

                        // Check if everything is sold.
                        if (quantity <= 0) {
                            // Add the entries.
                            for (auto entry : entriesToAdd) {
                                portfolioEntry.add_detail(entry);
                            }
                            return account;
                        }
                    }
                }
            }
        }

        // Stock not found.
        throw invalid_argument("'" + stockId + "' konnte in deinem Portfolio nicht gefunden werden.");
    }

    Account& Controller::get_account(string token) {
        string username = try_decode_token(token);

        for (int i = 0; i < _accounts.size(); i++) {
            if (_accounts[i].get_username() == username) {
                return _accounts[i];
            }
        }
        throw invalid_argument("Dein Account konnte nicht gefunden werden.");
    }

    Account& Controller::deposit(double amount, string token) {
        Account& account = get_account(token);
        account.set_balance(account.get_balance() + amount);
        return account;   
    }

    Account& Controller::withdraw(double amount, string token) {
        Account& account = get_account(token);
        if (account.get_balance() < amount) {
            throw invalid_argument("Du hast nicht genug Guthaben!");
        }
        account.set_balance(account.get_balance() - amount);
        return account;
    }

    string Controller::registerAccount(string username, string password) {
        for(Account account : _accounts) {
            if (account.get_username() == username) {
                throw invalid_argument("Account mit dem Username " + username + " existiert bereits!"); 
            } 
        }
        _accounts.push_back(Account(username, password));
        return generate_token(username);
    }

    string Controller::loginAccount(string username, string password) {
        bool found = false;
        bool passwordCorrect = false;
        for(Account account : _accounts) {
            if (account.get_username() == username) {
                found = true;
                if (account.get_password() == password) {
                    passwordCorrect = true;
                }
            } 
        }

        if (!found || !passwordCorrect) {
            throw invalid_argument("Username oder Password falsch!");
        }

        return generate_token(username);
    }

    const string Controller::generate_token(string username) {
        // Create the token using the jwt-cpp library.
        return jwt::create()
            .set_issuer("stocksafari")
            .set_type("JWT")
            .set_id(username)
            .set_issued_at(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{36000}) // Lasts 10 hours
            .sign(jwt::algorithm::hs256 { get_jwt_secret() });
    }

    const string Controller::try_decode_token(string token) {
        // Build a verifier.
        auto verify = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256 { get_jwt_secret() })
            .with_issuer("stocksafari");

        // Decode the token.
        auto decoded = jwt::decode(token);

        // Verify the decoded token. Throws a token_verification_exception.
        verify.verify(decoded);

        // Return the username.
        return decoded.get_id();
    }
    
}