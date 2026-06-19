/*
Author: Koh Chen Yang
File: ExampleBinary.cpp
Description:
Example program for pricing binary call and put options
using the Monte Carlo pricing engine.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/BinaryOption.hpp"

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

	// Binary call option
	BinaryOption callOption(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call	// Option type
	);

	// Binary put option
	BinaryOption putOption(
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

	// Price binary call
	MonteCarloResult callResult =
		engine.Price(
			callOption,
			market
		);

	// Price binary put
	MonteCarloResult putResult =
		engine.Price(
			putOption,
			market
		);

	ResultPrinter::Print(
		"Binary Call Option",
		callResult
	);

	ResultPrinter::Print(
		"Binary Put Option",
		putResult
	);

	return 0;
}