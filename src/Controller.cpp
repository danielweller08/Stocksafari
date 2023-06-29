#include <stocksafari/Controller.hpp>
#include <stdexcept>
#include <jwt-cpp/jwt.h>

using namespace std;

namespace StockSafari {

    Controller::Controller() { 
        _stocks.push_back(Stock("APPL", "Snapple", 0));
        _stocks.push_back(Stock("MSFT", "Microhard", 0));
        _stocks.push_back(Stock("AMZN", "Amazoo", 0));
        _stocks.push_back(Stock("GOOG", "Alphabutt", 0));
        _stocks.push_back(Stock("META", "Facebark", 0));
        _stocks.push_back(Stock("BRK.A", "Berkshire Hataway", 0));
        _stocks.push_back(Stock("JPM", "JPMoney Chase", 0));
        _stocks.push_back(Stock("PG", "Procter & Gamble With It", 0));
        _stocks.push_back(Stock("V", "Vroom vroom", 0));
        _stocks.push_back(Stock("WMT", "Wallyworld", 0));
        _stocks.push_back(Stock("MA", "Masterlord", 0));
        _stocks.push_back(Stock("XOM", "Exxtra money Mobil", 0));
        _stocks.push_back(Stock("NESM", "Noodle", 0));
        _stocks.push_back(Stock("T", "A-Team & T", 0));
        _stocks.push_back(Stock("PFE", "Pfeiffer", 0));
        _stocks.push_back(Stock("INTC", "Intellimouse", 0));
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

        get_stock(stockId).add_value(StockValue(value));
        return get_stock(stockId);
    }

    Account& Controller::buy_stock(string stockId, double quantity, string username) {

        // Check if balance is greater equal than the wanted quantity
        if(get_account(username).get_balance() >= (quantity * get_stock(stockId).get_value()) ) {
            //  Created AccountStock with parameters
            AccountStock account_stock = AccountStock(get_stock(stockId), quantity);  

            // Reduce balance by subtracting the value from it
            get_account(username).set_balance(get_account(username).get_balance() - (quantity * get_stock(stockId).get_value()));

            return get_account(username);
        }
        else {
            throw invalid_argument("Balance reicht nicht aus um gewünschten Stock zu kaufen.");

        }
        
    }

    Account& Controller::sell_stock(string stockId, double quantity, string username) {

        // Iterieren durch stocks des accounts  
        for(auto acc_stock : get_account(username).get_portfolio()) {

            if( stockId == acc_stock.get_stock().get_stockId() ) {

                // Alles verkaufen?
                if(acc_stock.get_quantity() == quantity) {
                    

                    // 	1. AccountStock Sold auf true setzen, SellValue, SellDate usw.

                    acc_stock.set_sold(true);
                    acc_stock.set_sellDate(std::chrono::system_clock::now());
                    acc_stock.set_sellValue(get_stock(stockId).get_value());

                    // 2. Balance erhöhen
                    get_account(username).set_balance(get_account(username).get_balance() + (quantity * get_stock(stockId).get_value() ) );

                }
                // Nur einen Teil verkaufen?
                else if (acc_stock.get_quantity() > quantity) {
                                
                    // 	1. Neuen AccountStock anlegen

                    AccountStock acc = AccountStock(get_stock(stockId), quantity);

                    // 		- Bekommt verkaufte Quantity mit aktueller Value als SellValue

                    acc.set_sellValue(get_stock(stockId).get_value());
                    acc.set_sold(true);
                    acc.set_sellDate(std::chrono::system_clock::now());

                    get_account(username).add_stock(acc);

                    // 	2. Alter AccountStock bekommt reduzierte Quantity

                    acc_stock.set_quantity(acc_stock.get_quantity() - quantity);


                    // 3. Balance erhöhen
                    get_account(username).set_balance( get_account(username).get_balance() + quantity * get_stock(stockId).get_value());
                }
                else {
                    throw invalid_argument("Es kann nicht so viel von diesem Stock verkauft werden.");
                }
            }
        }
        throw invalid_argument("Du besitzt diesen stock gar nicht.");
    }

    Account& Controller::get_account(string username) {
        if(_accounts.size() == 0) {
            throw invalid_argument("Account mit dem Username " + username + " existiert nicht!");
        }

        for (int i = 0; i < _accounts.size(); i++) {
            if (_accounts[i].get_username() == username) {
                return _accounts[i];
            }
        }
        throw invalid_argument("Account mit dem Username " + username + " existiert nicht!");
    }

    Account& Controller::create_account(string username, string password) {
        for(Account account : _accounts) {
            if (account.get_username() == username) {
                throw invalid_argument("Account mit dem Username " + username + " existiert!"); 
            } 
        }
        _accounts.push_back(Account(username, password));
        return get_account(username);
    }

    Account& Controller::deposit(string username, double amount) {
        Account& account = get_account(username);
        account.set_balance(account.get_balance() + amount);
        return account;   
    }

    Account& Controller::withdraw(string username, double amount) {
        Account& account = get_account(username);
        if (account.get_balance() < amount) {
            throw invalid_argument("Du hast nicht genug Guthaben!");
        }
        account.set_balance(account.get_balance() - amount);
        return account;
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

    const string Controller::decode_token(string token) {
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