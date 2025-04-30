#include "stdafx.h"
#include "TankScene.h"
#include "GraphicsPipeline.h"

TankCScene::TankCScene(CPlayer* pPlayer)
	: CSceneBase(pPlayer) {
	m_pPlayer = pPlayer;
}

TankCScene::~TankCScene()
{
}

void TankCScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;
	//CWallMesh* pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);
	std::shared_ptr<CMesh> mesh = std::make_shared<CWallMesh>(
		fHalfWidth * 2.0f,
		fHalfHeight * 2.0f,
		fHalfDepth * 2.0f,
		30
	);

	m_pWallsObject = std::make_unique<CWallsObject>();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(mesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
	m_pWallsObject->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	//CCubeMesh* pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);
	std::shared_ptr<CMesh> pCubeMesh = std::make_shared<CTankMesh>(6.0f, 6.0f, 1.0f);
	m_ppObjects.resize(10);
	//m_ppObjects = new CGameObject * [m_nObjects];

	m_ppObjects[0] = std::make_unique<CExplosiveObject>();
	m_ppObjects[0]->SetMesh(pCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, -45.0f, 14.0f);
	m_ppObjects[0]->SetPosition(-13.5f, -45.0f, 14.0f);
	//m_ppObjects[0]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[0]->SetRotationSpeed(90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = std::make_unique<CExplosiveObject>();
	m_ppObjects[1]->SetMesh(pCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, -45.0f, 10.0f);
	//m_ppObjects[1]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[1]->SetRotationSpeed(180.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = std::make_unique<CExplosiveObject>();
	m_ppObjects[2]->SetMesh(pCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, -45.0f, 20.0f);
	//m_ppObjects[2]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[2]->SetRotationSpeed(30.15f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = std::make_unique<CExplosiveObject>();
	m_ppObjects[3]->SetMesh(pCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 255));
	m_ppObjects[3]->SetPosition(0.0f, -45.0f, 0.0f);
	//m_ppObjects[3]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects[3]->SetRotationSpeed(40.6f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = std::make_unique<CExplosiveObject>();
	m_ppObjects[4]->SetMesh(pCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, -45.0f, 0.0f);
	//m_ppObjects[4]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[4]->SetRotationSpeed(50.06f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = std::make_unique<CExplosiveObject>();
	m_ppObjects[5]->SetMesh(pCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, -45.0f, 10.0f);
	//m_ppObjects[5]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[5]->SetRotationSpeed(60.06f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = std::make_unique<CExplosiveObject>();
	m_ppObjects[6]->SetMesh(pCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, -45.0f, 5.0f);
	//m_ppObjects[6]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[6]->SetRotationSpeed(60.06f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = std::make_unique<CExplosiveObject>();
	m_ppObjects[7]->SetMesh(pCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, -45.0f, 20.0f);
	//m_ppObjects[7]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_ppObjects[7]->SetRotationSpeed(70.06f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = std::make_unique<CExplosiveObject>();
	m_ppObjects[8]->SetMesh(pCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, -45.0f, 30.0f);
	//m_ppObjects[8]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[8]->SetRotationSpeed(90.06f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = std::make_unique<CExplosiveObject>();
	m_ppObjects[9]->SetMesh(pCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, -45.0f, 0.0f);
	//m_ppObjects[9]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects[9]->SetRotationSpeed(90.06f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, -1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);
	for (int i = 0; i < 10; ++i)
		m_ppObjects[i]->typenum = 1;
	std::shared_ptr<CMesh> pObstacleMesh = std::make_shared<CCubeMesh>(20.0f,8.0f, 20.0f);
	float fMinX = -45.0f;
	float fMaxX = 45.0f;
	float fMinZ = 50.0f;   // 플레이어(z=0)보다 충분히 앞에 배치
	float fMaxZ = 200.0f;
	float yPosition = -45.0f; // 바닥

	for (int i = 0; i < 7; i++) {
		auto obstacle = std::make_unique<CObstacleObject>();
		obstacle->SetMesh(pObstacleMesh);
		obstacle->SetColor(RGB(0, 0, 255));
		// x는 자유롭게 랜덤
		float x = fMinX + static_cast<float>(rand()) / RAND_MAX * (fMaxX - fMinX);
		// z는 항상 50 ~ 200 사이
		float z = fMinZ + static_cast<float>(rand()) / RAND_MAX * (fMaxZ - fMinZ);

		obstacle->SetPosition(x, yPosition, z);
		m_ppObjects.push_back(std::move(obstacle));
	}
	m_pPlayer->m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_pPlayer->m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
	// 여기서 반드시 초기화
	m_pPlayer->OnUpdateTransform();
	XMMATRIX fix = XMMatrixRotationX(XMConvertToRadians(-90.0f));
	XMStoreFloat4x4(&m_pPlayer->m_xmf4x4World, XMMatrixMultiply(XMLoadFloat4x4(&m_pPlayer->m_xmf4x4World), fix));
#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}

void TankCScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();
	m_ppObjects.clear();
	m_pWallsObject.reset();
#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis;
#endif
}
bool TankCScene::IsChangeSceneRequested() const {
	return ischange;
}
SceneType TankCScene::GetNextSceneName() const
{
	return SceneType::Start;
}
void TankCScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void TankCScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
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
		{
			CExplosiveObject* pExplosiveObject = static_cast<CExplosiveObject*>(m_ppObjects[int(wParam - '1')].get());
			pExplosiveObject->m_bBlowingUp = true;
			break;
		}
		case 'A':
			if (!isaim) isaim = true;
			else isaim = false;
			break;
		case 'S':
			if (!iscol) iscol = true;
			else iscol = false;
			break;
		case 'W':
			for (int i = 0; i < m_ppObjects.size(); ++i)
			{
				CExplosiveObject* pExplosiveObject = static_cast<CExplosiveObject*>(m_ppObjects[i].get());
				if (pExplosiveObject->m_bBlowingUp == false)	++killcount;
				pExplosiveObject->m_bBlowingUp = true;

			}

			killcount = 10;
			break;
		case VK_ESCAPE:
			ischange = true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
CGameObject* TankCScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
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
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance) && (m_ppObjects[i]->typenum == 1))
		{
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i].get();
		}
	}
	if (pNearestObject != nullptr) {
		((CTankPlayer*)m_pPlayer)->FireBullet(pNearestObject);
		pNearestObject = nullptr;
	}
	return(pNearestObject);
}
XMFLOAT3 GetCollisionNormal(const BoundingOrientedBox& movingBox, const BoundingOrientedBox& obstacleBox)
{
	XMFLOAT3 normal = { 0.0f, 0.0f, 0.0f };

	if (movingBox.Center.x > obstacleBox.Center.x) normal.x = 1.0f;
	else normal.x = -1.0f;

	if (movingBox.Center.z > obstacleBox.Center.z) normal.z = 1.0f;
	else normal.z = -1.0f;

	return normal;
}
void TankCScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->m_pObjectCollided = NULL;

	for (int i = 0; i < m_ppObjects.size(); i++)
	{
		for (int j = (i + 1); j < m_ppObjects.size(); j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				// 둘 중 하나라도 장애물이면
				if (dynamic_cast<CObstacleObject*>(m_ppObjects[i].get()) || dynamic_cast<CObstacleObject*>(m_ppObjects[j].get()))
				{

					CGameObject* pMovingObject = dynamic_cast<CObstacleObject*>(m_ppObjects[i].get()) ? m_ppObjects[j].get() : m_ppObjects[i].get();

					XMFLOAT3 normal = { 0.0f, 0.0f, 0.0f };
					if (dynamic_cast<CObstacleObject*>(m_ppObjects[i].get()))
						normal = GetCollisionNormal(pMovingObject->m_xmOOBB, m_ppObjects[i]->m_xmOOBB);
					else
						normal = GetCollisionNormal(pMovingObject->m_xmOOBB, m_ppObjects[j]->m_xmOOBB);

					XMVECTOR xmvNormal = XMVector3Normalize(XMLoadFloat3(&normal));
					XMVECTOR xmvMoveDir = XMLoadFloat3(&pMovingObject->m_xmf3MovingDirection);

					XMVECTOR xmvReflected = XMVector3Reflect(xmvMoveDir, xmvNormal);
					XMStoreFloat3(&pMovingObject->m_xmf3MovingDirection, xmvReflected);
				}
				else
				{
					m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j].get();
					m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i].get();
				}
			}
		}
	}
	for (int i = 0; i < m_ppObjects.size(); i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

void TankCScene::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_ppObjects.size(); i++)
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}
void TankCScene::CheckPlayerByObstacleCollision()
{
	if (iscol) {
		BoundingOrientedBox playerOOBB = m_pPlayer->m_xmOOBB;

		for (const auto& obj : m_ppObjects)
		{
			if (dynamic_cast<CObstacleObject*>(obj.get()))
			{
				if (playerOOBB.Intersects(obj->m_xmOOBB))
				{
					m_pPlayer->SetPosition(m_pPlayer->prpos.x, m_pPlayer->prpos.y, m_pPlayer->prpos.z);

					m_pPlayer->m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
					break;
				}
			}
			if (dynamic_cast<CExplosiveObject*>(obj.get()))
			{
				if (playerOOBB.Intersects(obj->m_xmOOBB))
				{
					m_pPlayer->SetPosition(0,-45,0);

					break;
				}
			}
		}
	}
}
void TankCScene::CheckPlayerByWallCollision()
{
	BoundingOrientedBox playerOOBB = m_pPlayer->m_xmOOBB;

	// 왼쪽, 오른쪽 벽면만 검사
	for (int i : {0, 1}) // ← 인덱스는 실제 좌/우 벽에 맞게 조정
	{
		PlaneIntersectionType result = playerOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[i]));

		if (result == BACK || result == INTERSECTING)
		{
			// 위치 되돌리기
			m_pPlayer->SetPosition(m_pPlayer->prpos.x, m_pPlayer->GetPosition().y, m_pPlayer->GetPosition().z);

			// 반사 방향 계산 (선택)
			XMVECTOR normal = XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[i]);
			XMVECTOR moveDir = XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection);
			XMVECTOR reflectDir = XMVector3Reflect(moveDir, normal);
			XMStoreFloat3(&m_pPlayer->m_xmf3MovingDirection, reflectDir);

			// 멈추고 싶다면 속도도 0
			// m_pPlayer->m_fMovingSpeed = 0.0f;

			break; // 두 벽 중 하나만 충돌해도 처리 끝
		}
	}
}

void TankCScene::CheckObjectByBulletCollisions()
{
	CBulletObject** ppBullets = ((CAirplanePlayer*)m_pPlayer)->m_ppBullets;

	for (int i = 0; i < m_ppObjects.size(); )
	{
		bool bDestroyed = false;
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				// 장애물일 경우
				if (CObstacleObject* pObstacle = dynamic_cast<CObstacleObject*>(m_ppObjects[i].get()))
				{
					if (iscol) {
						pObstacle->Damage();
						ppBullets[j]->Reset();

						if (pObstacle->IsDestroyed())
						{
							bDestroyed = true;
							break; // 장애물 죽으면 바로 삭제
						}
					}
				}
				else
				{
					// 폭발 오브젝트일 경우
					CExplosiveObject* pExplosiveObject = static_cast<CExplosiveObject*>(m_ppObjects[i].get());
					if (pExplosiveObject->m_bBlowingUp == false)	++killcount;
					pExplosiveObject->m_bBlowingUp = true;
					ppBullets[j]->Reset();

				}
			}
		}

		if (bDestroyed) {
			m_ppObjects.erase(m_ppObjects.begin() + i);
		}
		else
			++i;
	}
}

void TankCScene::Animate(float fElapsedTime)
{

	m_pWallsObject->Animate(fElapsedTime);

	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Animate(fElapsedTime);

	CheckPlayerByWallCollision();

	CheckObjectByWallCollisions();

	CheckObjectByObjectCollisions();

	CheckObjectByBulletCollisions();
	CheckPlayerByObstacleCollision();

	auto it = std::remove_if(m_ppObjects.begin(), m_ppObjects.end(),
		[](const std::unique_ptr<CGameObject>& obj) {
			CExplosiveObject* pExplosive = dynamic_cast<CExplosiveObject*>(obj.get());
			return (pExplosive && !pExplosive->m_bActive); // 폭발 끝나면 삭제
		});
	m_ppObjects.erase(it, m_ppObjects.end());
	if (killcount >= 10 && !win) {
		win = true;
		auto cubeMesh = std::make_shared<CCubeMesh>(1.0f, 1.0f, 1.0f);

		// 각각 글자별 큐브 좌표
		std::map<char, std::vector<XMFLOAT3>> letterCoords = {
	{'Y', { {0,6,0},{1,5,0},{2,4,0},{3,3,0},{4,4,0},{5,5,0},{6,6,0},{3,2,0},{3,1,0},{3,0,0} }},
	{'O', { {0,6,0},{1,6,0},{2,6,0},{3,6,0},{4,6,0},{5,6,0},{6,6,0},
			{0,5,0},{6,5,0},
			{0,4,0},{6,4,0},
			{0,3,0},{6,3,0},
			{0,2,0},{6,2,0},
			{0,1,0},{6,1,0},
			{0,0,0},{1,0,0},{2,0,0},{3,0,0},{4,0,0},{5,0,0},{6,0,0} }},
	{'U', { {0,6,0},{6,6,0},
			{0,5,0},{6,5,0},
			{0,4,0},{6,4,0},
			{0,3,0},{6,3,0},
			{0,2,0},{6,2,0},
			{0,1,0},{6,1,0},
			{1,0,0},{2,0,0},{3,0,0},{4,0,0},{5,0,0}}},
	{'W', {
			{0,6,0},{6,6,0},
			{0,5,0},{6,5,0},
			{0,4,0},{6,4,0},
			{1,3,0},{5,3,0},
			{2,2,0},{4,2,0},
			{2,1,0},{4,1,0},
			{3,0,0},

			{-3,6,0},{3,6,0},
			{-3,5,0},{3,5,0},
			{-3,4,0},{3,4,0},
			{-2,3,0},{2,3,0},
			{-1,2,0},{1,2,0},
			{-1,1,0},{1,1,0},
			{0,0,0}
		}},
	{'I', { {0,6,0},{1,6,0},{2,6,0},
			{1,5,0},
			{1,4,0},
			{1,3,0},
			{1,2,0},
			{1,1,0},
			{0,0,0},{1,0,0},{2,0,0}}},
	{'N', { {0,6,0},{6,6,0},
			{0,5,0},{1,5,0},{6,5,0},
			{0,4,0},{2,4,0},{6,4,0},
			{0,3,0},{3,3,0},{6,3,0},
			{0,2,0},{4,2,0},{6,2,0},
			{0,1,0},{5,1,0},{6,1,0},
			{0,0,0},{6,0,0}}},
	{'!', { {3,6,0},
			{3,5,0},
			{3,4,0},
			{3,2,0},
			{3,0,0}}}
		};

		// 출력할 문장
		std::string text = "YOU WIN!";

		// 기준점 잡기
		XMFLOAT3 playerPos = m_pPlayer->GetPosition();
		float baseX = playerPos.x - 15.0f; // 좌우 중심 맞추기용
		float baseY = playerPos.y + 5.0f;   // y를 낮게 (15 → 5)
		float baseZ = playerPos.z + 30.0f;  // 플레이어 앞쪽

		const float spacing = 6.0f; // 글자 간 간격 (조절가능)

		int letterIndex = 0;
		for (char c : text)
		{
			if (c == ' ') { letterIndex++; continue; } // 공백 건너뜀

			auto& coords = letterCoords[c];

			for (const auto& pos : coords)
			{
				auto letterObj = std::make_unique<CGameObject>();
				letterObj->SetMesh(cubeMesh);

				float x = baseX + letterIndex * spacing + pos.x * 0.6f;
				float y = baseY + pos.y * 0.6f;
				float z = baseZ + pos.z * 0.6f;
				letterObj->SetPosition(x, y, z);

				m_ppObjects.push_back(std::move(letterObj));
			}
			letterIndex++;
		}

	}
}
void TankCScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);

	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	
	m_pWallsObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_ppObjects.size(); i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);

	//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
