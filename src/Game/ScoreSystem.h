#pragma once
#include <vector>
#include <string>

class ScoreSystem
{
public:
	ScoreSystem();
	bool AddScoreToHighScore();
	void SaveHighScore();
	void LoadHighScore();

public :
	int CurrentScore;
	std::vector<int> HighScoreList;
	const int HighScoreLimit;

private:
	const std::string m_highScoreFileName;
};