/*
Author: Koh Chen Yang
File: MarketData.hpp
Description:
Header file for MarketData class.

Stores the market inputs required by the Monte Carlo
pricing engine, including spot price, risk-free rate,
volatility and dividend yield.
*/

#ifndef MARKETDATA_HPP
#define MARKETDATA_HPP

class MarketData
{
private:
	double m_spot;
	double m_rate;
	double m_volatility;
	double m_dividendYield;

public:
	MarketData();
	MarketData(
		double spot,
		double rate,
		double volatility,
		double dividendYield
	);

	double Spot() const;
	double Rate() const;
	double Volatility() const;
	double DividendYield() const;

	void Spot(double spot);
	void Rate(double rate);
	void Volatility(double volatility);
	void DividendYield(double dividendYield);
};

#endif