import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { StocksComponent } from './stocks/stocks.component';

import { HttpClientModule } from  '@angular/common/http';
import { StockDetailComponent } from './stocks/stock-detail/stock-detail.component';
import { StockDetailChartComponent } from './stocks/stock-detail/stock-detail-chart/stock-detail-chart.component';
import { NgApexchartsModule } from 'ng-apexcharts';
import { PortfolioComponent } from './portfolio/portfolio.component';

@NgModule({
  declarations: [
    AppComponent,
    StocksComponent,
    StockDetailComponent,
    StockDetailChartComponent,
    PortfolioComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    NgApexchartsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }

// Installation: https://www.ubuntupit.com/how-to-install-and-configure-angular-cli-on-linux-distributions/#:~:text=Install%20Angular%20CLI%20on%20Debian%20and%20Ubuntu%20Linux,3%20Step%203%3A%20Remove%20Angular%20CLI%20from%20Ubuntu
