#include <string>
#include <vector>
#include <stocksafari/StockValue.hpp>

#pragma once

namespace StockSafari {
    class Stock {
        public:
            Stock(std::string stockId, std::string name, double initialValue) :
                _stockId(stockId),
                _name(name),
                _values({ StockValue(initialValue) })
            { }

            const std::string get_stockId() { return _stockId; }

            const std::string get_name() { return _name; }

            const std::vector<StockValue> get_values() { return _values; }

            void add_value(double value) { _values.push_back(StockValue(value)); }

        private:
            /// @brief Id
            std::string _stockId;

            /// @brief Name
            std::string _name;

            /// @brief Stock value history.
            std::vector<StockValue> _values;

    };
}