import { Component, OnInit } from '@angular/core';
import { ChartOptions } from 'src/app/shared/models/chart-options.model';
import { DataService } from 'src/app/shared/services/data.service';

@Component({
  selector: 'app-stock-detail-chart',
  templateUrl: './stock-detail-chart.component.html',
  styleUrls: ['./stock-detail-chart.component.scss']
})
export class StockDetailChartComponent implements OnInit {
  chartOptions: ChartOptions = {
    series: [{
      name: "APPL",
      data: []
    }],
    chart: {
      type: "line",
      stacked: false,
      zoom: {
        type: "x",
        enabled: true,
        autoScaleYaxis: false
      },
      toolbar: {
        autoSelected: "zoom"
      },
      foreColor: "var(--bs-body-color)"
    },
    dataLabels: {
      enabled: false
    },
    markers: {
      size: 0
    },
    fill:{},
    grid:{
      show: true,
      borderColor: "var(--bs-border-color)"
    },
    xaxis: {
      type: "numeric"
    },
    yaxis:{
      min: 0
    },
    colors: []
  }

  constructor(private _dataService: DataService) { }

  ngOnInit(): void {
    this._dataService._stock.subscribe(
      stock => {
        this.chartOptions.series = [
          {
            name: stock?.stockId,
            data: stock!.values
          }
        ]
      }
    );
  }
}
