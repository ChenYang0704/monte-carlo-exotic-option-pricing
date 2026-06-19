/*
Author: Koh Chen Yang
File: RandomNumberGenerator.hpp
Description:
Header file for RandomNumberGenerator class.

Provides normally distributed random numbers for Monte Carlo
simulation using the C++ standard random library.
*/

#ifndef RANDOMNUMBERGENERATOR_HPP
#define RANDOMNUMBERGENERATOR_HPP

#include <random>

class RandomNumberGenerator
{
private:
	std::mt19937 m_generator;
	std::normal_distribution<double> m_normalDistribution;

public:
	RandomNumberGenerator();
	RandomNumberGenerator(unsigned int seed);

	double Normal();
};

#endif