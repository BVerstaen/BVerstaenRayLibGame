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
	int CurrentScore;

private:
	float m_gameTimer;

private:
	void SaveHighScore();
	void LoadHighScore();

public :
	std::vector<int> HighScoreList;
	const int HighScoreLimit;
private:
	const std::string m_highScoreFileName;
};