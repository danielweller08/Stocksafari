import { Component } from '@angular/core';
import { DataService } from '../shared/services/data.service';
import { Stock } from '../shared/models/stock.model';
import { registerLocaleData } from '@angular/common';
import localeDe from '@angular/common/locales/de';

// Register de locale for correct currency display.
registerLocaleData(localeDe, 'de');

@Component({
  selector: 'app-stocks',
  templateUrl: './stocks.component.html',
  styleUrls: ['./stocks.component.scss']
})
export class StocksComponent {

  stocks: Stock[] = [];

  constructor(private _dataService: DataService) {
    _dataService._stocks.subscribe(
      newValue => {
        this.stocks = newValue
      }
    );
  }
}
