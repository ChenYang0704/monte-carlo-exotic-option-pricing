/*
Author: Koh Chen Yang
File: BlackScholesAnalyticEngine.cpp
Description:
Implementation file for BlackScholesAnalyticEngine class.

Provides analytical Black-Scholes prices for European
and binary options. These analytical prices are used
as validation benchmarks for the Monte Carlo engine.
*/

#include "Engine/BlackScholesAnalyticEngine.hpp"

#include <boost/math/distributions/normal.hpp>

#include <cmath>

double BlackScholesAnalyticEngine::D1(
	double strike,
	double maturity,
	const MarketData& market
)
{
	double sigma =
		market.Volatility();

	return
		(
			std::log(
				market.Spot()
				/
				strike
			)
			+
			(
				market.Rate()
				-
				market.DividendYield()
				+
				0.5
				*
				sigma
				*
				sigma
				)
			*
			maturity
			)
		/
		(
			sigma
			*
			std::sqrt(
				maturity
			)
			);
}

double BlackScholesAnalyticEngine::D2(
	double strike,
	double maturity,
	const MarketData& market
)
{
	return
		D1(
			strike,
			maturity,
			market
		)
		-
		market.Volatility()
		*
		std::sqrt(
			maturity
		);
}

double BlackScholesAnalyticEngine::EuropeanPrice(
	double strike,
	double maturity,
	OptionType optionType,
	const MarketData& market
)
{
	boost::math::normal_distribution<>
		normal(
			0.0,
			1.0
		);

	double d1 =
		D1(
			strike,
			maturity,
			market
		);

	double d2 =
		D2(
			strike,
			maturity,
			market
		);

	double spot =
		market.Spot();

	double rate =
		market.Rate();

	double dividendYield =
		market.DividendYield();

	if (optionType == OptionType::Call)
	{
		return
			spot
			*
			std::exp(
				-dividendYield
				*
				maturity
			)
			*
			cdf(
				normal,
				d1
			)
			-
			strike
			*
			std::exp(
				-rate
				*
				maturity
			)
			*
			cdf(
				normal,
				d2
			);
	}

	return
		strike
		*
		std::exp(
			-rate
			*
			maturity
		)
		*
		cdf(
			normal,
			-d2
		)
		-
		spot
		*
		std::exp(
			-dividendYield
			*
			maturity
		)
		*
		cdf(
			normal,
			-d1
		);
}

double BlackScholesAnalyticEngine::BinaryPrice(
	double strike,
	double maturity,
	OptionType optionType,
	const MarketData& market
)
{
	boost::math::normal_distribution<>
		normal(
			0.0,
			1.0
		);

	double d2 =
		D2(
			strike,
			maturity,
			market
		);

	double discountFactor =
		std::exp(
			-market.Rate()
			*
			maturity
		);

	if (optionType == OptionType::Call)
	{
		return
			discountFactor
			*
			cdf(
				normal,
				d2
			);
	}

	return
		discountFactor
		*
		cdf(
			normal,
			-d2
		);
}