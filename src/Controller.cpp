#include <stocksafari/Controller.hpp>

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
    
}