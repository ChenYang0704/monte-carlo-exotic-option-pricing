/*
Author: Koh Chen Yang
File: MarketData.cpp
Description:
Implementation file for MarketData class.

Stores the market inputs required by the Monte Carlo
pricing engine, including spot price, risk-free rate,
volatility and dividend yield.
*/

#include "Core/MarketData.hpp"

MarketData::MarketData()
	: m_spot(0.0),
	m_rate(0.0),
	m_volatility(0.0),
	m_dividendYield(0.0)
{
}

MarketData::MarketData(
	double spot,
	double rate,
	double volatility,
	double dividendYield
)
	: m_spot(spot),
	m_rate(rate),
	m_volatility(volatility),
	m_dividendYield(dividendYield)
{
}

double MarketData::Spot() const
{
	return m_spot;
}

double MarketData::Rate() const
{
	return m_rate;
}

double MarketData::Volatility() const
{
	return m_volatility;
}

double MarketData::DividendYield() const
{
	return m_dividendYield;
}

void MarketData::Spot(double spot)
{
	m_spot = spot;
}

void MarketData::Rate(double rate)
{
	m_rate = rate;
}

void MarketData::Volatility(double volatility)
{
	m_volatility = volatility;
}

void MarketData::DividendYield(double dividendYield)
{
	m_dividendYield = dividendYield;
}