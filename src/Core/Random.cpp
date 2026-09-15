#include "Random.h"
#include <stdexcept>

Random::Random()
{
	if (s_instance)
		throw std::runtime_error("There can only be one random");

	s_instance = this;

	//Get a new seed
	std::random_device rd;
	m_randomGen.seed(rd());
}

Random::~Random()
{
	s_instance = nullptr;
}

#pragma region Singleton

Random* Random::s_instance = nullptr;
Random& Random::Instance()
{
	if (!s_instance)
		throw std::runtime_error("No random was created");

	return *s_instance;
}

#pragma endregion

const float Random::RandomRange(const float min, const float max)
{
	std::uniform_real_distribution<> dis(min, max);
	return dis(m_randomGen);
}

const int Random::RandomRange(const int min, const int max)
{
	std::uniform_int_distribution<> dis(min, max);
	return dis(m_randomGen);
}
