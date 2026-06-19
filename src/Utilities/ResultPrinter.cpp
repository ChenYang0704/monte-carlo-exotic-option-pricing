/*
Author: Koh Chen Yang
File: ResultPrinter.cpp
Description:
Implementation file for ResultPrinter class.

Provides utility functions for displaying Monte Carlo
pricing results.
*/

#include "Utilities/ResultPrinter.hpp"

#include <iostream>
#include <iomanip>

void ResultPrinter::Print(
	const std::string& title,
	const MonteCarloResult& result
)
{
	std::cout
		<< std::fixed
		<< std::setprecision(6);

	std::cout
		<< title
		<< "\n";

	std::cout
		<< "Price: "
		<< result.price
		<< "\n";

	std::cout
		<< "Standard Deviation: "
		<< result.standardDeviation
		<< "\n";

	std::cout
		<< "Standard Error: "
		<< result.standardError
		<< "\n";

	std::cout
		<< "95% Confidence Interval: ["
		<< result.confidenceIntervalLower
		<< ", "
		<< result.confidenceIntervalUpper
		<< "]\n\n";
}