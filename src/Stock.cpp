#include <string>
#include <vector>
#include <stocksafari/Stock.hpp>

namespace StockSafari {


    // Stock(std::string stockId, std::string name, double initialValue) :
    //     _stockId(stockId),
    //     _name(name),
    //     _values({ StockValue(initialValue) })
    // { }

    const std::string Stock::get_stockId() { return _stockId; }

    const std::string Stock::get_name() { return _name; }

    const double Stock::get_value() { return _values.back().get_value(); }

    const std::vector<StockValue> Stock::get_values() { return _values; }

    void Stock::add_value(StockValue value) { _values.push_back(value); }

}