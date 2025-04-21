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
	std::vector< XMFLOAT3>start= {
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
		{11, 9, 0}, {12, 9, 0}, {13, 9, 0}, {14, 9, 0}, {15, 9, 0}, {16, 9, 0}, {17, 9, 0}, {18, 9, 0}, {19, 9, 0}, {20, 9, 0},
		{15, 8, 0}, {15, 7, 0}, {15, 6, 0}, {15, 5, 0}, {15, 4, 0},
		{15, 3, 0}, {15, 2, 0}, {15, 1, 0}, {15, 0, 0},

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
	std::vector<XMFLOAT3> tutorial = {
		// T (x + 0)
		{1, 9, 0}, {2, 9, 0}, {3, 9, 0}, {4, 9, 0}, {5, 9, 0}, {6, 9, 0}, {7, 9, 0}, {8, 9, 0}, {9, 9, 0}, {10, 9, 0},
		{5, 8, 0}, {5, 7, 0}, {5, 6, 0}, {5, 5, 0}, {5, 4, 0},
		{5, 3, 0}, {5, 2, 0}, {5, 1, 0}, {5, 0, 0},

		// U (x + 10)
		{16, 9, 0}, {16, 8, 0}, {16, 7, 0}, {16, 6, 0}, {16, 5, 0}, {16, 4, 0}, {16, 3, 0}, {16, 2, 0},
		{17, 1, 0}, {18, 0, 0}, {19, 1, 0},
		{20, 2, 0}, {20, 3, 0}, {20, 4, 0}, {20, 5, 0}, {20, 6, 0}, {20, 7, 0}, {20, 8, 0}, {20, 9, 0},

		// T (x + 20)
		{26, 9, 0}, {27, 9, 0}, {28, 9, 0}, {29, 9, 0}, {30, 9, 0}, {31, 9, 0}, {32, 9, 0}, {33, 9, 0}, {34, 9, 0}, {35, 9, 0},
		{30, 8, 0}, {30, 7, 0}, {30, 6, 0}, {30, 5, 0}, {30, 4, 0},
		{30, 3, 0}, {30, 2, 0}, {30, 1, 0}, {30, 0, 0},

		// O (x + 30)
		{41, 9, 0}, {42, 9, 0}, {43, 9, 0},{44, 9, 0},{45, 9, 0},
		{41, 8, 0},             {45, 8, 0},
		{41, 7, 0},             {45, 7, 0},
		{41, 6, 0},             {45, 6, 0},
		{41, 5, 0},             {45, 5, 0},
		{41, 4, 0},             {45, 4, 0},
		{41, 3, 0},             {45, 3, 0},
		{41, 2, 0},             {45, 2, 0},
		{41, 1, 0},             {45, 1, 0},
		{41, 0, 0}, {42, 0, 0}, {43, 0, 0},{44, 0, 0},{45, 9, 0},

		// R (x + 40)
		{51, 9, 0}, {52, 9, 0}, {53, 9, 0}, {54, 9, 0}, {55, 9, 0},
		{51, 8, 0}, {52, 8, 0},
		{51, 7, 0}, {56, 7, 0},
		{51, 6, 0}, {52, 6, 0}, {53, 6, 0}, {54, 6, 0}, {55, 6, 0},
		{51, 5, 0}, {53, 5, 0},
		{51, 4, 0}, {54, 4, 0},
		{51, 3, 0}, {55, 3, 0},
		{51, 2, 0}, {56, 2, 0},


		// I (x + 50)
		{62, 9, 0}, {63, 9, 0}, {64, 9, 0},
				  {63, 8, 0},
				  {63, 7, 0},
				  {63, 6, 0},
				  {63, 5, 0},
				  {63, 4, 0},
				  {63, 3, 0},
				  {63, 2, 0},
		{62, 1, 0}, {63, 1, 0}, {64, 1, 0},

		// A (x + 60)
		{72, 9, 0},
{71, 8, 0}, {72, 8, 0}, {73, 8, 0},
{70, 7, 0}, {74, 7, 0},
{70, 6, 0}, {74, 6, 0},
{69, 5, 0}, {75, 5, 0},
{69, 4, 0}, {70, 4, 0}, {71, 4, 0}, {72, 4, 0}, {73, 4, 0}, {74, 4, 0}, {75, 4, 0},
{69, 3, 0}, {75, 3, 0},
{69, 2, 0}, {75, 2, 0},
{69, 1, 0}, {75, 1, 0},
{69, 0, 0}, {75, 0, 0},

		// L (x + 70)
		{81, 9, 0},
		{81, 8, 0},
		{81, 7, 0},
		{81, 6, 0},
		{81, 5, 0},
		{81, 4, 0},
		{81, 3, 0},
		{81, 2, 0},
		{81, 1, 0},
		{81, 0, 0}, {82, 0, 0}, {83, 0, 0},{84,0,0}
	};
	std::vector<XMFLOAT3> level1 = {
		{1, 9, 0},
		{1, 8, 0},
		{1, 7, 0},
		{1, 6, 0},
		{1, 5, 0},
		{1, 4, 0},
		{1, 3, 0},
		{1, 2, 0},
		{1, 1, 0},
		{1, 0, 0}, {2, 0, 0}, {3, 0, 0},{4,0,0},

		{10, 8, 0}, {11, 8, 0}, {12, 8, 0}, {13, 8, 0}, {14, 8, 0},
		{10, 7, 0}, {10, 6, 0}, {10, 5, 0}, {10, 4, 0}, {10, 3, 0}, {10, 2, 0}, {10, 1, 0},
		{11, 5, 0}, {12, 5, 0}, {13, 5, 0},{14, 5, 0},
		{11, 1, 0}, {12, 1, 0}, {13, 1, 0}, {14, 1, 0},

		{20, 8, 0}, {20.25,7, 0}, {20.5, 6, 0}, {20.75, 5, 0}, {21, 4, 0}, {21.25, 3, 0}, {21.5, 2, 0}, {21.75, 1, 0},
		{22.25, 2, 0}, {22.5, 3, 0}, {22.75, 4, 0}, {23, 5, 0}, {23.25, 6, 0}, {23.5, 7, 0}, {23.75, 8, 0},

		{30, 8, 0}, {31, 8, 0}, {32, 8, 0}, {33, 8, 0}, {34, 8, 0},
		{30, 7, 0}, {30, 6, 0}, {30, 5, 0}, {30, 4, 0}, {30, 3, 0}, {30, 2, 0}, {30, 1, 0},
		{31, 5, 0}, {32, 5, 0}, {33, 5, 0},{34, 5, 0},
		{31, 1, 0}, {32, 1, 0}, {33, 1, 0}, {34, 1, 0},

		{40, 9, 0},
		{40, 8, 0},
		{40, 7, 0},
		{40, 6, 0},
		{40, 5, 0},
		{40, 4, 0},
		{40, 3, 0},
		{40, 2, 0},
		{40, 1, 0},
		{40, 0, 0}, {41, 0, 0}, {42, 0, 0},{43,0,0},

	};
	std::vector<XMFLOAT3> level2 = {
		{1, 9, 0},
		{1, 8, 0},
		{1, 7, 0},
		{1, 6, 0},
		{1, 5, 0},
		{1, 4, 0},
		{1, 3, 0},
		{1, 2, 0},
		{1, 1, 0},
		{1, 0, 0}, {2, 0, 0}, {3, 0, 0},{4,0,0},

		{10, 8, 0}, {11, 8, 0}, {12, 8, 0}, {13, 8, 0}, {14, 8, 0},
		{10, 7, 0}, {10, 6, 0}, {10, 5, 0}, {10, 4, 0}, {10, 3, 0}, {10, 2, 0}, {10, 1, 0},
		{11, 5, 0}, {12, 5, 0}, {13, 5, 0},{14, 5, 0},
		{11, 1, 0}, {12, 1, 0}, {13, 1, 0}, {14, 1, 0},

		{20, 8, 0}, {20.25,7, 0}, {20.5, 6, 0}, {20.75, 5, 0}, {21, 4, 0}, {21.25, 3, 0}, {21.5, 2, 0}, {21.75, 1, 0},
		{22.25, 2, 0}, {22.5, 3, 0}, {22.75, 4, 0}, {23, 5, 0}, {23.25, 6, 0}, {23.5, 7, 0}, {23.75, 8, 0},

		{30, 8, 0}, {31, 8, 0}, {32, 8, 0}, {33, 8, 0}, {34, 8, 0},
		{30, 7, 0}, {30, 6, 0}, {30, 5, 0}, {30, 4, 0}, {30, 3, 0}, {30, 2, 0}, {30, 1, 0},
		{31, 5, 0}, {32, 5, 0}, {33, 5, 0},{34, 5, 0},
		{31, 1, 0}, {32, 1, 0}, {33, 1, 0}, {34, 1, 0},

		{40, 9, 0},
		{40, 8, 0},
		{40, 7, 0},
		{40, 6, 0},
		{40, 5, 0},
		{40, 4, 0},
		{40, 3, 0},
		{40, 2, 0},
		{40, 1, 0},
		{40, 0, 0}, {41, 0, 0}, {42, 0, 0},{43,0,0},

		{50, 9, 0}, {51, 9, 0}, {52, 9, 0}, {53, 9, 0},
		{53, 8, 0}, {53, 8, 0},
		{53, 7, 0},
		{53, 6, 0},
		{50, 5, 0}, {51, 5, 0}, {52, 5, 0},{53, 5, 0},
		{50, 4, 0},
		{50, 3, 0},
		{50, 2, 0},
		{53, 1, 0},
		{50, 0, 0}, {51, 0, 0}, {52, 0, 0}, {53, 0, 0},

	};
	std::vector<XMFLOAT3> end = {
		{1, 9, 0}, {2, 9, 0}, {3, 9, 0}, {4, 9, 0}, {5, 9, 0},
		{1, 8, 0}, {1, 7, 0}, {1, 6, 0}, {1, 5, 0}, {1, 4, 0}, {1, 3, 0}, {1, 2, 0},
		{2, 6, 0}, {3, 6, 0}, {4, 6, 0},{5, 6, 0},
		{2, 2, 0}, {3, 2, 0}, {4, 2, 0}, {5, 2, 0},

		{11, 2, 0}, {11, 3, 0}, {11, 4, 0},
		{11, 5, 0}, {11, 6, 0}, {11, 7, 0}, {11, 8, 0}, {11, 9, 0},

		{17, 2, 0}, {17, 3, 0}, {17, 4, 0},
		{17, 5, 0}, {17, 6, 0}, {17, 7, 0}, {17, 8, 0}, {17, 9, 0},

		{12, 3, 0}, {13, 4, 0}, {14, 5, 0},{15, 6,0}, { 16, 8, 0 }
		
	};
	float scale = 0.6f;
	auto& coords = start;
	for (const auto& pos : coords) {
		float x = (pos.x - 30) * scale;
		float y = (pos.y - 30) * scale;
		float z = pos.z + 50;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		cube->typenum = 3;
		m_ppObjects.push_back(std::move(cube));
	}
	auto& coords2 = tutorial;
	for (const auto& pos : coords2) {
		float x = (pos.x - 40) * scale;
		float y = (pos.y + 15) * scale;
		float z = pos.z + 50;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		cube->typenum = 0;
		m_ppObjects.push_back(std::move(cube));
	}

	auto& coords3 = level1;
	for (const auto& pos : coords3) {
		float x = (pos.x - 30) * scale;
		float y = (pos.y) * scale;
		float z = pos.z + 50;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		cube->typenum = 1;
		m_ppObjects.push_back(std::move(cube));
	}

	auto& coords4= level2;
	for (const auto& pos : coords4) {
		float x = (pos.x - 30) * scale;
		float y = (pos.y - 15) * scale;
		float z = pos.z + 50;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		cube->typenum = 2;
		m_ppObjects.push_back(std::move(cube));
	}
	auto& coords5 = end;
	for (const auto& pos : coords5) {
		float x = (pos.x - 30) * scale;
		float y = (pos.y - 45) * scale;
		float z = pos.z + 50;
		auto cube = std::make_unique<CGameObject>();
		cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		cube->typenum = 4;
		m_ppObjects.push_back(std::move(cube));
	}
}

void StartScene::ReleaseObjects()
{
	
}
bool StartScene::IsChangeSceneRequested() const {
	return ischange;
}
SceneType StartScene::GetNextSceneName() const
{
	return s;
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
	CGameObject* pNearestObject = nullptr;
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
	if (pNearestObject) {
		switch (pNearestObject->typenum)
		{
		case 0:
			s = SceneType::Title;
			break;
		case 1:
			s = SceneType::Roller;
			break;
		case 2:
			s = SceneType::Tank;
			break;
		case 3:
			s = SceneType::Roller;
			break;
		case 4:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		ischange = true;
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
	/*XMFLOAT3 center = {2.0f, 4.5f * 0.6f, 10.0f};
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
	}*/
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

	//if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);

	//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
