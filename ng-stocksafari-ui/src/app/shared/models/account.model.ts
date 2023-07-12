import { PortfolioEntry } from "./portfolio-entry.model";

export interface Account {
    username: string,
    balance: number,
    portfolio: PortfolioEntry[]
}