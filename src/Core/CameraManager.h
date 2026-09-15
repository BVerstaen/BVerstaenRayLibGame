#pragma once
#include "raylib.h"

class CameraManager
{
public: 
	CameraManager();

public:
	void Reset();

	void UpdateLogic(float deltaTime);
	void BeginScissor(const Rectangle playerRect);
	void EndScissor();

public:
	const Camera2D& GetCamera() const;

private:
	Camera2D m_camera;
	float m_tunnelHeight;
	bool m_isTunnelActive;
	float m_tunnelDelay;
	float m_counter;
};