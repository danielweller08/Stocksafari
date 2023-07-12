import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Params } from '@angular/router';
import { Stock } from 'src/app/shared/models/stock.model';
import { DataService } from 'src/app/shared/services/data.service';

@Component({
  selector: 'app-stock-detail',
  templateUrl: './stock-detail.component.html',
  styleUrls: ['./stock-detail.component.scss']
})
export class StockDetailComponent implements OnInit {

  id: string = "";
  isLoggedIn: boolean = false;
  stock: Stock|undefined = undefined;

  constructor(private _route: ActivatedRoute, private _dataService: DataService) { }

  ngOnInit(): void {
    // Get the id from the url and load the stock details.
    this.id = this._route.snapshot.paramMap.get('id')!;
    this._dataService.getStock(this.id);

    // Subscribe to the stock to get the details result and to be notified on changes.
    this._dataService._stock.subscribe(
      stock => this.stock = stock
    );

    // Subscribe to the login state of the user.
    this._dataService._isLoggedIn.subscribe(value => this.isLoggedIn = value);
  }
}
