#pragma once
#include <random>
class Random
{
	static std::mt19937 random;
public:
	// allows to use Random::Number() in main
	// no need to create object of random type
	// persist for lifetime
	// NOT == global variables
	// "this" does not exist 
	// can ONLY access static variables 
	static int Int(int min, int max);
	static float Float(float min, float max);
};