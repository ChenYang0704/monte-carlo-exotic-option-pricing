/*
Author: Koh Chen Yang
File: TestPrinter.hpp
Description:
Header file for TestPrinter class.

Provides utility functions for displaying test results
and comparisons between analytical and Monte Carlo prices.
*/

#ifndef TESTPRINTER_HPP
#define TESTPRINTER_HPP

#include <string>

class TestPrinter
{
public:
	static void PrintComparison(
		const std::string& title,
		double analyticalPrice,
		double monteCarloPrice,
		double confidenceIntervalLower,
		double confidenceIntervalUpper
	);
};

#endif