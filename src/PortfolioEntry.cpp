#include <stocksafari/PortfolioEntry.hpp>
#include <stdexcept>

using namespace std;

namespace StockSafari {
    /// @brief Total increase of stock 
    /// @return Increase as a number
    double PortfolioEntry::get_total_increase() const {
        double total_costs = 0;
        double total_quantity = 0;

        // Iterate through all unsold details.
        for (PortfolioEntryDetail detail: _details) {
            if (detail.get_sold() == false) {
                // Add the per stock cost multiplied by the amount of stocks bought.
                total_costs += detail.get_buyValue() * detail.get_quantity();
                // Add the quantity to the total.
                total_quantity += detail.get_quantity();
            }
        }

        // Get total costs if buyValue would be the current stock value.
        double current_costs = total_quantity * get_stock().get_value();

        return current_costs - total_costs;
    }

    /// @brief Percental increase of stocks bought
    /// @return Increase in percent
    double PortfolioEntry::get_percental_increase() const {
        double total_costs = 0;

        // Iterate through all unsold details.
        for (PortfolioEntryDetail detail: _details) {
            if (detail.get_sold() == false) {
                // Add the per stock cost multiplied by the amount of stocks bought.
                total_costs += detail.get_buyValue() * detail.get_quantity();
            }
        }

        // Check if total_costs are 0.
        if (total_costs == 0.0) {
            return 0.0;
        }

        // Divide increase with total costs and multiply by 100 to get percentage value.
        return (get_total_increase() / total_costs) * 100;
    }

    /// @brief Find active Stocks 
    /// @return True for no active stocks found
    bool PortfolioEntry::get_sold() const {
        for (PortfolioEntryDetail detail: _details) {
            if (detail.get_sold() == false) {
                // Active stocks found. Return false.
                return false;
            }
        }
        // No active stocks found. Return true;
        return true;
    }
}