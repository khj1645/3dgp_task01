#include "stdafx.h"
#include "RoallerCoaster.h"
#include "GraphicsPipeline.h"

RoallerCoasterScene::RoallerCoasterScene(CPlayer* pPlayer)
	: CSceneBase(pPlayer) {
	m_pPlayer = pPlayer;
}

RoallerCoasterScene::~RoallerCoasterScene()
{
}
XMFLOAT3 CatmullRom(const XMFLOAT3& p0, const XMFLOAT3& p1, const XMFLOAT3& p2, const XMFLOAT3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	XMFLOAT3 result;
	result.x = 0.5f * ((2 * p1.x) + (-p0.x + p2.x) * t +
		(2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 +
		(-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
	result.y = 0.5f * ((2 * p1.y) + (-p0.y + p2.y) * t +
		(2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 +
		(-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);
	result.z = 0.5f * ((2 * p1.z) + (-p0.z + p2.z) * t +
		(2 * p0.z - 5 * p1.z + 4 * p2.z - p3.z) * t2 +
		(-p0.z + 3 * p1.z - 3 * p2.z + p3.z) * t3);
	return result;
}
void RoallerCoasterScene::BuildObjects()
{
	std::vector<XMFLOAT3> controlPoints = {
			{ -20,  0,   0 },
			{ -15,  5,   5 },
			{ -10, 10,   0 },
			{  -5, 15,  -5 },
			{   0, 20,   0 },
			{   5, 15,  10 },
			{  10, 10,   0 },
			{  15,  5,  -10 },
			{  20,  0,   0 },
			{  25, -5,  10 },
			{  30, -10,  0 },
			{  35, -5, -10 },
			{  40,  0,   0 },
			{  45,  5,  10 },
			{  50, 10,   0 },
			{  55, 15, -10 },
			{  60, 20,   0 },
			{  65, 15,  10 },
			{  70, 10,   0 },
			{  75,  5, -10 },
			{  80,  0,   0 }
	};

	// ★ 곡선을 더 부드럽게
	for (size_t i = 0; i + 3 < controlPoints.size(); ++i) {
		XMFLOAT3 p0 = controlPoints[i];
		XMFLOAT3 p1 = controlPoints[i + 1];
		XMFLOAT3 p2 = controlPoints[i + 2];
		XMFLOAT3 p3 = controlPoints[i + 3];

		for (float t = 0.0f; t <= 1.0f; t += 0.005f) { // 아주 촘촘하게
			m_PathPoints.push_back(CatmullRom(p0, p1, p2, p3, t));
		}
	}
		
	auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);
	float scale = 0.6f;
	auto cube = std::make_unique<CGameObject>();
	cube->SetMesh(cubeMesh);
	cube->SetPosition(-10, 0, 0);
	m_ppObjects.push_back(std::move(cube));
	auto smc = std::make_shared<CCubeMesh>(0.2f, 0.2f, 0.2f);
	for (size_t i = 0; i < m_PathPoints.size(); i += 4)
	{
		const auto& pos = m_PathPoints[i];

		auto railObj = std::make_unique<CGameObject>();
		auto railObj2 = std::make_unique<CGameObject>();
		railObj->SetMesh(smc);
		railObj->SetPosition(pos.x, pos.y, pos.z - 2);

		m_ppObjects.push_back(std::move(railObj));

		railObj2->SetMesh(smc);
		railObj2->SetPosition(pos.x, pos.y, pos.z + 2);
		m_ppObjects.push_back(std::move(railObj2));

	}
}

void RoallerCoasterScene::ReleaseObjects()
{

}
bool RoallerCoasterScene::IsChangeSceneRequested() const {
	return ischange;
}
SceneType RoallerCoasterScene::GetNextSceneName() const
{
	return s;
}
void RoallerCoasterScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void RoallerCoasterScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		
		case 'N':
			ischange = true;
			s = SceneType::Tank;
			break;
		case VK_ESCAPE:
			ischange = true;
			s = SceneType::Start;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* RoallerCoasterScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
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

void RoallerCoasterScene::CheckObjectByObjectCollisions()
{
}

void RoallerCoasterScene::CheckObjectByWallCollisions()
{

}

void RoallerCoasterScene::CheckPlayerByWallCollision()
{
}

void RoallerCoasterScene::CheckObjectByBulletCollisions()
{

}
XMFLOAT3 Lerp(const XMFLOAT3& a, const XMFLOAT3& b, float t)
{
	return XMFLOAT3(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	);
}
void RoallerCoasterScene::Animate(float fElapsedTime)
{
	const float fSpeed = 500.f; // 이동 속도 (수정가능)
	m_pPlayer->m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fElapsedTime += fSpeed * fElapsedTime;

	if (m_fElapsedTime >= 1.0f)
	{
		m_fElapsedTime = 0.0f;
		index++;

		// 경로 끝나면 루프
		if (index >= static_cast<int>(m_PathPoints.size()) - 1)
		{
			index = 0;
		}
	}

	// pos0 -> pos1 보간
	const XMFLOAT3& pos0 = m_PathPoints[index];
	const XMFLOAT3& pos1 = m_PathPoints[index + 1];

	XMFLOAT3 newPos = Lerp(pos0, pos1, m_fElapsedTime);
	m_pPlayer->SetPosition(newPos);
	m_ppObjects[0]->SetPosition(newPos);

	// 항상 +X 바라보게
	m_pPlayer->m_xmf3Look = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_pPlayer->m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(m_pPlayer->m_xmf3Up, m_pPlayer->m_xmf3Look));

	m_pPlayer->OnUpdateTransform();

	// 카메라 업데이트
	XMFLOAT3 camTarget = m_pPlayer->GetPosition();

	// 플레이어 위치에서 +Y 방향으로 Offset
	XMFLOAT3 camPos =
		XMFLOAT3(0.0f, 0.0f, 0.0f); // Y축으로 30만큼 위로 올림

	// 카메라가 내려다보게 (camPos → camTarget 바라봄)
	m_pPlayer->GetCamera()->SetLookAt(camPos, camTarget, XMFLOAT3(0.0f, 1.0f, 0.0f)); // 위를 z+ 로!
	m_pPlayer->GetCamera()->GenerateViewMatrix();

	m_pPlayer->Animate(fElapsedTime);
}

void RoallerCoasterScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
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
