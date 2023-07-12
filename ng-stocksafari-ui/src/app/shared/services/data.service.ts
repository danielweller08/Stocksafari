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
  _toastMessage: BehaviorSubject<string> = new BehaviorSubject<string>("");
  private baseUrl: string = "http://localhost:8000";
  private token: string | null = sessionStorage.getItem("token");

  constructor(private _httpClient: HttpClient) {
    setInterval(() => {
      this.getStocks();
    }, 5000);

    this.getStocks();
  }

  getStocks() {
    this._httpClient.get<Stock[]>(this.baseUrl + "/stocks").subscribe({
        next: (data) => {
          this._stocks.next(data);
        },
        error: (e) => {
          this._toastMessage.next("Fehler beim Laden der Daten");
        }
      }
    );
  }

  getStock(id: string) {
    this._httpClient.get<Stock>(`${this.baseUrl}/stocks/${id}`).subscribe({
        next: (data) => {
          this._stock.next(data);
        },
        error: (e) => {
          this._toastMessage.next("Fehler beim Laden der Aktie");
        }
      }
    );
  }

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
          await firstValueFrom(this._httpClient.get<Account>(this.baseUrl + `/accounts/me`, { headers: { 'Authorization': `Bearer ${this.token}` }}))
            .then(
              value => {
                this._account.next(value);
                console.log(value);
              }
            );

          this._isLoggedIn.next(true);
        }
      });
  }

  logout() {
    sessionStorage.removeItem("token");
    this._isLoggedIn.next(false);
  }
}
