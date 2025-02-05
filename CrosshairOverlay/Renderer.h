#pragma once
#include <cmath>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include <string>
#include <functional>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include <Crosshair.h>
#include <SettingsManager.h>

// Geometry
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEG2RAD(x) ((float)(x) * (float)(M_PI / 180.f))

double deg2rad(double deg) {
	return deg * M_PI / 180.0;
}



class Renderer {
public:
	// Overlay
	void RenderOverlay(ImDrawList* canvas, Crosshair crosshair, int screenWidth, int screenHeight, ImVec2 screenCenter) {
		auto &io = ImGui::GetIO();
		const ImGuiViewport* mainViewPort = ImGui::GetMainViewport();

		ImGui::SetNextWindowSize(mainViewPort->Size);
		ImGui::SetNextWindowPos(mainViewPort->Pos);
		
		ImGui::Begin("##Overlay", nullptr,
			ImGuiWindowFlags_NoTitleBar  |
			ImGuiWindowFlags_NoBackground  |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoScrollbar/* | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiSliderFlags_AlwaysClamp*/);
		
		canvas = ImGui::GetWindowDrawList();
		if (Settings::draw) {
			// Cross
			if (Settings::draw_cross) {
				int x = (int)(screenWidth * 0.5f);
				int y = (int)(screenHeight * 0.5f);
				// Left Right
				crosshair.DrawLine(
					canvas,
					ImVec2(x - Settings::cross_size, y),
					ImVec2(x + Settings::cross_size, y),
					Settings::cross_thickness,
					ImColor(Settings::cross_color[0],
						Settings::cross_color[1],
						Settings::cross_color[2],
						Settings::cross_color[3])
				);
				// Top Bottom
				crosshair.DrawLine(
					canvas,
					ImVec2(x, y - Settings::cross_size),
					ImVec2(x, y + Settings::cross_size),
					Settings::cross_thickness,
					ImColor(Settings::cross_color[0],
						Settings::cross_color[1],
						Settings::cross_color[2],
						Settings::cross_color[3])
				);
			}
			// Circle
			if (Settings::draw_circle) {
				float fov = Settings::circle_size;
				float radius = tanf(DEG2RAD(fov) / 2) / tanf(DEG2RAD(Settings::game_fov) / 2) * screenWidth;
				crosshair.DrawCircle(
					canvas,
					ImVec2(screenWidth / 2, screenHeight / 2),
					radius,
					40,
					ImColor(Settings::circle_color[0],
						Settings::circle_color[1],
						Settings::circle_color[2],
						Settings::circle_color[3]),
					Settings::circle_thickness
				);
			}
			// Square
			if (Settings::draw_square) {

				crosshair.DrawSquare(
					canvas,
					screenCenter,
					Settings::square_size,
					ImColor(Settings::square_color[0],
						Settings::square_color[1],
						Settings::square_color[2],
						Settings::square_color[3]),
					Settings::square_thickness
				);
			}
			// Corners
			if (Settings::draw_corners) {
				float x = screenCenter.x - Settings::corners_size / 2;
				float y = screenCenter.y - Settings::corners_size / 2;
				float w = Settings::corners_size;
				float h = Settings::corners_size;

				crosshair.DrawCorners(
					canvas,
					x,
					y,
					w,
					h,
					ImColor(Settings::corners_color[0],
						Settings::corners_color[1],
						Settings::corners_color[2],
						Settings::corners_color[3]),
					Settings::corners_thickness
				);
			}
		}

		ImGui::End();
	}

	// Menu
	void menu(ImDrawList* canvas, Crosshair crosshair) {
		if (!Settings::menu) {
			return;
		}

		canvas = ImGui::GetBackgroundDrawList();
		// Style
		applyStyle();
		// Window Size
		ImGui::SetNextWindowSizeConstraints(ImVec2(menuWidth, menuHeight), ImVec2(menuWidth, menuHeight));
		ImGui::SetNextWindowSize(ImVec2(menuWidth, menuHeight), ImGuiCond_FirstUseEver);

		if (ImGui::Begin("menu", &Settings::menu, menuWindowFlags)) {
			ImVec2 menuSize = ImGui::GetWindowSize();
			
			
			ImGui::Text("Turn Off Key");
			ImGui::SameLine();
			ImGui::Text("Pre Made Settings");

			Keys(Settings::hide, "Hide Crosshair Button");
			ImGui::SameLine();
			static std::string defaultSetting = "Default";
			SettingsList(defaultSetting);

			// Cross
			ImGui::SetCursorPos(ImVec2(8, 49));
			ImGui::BeginChild(1, ImVec2(0, 140), menuChildFlags);
			ImGui::SeparatorText("Cross");
			ImGui::Checkbox("Draw Cross", &Settings::draw_cross);
			SliderFloat("Size##CrossSize", 190, &Settings::cross_size, 0, 350, "%.2f");
			SliderFloat("Thickness##CrossThickness", 190, &Settings::cross_thickness, 1, 50, "%.2f");
			ImGui::ColorEdit4("Color##CrossColor", Settings::cross_color);
			ImGui::EndChild();

			// Circle
			ImGui::SetCursorPos(ImVec2(8, 184));
			ImGui::BeginChild(2, ImVec2(0, 130), menuChildFlags);
			ImGui::SeparatorText("Circle");
			ImGui::Checkbox("Draw Circle", &Settings::draw_circle);
			SliderFloat("Size##CircleSize", 190, &Settings::circle_size, 0, 10, "%.2f");
			SliderFloat("Thickness##CircleThickness", 190, &Settings::circle_thickness, 1, 50, "%.2f");
			ImGui::ColorEdit4("Color##CircleColor", Settings::circle_color);
			ImGui::EndChild();

			// Square
			ImGui::SetCursorPos(ImVec2(8, 319));
			ImGui::BeginChild(3, ImVec2(0, 130), menuChildFlags);
			ImGui::SeparatorText("Square");
			ImGui::Checkbox("Draw Square", &Settings::draw_square);
			SliderFloat("Size##SquareSize", 190, &Settings::square_size, 0, 250, "%.2f");
			SliderFloat("Thickness##SquareThickness", 190, &Settings::square_thickness, 1, 50, "%.2f");
			ImGui::ColorEdit4("Color##SquareColor", Settings::square_color);
			ImGui::EndChild();

			// Corners
			ImGui::SetCursorPos(ImVec2(8, 454));
			ImGui::BeginChild(4, ImVec2(0, 130), menuChildFlags);
			ImGui::SeparatorText("Corners");
			ImGui::Checkbox("Draw Corners", &Settings::draw_corners);
			SliderFloat("Size##CornersSize", 190, &Settings::corners_size, 0, 250, "%.2f");
			SliderFloat("Thickness##CornersThickness", 190, &Settings::corners_thickness, 1, 50, "%.2f");
			ImGui::ColorEdit4("Color##CornersColor", Settings::corners_color);
			ImGui::EndChild();
			
		}
		ImGui::End();
	}

private:
	// Style
	const void applyStyle() {
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		// Set some style properties
		style.Alpha = 1.0f;                 // Set transparency (1.0 = fully opaque)
		style.WindowPadding = ImVec2(8, 8); // Window padding
		style.FramePadding = ImVec2(4, 4);  // Frame padding (for buttons, sliders, etc.)
		style.ItemSpacing = ImVec2(8, 4);   // Item spacing (between items in a window)
		style.IndentSpacing = 21;           // Indent spacing
		style.ScrollbarSize = 1;            // Scrollbar size
		style.GrabMinSize = 20;             // Minimum size for grab handles

		// Set border sizes
		style.FrameBorderSize = 1.0f;  // Border size for frames
		style.WindowBorderSize = 1.0f; // Border size for windows

		// Set rounding for windows and frames
		style.WindowRounding = 5.0f;    // Rounding for windows
		style.FrameRounding = 3.0f;     // Rounding for frames
		style.ScrollbarRounding = 9.0f; // Rounding for scrollbars
		style.GrabRounding = 3.0f;      // Rounding for grab handles
	}

	//  Menu Settings
	int menuWidth = 300;
	int menuHeight = 589;

	ImGuiWindowFlags menuWindowFlags =
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse;

	ImGuiWindowFlags menuChildFlags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoCollapse;

	// Slider with personal size defined
	void SliderFloat(const char* label, float sliderWidth, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
		ImGui::PushItemWidth(sliderWidth);
		ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
		ImGui::PopItemWidth();
	}

	// List of keys
	std::vector<int> keyCodes = {
	VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
	};
	// Map to hold the display name of keys
	std::unordered_map<int, std::string> keyNames = {
	{VK_F1, "F1"}, {VK_F2, "F2"}, {VK_F3, "F3"}, {VK_F4, "F4"}, {VK_F5, "F5"},
	{VK_F6, "F6"}, {VK_F7, "F7"}, {VK_F8, "F8"}, {VK_F9, "F9"}, {VK_F10, "F10"},
	{VK_F11, "F11"}, {VK_F12, "F12"},
	};
	// Key imgui list function
	void Keys(int& selectKey, const char* id)
	{
		static int current_item = 0;
		// Use a unique ID by appending the provided id to the base string
		std::string comboID = std::string("##SelectKey_") + id;

		// Set the width
		ImGui::SetNextItemWidth(80.0f);

		if (ImGui::BeginCombo(comboID.c_str(), keyNames[selectKey].c_str()))
		{
			for (int i = 0; i < keyCodes.size(); i++)
			{
				bool is_selected = (current_item == i);
				if (ImGui::Selectable(keyNames[keyCodes[i]].c_str(), is_selected))
				{
					current_item = i;
					selectKey = keyCodes[i]; // Update value based on selection
				}
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	};

	// Map to store the functions with associated names
	std::unordered_map<std::string, std::function<void()>> preSettingsNames = {
		{"Default", defaultSetting},
		{"RedCirle w/ Corners", circleRedCorners}, {"RedCorners w/ Corners", squareRedCorners},
		{"Circle w/ Corners", circleWithCorners}, {"Square w/ Corners", squareWithCorners},
		{"Circle and Cross", circleAndCross}, {"Square and Cross", squareAndCross},
		{"Red Cross w/ Circle", redCrossCircle}, {"Red Cross w/ Square", redCrossSquare}
	};

	void SettingsList(std::string& selectedSetting) {
		std::string comboID = "##SettingsList";

		// List to show in the box
		std::vector<const char*> settingsList;
		for (const auto& setting : preSettingsNames) {
			settingsList.push_back(setting.first.c_str());
		}

		ImGui::SetNextItemWidth(195.0f);

		if (ImGui::BeginCombo(comboID.c_str(), selectedSetting.c_str())) {
			for (int i = 0; i < preSettingsNames.size(); i++) {
				bool is_selected = (selectedSetting == settingsList[i]);
				if (ImGui::Selectable(settingsList[i], is_selected)) {
					selectedSetting = settingsList[i];
					preSettingsNames[selectedSetting](); // Call it
				}
				if (is_selected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
};																																