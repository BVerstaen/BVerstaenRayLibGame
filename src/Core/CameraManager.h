#pragma once
#include "raylib.h"

class CameraManager
{
public: 
	CameraManager();

public:
	const Camera2D& GetCamera() const;

public:
	Camera2D m_camera;
};