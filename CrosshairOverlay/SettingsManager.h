#pragma once

#include <Crosshair.h>

// Pre settings
void circleRedCorners() {
	Settings::draw_circle = Settings::circleRed_Corners::draw_circle;
	Settings::circle_size = Settings::circleRed_Corners::circle_size;
	Settings::circle_thickness = Settings::circleRed_Corners::circle_thickness;

	// Corners
	Settings::draw_corners = Settings::circleRed_Corners::draw_corners;

	Settings::corners_size = Settings::defaultSetting::corners_size;
	Settings::corners_thickness = Settings::defaultSetting::corners_thickness;

	// loop for color array
	for (int i = 0; i < 4; i++) {
		Settings::circle_color[i] = Settings::circleRed_Corners::circle_color[i];
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	};

	// Remove else
	Settings::draw_square = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
};

void squareRedCorners() {
	Settings::draw_square = Settings::squareRed_Corners::draw_square;
	Settings::square_size = Settings::squareRed_Corners::square_size;
	Settings::square_thickness = Settings::squareRed_Corners::square_thickness;

	// Corners
	Settings::draw_corners = Settings::squareRed_Corners::draw_corners;

	Settings::corners_size = Settings::defaultSetting::corners_size;
	Settings::corners_thickness = Settings::defaultSetting::corners_thickness;

	// loop for colors array
	for (int i = 0; i < 4; i++) {
		Settings::square_color[i] = Settings::squareRed_Corners::square_color[i];
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	}

	// Remove else
	Settings::draw_circle = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

void circleWithCorners() {
	Settings::draw_circle = Settings::circleRed_Corners::draw_circle;
	Settings::circle_size = Settings::circleRed_Corners::circle_size;
	Settings::circle_thickness = Settings::circleRed_Corners::circle_thickness;

	// Corners
	Settings::draw_corners = Settings::circleRed_Corners::draw_corners;

	Settings::corners_size = Settings::defaultSetting::corners_size;
	Settings::corners_thickness = Settings::defaultSetting::corners_thickness;

	// loop for color array
	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	};

	// Remove else
	Settings::draw_square = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

void squareWithCorners() {
	Settings::draw_square = Settings::squareRed_Corners::draw_square;
	Settings::square_size = Settings::squareRed_Corners::square_size;
	Settings::square_thickness = Settings::squareRed_Corners::square_thickness;

	// Corners
	Settings::draw_corners = Settings::squareRed_Corners::draw_corners;

	Settings::corners_size = Settings::defaultSetting::corners_size;
	Settings::corners_thickness = Settings::defaultSetting::corners_thickness;

	// loop for colors array
	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	}

	// Remove else
	Settings::draw_circle = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

// No corners
void circleAndCross() {
	Settings::draw_circle = Settings::circleRed_Corners::draw_circle;
	Settings::circle_size = Settings::circleRed_Corners::circle_size;
	Settings::circle_thickness = Settings::circleRed_Corners::circle_thickness;

	// loop for color array
	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	};

	// Remove else
	Settings::draw_square = false;
	Settings::draw_corners = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

void squareAndCross() {
	Settings::draw_square = Settings::squareRed_Corners::draw_square;
	Settings::square_size = Settings::squareRed_Corners::square_size;
	Settings::square_thickness = Settings::squareRed_Corners::square_thickness;

	// loop for colors array
	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	}

	// Remove else
	Settings::draw_circle = false;
	Settings::draw_corners = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

void redCrossCircle() {
	Settings::draw_circle = Settings::circleRed_Corners::draw_circle;
	Settings::circle_size = Settings::circleRed_Corners::circle_size;
	Settings::circle_thickness = Settings::circleRed_Corners::circle_thickness;

	// loop for color array
	for (int i = 0; i < 4; i++) {
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::cross_color[i] = Settings::redCross::cross_color[i];
	};

	// Remove else
	Settings::draw_square = false;
	Settings::draw_corners = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

void redCrossSquare() {
	Settings::draw_square = Settings::squareRed_Corners::draw_square;
	Settings::square_size = Settings::squareRed_Corners::square_size;
	Settings::square_thickness = Settings::squareRed_Corners::square_thickness;

	// loop for colors array
	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::redCross::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	}

	// Remove else
	Settings::draw_circle = false;
	Settings::draw_corners = false;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;
}

// Default Settings
void defaultSetting() {
	Settings::draw_circle = Settings::defaultSetting::draw_circle;
	Settings::circle_size = Settings::defaultSetting::circle_size;
	Settings::circle_thickness = Settings::defaultSetting::circle_thickness;
	
	Settings::draw_corners = Settings::defaultSetting::draw_corners;
	Settings::corners_size = Settings::defaultSetting::corners_size;
	Settings::corners_thickness = Settings::defaultSetting::corners_thickness;
	
	Settings::draw_square = Settings::defaultSetting::draw_square;
	Settings::square_size = Settings::defaultSetting::square_size;
	Settings::square_thickness = Settings::defaultSetting::square_thickness;

	Settings::draw_cross = Settings::defaultSetting::draw_cross;
	Settings::cross_size = Settings::defaultSetting::cross_size;
	Settings::cross_thickness = Settings::defaultSetting::cross_thickness;

	for (int i = 0; i < 4; i++) {
		Settings::cross_color[i] = Settings::defaultSetting::cross_color[i];
		Settings::circle_color[i] = Settings::defaultSetting::circle_color[i];
		Settings::square_color[i] = Settings::defaultSetting::square_color[i];
		Settings::corners_color[i] = Settings::defaultSetting::corners_color[i];
	}
}