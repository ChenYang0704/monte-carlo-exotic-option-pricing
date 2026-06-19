/*
Author: Koh Chen Yang
File: ResultPrinter.hpp
Description:
Header file for ResultPrinter class.

Provides utility functions for displaying Monte Carlo
pricing results.
*/

#ifndef RESULTPRINTER_HPP
#define RESULTPRINTER_HPP

#include "Core/MonteCarloResult.hpp"

#include <string>

class ResultPrinter
{
public:
	static void Print(
		const std::string& title,
		const MonteCarloResult& result
	);
};

#endif