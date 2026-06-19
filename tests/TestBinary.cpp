/*
Author: Koh Chen Yang
File: TestBinary.cpp
Description:
Test program for binary option pricing.

Compares Monte Carlo prices against analytical
Black-Scholes binary option prices for validation purposes.
*/

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/BinaryOption.hpp"

#include "Engine/MonteCarloEngine.hpp"
#include "Engine/BlackScholesAnalyticEngine.hpp"

#include "Utilities/TestPrinter.hpp"

#include <string>

static void RunTest(
	const std::string& title,
	const BinaryOption& option,
	const MarketData& market,
	const MonteCarloEngine& engine
)
{
	double analyticalPrice =
		BlackScholesAnalyticEngine::BinaryPrice(
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
		"ATM Binary Call",
		BinaryOption(
			100.0,				// Strike price
			1.0,				// Maturity (years)
			OptionType::Call	// Option type
		),
		market,
		engine
	);

	RunTest(
		"ATM Binary Put",
		BinaryOption(
			100.0,				// Strike price
			1.0,				// Maturity (years)
			OptionType::Put		// Option type
		),
		market,
		engine
	);

	RunTest(
		"Deep ITM Binary Call",
		BinaryOption(
			80.0,				// Strike price
			1.0,				// Maturity (years)
			OptionType::Call	// Option type
		),
		market,
		engine
	);

	RunTest(
		"Deep OTM Binary Call",
		BinaryOption(
			120.0,				// Strike price
			1.0,				// Maturity (years)
			OptionType::Call	// Option type
		),
		market,
		engine
	);

	return 0;
}