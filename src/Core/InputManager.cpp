#include "InputManager.h"
#include <stdexcept>


#pragma region Constructors / Desctructors
InputManager::InputManager()
{
	if (s_instance)
		throw std::runtime_error("There can only be one input manager");

	s_instance = this;
}

InputManager::~InputManager()
{
	s_instance = nullptr;
}
#pragma endregion

#pragma region Singleton
InputManager* InputManager::s_instance = nullptr;
InputManager& InputManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("No input manager was created");

	return *s_instance;
}
#pragma endregion


void InputManager::BindKeyPressed(KeyboardKey key, std::function<void()> func)
{
	if (m_actionPressedMap.count(key))
	{
		TraceLog(LOG_ERROR, "Key is already binded !");
		return;
	}
	m_actionPressedMap[key] = std::move(func);
}

void InputManager::BindKeyDown(KeyboardKey key, std::function<void()> func)
{
	if (m_actionDownMap.count(key))
	{
		TraceLog(LOG_ERROR, "Key is already binded !");
		return;
	}
	m_actionDownMap[key] = std::move(func);
}

void InputManager::BindKeyUp(KeyboardKey key, std::function<void()> func)
{
	if (m_actionUpMap.count(key))
	{
		TraceLog(LOG_ERROR, "Key is already binded !");
		return;
	}
	m_actionUpMap[key] = std::move(func);
}

void InputManager::ClearBindings()
{
	m_actionPressedMap.clear();
	m_actionDownMap.clear();
	m_actionUpMap.clear();
}

void InputManager::UpdateInputs()
{
	//Check pressed inputs
	for (auto input : m_actionPressedMap)
	{
		if (IsKeyPressed(input.first))
			input.second();
	}

	//Check down inputs
	for (auto input : m_actionDownMap)
	{
		if (IsKeyDown(input.first))
			input.second();
	}

	//Check up inputs
	for (auto input : m_actionUpMap)
	{
		if (IsKeyUp(input.first))
			input.second();
	}
}

bool InputManager::IsAnyKeyPressed()
{
	return GetKeyPressed() != 0;
}
