#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <Crosshair.h>
#include <Renderer.h>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Screen Dimensions
int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);
ImVec2 screenCenter = ImVec2(screenWidth * 0.5f, screenHeight * 0.5f);

bool receive_input = false;

// Objects
ImDrawList* canvas;
Crosshair crosshair = Crosshair();
Renderer renderer = Renderer();

// Update window for menu
void updateWindow(HWND updatedWindow) {
	LONG style = GetWindowLong(updatedWindow, GWL_EXSTYLE);

	if (Settings::menu) {
		style &= ~WS_EX_TRANSPARENT;
	}
	else {
		style |= WS_EX_TRANSPARENT;
	}

	SetWindowLong(updatedWindow, GWL_EXSTYLE, style);
	SetLayeredWindowAttributes(updatedWindow, 0, 255, LWA_ALPHA);
}

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param)) {
		return 0L;
	}

	if (message == WM_DESTROY) {
		PostQuitMessage(0);
		return 0L;
	}
	// Menu
	switch (message) {
	case WM_KEYDOWN :
		if (w_param == VK_INSERT) {
			Settings::menu = !Settings::menu;
			updateWindow(window);

			if (Settings::menu) {
				receive_input = true;
				SetCapture(window);
				
			}
			else {
				receive_input = false;
				ReleaseCapture();
				
			}
		}

		if (w_param == Settings::hide) {
			Settings::draw = !Settings::draw;
		}
		break;
	}

	return DefWindowProc(window, message, w_param, l_param);
}

bool registerWindow(HINSTANCE instance, WNDCLASSEX& wc) {
	wc = { };
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = window_procedure;
	wc.hInstance = instance;
	wc.lpszClassName = L"Crosshair Overlay";

	return RegisterClassExW(&wc);
}

HWND createOverlayWindow(const WNDCLASSEXW& wc, HINSTANCE instance, int width, int height) {
	HWND window = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		wc.lpszClassName,
		L"Crosshair Overlay",
		WS_POPUP,
		0,
		0,
		screenWidth,
		screenHeight,
		nullptr,
		nullptr,
		wc.hInstance,
		nullptr
	);

	// Make window fully transparent and layered
	SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA); // LWA_ALPHA allows to see content in transparent window

	// Extend frame into client area for more complex window borders
	{
		RECT client_area{};
		GetClientRect(window, &client_area);

		RECT window_area{};
		GetWindowRect(window, &window_area);

		POINT diff{};
		ClientToScreen(window, &diff);

		const MARGINS margins{
			window_area.left + (diff.x - window_area.left),
			window_area.top + (diff.y - window_area.top),
			client_area.right,
			client_area.bottom
		};

		DwmExtendFrameIntoClientArea(window, &margins);
	}

	return window;
}

bool initD3D11(HWND window, ID3D11Device*& device, ID3D11DeviceContext*& device_context, IDXGISwapChain*& swap_chain, ID3D11RenderTargetView*& render_target_view, D3D_FEATURE_LEVEL& level) {
	DXGI_SWAP_CHAIN_DESC sd{};
	sd.BufferDesc.RefreshRate.Numerator = 60U;
	sd.BufferDesc.RefreshRate.Denominator = 1U;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1U;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2U;
	sd.OutputWindow = window;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levels[2]{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	// Create Device and swap
	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0U,
		levels,
		2U,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		&level,
		&device_context
		))) {

		return false;
	}

	ID3D11Texture2D* back_buffer{ nullptr };
	swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

	if (back_buffer) {
		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
		back_buffer->Release();
	}
	else {
		return false;
	}

	return true;
}

void destroyOverlay(HWND window, WNDCLASSEXW wc, IDXGISwapChain* swap_chain, ID3D11DeviceContext* device_context, ID3D11Device* device, ID3D11RenderTargetView* render_target_view) {
	// Shutdown
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();

	if (swap_chain) {
		swap_chain->Release();
	}

	if (device_context) {
		device_context->Release();
	}

	if (device) {
		device->Release();
	}

	if (render_target_view) {
		render_target_view->Release();
	}


	DestroyWindow(window);
	UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

// To be able to have the overlay over games, they need to run in bordless window.
// For learn porpuse I want to try to hook this overlay to other overlay that anticheats allow
// I didnt bother because my games runs equally good, bordless or fullscreen I dont see diference in FPS...
// With time I may learn to do that, didnt sound difficult...
// Choose window and capture
// Idea here was to make it work like a screen recorder, choose app to capture, overlay on it. The point is that anticheats may detect that so it was kinda pointless
// Crosshairs are usefull in FPS games mostly and those games have all anticheats... Run this app in bordless window and never gonna be a problem.
// For learning porpuse will be nice to learn how to create a hook to other overlay that its allowed.
// I believe that anti cheats will not flag overlays like this one because they have nothing to do with the game directly, no read or write mem or intercep any kinda data

// Callback function for EnumWindows
/*
static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	char windowTitle[256];
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

	// Check if the window title matches the app you want to capture
	if (strcmp(windowTitle, "Target Application Title") == 0) {
		HWND* pTargetHWND = (HWND*)lParam;
		*pTargetHWND = hwnd;
		return FALSE;  // Stop enumeration when the window is found
	}
	return TRUE;
}

// Find window by title
static HWND FindTargetWindow() {
	HWND targetHWND = NULL;
	EnumWindows(EnumWindowsProc, (LPARAM)&targetHWND);
	return targetHWND;
}

static void captureScreen() {

}*/
INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE, PSTR, INT cmd_show) {
	// Register Create window, D3D11 init
	WNDCLASSEXW wc;
	if (!registerWindow(instance, wc)) {
		return -1;
	}

	// Create window
	HWND window = createOverlayWindow(wc, instance, screenWidth, screenHeight);
	if (!window) {
		return -1;
	}

	// D3D11
	ID3D11Device* device{ nullptr };
	ID3D11DeviceContext* device_context{ nullptr };
	IDXGISwapChain* swap_chain{ nullptr };
	ID3D11RenderTargetView* render_target_view{ nullptr };
	D3D_FEATURE_LEVEL level{};

	if (!initD3D11(window, device, device_context, swap_chain, render_target_view, level)) {
		return -1;
	}

	// Set up imgui
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, device_context);

	// Show and update
	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);
	SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	// loop
	bool running = true;
	while (running) {
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				running = false;
			}
		}

		if (!running) {
			break;
		}

		// Init stuff
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// Render Crosshair
		renderer.RenderOverlay(canvas, crosshair, screenWidth, screenHeight, screenCenter);

		// Render menu
		renderer.menu(canvas, crosshair);

		// Render and swap
		ImGui::Render();

		constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
		device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
		device_context->ClearRenderTargetView(render_target_view, color);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		swap_chain->Present(1U, 0U);
	}

	// Clean up
	destroyOverlay(window, wc, swap_chain, device_context, device, render_target_view);

	return 0;
}