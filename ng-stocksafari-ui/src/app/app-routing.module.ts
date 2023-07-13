import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { StocksComponent } from './stocks/stocks.component';
import { StockDetailComponent } from './stocks/stock-detail/stock-detail.component';
import { PortfolioComponent } from './portfolio/portfolio.component';
import { authGuard } from './shared/guards/auth.guard';

const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    redirectTo: 'stocks'
  },
  {
    path: 'stocks',
    component: StocksComponent
  },
  {
    path: 'stocks/:id',
    component: StockDetailComponent
  },
  {
    path: 'portfolio',
    component: PortfolioComponent,
    canActivate: [authGuard]
  },
  {
    path: '**',
    redirectTo: 'stocks'
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
