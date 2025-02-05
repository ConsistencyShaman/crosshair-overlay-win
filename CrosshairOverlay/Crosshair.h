#pragma once
#include <windows.h>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <string>

namespace Settings {
	// Var
	bool draw = true;
	int hide = VK_F4;

	float game_fov = 120;
	bool menu = false;
	
	// Cross
	bool draw_cross = true;
	float cross_size = 54;
	float cross_thickness = 1.5;
	float cross_color[4] = { 0, 255, 187, 150 };
	// Circle
	bool draw_circle = false;
	float circle_size = 3.95;
	float circle_thickness = 1.2;
	float circle_color[4] = { 0, 255, 187, 150 };
	// Square
	bool draw_square = false;
	float square_size = 44;
	float square_thickness = 1.2;
	float square_color[4] = { 0, 255, 187, 150 };
	// Corners
	bool draw_corners = false;
	float corners_size = 107.40;
	float corners_thickness = 1.2;
	float corners_color[4] = { 0, 255, 187, 150 };

	namespace circleRed_Corners {
		// Circle
		bool draw_circle = true;
		float circle_size = 3.05;
		float circle_thickness = 2.98;
		float circle_color[4] = { 255, 0, 0, 150 };
		// Corners
		bool draw_corners = true;
	}

	namespace squareRed_Corners {
		// Square
		bool draw_square = true;
		float square_size = 44;
		float square_thickness = 2.98;
		float square_color[4] = { 255, 0, 0, 150 };
		// Corners
		bool draw_corners = true;
	}

	namespace redCross {
		float cross_color[4] = { 255, 0, 0, 150 };
	}

	namespace defaultSetting {
		// Cross
		bool draw_cross = true;
		float cross_size = 54;
		float cross_thickness = 1.5;
		float cross_color[4] = { 0, 255, 187, 150 };
		// Circle
		bool draw_circle = false;
		float circle_size = 3.95;
		float circle_thickness = 1.2;
		float circle_color[4] = { 0, 255, 187, 150 };
		// Square
		bool draw_square = false;
		float square_size = 44;
		float square_thickness = 1.2;
		float square_color[4] = { 0, 255, 187, 150 };
		// Corners
		bool draw_corners = true;
		float corners_size = 107.40;
		float corners_thickness = 1.2;
		float corners_color[4] = { 0, 255, 187, 150 };
	}
}

class Crosshair {
public:
	// Draw functions
	// Line
	static void DrawLine(ImDrawList* canvas, const ImVec2& start, const ImVec2& end, float thickness, const ImColor& color) {
		canvas->AddLine((const ImVec2&)start, (const ImVec2&)end, ImColor(color), thickness);
	}

	// Circle
	static void DrawCircle(ImDrawList* canvas, const ImVec2& pos, float radius, int segments, const ImColor& color, float thickness) {
		canvas->AddCircle(ImVec2(pos.x, pos.y), radius, color, segments, thickness);
	}

	// Square
	static void DrawSquare(ImDrawList* canvas, ImVec2 screen_center, float size, ImColor color, float thickness) {
		// Calculate half the size for positioning the square centered on the screen
		float half_size = size / 2.0f;

		// Define the top-left and bottom-right corners of the square
		ImVec2 topLeft(screen_center.x - half_size, screen_center.y - half_size);
		ImVec2 bottomRight(screen_center.x + half_size, screen_center.y + half_size);

		// Draw the square centered on the screen
		canvas->AddRect(topLeft, bottomRight, color, 0.0f, ImDrawFlags_None, thickness);
	}

	// Corners
	static void DrawCorners(ImDrawList* canvas, float X, float Y, float W, float H, ImColor color, float thickness) {
		float lineW = (W / 4);
		float lineH = (H / 5.5);
		float lineT = -thickness;
		// Corners
		DrawLine(canvas, ImVec2(X, Y + thickness / 2), ImVec2(X, Y + lineH), thickness, color); // bottom right
		DrawLine(canvas, ImVec2(X + thickness / 2, Y), ImVec2(X + lineW, Y), thickness, color);
		DrawLine(canvas, ImVec2(X + W - lineW, Y), ImVec2(X + W - thickness / 2, Y), thickness, color); // bottom left
		DrawLine(canvas, ImVec2(X + W, Y + thickness / 2), ImVec2(X + W, Y + lineH), thickness, color);
		DrawLine(canvas, ImVec2(X, Y + H - lineH), ImVec2(X, Y + H - (thickness / 2)), thickness, color); // top right
		DrawLine(canvas, ImVec2(X + thickness / 2, Y + H), ImVec2(X + lineW, Y + H), thickness, color);
		DrawLine(canvas, ImVec2(X + W - lineW, Y + H), ImVec2(X + W - thickness / 2, Y + H), thickness, color); // top left
		DrawLine(canvas, ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H - (thickness / 2)), thickness, color);

	}
};