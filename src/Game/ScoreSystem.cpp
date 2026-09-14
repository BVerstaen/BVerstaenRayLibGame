#include "ScoreSystem.h"
#include <raylib.h>

ScoreSystem::ScoreSystem() :CurrentScore(0), HighScoreLimit(3), HighScoreList(), m_highScoreFileName("High.score")
{
	LoadHighScore();
}

//Returns true if score is in highscore
bool ScoreSystem::AddScoreToHighScore()
{

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
