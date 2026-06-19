/*
Author: Koh Chen Yang
File: BarrierOption.hpp
Description:
Header file for BarrierOption class.

Defines an up/down knock-in or knock-out barrier
call or put option. The payoff depends on whether
the simulated stock path touches the barrier.
*/

#ifndef BARRIEROPTION_HPP
#define BARRIEROPTION_HPP

#include "Option/Option.hpp"

class BarrierOption : public Option
{
private:
	double m_barrier;
	BarrierType m_barrierType;
	BarrierDirection m_barrierDirection;

	bool BarrierTouched(
		const std::vector<double>& path
	) const;

public:
	BarrierOption(
		double strike,
		double maturity,
		double barrier,
		OptionType optionType,
		BarrierType barrierType,
		BarrierDirection barrierDirection
	);

	virtual ~BarrierOption();

	double Barrier() const;
	BarrierType TypeOfBarrier() const;
	BarrierDirection Direction() const;

	double Payoff(
		const std::vector<double>& path
	) const override;
};

#endif