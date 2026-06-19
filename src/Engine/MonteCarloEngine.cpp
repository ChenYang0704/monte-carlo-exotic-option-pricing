/*
Author: Koh Chen Yang
File: MonteCarloEngine.cpp
Description:
Implementation file for MonteCarloEngine class.

Prices options using Monte Carlo simulation. The engine
generates stock price paths, evaluates option payoffs,
discounts the payoffs and computes summary statistics.
*/

#include "Engine/MonteCarloEngine.hpp"

#include "Core/RandomNumberGenerator.hpp"
#include "Core/Statistics.hpp"
#include "Engine/PathGenerator.hpp"

#include <cmath>
#include <vector>

MonteCarloEngine::MonteCarloEngine(
	int numberOfSimulations,
	int numberOfTimeSteps,
	unsigned int seed
)
	: m_numberOfSimulations(numberOfSimulations),
	m_numberOfTimeSteps(numberOfTimeSteps),
	m_seed(seed)
{
}

MonteCarloResult MonteCarloEngine::Price(
	const Option& option,
	const MarketData& market
) const
{
	RandomNumberGenerator rng(
		m_seed
	);

	PathGenerator pathGenerator(
		market,
		m_numberOfTimeSteps
	);

	std::vector<double> discountedPayoffs;

	discountedPayoffs.reserve(
		m_numberOfSimulations
	);

	double discountFactor =
		std::exp(
			-market.Rate()
			*
			option.Maturity()
		);

	for (int i = 0;
		i < m_numberOfSimulations;
		++i)
	{
		std::vector<double> path =
			pathGenerator.GeneratePath(
				option.Maturity(),
				rng
			);

		double payoff =
			option.Payoff(
				path
			);

		discountedPayoffs.push_back(
			discountFactor
			*
			payoff
		);
	}

	MonteCarloResult result;

	result.price =
		Statistics::Mean(
			discountedPayoffs
		);

	result.standardDeviation =
		Statistics::StandardDeviation(
			discountedPayoffs
		);

	result.standardError =
		Statistics::StandardError(
			discountedPayoffs
		);

	result.confidenceIntervalLower =
		Statistics::ConfidenceIntervalLower(
			result.price,
			result.standardError
		);

	result.confidenceIntervalUpper =
		Statistics::ConfidenceIntervalUpper(
			result.price,
			result.standardError
		);

	return result;
}