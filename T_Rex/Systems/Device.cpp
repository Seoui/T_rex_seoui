#include "stdafx.h"
#include "Device.h"

int APIENTRY WinMain
(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPSTR lPCmdLine,
	int nCmdShow
)
{
	InitWindow(hInstance, nCmdShow);
	InitDirect3D(hInstance);

	Running();
	Destroy();

	return 0;
}

UINT Width = 700;
UINT Height = 350;
HWND Hwnd = nullptr;
wstring Title = L"D2D";

IDXGISwapChain* SwapChain = nullptr;
ID3D11Device* Device = nullptr;
ID3D11DeviceContext* DeviceContext = nullptr;
ID3D11RenderTargetView* RTV = nullptr;

Keyboard* Key = nullptr;
CMouse* Mouse = nullptr;

void InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	//Register Wnd Class
	{
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)WHITE_BRUSH;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = Title.c_str();
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		WORD check = RegisterClassEx(&wc);
		assert(check != NULL);
	}

	//Create Window & Show Window
	{
		Hwnd = CreateWindowEx
		(
			NULL,
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			Width,
			Height,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		assert(Hwnd != nullptr);

		RECT rect = { 0, 0, (LONG)Width, (LONG)Height };
		UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;
		UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)Height) / 2;
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		MoveWindow
		(
			Hwnd, centerX, centerY,
			rect.right - rect.left,
			rect.bottom - rect.top,
			TRUE
		);

		ShowWindow(Hwnd, nCmdShow);
		UpdateWindow(Hwnd);
	}
}

void InitDirect3D(HINSTANCE hInstance)
{
	//SwapChain
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
	bufferDesc.RefreshRate.Numerator = 60;		// 분자 60
	bufferDesc.RefreshRate.Denominator = 1;		// 분모 1 , 60프레임
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // R 8비트, G 8비트, B 8비트, A 8비트, UNORM의미는 256가지 색상을 1로 표준화
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferDesc = bufferDesc;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.OutputWindow = Hwnd;
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	vector<D3D_FEATURE_LEVEL> feature_level =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	// Create Device & SwapChain
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		feature_level.data(),
		feature_level.size(),
		D3D11_SDK_VERSION,
		&swapDesc,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);
	assert(SUCCEEDED(hr));

	CreateBackBuffer();
}

void Destroy()
{
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(Device);
	SAFE_RELEASE(DeviceContext);
	
	DeleteBackBuffer();
}

WPARAM Running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	ImGui::Create(Hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();

	DirectWrite::Create();

	Time::Create();
	Time::Get()->Start();

	Key = new Keyboard();
	Mouse = new CMouse(Hwnd);

	InitScene();

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Time::Get()->Update();
			Update();
			Mouse->Update();
			ImGui::Update();
			Render();
		}
	}

	DestroyScene();

	SAFE_DELETE(Key);
	SAFE_DELETE(Mouse);
	Time::Delete();
	ImGui::Delete();
	DirectWrite::Delete();

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)Hwnd, msg, wParam, lParam))
		return true;
	 
	if (Mouse != nullptr)
		Mouse->WndProc(msg, wParam, lParam);

	switch (msg)
	{
	case WM_SIZE:
	{
		if(Device != nullptr)
		{
			ImGui::Invalidate();

			Width = LOWORD(lParam);
			Height = HIWORD(lParam);

			DeleteBackBuffer();
			DirectWrite::DeleteBackBuffer();

			HRESULT hr = SwapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(hr));

			DirectWrite::CreateBackBuffer();
			CreateBackBuffer();

			ImGui::Validate();
		}
	}
	break;
		case WM_DESTROY: PostQuitMessage(0); return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CreateBackBuffer()
{
	// Get BackBuffer
	ID3D11Texture2D* BackBuffer;
	HRESULT hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	assert(SUCCEEDED(hr));

	// Create RTV
	hr = Device->CreateRenderTargetView(BackBuffer, nullptr, &RTV);
	assert(SUCCEEDED(hr));
	BackBuffer->Release();

	// Set OM
	DeviceContext->OMSetRenderTargets(1, &RTV, nullptr);

	// Create Viewport
	{
		D3D11_VIEWPORT viewPort;
		ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
		viewPort.TopLeftX = 0;
		viewPort.TopLeftY = 0;
		viewPort.Width = (float)Width;
		viewPort.Height = (float)Height;

		DeviceContext->RSSetViewports(1, &viewPort);
	}
}

void DeleteBackBuffer()
{
	SAFE_RELEASE(RTV);
}