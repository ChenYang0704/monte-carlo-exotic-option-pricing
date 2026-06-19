/*
Author: Koh Chen Yang
File: BlackScholesAnalyticEngine.hpp
Description:
Header file for BlackScholesAnalyticEngine class.

Provides analytical Black-Scholes prices for European
and binary options. These analytical prices are used
as validation benchmarks for the Monte Carlo engine.
*/

#ifndef BLACKSCHOLESANALYTICENGINE_HPP
#define BLACKSCHOLESANALYTICENGINE_HPP

#include "Core/MarketData.hpp"
#include "Option/OptionEnums.hpp"

class BlackScholesAnalyticEngine
{
private:
	static double D1(
		double strike,
		double maturity,
		const MarketData& market
	);

	static double D2(
		double strike,
		double maturity,
		const MarketData& market
	);

public:
	static double EuropeanPrice(
		double strike,
		double maturity,
		OptionType optionType,
		const MarketData& market
	);

	static double BinaryPrice(
		double strike,
		double maturity,
		OptionType optionType,
		const MarketData& market
	);
};

#endif