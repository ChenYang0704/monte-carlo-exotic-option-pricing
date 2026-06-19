/*
Author: Koh Chen Yang
File: TestBarrier.cpp
Description:
Test program for single-barrier option pricing.

Validates barrier option prices using the knock-in /
knock-out parity relationship and timestep sensitivity
checks for barrier monitoring.
*/

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"
#include "Option/BarrierOption.hpp"

#include "Engine/MonteCarloEngine.hpp"

#include "Utilities/TestPrinter.hpp"
#include "Utilities/ResultPrinter.hpp"

#include <cmath>
#include <string>
#include <iostream>

static void RunParityTest(
	const std::string& title,
	const EuropeanOption& europeanOption,
	const BarrierOption& knockInOption,
	const BarrierOption& knockOutOption,
	const MarketData& market,
	const MonteCarloEngine& engine
)
{
	MonteCarloResult europeanResult =
		engine.Price(
			europeanOption,
			market
		);

	MonteCarloResult knockInResult =
		engine.Price(
			knockInOption,
			market
		);

	MonteCarloResult knockOutResult =
		engine.Price(
			knockOutOption,
			market
		);

	double barrierParityPrice =
		knockInResult.price
		+
		knockOutResult.price;

	TestPrinter::PrintComparison(
		title,
		europeanResult.price,
		barrierParityPrice,
		europeanResult.confidenceIntervalLower,
		europeanResult.confidenceIntervalUpper
	);
}

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

	RunParityTest(
		"Up Barrier Call Parity",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Call
		),
		BarrierOption(
			100.0,
			1.0,
			120.0,
			OptionType::Call,
			BarrierType::KnockIn,
			BarrierDirection::Up
		),
		BarrierOption(
			100.0,
			1.0,
			120.0,
			OptionType::Call,
			BarrierType::KnockOut,
			BarrierDirection::Up
		),
		market,
		engine
	);

	RunParityTest(
		"Down Barrier Call Parity",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Call
		),
		BarrierOption(
			100.0,
			1.0,
			80.0,
			OptionType::Call,
			BarrierType::KnockIn,
			BarrierDirection::Down
		),
		BarrierOption(
			100.0,
			1.0,
			80.0,
			OptionType::Call,
			BarrierType::KnockOut,
			BarrierDirection::Down
		),
		market,
		engine
	);

	RunParityTest(
		"Up Barrier Put Parity",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Put
		),
		BarrierOption(
			100.0,
			1.0,
			120.0,
			OptionType::Put,
			BarrierType::KnockIn,
			BarrierDirection::Up
		),
		BarrierOption(
			100.0,
			1.0,
			120.0,
			OptionType::Put,
			BarrierType::KnockOut,
			BarrierDirection::Up
		),
		market,
		engine
	);

	RunParityTest(
		"Down Barrier Put Parity",
		EuropeanOption(
			100.0,
			1.0,
			OptionType::Put
		),
		BarrierOption(
			100.0,
			1.0,
			80.0,
			OptionType::Put,
			BarrierType::KnockIn,
			BarrierDirection::Down
		),
		BarrierOption(
			100.0,
			1.0,
			80.0,
			OptionType::Put,
			BarrierType::KnockOut,
			BarrierDirection::Down
		),
		market,
		engine
	);

	// Timestep sensitivity test
	BarrierOption upAndOutCall(
		100.0,						// Strike price
		1.0,						// Maturity (years)
		120.0,						// Barrier level
		OptionType::Call,			// Option type
		BarrierType::KnockOut,		// Barrier type
		BarrierDirection::Up		// Barrier direction
	);

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

	MonteCarloResult coarseBarrierResult =
		coarseEngine.Price(
			upAndOutCall,
			market
		);

	MonteCarloResult fineBarrierResult =
		fineEngine.Price(
			upAndOutCall,
			market
		);

	ResultPrinter::Print(
		"Up-and-Out Call - 4 Time Steps",
		coarseBarrierResult
	);

	ResultPrinter::Print(
		"Up-and-Out Call - 256 Time Steps",
		fineBarrierResult
	);

	PrintCheck(
		"Barrier Timestep Sensitivity Test",
		"Finer monitoring should usually reduce an up-and-out option price",
		fineBarrierResult.price
		<=
		coarseBarrierResult.price
	);

	return 0;
}