import { Injectable } from '@angular/core';
import { BehaviorSubject, firstValueFrom } from 'rxjs';
import { Stock } from '../models/stock.model';
import { HttpClient } from '@angular/common/http';
import { Account } from '../models/account.model';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  _stocks: BehaviorSubject<Stock[]> = new BehaviorSubject<Stock[]>([]);
  _stock: BehaviorSubject<Stock|undefined> = new BehaviorSubject<Stock|undefined>(undefined);
  _isLoggedIn: BehaviorSubject<boolean> = new BehaviorSubject<boolean>(false);
  _account: BehaviorSubject<Account | undefined> = new BehaviorSubject<Account | undefined>(undefined);
  _errorToastMessage: BehaviorSubject<string> = new BehaviorSubject<string>("");
  _successToastMessage: BehaviorSubject<string> = new BehaviorSubject<string>("");
  private baseUrl: string = "http://localhost:8000";
  private token: string | null = sessionStorage.getItem("token");

  constructor(private _httpClient: HttpClient) {
    // Refresh the stocks every 10 seconds.
    setInterval(() => {
      this.getStocks();
    }, 5000);

    // Get the stocks once on startup.
    this.getStocks();
  }

  /**
   * Gets the stocks from the api and writes them as new value to _stocks.
   */
  getStocks() {
    this._httpClient.get<Stock[]>(this.baseUrl + "/stocks").subscribe({
        next: (data) => {
          this._stocks.next(data);
        },
        error: (e) => {
          this._errorToastMessage.next("Fehler beim Laden der Daten");
        }
      }
    );
  }

  /**
   * Get a specific stock by id. Writes it as new value to _stock.
   * @param id id of the stock.
   */
  getStock(id: string) {
    this._httpClient.get<Stock>(`${this.baseUrl}/stocks/${id}`).subscribe({
        next: (data) => {
          this._stock.next(data);
        },
        error: (e) => {
          this._errorToastMessage.next("Fehler beim Laden der Aktie");
        }
      }
    );
  }

  /**
   * Buys the given stock and refreshes the account state.
   * @param id id of the stock to buy.
   * @param quantity amount of stocks to buy.
   */
  async buyStock(id: string, quantity: number) {
    if (!this._isLoggedIn.value) {
      this._errorToastMessage.next("Du kannst nur Stocks kaufen, wenn du eingeloggt bist.");
      return;
    }

    let succeeded = true;
    await firstValueFrom(this._httpClient.post<Account>(`${this.baseUrl}/stocks/${id}/buy?quantity=${quantity}`, null, { headers: { 'Authorization': `Bearer ${this.token}` }}))
      .catch((e) => {
        // Exception caught.
        console.log(e);
        succeeded = false;
        if (e.status == 400) {
          this._errorToastMessage.next(e.error.detail);
        }
        else {
          this._errorToastMessage.next("Fehler beim Kaufen der Aktie aufgetreten.");
        }
      })
      .then(async value => {
        if (succeeded) {
          this._account.next(value!);
          this._successToastMessage.next(id + " Aktie(n) erfolgreich gekauft");
        }
      });
  }

  /**
   * Sells the given stock and refreshes the account state.
   * @param id id of the stock to sell.
   * @param quantity amount of stocks to sell.
   */
  async sellStock(id: string, quantity: number) {
    if (!this._isLoggedIn.value) {
      this._errorToastMessage.next("Du kannst nur Stocks verkaufen, wenn du eingeloggt bist.");
      return;
    }

    let succeeded = true;
    await firstValueFrom(this._httpClient.post<Account>(`${this.baseUrl}/stocks/${id}/sell?quantity=${quantity}`, null, { headers: { 'Authorization': `Bearer ${this.token}` }}))
      .catch((e) => {
        // Exception caught.
        console.log(e);
        succeeded = false;
        if (e.status == 400) {
          this._errorToastMessage.next(e.error.detail);
        }
        else {
          this._errorToastMessage.next("Fehler beim Verkaufen der Aktie aufgetreten.");
        }
      })
      .then(async value => {
        if (succeeded) {
          this._account.next(value!);
          this._successToastMessage.next(id + " Aktie(n) erfolgreich verkauft");
        }
      });
  }

  /**
   * Deposits the given amount to the account and refreshes the account state.
   * @param amount Amount of money to deposit.
   */
  async deposit(amount: number) {
    if (!this._isLoggedIn.value) {
      this._errorToastMessage.next("Du kannst nur Guthaben aufladen, wenn du eingeloggt bist.");
      return;
    }

    let succeeded = true;
    await firstValueFrom(this._httpClient.post<Account>(`${this.baseUrl}/accounts/me/deposit?amount=${amount}`, null, { headers: { 'Authorization': `Bearer ${this.token}` }}))
      .catch((e) => {
        // Exception caught.
        succeeded = false;
        this._errorToastMessage.next("Fehler bei der Aufladung aufgetreten.");
      })
      .then(value => {
        if (succeeded) {
          this._account.next(value!);
        }
      });
  }

  /**
   * Withdraws the given amount to the account and refreshes the account state.
   * @param amount Amount of money to withdraw.
   */
  async withdraw(amount: number) {
    if (!this._isLoggedIn.value) {
      this._errorToastMessage.next("Du kannst nur Guthaben auszahlen, wenn du eingeloggt bist.");
      return;
    }

    let succeeded = true;
    await firstValueFrom(this._httpClient.post<Account>(`${this.baseUrl}/accounts/me/withdraw?amount=${amount}`, null, { headers: { 'Authorization': `Bearer ${this.token}` }}))
      .catch((e) => {
        // Exception caught.
        console.log(e);
        succeeded = false;
        if (e.status == 400) {
          this._errorToastMessage.next(e.error.detail);
        }
        else {
          this._errorToastMessage.next("Fehler bei der Auszahlung aufgetreten.");
        }
      })
      .then(value => {
        if (succeeded) {
          this._account.next(value!);
        }
      });
  }

  /**
   * Logs in or registers user with the given username and password.
   * @param method login or register
   * @param username username
   * @param password password
   */
  async loginOrRegister(method: string, username: string, password: string) {
    if (method == "register") method = "new"; // Register endpoint suffix is 'new'.

    let succeeded = true;
    // Login or register.
    await firstValueFrom(this._httpClient.post(this.baseUrl + `/accounts/${method}`, { 'username': username, 'password': password }))
      .catch((e) => {
        // Exception caught.
        succeeded = false;
        throw e.error.detail;
      })
      .then(async (value: any) => {
        if (succeeded) {
          // Request succeeded.

          // Write back the token.
          this.token = value.access_token;
          sessionStorage.setItem("token", this.token!);

          // Get the account information.
          await this.getAccount();

          this._isLoggedIn.next(true);
        }
      });
  }

  /**
   * Gets the current state of the logged in user account.
   */
  async getAccount() {
    if (this.token != null) {
      // Get the account information.
      await firstValueFrom(this._httpClient.get<Account>(this.baseUrl + `/accounts/me`, { headers: { 'Authorization': `Bearer ${this.token}` }}))
      .then(
        value => {
          this._account.next(value);
        }
      );
    }
  }

  /**
   * Logs out the currently logged in user.
   */
  logout() {
    sessionStorage.removeItem("token");
    this._isLoggedIn.next(false);
  }
}
