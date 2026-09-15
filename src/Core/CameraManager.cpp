#include "CameraManager.h"
#include <cmath>

#include <string>

CameraManager::CameraManager() : m_tunnelHeight(128), m_isTunnelActive(false), m_tunnelDelay(5.0f), m_counter(0.0f)
{
	m_camera = Camera2D();
	m_camera.target = Vector2(0, 0);
	m_camera.offset = Vector2(0, 0);
	m_camera.rotation = 0.1f;
	m_camera.zoom = 1.5f;
}


void CameraManager::Reset()
{
	m_counter = 0.0f;
	m_isTunnelActive = false;
}

void CameraManager::UpdateLogic(float deltaTime)
{
	m_counter += deltaTime;
	if (m_counter >= m_tunnelDelay)
	{
		m_counter -= m_tunnelDelay;
		m_isTunnelActive = !m_isTunnelActive;
	}
}

void CameraManager::BeginScissor(const Rectangle playerRect)
{
	if (m_isTunnelActive)
	{
		float progress = m_counter / m_tunnelDelay;
		progress = std::sin(progress * PI);

		TraceLog(LOG_INFO, std::to_string(progress).c_str());

		float newYPos = std::lerp(0, playerRect.y - (m_tunnelHeight / 2), progress);
		float newHeight = std::lerp(600, playerRect.height + m_tunnelHeight, progress);
		BeginScissorMode(0, newYPos, 800, newHeight);
	}
}

void CameraManager::EndScissor()
{
	if (m_isTunnelActive)
		EndScissorMode();
}

const Camera2D& CameraManager::GetCamera() const
{
	return m_camera;
}
