#include <chrono>
#include <stocksafari/Stock.hpp>

#pragma once

namespace StockSafari {
    class AccountStock {
        public:
            AccountStock(Stock stock, double quantity) :
                _stock(stock),
                _buyValue(stock.get_value()),
                _sellValue(0),
                _buyDate(std::chrono::system_clock::now()),
                _quantity(quantity),
                _sold(false)
            { }

            const double get_buyValue() { return _buyValue; }

            const double get_sellValue() { return _sellValue; }
            void set_sellValue(double value) { _sellValue = value; }

            const std::chrono::time_point<std::chrono::system_clock> get_buyDate() { return _buyDate; }

            const std::chrono::time_point<std::chrono::system_clock> get_sellDate() { return _sellDate; }
            void set_sellDate(std::chrono::time_point<std::chrono::system_clock> value) { _sellDate = value; }

            Stock get_stock() { return _stock; }

            const double get_quantity() { return _quantity; }
            void set_quantity(double value) { _quantity = value; }

            const bool get_sold() { return _sold; }
            void set_sold(bool value) { _sold = value; }

        private:
            /// @brief Value of the stock at moment of buying.
            double _buyValue;

            /// @brief Value of the stock at moment of selling.
            double _sellValue;

            /// @brief Moment of buying.
            std::chrono::time_point<std::chrono::system_clock> _buyDate;

            /// @brief Moment of selling.
            std::chrono::time_point<std::chrono::system_clock> _sellDate;

            /// @brief Stock reference.
            Stock _stock;

            /// @brief Buying quantity.
            double _quantity;

            /// @brief Indicates if stock is sold.
            bool _sold;
    };
}