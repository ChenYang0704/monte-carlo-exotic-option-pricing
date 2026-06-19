/*
Author: Koh Chen Yang
File: PathGenerator.cpp
Description:
Implementation file for PathGenerator class.

Generates simulated stock price paths under the
Black-Scholes geometric Brownian motion model.
*/

#include "Engine/PathGenerator.hpp"

#include <cmath>

PathGenerator::PathGenerator(
	const MarketData& market,
	int numberOfTimeSteps
)
	: m_market(market),
	m_numberOfTimeSteps(numberOfTimeSteps)
{
}

std::vector<double> PathGenerator::GeneratePath(
	double maturity,
	RandomNumberGenerator& rng
) const
{
	std::vector<double> path;

	path.reserve(
		m_numberOfTimeSteps + 1
	);

	double stockPrice =
		m_market.Spot();

	path.push_back(
		stockPrice
	);

	// Black-Scholes geometric Brownian motion:
	// S(t+dt) = S(t) * exp((r - q - 0.5 * sigma^2) * dt + sigma * sqrt(dt) * Z)
	// where Z ~ N(0,1)

	// Time increment
	double dt =
		maturity /
		static_cast<double>(
			m_numberOfTimeSteps
			);

	// Constant drift component
	double drift =
		(
			m_market.Rate()
			-
			m_market.DividendYield()
			-
			0.5
			*
			m_market.Volatility()
			*
			m_market.Volatility()
			)
		*
		dt;

	// Constant diffusion component
	double diffusion =
		m_market.Volatility()
		*
		std::sqrt(dt);

	for (int i = 0; i < m_numberOfTimeSteps; ++i)
	{
		double z =
			rng.Normal();

		stockPrice *=
			std::exp(
				drift
				+
				diffusion
				*
				z
			);

		path.push_back(
			stockPrice
		);
	}

	return path;
}

