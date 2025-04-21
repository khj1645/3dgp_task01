#pragma once

#include <memory>
#include "stdafx.h"
#include "SceneBase.h"
#include "TankScene.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "RoallerCoaster.h"
#include "Camera.h"


class CSceneManager {
public:
    CSceneManager() = default;
    ~CSceneManager() = default;

    void ChangeScene(SceneType type);
    void BuildObjects();
    void ReleaseObjects();
    void Update(float dt);
    void Render(HDC hDC, CCamera* pCamera);
    void HandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
    SceneType GetCurrentSceneType() const;
    void CSceneManager::SetPlayer(CPlayer* pPlayer);
private:
    std::shared_ptr<CSceneBase> m_pCurrentScene = nullptr;
    SceneType m_CurrentSceneType = SceneType::Start;
    CPlayer* m_pPlayer;
};