/*
Author: Koh Chen Yang
File: ExampleAsian.cpp
Description:
Example program for pricing arithmetic Asian options
using the Monte Carlo pricing engine.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/AsianOption.hpp"

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

	// Monte Carlo engine
	MonteCarloEngine engine(
		100000,	// Number of simulations
		252,	// Number of time steps
		12345	// Random seed
	);

	// Fixed-strike Asian call
	AsianOption fixedCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call,	// Option type
		StrikeType::Fixed	// Strike type
	);

	// Fixed-strike Asian put
	AsianOption fixedPut(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put,	// Option type
		StrikeType::Fixed	// Strike type
	);

	// Floating-strike Asian call
	AsianOption floatingCall(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Call,		// Option type
		StrikeType::Floating	// Strike type
	);

	// Floating-strike Asian put
	AsianOption floatingPut(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Put,		// Option type
		StrikeType::Floating	// Strike type
	);

	MonteCarloResult fixedCallResult =
		engine.Price(
			fixedCall,
			market
		);

	MonteCarloResult fixedPutResult =
		engine.Price(
			fixedPut,
			market
		);

	MonteCarloResult floatingCallResult =
		engine.Price(
			floatingCall,
			market
		);

	MonteCarloResult floatingPutResult =
		engine.Price(
			floatingPut,
			market
		);

	ResultPrinter::Print(
		"Fixed-Strike Asian Call",
		fixedCallResult
	);

	ResultPrinter::Print(
		"Fixed-Strike Asian Put",
		fixedPutResult
	);

	ResultPrinter::Print(
		"Floating-Strike Asian Call",
		floatingCallResult
	);

	ResultPrinter::Print(
		"Floating-Strike Asian Put",
		floatingPutResult
	);

	return 0;
}