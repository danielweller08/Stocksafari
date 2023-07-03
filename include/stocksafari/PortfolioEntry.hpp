#include <string>
#include <vector>
#include <stocksafari/Stock.hpp>
#include <stocksafari/PortfolioEntryDetail.hpp>

#pragma once

namespace StockSafari {
    /// @brief Portfolio entry class.
    class PortfolioEntry {
        public:
            /// @brief Constructor. Initially creates a detail with the given stock and quantity information.
            PortfolioEntry(Stock& stock, double quantity) :
                _stock(stock),
                _details({ PortfolioEntryDetail(stock.get_value(), quantity) })
            { }

            /// @brief Gets the stock.
            /// @return Reference to the stock.
            Stock& get_stock() const { return _stock; }

            /// @brief Gets the details list.
            /// @return Reference to the portfolio details.
            std::vector<PortfolioEntryDetail>& get_details() { return _details; }

            /// @brief Adds a new element to the portfolio details.
            /// @param value The new detail.
            void add_detail(PortfolioEntryDetail value) { _details.push_back(value); }

            /// @brief Gets the total increase the stock has made since buy date.
            /// @return The amount of money the account has made with that stock.
            double get_total_increase() const;

            /// @brief Gets the percental increase the stock has made since buy date.
            /// @return The percentage the stock has increased its value with.
            double get_percental_increase() const;

        private:
            /// @brief Stock
            Stock& _stock;

            /// @brief Entry details.
            std::vector<PortfolioEntryDetail> _details;
    };
}