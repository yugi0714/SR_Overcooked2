#include "CCubeTex.h"

CCubeTex::CCubeTex()
{
}

CCubeTex::CCubeTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CCubeTex::CCubeTex(const CCubeTex& rhs)
	: CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex()
{
}

HRESULT CCubeTex::Ready_Buffer()
{
	m_dwTriCnt = 12;
	m_dwVtxCnt = 8;
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwFVF = FVF_CUBE;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	if (FAILED(CVIBuffer::Ready_Buffer()))
		return E_FAIL;


	VTXCUBE* pVertex = NULL;

	// 버텍스 버퍼에 보관된 정점 중 첫 번째 정점의 주소를 얻어오는 매개 변수
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	// 전면
	pVertex[0].vPosition = { -1.f, 1.f, -1.f };
	pVertex[0].vTexUV = pVertex[0].vPosition;

	pVertex[1].vPosition = { 1.f, 1.f, -1.f };
	pVertex[1].vTexUV = pVertex[1].vPosition;

	pVertex[2].vPosition = { 1.f, -1.f, -1.f };
	pVertex[2].vTexUV = pVertex[2].vPosition;

	pVertex[3].vPosition = { -1.f, -1.f, -1.f };
	pVertex[3].vTexUV = pVertex[3].vPosition;

	// 후면
	pVertex[4].vPosition = { -1.f, 1.f, 1.f };
	pVertex[4].vTexUV = pVertex[4].vPosition;

	pVertex[5].vPosition = { 1.f, 1.f, 1.f };
	pVertex[5].vTexUV = pVertex[5].vPosition;

	pVertex[6].vPosition = { 1.f, -1.f, 1.f };
	pVertex[6].vTexUV = pVertex[6].vPosition;

	pVertex[7].vPosition = { -1.f, -1.f, 1.f };
	pVertex[7].vTexUV = pVertex[7].vPosition;

	m_pVB->Unlock();

	INDEX32* pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// X+
	// 오른쪽 위
	pIndex[0]._0 = 1;
	pIndex[0]._1 = 5;
	pIndex[0]._2 = 6;

	// 왼쪽 아래
	pIndex[1]._0 = 1;
	pIndex[1]._1 = 6;
	pIndex[1]._2 = 2;

	// X-
	// 오른쪽 위
	pIndex[2]._0 = 4;
	pIndex[2]._1 = 0;
	pIndex[2]._2 = 3;

	// 왼쪽 아래
	pIndex[3]._0 = 4;
	pIndex[3]._1 = 3;
	pIndex[3]._2 = 7;

	// Y+
	// 오른쪽 위
	pIndex[4]._0 = 4;
	pIndex[4]._1 = 5;
	pIndex[4]._2 = 1;

	// 왼쪽 아래
	pIndex[5]._0 = 4;
	pIndex[5]._1 = 1;
	pIndex[5]._2 = 0;

	// Y-
	// 오른쪽 위
	pIndex[6]._0 = 3;
	pIndex[6]._1 = 2;
	pIndex[6]._2 = 6;

	// 왼쪽 아래
	pIndex[7]._0 = 3;
	pIndex[7]._1 = 6;
	pIndex[7]._2 = 7;

	// Z+
	// 오른쪽 위
	pIndex[8]._0 = 7;
	pIndex[8]._1 = 6;
	pIndex[8]._2 = 5;

	// 왼쪽 아래
	pIndex[9]._0 = 7;
	pIndex[9]._1 = 5;
	pIndex[9]._2 = 4;

	// Z-
	// 오른쪽 위
	pIndex[10]._0 = 0;
	pIndex[10]._1 = 1;
	pIndex[10]._2 = 2;

	// 왼쪽 아래
	pIndex[11]._0 = 0;
	pIndex[11]._1 = 2;
	pIndex[11]._2 = 3;

	m_pIB->Unlock();


	return S_OK;
}

void CCubeTex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CComponent* CCubeTex::Clone()
{
	return new CCubeTex(*this);
}

CCubeTex* CCubeTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCubeTex* pCubeTex = new CCubeTex(pGraphicDev);

	if (FAILED(pCubeTex->Ready_Buffer()))
	{
		Safe_Release(pCubeTex);
		MSG_BOX("CubeTex Create Failed");
		return nullptr;
	}

	return pCubeTex;
}

void CCubeTex::Free()
{
	CVIBuffer::Free();
}
