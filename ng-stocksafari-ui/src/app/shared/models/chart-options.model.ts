import { ApexAxisChartSeries, ApexChart, ApexDataLabels, ApexFill, ApexGrid, ApexMarkers, ApexXAxis, ApexYAxis } from "ng-apexcharts";

export interface ChartOptions {
    series: ApexAxisChartSeries;
    chart: ApexChart;
    dataLabels: ApexDataLabels;
    markers: ApexMarkers;
    fill: ApexFill;
    xaxis: ApexXAxis;
    yaxis: ApexYAxis;
    colors: string[];
    grid: ApexGrid;
}