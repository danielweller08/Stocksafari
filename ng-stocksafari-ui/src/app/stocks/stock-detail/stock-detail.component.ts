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
    console.log(this._route.snapshot.paramMap);
    this._dataService.getStock(this.id);

    // Subscribe to the stock to get the details result and to be notified on changes.
    this._dataService._stock.subscribe(
      stock => this.stock = stock
    );

    // Subscribe to the login state of the user.
    this._dataService._isLoggedIn.subscribe(value => this.isLoggedIn = value);
  }

  /**
   * Buys amounts of the selected stock.
   */
  async buyStock() {
    let quantity = (document.getElementById('buyInput') as any)!.value;
    await this._dataService.buyStock(this.stock!.stockId, quantity);

    // Hide the modal.
    (document.getElementById(`buyModalDismiss`) as any).click();
  }
}
