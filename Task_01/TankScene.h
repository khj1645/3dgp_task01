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
	bool ischange{ false };
    std::vector<XMFLOAT3> you_win_positions = {
        // Y
        {0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 3, 0},
        {1, 1, 0},
        {2, 0, 0}, {2, 1, 0}, {2, 2, 0}, {2, 3, 0},

        // O (x offset +5)
        {5, 0, 0}, {5, 1, 0}, {5, 2, 0}, {5, 3, 0},
        {6, 3, 0},
        {7, 0, 0}, {7, 1, 0}, {7, 2, 0}, {7, 3, 0},

        // U (x offset +10)
        {10, 3, 0},
        {10, 2, 0},
        {10, 1, 0},
        {10, 0, 0},
        {11, 0, 0},
        {12, 1, 0},
        {12, 2, 0},
        {12, 3, 0},

        // (ฐ๘น้) (x offset +4)

        // W (x offset +18)
        {18, 3, 0},
        {18, 2, 0},
        {19, 1, 0},
        {20, 2, 0},
        {21, 1, 0},
        {22, 2, 0},
        {23, 3, 0},

        // I (x offset +3)
        {26, 3, 0},
        {26, 2, 0},
        {26, 1, 0},
        {26, 0, 0},

        // N (x offset +4)
        {30, 0, 0}, {30, 1, 0}, {30, 2, 0}, {30, 3, 0},
        {31, 1, 0},
        {32, 2, 0},
        {33, 0, 0}, {33, 1, 0}, {33, 2, 0}, {33, 3, 0},

        // ! (x offset +4)
        {37, 2, 0},
        {37, 1, 0},
        {37, 0, 0},
    };
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

