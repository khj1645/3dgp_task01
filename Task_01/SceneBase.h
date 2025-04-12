#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"

class CSceneBase
{
public:
	CSceneBase(CPlayer* pPlayer) {};
	virtual ~CSceneBase() {};

protected:
	std::vector<std::unique_ptr<CGameObject>> m_ppObjects;

	// std::unique_ptr<CWallsObject> m_pWallsObject;

	CPlayer* m_pPlayer = NULL;

#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif

public:
	virtual void BuildObjects() = 0;
	virtual void ReleaseObjects() = 0;


	virtual void Animate(float fElapsedTime) = 0;
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) = 0;

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) = 0;
	virtual CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera) = 0;

};

