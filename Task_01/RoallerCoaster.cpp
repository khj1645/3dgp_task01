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
	std::vector<XMVECTOR> controlPoints = {
		{0, 0, 50},    // 시작 - Z+ 방향
		{30, 10, 30},
		{50, 20, 0},
		{30, 30, -30},
		{0, 40, -50},  // 반바퀴
		{-30, 30, -30},
		{-50, 20, 0},
		{-30, 10, 30},
		{0, 0, 50},    // 제자리 복귀

		// 두 번째 레벨 (Z축 아래로 나선형)
		{0, -10, 80},
		{40, -20, 40},
		{80, -30, 0},
		{40, -40, -40},
		{0, -50, -80},
		{-40, -40, -40},
		{-80, -30, 0},
		{-40, -20, 40},
		{0, -10, 80},

		// 마지막 스프린트
		{0, 0, 100},
		{50, 10, 100},
		{100, 20, 50},
		{100, 30, 0}
	};

	for (size_t i = 0; i + 3 < controlPoints.size(); ++i) {
		XMVECTOR p0 = controlPoints[i];
		XMVECTOR p1 = controlPoints[i + 1];
		XMVECTOR p2 = controlPoints[i + 2];
		XMVECTOR p3 = controlPoints[i + 3];

		for (float t = 0.0f; t <= 1.0f; t += 0.005f) {
			m_PathPoints.push_back(XMVectorCatmullRom(p0, p1, p2, p3, t));
		}
	}
		
	auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);
	float scale = 0.6f;
	auto cube = std::make_unique<CGameObject>();
	cube->SetMesh(cubeMesh);
	cube->SetPosition(-10, 0, 0);
	m_ppObjects.push_back(std::move(cube));
	auto smc = std::make_shared<CCubeMesh>(0.2f, 0.2f, 0.2f);
	for (size_t i = 0; i < m_PathPoints.size(); i += 10)
	{
		auto pos = m_PathPoints[i];
		XMFLOAT3 rpos;
		auto railObj = std::make_unique<CGameObject>();
		auto railObj2 = std::make_unique<CGameObject>();
		railObj->SetMesh(smc);
		XMStoreFloat3(&rpos, pos);
		railObj->SetPosition(rpos.x, rpos.y, rpos.z - 2);

		m_ppObjects.push_back(std::move(railObj));

		railObj2->SetMesh(smc);
		railObj2->SetPosition(rpos.x, rpos.y, rpos.z + 2);
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
	CGameObject* pNearestObject = NULL;
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
	const float fSpeed = 250.f; // 이동 속도 (수정가능)
	m_pPlayer->m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fElapsedTime += fSpeed * fElapsedTime;

	while (m_fElapsedTime >= 1.0f)
	{
		m_fElapsedTime -= 1.0f;
		index = (index + 1);

		// ✅ 경로 끝에 도달하면 Scene 전환 요청
		if (index >= m_PathPoints.size() - 1)
		{
			index = m_PathPoints.size() - 2; // 안전하게 고정
			ischange = true;
			s = SceneType::Tank;
			return; // 더 진행할 필요 없으니 바로 리턴
		}
	}

	// pos0 -> pos1 보간
	const XMVECTOR& pos0 = m_PathPoints[index];
	const XMVECTOR& pos1 = m_PathPoints[index + 1];
	XMFLOAT3 newpos;
	XMStoreFloat3(&newpos,XMVectorLerp(pos0, pos1, m_fElapsedTime));
	m_pPlayer->SetPosition(newpos);
	m_ppObjects[0]->SetPosition(newpos);

	m_pPlayer->m_xmf3Look = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_pPlayer->m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(m_pPlayer->m_xmf3Up, m_pPlayer->m_xmf3Look));

	m_pPlayer->OnUpdateTransform();

	XMFLOAT3 camTarget = m_pPlayer->GetPosition();

	XMFLOAT3 camPos = XMFLOAT3(
		camTarget.x - 20.0f,
		camTarget.y,
		camTarget.z - 20.0f
	);

	m_pPlayer->GetCamera()->SetLookAt(camPos, camTarget, XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pPlayer->GetCamera()->GenerateViewMatrix();

	m_pPlayer->Animate(fElapsedTime);
}

void RoallerCoasterScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);
	//m_pWallsObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

  // if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);
	
	//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
