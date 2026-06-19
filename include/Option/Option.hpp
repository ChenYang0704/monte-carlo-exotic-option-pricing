/*
Author: Koh Chen Yang
File: Option.hpp
Description:
Header file for Option base class.

Defines the common interface and data members shared by
all option types supported by the Monte Carlo pricing
library.

Derived classes are responsible for implementing their
own payoff calculations.
*/

#ifndef OPTION_HPP
#define OPTION_HPP

#include "Option/OptionEnums.hpp"

#include <vector>

class Option
{
protected:
	double m_strike;
	double m_maturity;
	OptionType m_optionType;

public:
	Option(
		double strike,
		double maturity,
		OptionType optionType
	);

	virtual ~Option();

	double Strike() const;
	double Maturity() const;
	OptionType Type() const;

	virtual double Payoff(
		const std::vector<double>& path
	) const = 0;
};

#endif