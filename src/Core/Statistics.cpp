/*
Author: Koh Chen Yang
File: Statistics.cpp
Description:
Implementation file for Statistics class.

Provides utility functions for computing summary
statistics from Monte Carlo simulation results.
*/

#include "Core/Statistics.hpp"

#include <cmath>
#include <stdexcept>

double Statistics::Mean(
	const std::vector<double>& values
)
{
	if (values.empty())
	{
		throw std::invalid_argument(
			"Cannot compute mean of empty vector."
		);
	}

	double sum = 0.0;

	for (std::size_t i = 0; i < values.size(); ++i)
	{
		sum += values[i];
	}

	return sum / static_cast<double>(values.size());
}

double Statistics::Variance(
	const std::vector<double>& values
)
{
	if (values.size() < 2)
	{
		throw std::invalid_argument(
			"Variance requires at least two observations."
		);
	}

	double mean = Mean(values);

	double variance = 0.0;

	for (std::size_t i = 0; i < values.size(); ++i)
	{
		double difference = values[i] - mean;

		variance += difference * difference;
	}

	return variance /
		static_cast<double>(values.size() - 1);
}

double Statistics::StandardDeviation(
	const std::vector<double>& values
)
{
	return std::sqrt(
		Variance(values)
	);
}

double Statistics::StandardError(
	const std::vector<double>& values
)
{
	return StandardDeviation(values)
		/
		std::sqrt(
			static_cast<double>(values.size())
		);
}

double Statistics::ConfidenceIntervalLower(
	double mean,
	double standardError
)
{
	return mean - 1.96 * standardError;
}

double Statistics::ConfidenceIntervalUpper(
	double mean,
	double standardError
)
{
	return mean + 1.96 * standardError;
}