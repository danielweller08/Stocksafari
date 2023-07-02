#include <stocksafari/Controller.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/chrono.h>

namespace py = pybind11;
using namespace StockSafari;

PYBIND11_MODULE(stocksafari, m) {
    m.doc() = "StockSafari";

    py::class_<Account>(m, "Account")
        .def("get_balance", &Account::get_balance)
        .def("get_password", &Account::get_password)
        .def("get_portfolio", &Account::get_portfolio)
        .def("get_username", &Account::get_username);

    py::class_<AccountStock>(m, "AccountStock")
        .def("get_buyDate", &AccountStock::get_buyDate)
        .def("get_buyValue", &AccountStock::get_buyValue)
        .def("get_quantity", &AccountStock::get_quantity)
        .def("get_sellDate", &AccountStock::get_sellDate)
        .def("get_sold", &AccountStock::get_sold)
        .def("get_stock", &AccountStock::get_stock);

    py::class_<Stock>(m, "Stock")
        .def("get_name", &Stock::get_name)
        .def("get_stockId", &Stock::get_stockId)
        .def("get_value", &Stock::get_value)
        .def("get_values", &Stock::get_values)
        .def("add_value", &Stock::add_value);

    py::class_<Controller>(m, "Controller")
        .def(py::init<>())
        .def("buy_stock", &Controller::buy_stock)
        .def("deposit", &Controller::deposit)
        .def("get_account", &Controller::get_account)
        .def("get_stock", &Controller::get_stock)
        .def("get_stocks", &Controller::get_stocks)
        .def("loginAccount", &Controller::loginAccount)
        .def("registerAccount", &Controller::registerAccount)
        .def("sell_stock", &Controller::sell_stock)
        .def("set_stockValue", &Controller::set_stockValue)
        .def("withdraw", &Controller::withdraw);
}