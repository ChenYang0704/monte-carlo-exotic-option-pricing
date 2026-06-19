/*
Author: Koh Chen Yang
File: ExampleSimulationConvergence.cpp
Description:
Example program demonstrating how Monte Carlo standard
error decreases as the number of simulations increases.

The Monte Carlo price is compared against the analytical
Black-Scholes price to show how pricing accuracy improves
as the number of simulations increases.
*/

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/EuropeanOption.hpp"

#include "Engine/MonteCarloEngine.hpp"
#include "Engine/BlackScholesAnalyticEngine.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

static void PrintHeader()
{
	std::cout
		<< std::setw(15) << "Simulations"
		<< std::setw(15) << "MC Price"
		<< std::setw(15) << "Abs Error"
		<< std::setw(15) << "Std Error"
		<< std::setw(15) << "CI Half-Width"
		<< "\n";

	std::cout
		<< std::string(75, '-')
		<< "\n";
}

static void PrintRow(
	int numberOfSimulations,
	const MonteCarloResult& result,
	double analyticalPrice
)
{
	double confidenceIntervalHalfWidth =
		1.96 * result.standardError;

	double absoluteError =
		std::fabs(
			result.price - analyticalPrice
		);

	std::cout
		<< std::setw(15) << numberOfSimulations
		<< std::setw(15) << result.price
		<< std::setw(15) << absoluteError
		<< std::setw(15) << result.standardError
		<< std::setw(15) << confidenceIntervalHalfWidth
		<< "\n";
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

	double analyticalPrice =
		BlackScholesAnalyticEngine::EuropeanPrice(
			100.0,
			1.0,
			OptionType::Call,
			market
		);

	std::vector<int> simulationCounts;

	simulationCounts.push_back(1000);
	simulationCounts.push_back(10000);
	simulationCounts.push_back(100000);
	simulationCounts.push_back(1000000);

	std::cout
		<< "European Call Simulation Convergence\n\n";

	std::cout
		<< "Analytical Price: "
		<< analyticalPrice
		<< "\n\n";

	PrintHeader();

	for (std::size_t i = 0; i < simulationCounts.size(); ++i)
	{
		MonteCarloEngine engine(
			simulationCounts[i],	// Number of simulations
			256,					// Number of time steps
			12345					// Random seed
		);

		MonteCarloResult result =
			engine.Price(
				europeanCall,
				market
			);

		PrintRow(
			simulationCounts[i],
			result,
			analyticalPrice
		);
	}

	return 0;
}