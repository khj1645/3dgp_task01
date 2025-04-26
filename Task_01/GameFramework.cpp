//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include <memory>
#include "stdafx.h"
#include "GameFramework.h"
#include "TankScene.h"
#include "StartScene.h"
#include "TitleScene.h"
#include "RoallerCoaster.h"

void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer();

	BuildObjects();

	_tcscpy_s(m_pszFrameRate, _T("LabProject ("));
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC = ::GetDC(m_hWnd);

	m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
	::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{
	HDC hDC = ::GetDC(m_hWnd);
	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::BuildObjects()
{
	CCamera* pCamera = new CCamera();
	pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera->SetFOVAngle(60.0f);

	pCamera->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	//CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);
	std::shared_ptr<CMesh> pAirplaneMesh = std::make_shared<CTankMesh>(6.0f, 6.0f, 1.0f);
	m_pPlayer = new CTankPlayer();
	m_pPlayer->m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_pPlayer->m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_pPlayer->OnUpdateTransform();
	m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
	m_pPlayer->SetMesh(pAirplaneMesh);
	m_pPlayer->SetColor(RGB(0, 0, 255));
	m_pPlayer->SetCamera(pCamera);
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));
	m_SceneManager.SetPlayer(m_pPlayer);
	auto tankScene = std::make_shared<TitleScene>(m_pPlayer);
	std::shared_ptr<CSceneBase> baseScene = std::static_pointer_cast<CSceneBase>(tankScene);
	m_SceneManager.ChangeScene(SceneType::Title);
	m_SceneManager.BuildObjects();
	//m_pScene = new CScene(m_pPlayer);
	//m_pScene->BuildObjects();
}

void CGameFramework::ReleaseObjects()
{
	m_SceneManager.ReleaseObjects();

	if (m_pPlayer) delete m_pPlayer;
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	//m_SceneManager.HandleInput(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		if (nMessageID == WM_RBUTTONDOWN) m_pLockedObject = m_SceneManager.PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		//if (m_SceneManager.GetCurrentSceneType() == SceneType::Title && m_pLockedObject != nullptr) {
		//	//auto newScene = std::make_shared<StartScene>(m_pPlayer);
		//	//m_SceneManager.ChangeScene(newScene, SceneType::Start);
		//}
		else if (m_SceneManager.GetCurrentSceneType() == SceneType::Start && m_pLockedObject != nullptr) {
			//m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
			//m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));

			//auto newScene = std::make_shared<RoallerCoasterScene>(m_pPlayer);
			//m_SceneManager.ChangeScene(newScene, SceneType::Roller);
		}
		//else if (m_SceneManager.GetCurrentSceneType() == SceneType::Roller) {
		//	m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
		//	//m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
		//	auto newScene = std::make_shared<TankCScene>(m_pPlayer);
		//	m_SceneManager.ChangeScene(newScene, SceneType::Tank);
		//}
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	//m_SceneManager.HandleInput(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			break;
		case VK_CONTROL:
			if (m_SceneManager.GetCurrentSceneType() == SceneType::Tank) {
				((CTankPlayer*)m_pPlayer)->FireBullet(m_pLockedObject);
				m_pLockedObject = NULL;
			}
			break;
		default:
			m_SceneManager.HandleInput(hWnd, nMessageID, wParam, lParam);
			break;
		}
		break;
	default:
		break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
			m_GameTimer.Stop();
		else
			m_GameTimer.Start();
		break;
	}
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}

void CGameFramework::ProcessInput()
{
	if (m_SceneManager.GetCurrentSceneType() == SceneType::Tank || m_SceneManager.GetCurrentSceneType() == SceneType::Roller) {
		static UCHAR pKeyBuffer[256];
		if (GetKeyboardState(pKeyBuffer))
		{
			DWORD dwDirection = 0;
			if (pKeyBuffer[VK_UP] & 0xF0) dwDirection |= DIR_FORWARD;
			if (pKeyBuffer[VK_DOWN] & 0xF0) dwDirection |= DIR_BACKWARD;
			if (pKeyBuffer[VK_LEFT] & 0xF0) dwDirection |= DIR_LEFT;
			if (pKeyBuffer[VK_RIGHT] & 0xF0) dwDirection |= DIR_RIGHT;
			if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
			if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;

			if (dwDirection) m_pPlayer->Move(dwDirection, 0.15f);
		}

		if (GetCapture() == m_hWnd)
		{
			SetCursor(NULL);
			POINT ptCursorPos;
			GetCursorPos(&ptCursorPos);
			float cxMouseDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
			float cyMouseDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
			SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
			if (cxMouseDelta || cyMouseDelta)
			{
				if (pKeyBuffer[VK_RBUTTON] & 0xF0)
					m_pPlayer->Rotate(0, 0.0f, -cxMouseDelta);
				else
					m_pPlayer->Rotate(0, cxMouseDelta, 0.0f);
			}
		}
		m_pPlayer->prpos = m_pPlayer->GetPosition();
		m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
	}
}

void CGameFramework::AnimateObjects()
{
	//m_pPlayer->prpos = m_pPlayer->GetPosition();
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();
	if (m_pPlayer) m_pPlayer->Animate(fTimeElapsed);
	m_SceneManager.Update(fTimeElapsed);
}

void CGameFramework::FrameAdvance()
{
	m_GameTimer.Tick(60.0f);
	ProcessInput();

	AnimateObjects();

	ClearFrameBuffer(RGB(255, 255, 255));

	CCamera* pCamera = m_pPlayer->GetCamera();
	m_SceneManager.Render(m_hDCFrameBuffer, pCamera);

	PresentFrameBuffer();

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}


