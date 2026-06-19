/*
Author: Koh Chen Yang
File: ExampleTimestepSensitivity.cpp
Description:
Example program demonstrating timestep sensitivity for
path-dependent exotic options.

Asian, barrier and lookback options are tested separately
because their timestep sensitivity comes from different
path-monitoring effects.
*/

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"

#include "Option/OptionEnums.hpp"
#include "Option/AsianOption.hpp"
#include "Option/BarrierOption.hpp"
#include "Option/LookbackOption.hpp"

#include "Engine/MonteCarloEngine.hpp"

#include <iostream>
#include <iomanip>
#include <vector>

static void PrintHeader()
{
	std::cout
		<< std::setw(15) << "Time Steps"
		<< std::setw(15) << "Price"
		<< std::setw(15) << "Change"
		<< std::setw(15) << "Std Error"
		<< "\n";

	std::cout
		<< std::string(60, '-')
		<< "\n";
}

static void PrintRow(
	int numberOfTimeSteps,
	const MonteCarloResult& result,
	double change
)
{
	std::cout
		<< std::setw(15) << numberOfTimeSteps
		<< std::setw(15) << result.price
		<< std::setw(15) << change
		<< std::setw(15) << result.standardError
		<< "\n";
}

static void RunTimestepSensitivity(
	const std::string& title,
	const Option& option,
	const MarketData& market,
	const std::vector<int>& timeSteps,
	int numberOfSimulations,
	int seed
)
{
	std::cout
		<< title
		<< "\n\n";

	PrintHeader();

	double previousPrice = 0.0;

	for (std::size_t i = 0; i < timeSteps.size(); ++i)
	{
		MonteCarloEngine engine(
			numberOfSimulations,
			timeSteps[i],
			seed
		);

		MonteCarloResult result =
			engine.Price(
				option,
				market
			);

		double change = 0.0;

		if (i > 0)
		{
			change =
				result.price
				-
				previousPrice;
		}

		PrintRow(
			timeSteps[i],
			result,
			change
		);

		previousPrice =
			result.price;
	}

	std::cout << "\n";
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

	AsianOption asianCall(
		100.0,
		1.0,
		OptionType::Call,
		StrikeType::Fixed
	);

	BarrierOption barrierCall(
		100.0,
		1.0,
		120.0,
		OptionType::Call,
		BarrierType::KnockOut,
		BarrierDirection::Up
	);

	LookbackOption lookbackCall(
		100.0,
		1.0,
		OptionType::Call,
		StrikeType::Fixed
	);

	std::vector<int> standardTimeSteps;

	standardTimeSteps.push_back(4);
	standardTimeSteps.push_back(16);
	standardTimeSteps.push_back(64);
	standardTimeSteps.push_back(256);
	standardTimeSteps.push_back(1024);

	std::vector<int> extendedTimeSteps = standardTimeSteps;

	extendedTimeSteps.push_back(4096);

	int numberOfSimulations = 100000;
	int seed = 12345;

	std::cout
		<< "Timestep Sensitivity for Path-Dependent Options\n\n";

	RunTimestepSensitivity(
		"Asian Fixed-Strike Call",
		asianCall,
		market,
		standardTimeSteps,
		numberOfSimulations,
		seed
	);

	RunTimestepSensitivity(
		"Up-and-Out Barrier Call",
		barrierCall,
		market,
		extendedTimeSteps,
		numberOfSimulations,
		seed
	);

	RunTimestepSensitivity(
		"Fixed-Strike Lookback Call",
		lookbackCall,
		market,
		extendedTimeSteps,
		numberOfSimulations,
		seed
	);

	return 0;
}