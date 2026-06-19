/*
Author: Koh Chen Yang
File: EuropeanOption.hpp
Description:
Header file for EuropeanOption class.

Defines a European call or put option. The payoff depends
only on the terminal stock price at maturity.
*/

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "Option/Option.hpp"

class EuropeanOption : public Option
{
public:
	EuropeanOption(
		double strike,
		double maturity,
		OptionType optionType
	);

	virtual ~EuropeanOption();

	double Payoff(
		const std::vector<double>& path
	) const override;
};

#endif