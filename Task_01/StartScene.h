#pragma once

#include <vector>
#include <map>
#include <string>
#include "SceneBase.h"
#include "GameObject.h"
#include "Camera.h"
#include "memory"
#include "Player.h"

class StartScene : public CSceneBase
{
public:
	StartScene(CPlayer* pPlayer);
	virtual ~StartScene();

private:
	//std::unique_ptr<CWallsObject> m_pWallsObject;
	//CWallsObject* m_pWallsObject = NULL;
	bool ischange{ false };
	SceneType s;

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
	virtual bool IsChangeSceneRequested() const;
	virtual SceneType GetNextSceneName() const;
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

