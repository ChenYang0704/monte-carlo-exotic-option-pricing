/*
Author: Koh Chen Yang
File: AsianOption.cpp
Description:
Implementation file for AsianOption class.
*/

#include "Option/AsianOption.hpp"

#include <algorithm>
#include <stdexcept>

AsianOption::AsianOption(
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

AsianOption::~AsianOption()
{
}

StrikeType AsianOption::StrikeStyle() const
{
	return m_strikeType;
}

double AsianOption::Payoff(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"AsianOption payoff requires a non-empty path."
		);
	}

	double sum = 0.0;

	for (std::size_t i = 0; i < path.size(); ++i)
	{
		sum += path[i];
	}

	double averagePrice =
		sum / static_cast<double>(path.size());

	double terminalPrice =
		path.back();

	if (m_strikeType == StrikeType::Fixed)
	{
		// Asian Fixed Strike Call Payoff
		if (m_optionType == OptionType::Call)
		{
			return std::max(
				averagePrice - m_strike,
				0.0
			);
		}

		// Asian Fixed Strike Put Payoff
		return std::max(
			m_strike - averagePrice,
			0.0
		);
	}

	// Asian Floating Strike Call Payoff
	if (m_optionType == OptionType::Call)
	{
		return std::max(
			terminalPrice - averagePrice,
			0.0
		);
	}

	// Asian Floating Strike Put Payoff
	return std::max(
		averagePrice - terminalPrice,
		0.0
	);
}