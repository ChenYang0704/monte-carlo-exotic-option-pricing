/*
Author: Koh Chen Yang
File: RandomNumberGenerator.cpp
Description:
Implementation file for RandomNumberGenerator class.

Provides normally distributed random numbers for Monte Carlo
simulation using the C++ standard random library.
*/

#include "Core/RandomNumberGenerator.hpp"

RandomNumberGenerator::RandomNumberGenerator()
	: m_generator(12345),
	m_normalDistribution(0.0, 1.0)
{
}

RandomNumberGenerator::RandomNumberGenerator(
	unsigned int seed
)
	: m_generator(seed),
	m_normalDistribution(0.0, 1.0)
{
}

double RandomNumberGenerator::Normal()
{
	return m_normalDistribution(
		m_generator
	);
}