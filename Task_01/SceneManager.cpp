#include "stdafx.h"
#include "SceneManager.h"

void CSceneManager::ChangeScene(std::shared_ptr<CSceneBase> newScene, SceneType type) {
    if (m_pCurrentScene) m_pCurrentScene->ReleaseObjects();
    m_pCurrentScene = std::move(newScene);
    m_CurrentSceneType = type;

    if (m_pCurrentScene) m_pCurrentScene->BuildObjects();
}

void CSceneManager::Update(float dt) {
    if (m_pCurrentScene) m_pCurrentScene->Animate(dt);
}

void CSceneManager::Render(HDC hDC, CCamera* pCamera) {
    if (m_pCurrentScene) m_pCurrentScene->Render(hDC, pCamera);
}

void CSceneManager::HandleInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!m_pCurrentScene) return;

    if (msg == WM_KEYDOWN || msg == WM_KEYUP)
        m_pCurrentScene->OnProcessingKeyboardMessage(hWnd, msg, wParam, lParam);
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