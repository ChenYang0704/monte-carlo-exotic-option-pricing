/*
Author: Koh Chen Yang
File: ExampleLookback.cpp
Description:
Example program for pricing fixed-strike and floating-strike
lookback options using the Monte Carlo pricing engine.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/LookbackOption.hpp"

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

	// Fixed-strike lookback call
	LookbackOption fixedCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call,	// Option type
		StrikeType::Fixed	// Strike type
	);

	// Fixed-strike lookback put
	LookbackOption fixedPut(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put,	// Option type
		StrikeType::Fixed	// Strike type
	);

	// Floating-strike lookback call
	LookbackOption floatingCall(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Call,		// Option type
		StrikeType::Floating	// Strike type
	);

	// Floating-strike lookback put
	LookbackOption floatingPut(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Put,		// Option type
		StrikeType::Floating	// Strike type
	);

	ResultPrinter::Print(
		"Fixed-Strike Lookback Call",
		engine.Price(
			fixedCall,
			market
		)
	);

	ResultPrinter::Print(
		"Fixed-Strike Lookback Put",
		engine.Price(
			fixedPut,
			market
		)
	);

	ResultPrinter::Print(
		"Floating-Strike Lookback Call",
		engine.Price(
			floatingCall,
			market
		)
	);

	ResultPrinter::Print(
		"Floating-Strike Lookback Put",
		engine.Price(
			floatingPut,
			market
		)
	);

	return 0;
}