#include <string>
#include <vector>
#include <stocksafari/Stock.hpp>
#include <stocksafari/PortfolioEntryDetail.hpp>

#pragma once

namespace StockSafari {
    class PortfolioEntry {
        public:
            PortfolioEntry(Stock& stock, double quantity) :
                _stock(stock),
                _details({ PortfolioEntryDetail(stock.get_value(), quantity) })
            { }

            Stock& get_stock() const { return _stock; }

            std::vector<PortfolioEntryDetail>& get_details() { return _details; }
            void add_detail(PortfolioEntryDetail value) { _details.push_back(value); }

            double get_total_increase() const;

            double get_percental_increase() const;

        private:
            /// @brief Stock
            Stock& _stock;

            /// @brief Entry details.
            std::vector<PortfolioEntryDetail> _details;
    };
}