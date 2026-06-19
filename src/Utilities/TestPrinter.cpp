/*
Author: Koh Chen Yang
File: TestPrinter.cpp
Description:
Implementation file for TestPrinter class.

Provides utility functions for displaying test results
and comparisons between analytical and Monte Carlo prices.
*/

#include "Utilities/TestPrinter.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

void TestPrinter::PrintComparison(
	const std::string& title,
	double analyticalPrice,
	double monteCarloPrice,
	double confidenceIntervalLower,
	double confidenceIntervalUpper
)
{
	double absoluteError =
		std::fabs(
			monteCarloPrice
			-
			analyticalPrice
		);

	bool insideConfidenceInterval =
		(
			analyticalPrice >= confidenceIntervalLower
			)
		&&
		(
			analyticalPrice <= confidenceIntervalUpper
			);

	std::cout
		<< std::fixed
		<< std::setprecision(6);

	std::cout
		<< "=================================================\n"
		<< title
		<< "\n"
		<< "=================================================\n\n";

	std::cout
		<< "Analytical Price: "
		<< analyticalPrice
		<< "\n";

	std::cout
		<< "Monte Carlo Price: "
		<< monteCarloPrice
		<< "\n";

	std::cout
		<< "Absolute Error: "
		<< absoluteError
		<< "\n";

	std::cout
		<< "95% Confidence Interval: ["
		<< confidenceIntervalLower
		<< ", "
		<< confidenceIntervalUpper
		<< "]\n";

	std::cout
		<< "Analytical Price Within CI: "
		<< (insideConfidenceInterval ? "YES" : "NO")
		<< "\n\n";
}