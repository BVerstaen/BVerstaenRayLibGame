#include "ScoreSystem.h"
#include <raylib.h>

ScoreSystem::ScoreSystem() :CurrentScore(0), HighScoreLimit(3), HighScoreList(), m_highScoreFileName("High.score")
{
	LoadHighScore();
}

void ScoreSystem::UpdateScore(float deltaTime)
{
	m_gameTimer += deltaTime;
	if (m_gameTimer >= 1.0f)
	{
		++CurrentScore;
		m_gameTimer -= 1.0f;
	}
}

void ScoreSystem::ResetScore()
{
	m_gameTimer = 0.0f;
	CurrentScore = 0;
}

//Returns true if score is in highscore
bool ScoreSystem::AddScoreToHighScore()
{
	for (int i = 0; i < HighScoreList.size(); i++)
	{
		if (CurrentScore >= HighScoreList[i])
		{
			HighScoreList.insert(HighScoreList.begin() + i, CurrentScore);

			//Keep as top 3
			HighScoreList.resize(HighScoreLimit);
			SaveHighScore();
			return true;
		}
	}
	return false;
}

void ScoreSystem::SaveHighScore()
{
	const int dataSize = HighScoreLimit * sizeof(int);
	bool success = SaveFileData(m_highScoreFileName.c_str(), HighScoreList.data(), dataSize);

	if (!success)
		TraceLog(LOG_ERROR, "Fail to save highscores");
}

void ScoreSystem::LoadHighScore()
{
	HighScoreList.clear();
	HighScoreList.resize(HighScoreLimit);

	int loadingDataSize = 0;
	unsigned char* fileData = LoadFileData(m_highScoreFileName.c_str(), &loadingDataSize);

	if (fileData == nullptr)
		return;

	//Fill up highscore list
	const int dataSize = HighScoreLimit * sizeof(int);
	std::memcpy(HighScoreList.data(),fileData, dataSize);

	UnloadFileData(fileData);
}
