#include <string>
#include <vector>

#pragma once

namespace StockSafari {
    /// @brief Stock class.
    class Stock {
        public:
            /// @brief Constructor.
            Stock(std::string stockId, std::string name, double initialValue, double increase) :
                _stockId(stockId),
                _name(name),
                _values({ initialValue }),
                _increase(increase)
            { }

            /// @brief Gets the stocks id.
            /// @return The stocks id.
            std::string get_stockId() { return _stockId; }

            /// @brief Gets the stocks name.
            /// @return The stocks name.
            const std::string get_name() { return _name; }

            /// @brief Gets the stocks current value aka. the top of the values history.
            /// @return The stocks value.
            const double get_value() { return _values.back(); }

            /// @brief Gets the stocks value history.
            /// @return The stocks value history.
            std::vector<double>& get_values() { return _values; }

            /// @brief Adds a new value to the top of the value history.
            /// @param value Value to be added.
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