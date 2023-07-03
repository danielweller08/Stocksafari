#include <string>
#include <vector>
#include <chrono>

#pragma once

namespace StockSafari {
    class PortfolioEntryDetail {
        public:
            PortfolioEntryDetail(double buyValue, double quantity) :
                _buyValue(buyValue),
                _buyDate(std::chrono::system_clock::now()),
                _sellValue(0),
                _sellDate(std::chrono::time_point<std::chrono::system_clock>{}),
                _quantity(quantity),
                _sold(false)
            { }

            const double get_buyValue() { return _buyValue; }
            void set_buyValue(double value) { _buyValue = value; }

            const double get_sellValue() { return _sellValue; }

            const std::chrono::time_point<std::chrono::system_clock> get_buyDate() { return _buyDate; }
            void set_buyDate(std::chrono::time_point<std::chrono::system_clock> value) { _buyDate = value; }

            const std::chrono::time_point<std::chrono::system_clock> get_sellDate() { return _sellDate; }

            const double get_quantity() { return _quantity; }
            void set_quantity(double value) { _quantity = value; }

            const bool get_sold() { return _sold; }

            void sell(double sellValue) {
                _sellValue = sellValue;
                _sellDate = std::chrono::system_clock::now();
                _sold = true;
            }

        private:
            /// @brief Value of the stock at moment of buying.
            double _buyValue;

            /// @brief Value of the stock at moment of selling.
            double _sellValue;

            /// @brief Moment of buying.
            std::chrono::time_point<std::chrono::system_clock> _buyDate;

            /// @brief Moment of selling.
            std::chrono::time_point<std::chrono::system_clock> _sellDate;

            /// @brief Buying quantity.
            double _quantity;

            /// @brief Indicates if stock is sold.
            bool _sold;
    };
}