#include <string>
#include <vector>
#include <chrono>

#pragma once

namespace StockSafari {
    /// @brief Portfolio Entry Detail class.
    class PortfolioEntryDetail {
        public:
            /// @brief Contstructor.
            PortfolioEntryDetail(double buyValue, double quantity) :
                _buyValue(buyValue),
                _buyDate(std::chrono::system_clock::now()),
                _sellValue(0),
                _sellDate(std::chrono::time_point<std::chrono::system_clock>{}),
                _quantity(quantity),
                _sold(false)
            { }

            /// @brief Gets the value of the stock at buy date.
            /// @return The value of the stock.
            const double get_buyValue() { return _buyValue; }

            /// @brief Gets the value of the stock at sell date.
            /// @return The value of the stock.
            const double get_sellValue() { return _sellValue; }

            /// @brief Gets the buy date.
            /// @return Buy date.
            const std::chrono::time_point<std::chrono::system_clock> get_buyDate() { return _buyDate; }

            /// @brief Sets the buy date.
            /// @param value Buy date.
            void set_buyDate(std::chrono::time_point<std::chrono::system_clock> value) { _buyDate = value; }

            /// @brief Gets the sell date.
            /// @return Sell date.
            const std::chrono::time_point<std::chrono::system_clock> get_sellDate() { return _sellDate; }

            /// @brief Gets the quantity.
            /// @return Quantity.
            const double get_quantity() { return _quantity; }

            /// @brief Sets the quantity.
            /// @param value Quantity.
            void set_quantity(double value) { _quantity = value; }

            /// @brief Gets a value indicating if the stocks have been sold.
            /// @return A value indicating if the stocks have been sold.
            const bool get_sold() { return _sold; }

            /// @brief Sets the properties relevant when selling stocks.
            /// @param sellValue The value of the stock when selling.
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