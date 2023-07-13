import { Component, OnInit } from '@angular/core';
import { DataService } from '../shared/services/data.service';
import { Account } from '../shared/models/account.model';
import { Stock } from '../shared/models/stock.model';

@Component({
  selector: 'app-portfolio',
  templateUrl: './portfolio.component.html',
  styleUrls: ['./portfolio.component.scss']
})
export class PortfolioComponent implements OnInit {

  account: Account | undefined = undefined;
  selectedStock: Stock | undefined;
  stockAmount = 0;

  constructor(private _dataService: DataService) { }

  ngOnInit(): void {
    // Subscribe to Account changes.
    this._dataService._account.subscribe(value => {
      this.account = value;
      this.stockAmount = value!.portfolio.filter(x => x.sold == false).length;
    });

    this._dataService.getAccount();

    setInterval(() => {
      this._dataService.getAccount();
    }, 5000);
  }

  async deposit() {
    let amount = (document.getElementById('depositInput') as any)!.value;
    await this._dataService.deposit(amount);

    // Hide the modal.
    (document.getElementById(`depositModalDismiss`) as any).click();
  }

  async withdraw() {
    let amount = (document.getElementById('withdrawInput') as any)!.value;
    await this._dataService.withdraw(amount);

    // Hide the modal.
    (document.getElementById(`withdrawModalDismiss`) as any).click();
  }

  async sellStock(id: string) {
    let quantity = (document.getElementById('sellInput') as any)!.value;
    await this._dataService.sellStock(id, quantity);

    // Hide the modal.
    (document.getElementById(`sellModalDismiss`) as any).click();
  }

}
