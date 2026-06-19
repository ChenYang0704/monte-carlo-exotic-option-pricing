/*
Author: Koh Chen Yang
File: ExampleBarrier.cpp
Description:
Example program for pricing single-barrier knock-in and
knock-out options using the Monte Carlo pricing engine.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/BarrierOption.hpp"

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

	// Up-and-Out call option
	BarrierOption upAndOutCall(
		100.0,						// Strike price
		1.0,						// Maturity (years)
		120.0,						// Barrier level
		OptionType::Call,			// Option type
		BarrierType::KnockOut,		// Barrier type
		BarrierDirection::Up		// Barrier direction
	);

	// Up-and-In call option
	BarrierOption upAndInCall(
		100.0,						// Strike price
		1.0,						// Maturity (years)
		120.0,						// Barrier level
		OptionType::Call,			// Option type
		BarrierType::KnockIn,		// Barrier type
		BarrierDirection::Up		// Barrier direction
	);

	// Down-and-Out put option
	BarrierOption downAndOutPut(
		100.0,						// Strike price
		1.0,						// Maturity (years)
		80.0,						// Barrier level
		OptionType::Put,			// Option type
		BarrierType::KnockOut,		// Barrier type
		BarrierDirection::Down		// Barrier direction
	);

	// Down-and-In put option
	BarrierOption downAndInPut(
		100.0,						// Strike price
		1.0,						// Maturity (years)
		80.0,						// Barrier level
		OptionType::Put,			// Option type
		BarrierType::KnockIn,		// Barrier type
		BarrierDirection::Down		// Barrier direction
	);

	ResultPrinter::Print(
		"Up-and-Out Call",
		engine.Price(
			upAndOutCall,
			market
		)
	);

	ResultPrinter::Print(
		"Up-and-In Call",
		engine.Price(
			upAndInCall,
			market
		)
	);

	ResultPrinter::Print(
		"Down-and-Out Put",
		engine.Price(
			downAndOutPut,
			market
		)
	);

	ResultPrinter::Print(
		"Down-and-In Put",
		engine.Price(
			downAndInPut,
			market
		)
	);

	return 0;
}