/*
Author: Koh Chen Yang
File: TestMonteCarloEngine.cpp
Description:
Test program for MonteCarloEngine class.

Performs engine-level checks including reproducibility,
simulation convergence and zero-volatility deterministic
behaviour.
*/

#include "Core/MarketData.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"

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

	EuropeanOption europeanCall(
		100.0,				// Strike price
		1.0,				// Maturity (years)
		OptionType::Call	// Option type
	);

	// Reproducibility test
	MonteCarloEngine engine1(
		100000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	MonteCarloEngine engine2(
		100000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	MonteCarloResult result1 =
		engine1.Price(
			europeanCall,
			market
		);

	MonteCarloResult result2 =
		engine2.Price(
			europeanCall,
			market
		);

	PrintCheck(
		"Reproducibility Test",
		"Same seed and same settings should produce the same price",
		std::fabs(
			result1.price
			-
			result2.price
		)
		< 1.0e-12
	);

	// Simulation convergence study
	MonteCarloEngine lowSimulationEngine(
		1000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	MonteCarloEngine highSimulationEngine(
		100000,	// Number of simulations
		256,	// Number of time steps
		12345	// Random seed
	);

	MonteCarloResult lowSimulationResult =
		lowSimulationEngine.Price(
			europeanCall,
			market
		);

	MonteCarloResult highSimulationResult =
		highSimulationEngine.Price(
			europeanCall,
			market
		);

	ResultPrinter::Print(
		"European Call - 1,000 Simulations",
		lowSimulationResult
	);

	ResultPrinter::Print(
		"European Call - 100,000 Simulations",
		highSimulationResult
	);

	PrintCheck(
		"Simulation Convergence Test",
		"100,000 simulations should produce lower standard error than 1,000 simulations",
		highSimulationResult.standardError
		<
		lowSimulationResult.standardError
	);

	// Zero-volatility deterministic test
	MarketData zeroVolMarket(
		100.0,	// Spot price
		0.05,	// Risk-free rate
		0.00,	// Volatility
		0.00	// Dividend yield
	);

	MonteCarloResult zeroVolResult =
		engine1.Price(
			europeanCall,
			zeroVolMarket
		);

	double terminalPrice =
		zeroVolMarket.Spot()
		*
		std::exp(
			(
				zeroVolMarket.Rate()
				-
				zeroVolMarket.DividendYield()
				)
			*
			europeanCall.Maturity()
		);

	double deterministicPrice =
		std::exp(
			-zeroVolMarket.Rate()
			*
			europeanCall.Maturity()
		)
		*
		std::max(
			terminalPrice
			-
			europeanCall.Strike(),
			0.0
		);

	PrintCheck(
		"Zero Volatility Test",
		"Monte Carlo price should match deterministic discounted payoff",
		std::fabs(
			zeroVolResult.price
			-
			deterministicPrice
		)
		< 1.0e-10
	);

	return 0;
}