/*
Author: Koh Chen Yang
File: BinaryOption.hpp
Description:
Header file for BinaryOption class.

Defines a binary call or put option.
The payoff depends only on the terminal stock price
at maturity.
*/

#ifndef BINARYOPTION_HPP
#define BINARYOPTION_HPP

#include "Option/Option.hpp"

class BinaryOption : public Option
{
public:
	BinaryOption(
		double strike,
		double maturity,
		OptionType optionType
	);

	virtual ~BinaryOption();

	double Payoff(
		const std::vector<double>& path
	) const override;
};

#endif