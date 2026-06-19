/*
Author: Koh Chen Yang
File: BarrierOption.cpp
Description:
Implementation file for BarrierOption class.
*/

#include "Option/BarrierOption.hpp"

#include <algorithm>
#include <stdexcept>

BarrierOption::BarrierOption(
	double strike,
	double maturity,
	double barrier,
	OptionType optionType,
	BarrierType barrierType,
	BarrierDirection barrierDirection
)
	: Option(
		strike,
		maturity,
		optionType
	),
	m_barrier(barrier),
	m_barrierType(barrierType),
	m_barrierDirection(barrierDirection)
{
}

BarrierOption::~BarrierOption()
{
}

double BarrierOption::Barrier() const
{
	return m_barrier;
}

BarrierType BarrierOption::TypeOfBarrier() const
{
	return m_barrierType;
}

BarrierDirection BarrierOption::Direction() const
{
	return m_barrierDirection;
}

bool BarrierOption::BarrierTouched(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"BarrierOption requires a non-empty path."
		);
	}

	for (std::size_t i = 0; i < path.size(); ++i)
	{
		if (m_barrierDirection == BarrierDirection::Up)
		{
			if (path[i] >= m_barrier)
			{
				return true;
			}
		}
		else
		{
			if (path[i] <= m_barrier)
			{
				return true;
			}
		}
	}

	return false;
}

double BarrierOption::Payoff(
	const std::vector<double>& path
) const
{
	if (path.empty())
	{
		throw std::invalid_argument(
			"BarrierOption payoff requires a non-empty path."
		);
	}

	bool touched =
		BarrierTouched(
			path
		);

	// Knock-Out Barrier Condition
	if (
		m_barrierType
		==
		BarrierType::KnockOut
		&&
		touched
		)
	{
		return 0.0;
	}

	// Knock-In Barrier Condition
	if (
		m_barrierType
		==
		BarrierType::KnockIn
		&&
		!touched
		)
	{
		return 0.0;
	}

	double terminalPrice =
		path.back();

	// Barrier Call Payoff
	if (m_optionType == OptionType::Call)
	{
		return std::max(
			terminalPrice - m_strike,
			0.0
		);
	}

	// Barrier Put Payoff
	return std::max(
		m_strike - terminalPrice,
		0.0
	);
}