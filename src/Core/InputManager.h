#pragma once
#include <functional>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "raylib.h"


class InputManager
{
#pragma region Constructors / Desctructors / Mouvement
public:
	InputManager();
	~InputManager();
	InputManager(const InputManager& inputManager) = delete;
	InputManager& operator=(const InputManager& inputManager) = delete;

	InputManager(InputManager&& inputManager) = delete;
	InputManager& operator=(InputManager&& inputManager) = delete;
#pragma endregion

#pragma region Singleton
public:
	static InputManager& Instance();
private:
	static InputManager* s_instance;
#pragma endregion

public:
	void BindKeyPressed(KeyboardKey key, std::function<void()> func);
	void BindKeyDown(KeyboardKey key, std::function<void()> func);
	void BindKeyUp(KeyboardKey key, std::function<void()> func);
	void ClearBindings();
	void UpdateInputs();

	bool IsAnyKeyPressed();

private:
	std::unordered_map<KeyboardKey, std::function<void()>> m_actionPressedMap;
	std::unordered_map<KeyboardKey, std::function<void()>> m_actionDownMap;
	std::unordered_map<KeyboardKey, std::function<void()>> m_actionUpMap;
};
