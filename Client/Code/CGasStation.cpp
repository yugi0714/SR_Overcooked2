#include "pch.h"
#include "CGasStation.h"

CGasStation::CGasStation(LPDIRECT3DDEVICE9 pGraphicDev)
	: CInteract(pGraphicDev)
{
}

CGasStation::CGasStation(const CGameObject& rhs)
	: CInteract(rhs)
{
}

CGasStation::~CGasStation()
{
}

HRESULT CGasStation::Ready_GameObject()
{
	return S_OK;
}

_int CGasStation::Update_GameObject(const _float& fTimeDelta)
{
	return 0;
}

void CGasStation::LateUpdate_GameObject(const _float& fTimeDelta)
{
}

void CGasStation::Render_GameObject()
{
}

HRESULT CGasStation::Add_Component()
{
	return S_OK;
}

CGasStation* CGasStation::Create(LPDIRECT3DDEVICE9 pGraphicDev) {
	return nullptr;
}

void CGasStation::Free()
{
}

_bool CGasStation::Get_CanPlace(ICarry* pCarry) const
{
	return _bool();
}

void CGasStation::Set_CarryTypes()
{
}