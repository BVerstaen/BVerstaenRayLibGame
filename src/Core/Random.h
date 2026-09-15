#pragma once
#include <random>

class Random
{
#pragma region Constructors / Desctructors / Movement
public:
	Random();
	~Random();
	Random(const Random& random) = delete;
	Random& operator=(const Random& random) = delete;

	Random(Random&& random) = delete;
	Random& operator=(Random&& random) = delete;
#pragma endregion

#pragma region Singleton
public:
	// Accès à l'instance globale de random (à utiliser de préférence)
	static Random& Instance();
private:
	static Random* s_instance;
#pragma endregion

private:
	std::mt19937 m_randomGen;

public:
	const float RandomRange(const float min, const float max);
	const int RandomRange(const int min, const int max);
};
