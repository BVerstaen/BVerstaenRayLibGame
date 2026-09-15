#pragma once
#include <vector>
#include <string>

class ScoreSystem
{
public:
	ScoreSystem();

public:
	void UpdateScore(float deltaTime, float backgroundSpeed);
	void ResetScore();
	bool AddScoreToHighScore();

private:
	void SaveHighScore();
	void LoadHighScore();

public :
	std::vector<int> HighScoreList;
	const int HighScoreLimit;
	int CurrentScore;

private:
	const std::string m_highScoreFileName;
	float m_gameTimer;
};