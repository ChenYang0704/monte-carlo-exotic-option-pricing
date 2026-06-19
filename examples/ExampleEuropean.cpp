/*
Author: Koh Chen Yang
File: ExampleEuropean.cpp
Description:
Example program for pricing European call and put options
using the Monte Carlo pricing engine.
*/

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"

#include "Engine/MonteCarloEngine.hpp"

#include "Utilities/ResultPrinter.hpp"

int main()
{
	// Market data
	MarketData market(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.20,	// Volatility
		0.00	// Dividend yield
	);

	// European call option
	EuropeanOption callOption(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call	// Option type
	);

	// European put option
	EuropeanOption putOption(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put		// Option type
	);

	// Monte Carlo engine
	MonteCarloEngine engine(
		100000,	// Number of simulations
		252,	// Number of time steps
		12345	// Random seed
	);

	// Price call option
	MonteCarloResult callResult =
		engine.Price(
			callOption,
			market
		);

	// Price put option
	MonteCarloResult putResult =
		engine.Price(
			putOption,
			market
		);

	// Print results
	ResultPrinter::Print(
		"European Call Option",
		callResult
	);

	ResultPrinter::Print(
		"European Put Option",
		putResult
	);

	return 0;
}