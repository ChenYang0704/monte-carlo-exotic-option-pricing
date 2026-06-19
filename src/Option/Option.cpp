/*
Author: Koh Chen Yang
File: Option.cpp
Description:
Implementation file for Option base class.
*/

#include "Option/Option.hpp"

Option::Option(
	double strike,
	double maturity,
	OptionType optionType
)
	: m_strike(strike),
	m_maturity(maturity),
	m_optionType(optionType)
{
}

Option::~Option()
{
}

double Option::Strike() const
{
	return m_strike;
}

double Option::Maturity() const
{
	return m_maturity;
}

OptionType Option::Type() const
{
	return m_optionType;
}