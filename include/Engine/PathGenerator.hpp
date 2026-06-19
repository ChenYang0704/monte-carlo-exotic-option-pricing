/*
Author: Koh Chen Yang
File: PathGenerator.hpp
Description:
Header file for PathGenerator class.

Generates simulated stock price paths under the
Black-Scholes geometric Brownian motion model.
*/

#ifndef PATHGENERATOR_HPP
#define PATHGENERATOR_HPP

#include "Core/MarketData.hpp"
#include "Core/RandomNumberGenerator.hpp"

#include <vector>

class PathGenerator
{
private:
	MarketData m_market;
	int m_numberOfTimeSteps;

public:
	PathGenerator(
		const MarketData& market,
		int numberOfTimeSteps
	);

	std::vector<double> GeneratePath(
		double maturity,
		RandomNumberGenerator& rng
	) const;
};

#endif