# Run with
#   uvicorn stocksafari_fastapi:api --port 8000 --reload
# or, if uvicorn is not in PATH, run as
#   python3 -m uvicorn stocksafari:api --port 8000  --reload

# Import magic
try:
    import stocksafari
except ImportError as e:
    print(f"Importing the shared library 'stocksafari' did not work.")
    print(f"Is (a link to) the shared library 'stocksafari.____.so' in the same directory as this python script?")
    print(f"The import caused the following exception '{e}'")
    print(f"Exiting")
    exit(1)

from stocksafari import Controller
import os
from fastapi import FastAPI, Request, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import uvicorn
import numpy as np
import threading
import time

# Method to extract and format the Authorization header.
def get_auth_token(request: Request):
    auth_header = request.headers.get('authorization')
    return auth_header.removeprefix('Bearer ')

# Init Controller
c = Controller()

def update_stocks(args, kwargs):
    # c = args[0]

    # Generate 999 stock values each initially
    for stock in c.get_stocks():
        start = stock.get_value()
        drift = stock.get_increase() * 0.2 # 10*(2* np.random.rand () - 1.0)
        kurs = kursverlauf(drift, 0.8, 0.001, start, 999)

        for i in kurs:
            c.set_stockValue(stock.get_stockId(), np.round(i, 2))

    stockCourses = []
    while True:
        # Update the stockCourses with 1000 new values per stock.
        for stock in c.get_stocks():

            start = stock.get_value()
            drift = stock.get_increase() * 0.2
            kurs = kursverlauf(drift, 0.8, 0.001, start, 1000)
            stockCourses.append(kurs)

        for i in range(1000):
            for j in range(len(c.get_stocks())):
                c.set_stockValue(c.get_stocks()[j].get_stockId(), np.round(stockCourses[j][i], 2))

            time.sleep(6) # Sleep a sec before updating the next values.

# Method to start a background thread.
def start_thread(function_name, *args, **kwargs):
    t = threading.Thread(target=function_name, args=args, kwargs=kwargs)
    t.daemon = True
    t.start()
    return t

def kursverlauf (tendenz , streuung , dt , start , anzahl):
    sqdt = np.sqrt(dt)
    kurs = np.zeros(anzahl)
    kurs [0] = start
    for i in range(anzahl -1):
        Y = 2*np.random.rand () - 1.0
        kurs[i+1] = np.round(kurs[i] * (1 + tendenz *dt + streuung *sqdt*Y), 2)
    return kurs

# Response Models
class Stock:
    def __init__(self, pybindStock):
       self.stockId = pybindStock.get_stockId()
       self.name = pybindStock.get_name()
       self.value = pybindStock.get_value()

class StockWithValues:
    def __init__(self, pybindStock):
       self.stockId = pybindStock.get_stockId()
       self.name = pybindStock.get_name()
       self.values = pybindStock.get_values()

class PortfolioEntryDetail:
    def __init__(self, pybindPortfolioEntryDetail):
        self.quantity = pybindPortfolioEntryDetail.get_quantity();
        self.buyValue = pybindPortfolioEntryDetail.get_buyValue()
        self.buyDate = pybindPortfolioEntryDetail.get_buyDate()
        self.sellValue = pybindPortfolioEntryDetail.get_sellValue()
        self.sellDate = pybindPortfolioEntryDetail.get_sellDate()
        self.sold = pybindPortfolioEntryDetail.get_sold()

class PortfolioEntry:
    def __init__(self, pybindPortfolioEntry):
        self.total_increase = pybindPortfolioEntry.get_total_increase()
        self.percental_increase = pybindPortfolioEntry.get_percental_increase()
        self.sold = pybindPortfolioEntry.get_sold()
        self.stock = Stock(pybindPortfolioEntry.get_stock())
        self.details = []
        for detail in pybindPortfolioEntry.get_details():
            self.details.append(PortfolioEntryDetail(detail))

class Account:
    def __init__(self, pybindAccount):
        self.username = pybindAccount.get_username()
        self.balance = pybindAccount.get_balance()
        self.portfolio = []
        for portfolioEntry in pybindAccount.get_portfolio():
            self.portfolio.append(PortfolioEntry(portfolioEntry))

# Request models
class AuthRequest(BaseModel):
    username: str
    password: str

start_thread(update_stocks, None, None)

# Init FastAPI
api = FastAPI()

api.add_middleware(
    CORSMiddleware,
    allow_origins=['*']
)

# Define endpoint for reading all stocks.
@api.get("/stocks")
async def get_stocks():
    try:
        stocks = c.get_stocks()
        data = []
      
        for stock in stocks:
            data.append(Stock(stock))

        return data

    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

# Define endpoint for reading stock details by id.
@api.get("/stocks/{stockId}")
async def get_stock(stockId: str):
    try:
        return StockWithValues(c.get_stock(stockId))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for buying a stock, auth is required.
@api.post("/stocks/{stockId}/buy")
async def buy_stock(stockId: str, quantity: float, request: Request):
    try:
        return Account(c.buy_stock(stockId, quantity, get_auth_token(request)))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for selling a stock, auth is required.
@api.post("/stocks/{stockId}/sell")
async def sell_stock(stockId: str, quantity: float, request: Request):
    try:
        return Account(c.sell_stock(stockId, quantity, get_auth_token(request)))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for reading account information including the portfolio, auth is required.
@api.get("/accounts/me")
async def get_account(request: Request):
    try:
        account = Account(c.get_account(get_auth_token(request)))
        return account;
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for logging in, returns a bearer token.
@api.post("/accounts/login")
async def login(request: AuthRequest):
    try:
        return {
            "access_token": c.loginAccount(request.username, request.password)
        }
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for signing in, returns a bearer token.
@api.post("/accounts/new")
async def new(request: AuthRequest):
    try:
        return {
            "access_token": c.registerAccount(request.username, request.password)
        }
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for depositing money, auth is required.
@api.post("/accounts/me/deposit")
async def deposit(amount: float, request: Request):
    try:
        return Account(c.deposit(amount, get_auth_token(request)))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
# Define endpoint for withdrawing money, auth is required.
@api.post("/accounts/me/withdraw")
async def withdraw(amount: float, request: Request):
    try:
        return Account(c.withdraw(amount, get_auth_token(request)))
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

if __name__ == '__main__':
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}:api", host="127.0.0.1", port=8000, log_level="info", reload=True)