#pragma once

#include <memory>
#include "SceneBase.h"
#include "TankScene.h"
#include "StartScene.h"
#include "Camera.h"


enum class SceneType {
    Start,
    Roller,
    Tank
};

class CSceneManager {
public:
    CSceneManager() = default;
    ~CSceneManager() = default;

    void ChangeScene(std::shared_ptr<CSceneBase> newScene, SceneType type);
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