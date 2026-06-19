/*
Author: Koh Chen Yang
File: MonteCarloResult.hpp
Description:
Header file for MonteCarloResult structure.

Stores the output of a Monte Carlo pricing simulation,
including the estimated option price and statistical
measures of simulation error.
*/

#ifndef MONTECARLORESULT_HPP
#define MONTECARLORESULT_HPP

struct MonteCarloResult
{
	double price;

	double standardDeviation;
	double standardError;

	double confidenceIntervalLower;
	double confidenceIntervalUpper;
};

#endif