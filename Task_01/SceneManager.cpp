#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::ChangeScene(SceneType type) {
    if (m_pCurrentScene) {
        m_pCurrentScene->ReleaseObjects();
        m_pCurrentScene.reset();
        m_pPlayer->Reset();
    }
    switch (type)
    {
    case SceneType::Start:
        m_pPlayer->GetCamera()->Reset();
        m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
        m_pCurrentScene = std::make_unique<StartScene>(m_pPlayer);
        m_CurrentSceneType = SceneType::Start;
        break;

    case SceneType::Roller:
        m_pPlayer->GetCamera()->Reset();
        m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
        m_pCurrentScene = std::make_unique<RoallerCoasterScene>(m_pPlayer);
        m_CurrentSceneType = SceneType::Roller;
        break;

    case SceneType::Tank:
        m_pPlayer->SetPosition(0.0f, -45.0f, 0.0f);
        m_pPlayer->GetCamera()->Reset();
        m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
        m_pCurrentScene = std::make_unique<TankCScene>(m_pPlayer);
        m_CurrentSceneType = SceneType::Tank;
        break;

    case SceneType::Title:
        m_pPlayer->GetCamera()->Reset();
        m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
        m_pCurrentScene = std::make_unique<TitleScene>(m_pPlayer);
        m_CurrentSceneType = SceneType::Title;
        break;
    }

    // »õ ¾À ÃÊ±âÈ­
    if (m_pCurrentScene)
        m_pCurrentScene->BuildObjects();
}

void CSceneManager::Update(float dt) {
    if (m_pCurrentScene) m_pCurrentScene->Animate(dt);
    if (m_pCurrentScene->IsChangeSceneRequested())
    {
        SceneType s = m_pCurrentScene->GetNextSceneName();
        ChangeScene(s);
    }
}

void CSceneManager::Render(HDC hDC, CCamera* pCamera) {
    if (m_pCurrentScene) m_pCurrentScene->Render(hDC, pCamera);
}

void CSceneManager::HandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!m_pCurrentScene) return;
    if (msg == WM_KEYDOWN || msg == WM_KEYUP) {
        
        m_pCurrentScene->OnProcessingKeyboardMessage(hWnd, msg, wParam, lParam);
    }
    else if (msg == WM_MOUSEMOVE || msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN)
        m_pCurrentScene->OnProcessingMouseMessage(hWnd, msg, wParam, lParam);
}
void CSceneManager::BuildObjects() {
    m_pCurrentScene->BuildObjects();
}
void CSceneManager::ReleaseObjects() {
    m_pCurrentScene->ReleaseObjects();
}

CGameObject* CSceneManager::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera) {
    return m_pCurrentScene->PickObjectPointedByCursor(xClient, yClient, pCamera);
}

SceneType CSceneManager::GetCurrentSceneType() const {
    return m_CurrentSceneType;
}

void CSceneManager::SetPlayer(CPlayer* pPlayer) {
    m_pPlayer = pPlayer;
}