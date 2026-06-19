/*
Author: Koh Chen Yang
File: Statistics.hpp
Description:
Header file for Statistics class.

Provides utility functions for computing summary
statistics from Monte Carlo simulation results.
*/

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

class Statistics
{
public:
	static double Mean(
		const std::vector<double>& values
	);

	static double Variance(
		const std::vector<double>& values
	);

	static double StandardDeviation(
		const std::vector<double>& values
	);

	static double StandardError(
		const std::vector<double>& values
	);

	static double ConfidenceIntervalLower(
		double mean,
		double standardError
	);

	static double ConfidenceIntervalUpper(
		double mean,
		double standardError
	);
};

#endif