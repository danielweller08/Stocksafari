import { Injectable } from '@angular/core';
import { BehaviorSubject, tap } from 'rxjs';
import { Stock } from '../models/stock.model';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  _stocks: BehaviorSubject<Stock[]> = new BehaviorSubject<Stock[]>([]);
  baseUrl: string = "http://localhost:8000";

  constructor(private _httpClient: HttpClient) {
    setInterval(() => {
      this.getStocks();
    }, 5000);

    this.getStocks();
  }

  getStocks() {
    this._httpClient.get<Stock[]>(this.baseUrl + "/stocks").subscribe(
      (data: Stock[]) => {
        this._stocks.next(data);
      }
    );
  }
}
