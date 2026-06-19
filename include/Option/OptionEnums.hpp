/*
Author: Koh Chen Yang
File: OptionEnums.hpp
Description:
Enumerations used throughout the Monte Carlo pricing library.

Defines the option characteristics required by the
supported exotic option types, including:

- OptionType (Call / Put)
- StrikeType (Fixed / Floating)
- BarrierType (Knock-In / Knock-Out)
- BarrierDirection (Up / Down)
*/

#ifndef OPTIONENUMS_HPP
#define OPTIONENUMS_HPP

enum class OptionType
{
	Call,
	Put
};

enum class StrikeType
{
	Fixed,
	Floating
};

enum class BarrierType
{
	KnockIn,
	KnockOut
};

enum class BarrierDirection
{
	Up,
	Down
};

#endif
