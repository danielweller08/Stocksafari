#include <chrono>

#pragma once

namespace StockSafari {
    class StockValue {
        public:
            StockValue(double value) :
                _value(value), 
                _date(std::chrono::system_clock::now()) 
            { }

            const double get_value() { return _value; }

            const std::chrono::time_point<std::chrono::system_clock> get_date() { return _date; }

        private:
            /// @brief Value of the stock point.
            double _value;

            /// @brief Date of the stock point.
            std::chrono::time_point<std::chrono::system_clock> _date;
    };
}