#include "stdafx.h"
#include "StartScene.h"
#include "GraphicsPipeline.h"

StartScene::StartScene(CPlayer* pPlayer)
	: CSceneBase(pPlayer) {
	m_pPlayer = pPlayer;
}

StartScene::~StartScene()
{
}

void StartScene::BuildObjects()
{
	auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);
	std::map<std::string, std::vector<XMFLOAT3>> word_letter_positions;
	std::vector<XMFLOAT3> letter_K = {
	{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 3, 0}, {0, 4, 0}, {0, 5, 0},
	{1, 2, 0}, {2, 1, 0}, {2, 3, 0}, {3, 0, 0}, {3, 4, 0}
	};
	word_letter_positions["Start"] = {
		// S
		{1, 9, 0}, {2, 9, 0}, {3, 9, 0}, {4, 9, 0}, {5, 9, 0},
		{0, 8, 0}, {5, 8, 0},
		{0, 7, 0},
		{0, 6, 0},
		{1, 5, 0}, {2, 5, 0}, {3, 5, 0}, {4, 5, 0},
		{5, 4, 0},
		{5, 3, 0},
		{5, 2, 0},
		{0, 1, 0}, {5, 1, 0},
		{1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0},

		// T (x offset +12)
		{13, 9, 0}, {14, 9, 0}, {15, 9, 0}, {16, 9, 0}, {17, 9, 0}, {18, 9, 0}, {19, 9, 0}, {20, 9, 0}, {21, 9, 0}, {22, 9, 0},
		{17, 8, 0}, {17, 7, 0}, {17, 6, 0}, {17, 5, 0}, {17, 4, 0},
		{17, 3, 0}, {17, 2, 0}, {17, 1, 0}, {17, 0, 0},

		// A (x offset +24)
		{27, 9, 0},
{26, 8, 0}, {27, 8, 0}, {28, 8, 0},
{25, 7, 0}, {29, 7, 0},
{25, 6, 0}, {29, 6, 0},
{24, 5, 0}, {30, 5, 0},
{24, 4, 0}, {25, 4, 0}, {26, 4, 0}, {27, 4, 0}, {28, 4, 0}, {29, 4, 0}, {30, 4, 0},
{24, 3, 0}, {30, 3, 0},
{24, 2, 0}, {30, 2, 0},
{24, 1, 0}, {30, 1, 0},
{24, 0, 0}, {30, 0, 0},

		// R (x offset +36)
		{36, 9, 0}, {37, 9, 0}, {38, 9, 0}, {39, 9, 0}, {40, 9, 0},
		{36, 8, 0}, {41, 8, 0},
		{36, 7, 0}, {41, 7, 0},
		{36, 6, 0}, {37, 6, 0}, {38, 6, 0}, {39, 6, 0}, {40, 6, 0},
		{36, 5, 0}, {38, 5, 0},
		{36, 4, 0}, {39, 4, 0},
		{36, 3, 0}, {40, 3, 0},
		{36, 2, 0}, {41, 2, 0},

		// T (x offset +48)
		{49, 9, 0}, {50, 9, 0}, {51, 9, 0}, {52, 9, 0}, {53, 9, 0}, {54, 9, 0}, {55, 9, 0}, {56, 9, 0}, {57, 9, 0}, {58, 9, 0},
		{53, 8, 0}, {53, 7, 0}, {53, 6, 0}, {53, 5, 0}, {53, 4, 0},
		{53, 3, 0}, {53, 2, 0}, {53, 1, 0}, {53, 0, 0}
	};
		float scale = 0.6f;
	auto& coords = word_letter_positions["Start"];
	for (const auto& pos : coords) {
		float x = (pos.x - 30) * scale;
		float y = pos.y * scale;
		float z = pos.z + 10;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		m_ppObjects.push_back(std::move(cube));
	}
}

void StartScene::ReleaseObjects()
{
	
}

void StartScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void StartScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		
		case 'A':
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* StartScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;
	CGameObject* pNearestObject = NULL;
	for (int i = 0; i < m_ppObjects.size(); i++)
	{
		float fHitDistance = FLT_MAX;
		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
		{
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i].get();
		}
	}
	return(pNearestObject);
}

void StartScene::CheckObjectByObjectCollisions()
{
}

void StartScene::CheckObjectByWallCollisions()
{
	
}

void StartScene::CheckPlayerByWallCollision()
{
}

void StartScene::CheckObjectByBulletCollisions()
{
	
}

void StartScene::Animate(float fElapsedTime)
{
	XMFLOAT3 center = { 0.3f, 4.5f * 0.6f, 10.0f };
	//m_pWallsObject->Animate(fElapsedTime);
	for (auto& cube : m_ppObjects)
	{
		// 큐브의 현재 위치
		XMFLOAT3 pos = cube->GetPosition();

		// 중심 기준 상대 좌표
		XMFLOAT3 relative = {
			pos.x - center.x,
			pos.y - center.y,
			pos.z - center.z
		};

		// 회전 행렬 생성
		float angle = 90.f * fElapsedTime;
		XMFLOAT3 yAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
		XMFLOAT4X4 rotMat = Matrix4x4::RotationAxis(yAxis, angle);
		XMFLOAT3 rotated = Vector3::TransformCoord(relative, rotMat);

		// 회전된 위치 = 중심 + 회전 상대
		XMFLOAT3 finalPos = {
			rotated.x + center.x,
			rotated.y + center.y,
			rotated.z + center.z
		};

		cube->SetPosition(finalPos);
	}
	//for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Animate(fElapsedTime);

	CheckPlayerByWallCollision();

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();
}

void StartScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);
	//m_pWallsObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);

	//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
