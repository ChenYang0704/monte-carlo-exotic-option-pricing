/*
Author: Koh Chen Yang
File: MonteCarloEngine.hpp
Description:
Header file for MonteCarloEngine class.

Prices options using Monte Carlo simulation. The engine
generates stock price paths, evaluates option payoffs,
discounts the payoffs and computes summary statistics.
*/

#ifndef MONTECARLOENGINE_HPP
#define MONTECARLOENGINE_HPP

#include "Core/MarketData.hpp"
#include "Core/MonteCarloResult.hpp"
#include "Option/Option.hpp"

class MonteCarloEngine
{
private:
	int m_numberOfSimulations;
	int m_numberOfTimeSteps;
	unsigned int m_seed;

public:
	MonteCarloEngine(
		int numberOfSimulations,
		int numberOfTimeSteps,
		unsigned int seed
	);

	MonteCarloResult Price(
		const Option& option,
		const MarketData& market
	) const;
};

#endif