#include <string>
#include <vector>

#pragma once

namespace StockSafari {
    class Stock {
        public:
            Stock(std::string stockId, std::string name, double initialValue, double increase) :
                _stockId(stockId),
                _name(name),
                _values({ initialValue }),
                _increase(increase)
            { }

            std::string get_stockId() { return _stockId; }

            const std::string get_name() { return _name; }

            const double get_value() { return _values.back(); }

            std::vector<double>& get_values() { return _values; }

            void add_value(double value) { _values.push_back(value); };

        private:
            /// @brief Id
            std::string _stockId;

            /// @brief Name
            std::string _name;

            /// @brief The market value increase in percent.
            double _increase;

            /// @brief Stock value history.
            std::vector<double> _values;

    };
}