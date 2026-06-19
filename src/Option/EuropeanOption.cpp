/*
Author: Koh Chen Yang
File: EuropeanOption.cpp
Description:
Implementation file for EuropeanOption class.
*/

#include "Option/EuropeanOption.hpp"

#include <algorithm>
#include <stdexcept>

EuropeanOption::EuropeanOption(
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

EuropeanOption::~EuropeanOption()
{
}

double EuropeanOption::Payoff(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"EuropeanOption payoff requires a non-empty path."
		);
	}

	double terminalPrice = path.back();

	// European Call Payoff
	if (m_optionType == OptionType::Call) 
	{
		return std::max(
			terminalPrice - m_strike,
			0.0
		);
	}

	// European Put Payoff
	return std::max(
		m_strike - terminalPrice,
		0.0
	);
}