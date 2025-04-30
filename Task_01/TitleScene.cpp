#include "stdafx.h"
#include "TitleScene.h"
#include "GraphicsPipeline.h"

TitleScene::TitleScene(CPlayer* pPlayer)
	: CSceneBase(pPlayer) {
	m_pPlayer = pPlayer;
}

TitleScene::~TitleScene()
{
}

void TitleScene::BuildObjects()
{

	auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);
	auto widthbarMesh = std::make_shared<CCubeMesh>(1.0f, 6.0f, 1.0f);
	std::map<std::string, std::vector<XMFLOAT3>> word_letter_positions;
	word_letter_positions["김한준"] = {
		  {0, 5, 0}, {1, 5, 0}, {2, 5, 0}, {3, 5, 0}, {4, 5, 0},
		  {4, 4, 0}, {4, 3, 0}, {4, 2, 0}, {4, 1, 0},		// ㄱ

		  {6, 3, 0},			// ㅣ								

		  {4, -1, 0}, {5, -1, 0}, {6, -1, 0},

		  {4, -2, 0}, {6, -2, 0},	// ㅁ

		  {4, -3, 0}, {5, -3, 0}, {6, -3, 0},


	{ 10, 2.5, 0 }, {11, 2.5, 0}, { 12, 2.5, 0 },
	{10, 1.5, 0}, {12, 1.5, 0},

	{10, 0.5, 0}, {11, 0.5, 0}, {12, 0.5, 0},

	{9, 4, 0}, {10, 4, 0}, {11, 4, 0}, {12, 4, 0}, {13, 4, 0},

	{10, 5.5, 0}, {11, 5.5, 0}, {12, 5.5, 0},			// ㅎ

	{15, 3.5, 0},{16, 3.5, 0}, {17, 3.5, 0},			// ㅣ

	{12, -3, 0}, {13, -3, 0}, {14, -3, 0}, {15, -3, 0},
	{12, -1, 0}, {12, -2, 0}, {12, -3, 0},			// ㄴ

		{19,6,0}, { 20, 6, 0 }, {21, 6, 0}, {22, 6, 0}, {23, 6, 0}, {24, 6, 0},{25, 6, 0},

	{22, 5, 0}, {21, 4, 0}, {20, 3, 0},{19, 2, 0},

	{23, 4, 0}, {24, 3, 0}, {25, 2, 0},							// ㅈ

		{19,0.5,0},{20,0.5,0},{21,0.5,0}, { 22,0.5,0 },{23,0.5,0},{24,0.5,0},{25,0.5,0}, {22,-0.5,0}, {22,-1.5,0},							// ㅜ

	{20.5, -3, 0}, {21.5, -3, 0}, {22.5, -3, 0}, {23.5, -3, 0},
	{20.5, -1, 0}, {20.5, -2, 0}, {20.5, -3, 0}						// ㄴ
	};
	std::vector<XMFLOAT3> letter_3 = {
{0, 7, 0}, {1, 7, 0}, {2, 7, 0},
			  {2, 6, 0},
	{1, 5, 0}, {2, 5, 0},
			  {2, 4, 0},
	{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, // 3

	{5, 7, 0}, {6, 7, 0},

	{5, 6, 0}, {5, 5, 0}, {5, 4, 0}, {5, 3, 0},

	{5, 2, 0}, {6, 2, 0},

	{7, 6, 0}, {7, 5, 0}, {7, 4, 0}, {7, 3, 0}, // d

	{10, 7, 0}, {11, 7, 0}, {12, 7, 0}, {13, 7, 0},

	{10.5, 6, 0},           {12.5, 6, 0},
	{10.5, 5, 0},           {12.5, 5, 0},

	{10, 4, 0}, {11, 4, 0}, {12, 4, 0}, {13, 4, 0},

	{9.5, 2, 0}, {10.5, 2, 0}, {11.5, 2, 0}, {12.5, 2, 0}, {13.5, 2, 0},	// 프

	 {16.5, 7.5, 0}, {17.5, 7.5, 0}, {18.5, 7.5, 0},
	{18.5, 6.5, 0},
	{16.5, 5.5, 0}, {17.5, 5.5, 0}, {18.5, 5.5, 0},
	{16.5, 4.5, 0},
	{16.5, 3.5, 0}, {17.5, 3.5, 0}, {18.5, 3.5, 0},
		{17.5,2,0},
	{15.5, 1, 0}, {16.5, 1, 0}, {17.5, 1, 0}, {18.5, 1, 0}, {19.5, 1, 0},	// 로

	{22, 7.5, 0}, {23, 7.5, 0}, {24, 7.5, 0}, {25, 7.5, 0},{26,7.5,0},
	{26, 6.5, 0}, {26, 5.5, 0},{26,4.5,0},{26,3.5,0},

	{21.5, 1, 0 }, { 22.5, 1, 0 }, { 23.5, 1, 0 }, { 24.5, 1, 0 }, { 25.5, 1, 0 },{26.5,1,0},{27.5,1,0},	// 그

	 {29.5, 7.5, 0}, {30.5, 7.5, 0}, {31.5, 7.5, 0},
	{31.5, 6.5, 0},
	{29.5, 5.5, 0}, {30.5, 5.5, 0}, {31.5, 5.5, 0},
	{29.5, 4.5, 0},
	{29.5, 3.5, 0}, {30.5, 3.5, 0}, {31.5, 3.5, 0},

	{33, 5.5, 0},{34, 5.5, 0}, {35, 5.5, 0},		// 래


	{37, 7.5, 0}, {38, 7.5, 0}, {39, 7.5, 0},{40,7.5,0},

	{37, 6.5, 0}, {40, 6.5, 0},
	{37, 5.5, 0}, {40, 5.5, 0},

	{37, 4.5, 0}, {38, 4.5, 0}, {39, 4.5, 0},{40,4.5,0},

		{42,5.5,0},

	{39, 2, 0}, {40, 2, 0},

	{38,1, 0},							{41, 1, 0},
	{38, 0, 0},							{41, 0, 0},

	{39, -1, 0}, {40, -1, 0},

	{46,7,0},{46,6,0},{46,5,0},{46,4,0},{46,3,0},
	{45,2,0}, { 46,2,0 },{ 47,2,0 },
	{45,6.5,0}

	};
	float scale = 0.6f;
	auto& coords = word_letter_positions["김한준"];
	for (const auto& pos : coords) {
		float x = (pos.x - 20);
		float y = pos.y;
		float z = pos.z + 20;
		auto cube = std::make_unique<CGameObject>();
		if (((pos.x == 6) && pos.y == 3 && pos.z == 0) || (((pos.x == 15) && pos.y == 3.5 && pos.z == 0))) {
			// ㅣ는 따로 긴 큐브 메쉬 사용
			cube->SetMesh(widthbarMesh);
		}
		else {
			cube->SetMesh(cubeMesh);
		}
		cube->SetPosition(x, y, z);
		m_ppObjects.push_back(std::move(cube));
	}
	for (int i=0;i<74;++i)
		m_ppObjects[i]->typenum = 1;
	for (const XMFLOAT3& pos : letter_3) {
		float x = (pos.x - 20);
		float y = pos.y - 20;
		float z = pos.z + 20;
		auto cube = std::make_unique<CGameObject>();
		if (pos.x == 33 || pos.x == 35 || pos.x == 42)
			cube->SetMesh(widthbarMesh);
		else
			cube->SetMesh(cubeMesh);
		cube->SetPosition(x, y, z);
		m_ppObjects.push_back(std::move(cube));

	}

}
void TitleScene::ReleaseObjects()
{

}

void TitleScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void TitleScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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

CGameObject* TitleScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
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
	if (pNearestObject != nullptr && pNearestObject->typenum == 1) {
		m_ppObjects.clear();
		CExplosiveObject::PrepareExplosion();
		auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);
		auto explo = std::make_unique<CExplosiveObject>();
		explo->SetMesh(cubeMesh);
		explo->SetColor(RGB(255, 0, 0));
		explo->SetPosition(-4.5f, 0.9f, 20.0f);
		explo->m_bBlowingUp = true;
		isboom = true;
		m_ppObjects.push_back(std::move(explo));
	}
	return(pNearestObject);
}

void TitleScene::CheckObjectByObjectCollisions()
{
}

void TitleScene::CheckObjectByWallCollisions()
{

}

void TitleScene::CheckPlayerByWallCollision()
{
}

void TitleScene::CheckObjectByBulletCollisions()
{

}
bool TitleScene::IsChangeSceneRequested() const { return explosionTime > 2.0f; }
SceneType TitleScene::GetNextSceneName() const
{
	 return SceneType::Start;
}
void TitleScene::Animate(float fElapsedTime)
{

	XMFLOAT3 center = { -4.5f, 0.9f, 20.0f };
	XMFLOAT3 yAxis = { 0.0f, 1.0f, 0.0f };
	float angle = 90.f * fElapsedTime;
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->RotateAround(center, yAxis, angle);
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Animate(fElapsedTime);
	if(isboom)
		explosionTime += fElapsedTime;
}

void TitleScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
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
