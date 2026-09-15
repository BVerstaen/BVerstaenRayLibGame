#include "CameraManager.h"

CameraManager::CameraManager()
{
	m_camera = Camera2D();
	m_camera.target = Vector2(0, 0);
	m_camera.offset = Vector2(0, 0);
	m_camera.rotation = 0.0f;
	m_camera.zoom = 1.5f;
}

const Camera2D& CameraManager::GetCamera() const
{
	return m_camera;
}
