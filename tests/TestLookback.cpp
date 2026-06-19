/*
Author: Koh Chen Yang
File: TestLookback.cpp
Description:
Test program for lookback option pricing.

Performs sanity checks for fixed-strike and floating-strike
lookback options using dominance, volatility monotonicity,
zero-volatility behaviour and timestep sensitivity.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"
#include "Option/LookbackOption.hpp"

#include "Engine/MonteCarloEngine.hpp"

#include "Utilities/ResultPrinter.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

static void PrintCheck(
	const std::string& title,
	const std::string& condition,
	bool passed
)
{
	std::cout
		<< "=================================================\n"
		<< title
		<< "\n"
		<< "=================================================\n";

	std::cout
		<< "Condition: "
		<< condition
		<< "\n";

	std::cout
		<< "Test Result: "
		<< (passed ? "PASS" : "FAIL")
		<< "\n\n";
}

int main()
{
	std::cout
		<< std::fixed
		<< std::setprecision(6);

	MarketData market(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.20,	// Volatility
		0.00	// Dividend yield
	);

	MonteCarloEngine engine(
		100000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	EuropeanOption europeanCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call	// Option type
	);

	EuropeanOption europeanPut(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put		// Option type
	);

	LookbackOption fixedLookbackCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call,	// Option type
		StrikeType::Fixed	// Strike type
	);

	LookbackOption fixedLookbackPut(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put,	// Option type
		StrikeType::Fixed	// Strike type
	);

	LookbackOption floatingLookbackCall(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Call,		// Option type
		StrikeType::Floating	// Strike type
	);

	LookbackOption floatingLookbackPut(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Put,		// Option type
		StrikeType::Floating	// Strike type
	);

	MonteCarloResult europeanCallResult =
		engine.Price(
			europeanCall,
			market
		);

	MonteCarloResult europeanPutResult =
		engine.Price(
			europeanPut,
			market
		);

	MonteCarloResult fixedCallResult =
		engine.Price(
			fixedLookbackCall,
			market
		);

	MonteCarloResult fixedPutResult =
		engine.Price(
			fixedLookbackPut,
			market
		);

	MonteCarloResult floatingCallResult =
		engine.Price(
			floatingLookbackCall,
			market
		);

	MonteCarloResult floatingPutResult =
		engine.Price(
			floatingLookbackPut,
			market
		);

	PrintCheck(
		"Fixed Lookback Call Dominance",
		"Fixed Lookback Call >= European Call",
		fixedCallResult.price >= europeanCallResult.price
	);

	PrintCheck(
		"Fixed Lookback Put Dominance",
		"Fixed Lookback Put >= European Put",
		fixedPutResult.price >= europeanPutResult.price
	);

	PrintCheck(
		"Floating Lookback Call Non-Negativity",
		"Floating Lookback Call >= 0",
		floatingCallResult.price >= 0.0
	);

	PrintCheck(
		"Floating Lookback Put Non-Negativity",
		"Floating Lookback Put >= 0",
		floatingPutResult.price >= 0.0
	);

	// Volatility monotonicity test
	MarketData lowVolMarket(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.10,	// Volatility
		0.00	// Dividend yield
	);

	MarketData highVolMarket(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.40,	// Volatility
		0.00	// Dividend yield
	);

	double lowVolFixedCallPrice =
		engine.Price(
			fixedLookbackCall,
			lowVolMarket
		).price;

	double highVolFixedCallPrice =
		engine.Price(
			fixedLookbackCall,
			highVolMarket
		).price;

	PrintCheck(
		"Lookback Volatility Monotonicity",
		"Fixed Lookback Call price increases with volatility",
		highVolFixedCallPrice >= lowVolFixedCallPrice
	);

	// Timestep sensitivity test
	MonteCarloEngine coarseEngine(
		100000,	// Number of simulations
		4,		// Number of time steps
		12345	// Random seed
	);

	MonteCarloEngine fineEngine(
		100000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	MonteCarloResult coarseLookbackResult =
		coarseEngine.Price(
			fixedLookbackCall,
			market
		);

	MonteCarloResult fineLookbackResult =
		fineEngine.Price(
			fixedLookbackCall,
			market
		);

	ResultPrinter::Print(
		"Fixed Lookback Call - 4 Time Steps",
		coarseLookbackResult
	);

	ResultPrinter::Print(
		"Fixed Lookback Call - 256 Time Steps",
		fineLookbackResult
	);

	PrintCheck(
		"Lookback Timestep Sensitivity Test",
		"Finer monitoring should usually increase a fixed lookback call price",
		fineLookbackResult.price
		>=
		coarseLookbackResult.price
	);

	return 0;
}