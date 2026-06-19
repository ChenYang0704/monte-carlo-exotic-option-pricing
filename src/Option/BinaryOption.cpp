/*
Author: Koh Chen Yang
File: BinaryOption.cpp
Description:
Implementation file for BinaryOption class.
*/

#include "Option/BinaryOption.hpp"

#include <stdexcept>

BinaryOption::BinaryOption(
	double strike,
	double maturity,
	OptionType optionType
)
	: Option(
		strike,
		maturity,
		optionType
	)
{
}

BinaryOption::~BinaryOption()
{
}

double BinaryOption::Payoff(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"BinaryOption payoff requires a non-empty path."
		);
	}

	double terminalPrice = path.back();

	// Binary Call Payoff
	if (Type() == OptionType::Call)
	{
		if (terminalPrice > Strike())
		{
			return 1.0;
		}

		return 0.0;
	}

	// Binary Put Payoff
	if (terminalPrice < Strike())
	{
		return 1.0;
	}

	return 0.0;
}