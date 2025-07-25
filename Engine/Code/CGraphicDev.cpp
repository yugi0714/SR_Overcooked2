#include "CGraphicDev.h"

IMPLEMENT_SINGLETON(CGraphicDev)

CGraphicDev::CGraphicDev() : m_pSDK(nullptr), m_pGraphicDev(nullptr)
{
}

CGraphicDev::~CGraphicDev()
{
}

HRESULT CGraphicDev::Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev)
{
	// 1. 그래픽 카드의 성능을 조사할 객체 생성
	 
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (nullptr == m_pSDK)
		return E_FAIL;

	 
	// 2. 그래픽 카드의 성능 조사

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// D3DADAPTER_DEFAULT : 현재 컴퓨터에 설치된 기본 그래픽 카드

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
		return E_FAIL;

	_ulong	dwFlag(0);

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		dwFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	else
		dwFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth = iSizeX;
	d3dpp.BackBufferHeight = iSizeY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD = 스왑 체인 방식
	// D3DSWAPEFFECT_FLIP =  하나의 버퍼를 번갈아 사용
	// D3DSWAPEFFECT_COPY = 더블 버퍼링과 비슷한 기법
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	d3dpp.hDeviceWindow = hWnd;
	
	d3dpp.Windowed = eMode;	// 창 모드 또는 전체화면 모드

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	// 3. 그래픽 카드의 기능을 사용할 객체 생성

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL,
									hWnd, 
									dwFlag, 
									&d3dpp, 
									&m_pGraphicDev)))
		return E_FAIL;

	*ppGraphicDev = this;

	return S_OK;
}

//  후면버퍼 동작 1. 지우기
//				2. 픽셀 값을 채울것 명령

void CGraphicDev::Render_Begin(D3DXCOLOR Color)
{
	m_pGraphicDev->Clear(0,
						NULL,
						D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
						Color,		// 후면 버퍼 텍스처 색상
						1.f,		// z버퍼 초기화 값
						0);			// 스텐실 초기화 값

	m_pGraphicDev->BeginScene();

}

//  후면버퍼 동작 1. 픽셀 값 채우기 종료
//				2. 전면 버퍼와 서피스 교환

void CGraphicDev::Render_End()
{
	m_pGraphicDev->EndScene();

	m_pGraphicDev->Present(NULL, NULL, NULL, NULL);

	// 3 인자 : 핸들 값
}

void CGraphicDev::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pSDK);
}
