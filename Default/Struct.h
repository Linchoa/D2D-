#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// 위치 벡터
	D3DXVECTOR3		vDir;		// 방향 벡터

	D3DXVECTOR3		vLook;		// 방향 벡터
	D3DXVECTOR3		vNormal;	// 법선 벡터
	
	D3DXMATRIX		matWorld;	// 월드 행렬

}INFO;


static D3DXVECTOR3			Get_Mouse(void)
{
	POINT		pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3(float(pt.x), float(pt.y), 0.f);
}