/*
Author: Koh Chen Yang
File: LookbackOption.cpp
Description:
Implementation file for LookbackOption class.
*/

#include "Option/LookbackOption.hpp"

#include <algorithm>
#include <stdexcept>

LookbackOption::LookbackOption(
	double strike,
	double maturity,
	OptionType optionType,
	StrikeType strikeType
)
	: Option(
		strike,
		maturity,
		optionType
	),
	m_strikeType(strikeType)
{
}

LookbackOption::~LookbackOption()
{
}

StrikeType LookbackOption::StrikeStyle() const
{
	return m_strikeType;
}

double LookbackOption::Payoff(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"LookbackOption payoff requires a non-empty path."
		);
	}

	double terminalPrice =
		path.back();

	double maximumPrice =
		*std::max_element(
			path.begin(),
			path.end()
		);

	double minimumPrice =
		*std::min_element(
			path.begin(),
			path.end()
		);

	if (m_strikeType == StrikeType::Fixed)
	{
		// Fixed Strike Lookback Call Payoff
		if (m_optionType == OptionType::Call)
		{
			return std::max(
				maximumPrice - m_strike,
				0.0
			);
		}

		// Fixed Strike Lookback Put Payoff
		return std::max(
			m_strike - minimumPrice,
			0.0
		);
	}

	// Floating Strike Lookback Call Payoff
	if (m_optionType == OptionType::Call)
	{
		return std::max(
			terminalPrice - minimumPrice,
			0.0
		);
	}

	// Floating Strike Lookback Put Payoff
	return std::max(
		maximumPrice - terminalPrice,
		0.0
	);
}