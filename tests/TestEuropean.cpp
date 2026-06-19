/*
Author: Koh Chen Yang
File: TestEuropean.cpp
Description:
Test program for European option pricing.

Compares Monte Carlo prices against analytical
Black-Scholes prices for validation purposes.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"

#include "Engine/MonteCarloEngine.hpp"
#include "Engine/BlackScholesAnalyticEngine.hpp"

#include "Utilities/TestPrinter.hpp"

static void RunTest(
	const std::string& title,
	const EuropeanOption& option,
	const MarketData& market,
	const MonteCarloEngine& engine
)
{
	double analyticalPrice =
		BlackScholesAnalyticEngine::EuropeanPrice(
			option.Strike(),
			option.Maturity(),
			option.Type(),
			market
		);

	MonteCarloResult result =
		engine.Price(
			option,
			market
		);

	TestPrinter::PrintComparison(
		title,
		analyticalPrice,
		result.price,
		result.confidenceIntervalLower,
		result.confidenceIntervalUpper
	);
}

int main()
{
	MarketData market(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.20,	// Volatility
		0.00	// Dividend yield
	);

	MonteCarloEngine engine(
		100000,	// Number of simulations
		252,	// Number of time steps
		12345	// Random seed
	);

	RunTest(
		"ATM Call",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Call
		),
		market,
		engine
	);

	RunTest(
		"ATM Put",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Put
		),
		market,
		engine
	);

	RunTest(
		"Deep ITM Call",
		EuropeanOption(
			80.0,
			1.0,
			OptionType::Call
		),
		market,
		engine
	);

	RunTest(
		"Deep OTM Call",
		EuropeanOption(
			120.0,
			1.0,
			OptionType::Call
		),
		market,
		engine
	);

	return 0;
}