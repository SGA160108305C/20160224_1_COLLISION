#include "stdafx.h"
#include "UI_Manager.h"


UI_Manager::UI_Manager()
{
}


UI_Manager::~UI_Manager()
{
}

void UI_Manager::Initialize()
{
	Destroy();

	//폰트 생성
	D3DXFONT_DESC font_desc;
	ZeroMemory(&font_desc, sizeof(D3DXFONT_DESC));
	font_desc.Height = 50;
	font_desc.Width = 25;
	font_desc.Weight = FW_NORMAL;
	font_desc.MipLevels = D3DX_DEFAULT;
	font_desc.Italic = false;
	font_desc.CharSet = DEFAULT_CHARSET;
	font_desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	font_desc.Quality = DEFAULT_QUALITY;
	font_desc.PitchAndFamily = FF_DONTCARE;
	wcscpy_s(font_desc.FaceName, L"휴먼편지체");	//글꼴 스타일
	//AddFontResource(L"./Data/Font/umberto.ttf");
	//wcscpy_s(font_desc.FaceName, L"umberto");
	D3DXCreateFontIndirect(GameManager::GetDevice(), &font_desc, &font);
	
}

void UI_Manager::Destroy()
{
	SAFE_RELEASE(font);

}

void UI_Manager::Update()
{
}

void UI_Manager::Render()
{
}

LRESULT UI_Manager::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	return result;
}
