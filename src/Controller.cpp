#include <stocksafari/Controller.hpp>
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