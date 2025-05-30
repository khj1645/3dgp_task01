#pragma once

#include <map>
#include <string>
#include "SceneBase.h"
#include "GameObject.h"
#include "Camera.h"
#include "memory"
#include "Player.h"

class TankCScene : public CSceneBase
{
public:
	TankCScene(CPlayer* pPlayer);
	virtual ~TankCScene();

private:
    int killcount{ 0 };
	bool win{ false };
	std::unique_ptr<CWallsObject> m_pWallsObject;
	bool ischange{ false };
	bool iscol{ true };
	bool isaim{ false };
	//CWallsObject* m_pWallsObject = NULL;

#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();

	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckPlayerByObstacleCollision();
	void CheckObjectByBulletCollisions();
	virtual bool IsChangeSceneRequested() const;
	virtual SceneType GetNextSceneName() const;
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

