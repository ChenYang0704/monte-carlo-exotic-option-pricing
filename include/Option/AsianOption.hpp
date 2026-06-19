/*
Author: Koh Chen Yang
File: AsianOption.hpp
Description:
Header file for AsianOption class.

Defines a fixed-strike or floating-strike arithmetic
Asian call or put option. The payoff depends on the
average stock price over the simulated path.
*/

#ifndef ASIANOPTION_HPP
#define ASIANOPTION_HPP

#include "Option/Option.hpp"

class AsianOption : public Option
{
private:
	StrikeType m_strikeType;

public:
	AsianOption(
		double strike,
		double maturity,
		OptionType optionType,
		StrikeType strikeType
	);

	virtual ~AsianOption();

	StrikeType StrikeStyle() const;

	double Payoff(
		const std::vector<double>& path
	) const override;
};

#endif