#pragma once
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CVertex
{
public:
	CVertex() { m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	CVertex(float x, float y, float z) { m_xmf3Position = XMFLOAT3(x, y, z); }
	~CVertex() { }

	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
};

class CPolygon
{
public:
	CPolygon() { }
	CPolygon(int nVertices);
	~CPolygon() = default;

	//int							m_nVertices = 0;
	//CVertex						*m_pVertices = NULL;
	std::vector<CVertex> m_pVertices;

	void SetVertex(int nIndex, CVertex& vertex);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh
{
public:
	CMesh() { }
	CMesh(int nPolygons);
	virtual ~CMesh() = default;

private:
	int							m_nReferences = 1;

public:
	void AddRef() { m_nReferences++; }
	void Release() { m_nReferences--; if (m_nReferences <= 0) delete this; }

protected:
	//int							m_nPolygons = 0;
	//CPolygon					**m_ppPolygons = NULL;
	std::vector<CPolygon> m_ppPolygons;

public:
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox();

public:
	void SetPolygon(int nIndex, CPolygon &pPolygon);

	virtual void Render(HDC hDCFrameBuffer);

	BOOL RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance);
	int CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance);
};

class CCubeMesh : public CMesh
{
public:
	CCubeMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CCubeMesh() { }
};

class CWallMesh : public CMesh
{
public:
	CWallMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f, int nSubRects = 20);
	virtual ~CWallMesh() { }
};

class CAirplaneMesh : public CMesh
{
public:
	CAirplaneMesh(float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	virtual ~CAirplaneMesh() { }
};

class CTankMesh : public CMesh
{
public:
	CTankMesh(float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	
	virtual ~CTankMesh() {}
};

class CAxisMesh : public CMesh
{
public:
	CAxisMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CAxisMesh() { }

	virtual void Render(HDC hDCFrameBuffer);
};
