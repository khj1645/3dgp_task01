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
	{ -15,  0,   0 },  // p0
	{ -10,  0,   0 },  // p1 ← 시작점
	{  -5,  3,   0 },  // p2
	{   0,  5,  0 },
	{   5,  2,  10},
	{  10,  0,  0 },
	{  15, -3,  0 },
	{  20,  0,  0 },
	{  25,  5,  0 },
	{  30,  3,  0 },
	{  35,  0,  0 },
	};

	for (size_t i = 0; i + 3 < controlPoints.size(); ++i) {
		XMFLOAT3 p0 = controlPoints[i];
		XMFLOAT3 p1 = controlPoints[i + 1];
		XMFLOAT3 p2 = controlPoints[i + 2];
		XMFLOAT3 p3 = controlPoints[i + 3];

		for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
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
		railObj->SetPosition(pos.x, pos.y, pos.z);

		m_ppObjects.push_back(std::move(railObj));

		railObj2->SetMesh(smc);
		railObj2->SetPosition(pos.x, pos.y, pos.z + 1);
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

void RoallerCoasterScene::Animate(float fElapsedTime)
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
	index++;
	if (index >= 801) {
		//ischange = true;
		s = SceneType::Tank;
	}
	int nin = min(800, index);
	XMFLOAT3 pos = m_PathPoints[index];
	m_ppObjects[0]->SetPosition(m_PathPoints[nin].x, m_PathPoints[nin].y, m_PathPoints[nin].z);
	m_pPlayer->SetPosition(m_PathPoints[nin].x, m_PathPoints[nin].y, m_PathPoints[nin].z);

	CheckPlayerByWallCollision();

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();
}

void RoallerCoasterScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
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
