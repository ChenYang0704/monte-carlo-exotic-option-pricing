/*
Author: Koh Chen Yang
File: LookbackOption.hpp
Description:
Header file for LookbackOption class.

Defines a fixed-strike or floating-strike lookback
call or put option. The payoff depends on the maximum
or minimum stock price observed over the simulated path.
*/

#ifndef LOOKBACKOPTION_HPP
#define LOOKBACKOPTION_HPP

#include "Option/Option.hpp"

class LookbackOption : public Option
{
private:
	StrikeType m_strikeType;

public:
	LookbackOption(
		double strike,
		double maturity,
		OptionType optionType,
		StrikeType strikeType
	);

	virtual ~LookbackOption();

	StrikeType StrikeStyle() const;

	double Payoff(
		const std::vector<double>& path
	) const override;
};

#endif