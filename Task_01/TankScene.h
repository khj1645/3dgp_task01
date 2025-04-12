#pragma once

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
	std::unique_ptr<CWallsObject> m_pWallsObject;
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
	void CheckObjectByBulletCollisions();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

