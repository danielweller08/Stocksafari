import { PortfolioEntryDetail } from "./portfolio-entry-detail.model";
import { Stock } from "./stock.model";

export interface PortfolioEntry {
    total_increase: number,
    percental_increase: number,
    sold: boolean,
    stock: Stock,
    details: PortfolioEntryDetail[]
}