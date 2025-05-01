#pragma once

#include <vector>
#include <map>
#include <string>
#include "SceneBase.h"
#include "GameObject.h"
#include "Camera.h"
#include "memory"
#include "Player.h"

class RoallerCoasterScene : public CSceneBase
{
public:
	RoallerCoasterScene(CPlayer* pPlayer);
	virtual ~RoallerCoasterScene();

private:
	//std::unique_ptr<CWallsObject> m_pWallsObject;
	//CWallsObject* m_pWallsObject = NULL;
	std::vector<XMVECTOR> m_PathPoints;
	float m_fDistanceAlongPath = 0.0f;
	float m_fSpeed = 10.0f; // 1초에 10유닛 이동
	int index{ 0 };
	float m_fElapsedTime = 0.0f;
	bool ischange{ false };
	SceneType s;
#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual bool IsChangeSceneRequested() const;
	virtual SceneType GetNextSceneName() const;
	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

