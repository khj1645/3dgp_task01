#pragma once

#include <vector>
#include <map>
#include <string>
#include "SceneBase.h"
#include "GameObject.h"
#include "Camera.h"
#include "memory"
#include "Player.h"

class TitleScene : public CSceneBase
{
public:
	TitleScene(CPlayer* pPlayer);
	virtual ~TitleScene();

private:
	//std::unique_ptr<CWallsObject> m_pWallsObject;
	//CWallsObject* m_pWallsObject = NULL;
	bool isboom{ false };
	float explosionTime{ 0 };

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
	virtual bool IsChangeSceneRequested() const;
	virtual SceneType GetNextSceneName() const;
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

