/*
Author: Koh Chen Yang
File: TestAsian.cpp
Description:
Test program for arithmetic Asian option pricing.

Performs sanity checks for fixed-strike and floating-strike
Asian options. Since arithmetic Asian options do not have a
simple Black-Scholes closed-form formula, validation is based
on economic relationships and timestep sensitivity checks.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"
#include "Option/AsianOption.hpp"

#include "Engine/MonteCarloEngine.hpp"

#include "Utilities/ResultPrinter.hpp"

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

	AsianOption fixedAsianCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call,	// Option type
		StrikeType::Fixed	// Strike type
	);

	AsianOption fixedAsianPut(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Put,	// Option type
		StrikeType::Fixed	// Strike type
	);

	AsianOption floatingAsianCall(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Call,		// Option type
		StrikeType::Floating	// Strike type
	);

	AsianOption floatingAsianPut(
		100.0,					// Dummy strike (unused)
		1.0,					// Maturity (years)
		OptionType::Put,		// Option type
		StrikeType::Floating	// Strike type
	);

	MonteCarloResult europeanCallResult =
		engine.Price(europeanCall, market);

	MonteCarloResult europeanPutResult =
		engine.Price(europeanPut, market);

	MonteCarloResult fixedAsianCallResult =
		engine.Price(fixedAsianCall, market);

	MonteCarloResult fixedAsianPutResult =
		engine.Price(fixedAsianPut, market);

	MonteCarloResult floatingAsianCallResult =
		engine.Price(floatingAsianCall, market);

	MonteCarloResult floatingAsianPutResult =
		engine.Price(floatingAsianPut, market);

	PrintCheck(
		"Fixed Asian Call vs European Call",
		"Fixed Asian Call <= European Call",
		fixedAsianCallResult.price <= europeanCallResult.price
	);

	PrintCheck(
		"Fixed Asian Put vs European Put",
		"Fixed Asian Put <= European Put",
		fixedAsianPutResult.price <= europeanPutResult.price
	);

	PrintCheck(
		"Floating Asian Call Non-Negativity",
		"Floating Asian Call >= 0",
		floatingAsianCallResult.price >= 0.0
	);

	PrintCheck(
		"Floating Asian Put Non-Negativity",
		"Floating Asian Put >= 0",
		floatingAsianPutResult.price >= 0.0
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

	MonteCarloResult coarseAsianResult =
		coarseEngine.Price(
			fixedAsianCall,
			market
		);

	MonteCarloResult fineAsianResult =
		fineEngine.Price(
			fixedAsianCall,
			market
		);

	ResultPrinter::Print(
		"Fixed Asian Call - 4 Time Steps",
		coarseAsianResult
	);

	ResultPrinter::Print(
		"Fixed Asian Call - 256 Time Steps",
		fineAsianResult
	);

	PrintCheck(
		"Asian Timestep Sensitivity Test",
		"Asian option price should change when averaging frequency changes",
		std::fabs(
			coarseAsianResult.price
			-
			fineAsianResult.price
		)
		>
		1.0e-6
	);

	return 0;
}