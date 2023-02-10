 #pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const float GAUGE_WIDTH = 20.0f;							// Default width of the gauge.
const float GAUGE_HEIGHT = 50.0f;							// Default height of the gauge.

const Vector2f TO_CENTER = Vector2f(5.0f, 5.0f);			// Offset in order to center part of the gauge
const Vector2f BACKGROUND_MARGIN = Vector2f(10.0f, 10.0f);	// Gauge background margin
const Vector2f VERTICAL_OFFSET = Vector2f(5.0f, 55.0f);		// Vertical offset to apply at the gauge value
															// if the gauge is vertical.

/// <summary>
/// A progress bar used with other element to represent their progresion.
/// </summary>
class Gauge
{
public:

	// CONSTRUCTOR & DESTRUCTOR

	Gauge(bool isHorizontal, Vector2f position);
	Gauge(bool isHorizontal, Vector2f position, Vector2f size, Color gaugeColor);
	~Gauge() {}

	/// <summary>
	/// Draw the 3 sprites of the gauge
	/// </summary>
	/// <param name="window">Game window</param>
	void DrawGauge(RenderWindow* window) const;

	/// <summary>
	/// Fill the gauge by updating the size of the gauge value's sprite.
	/// </summary>
	/// <param name="fillValue">New value of the fill value of the gauge</param>
	void FillGauge(const float& fillValue);

private:

	/// <summary>
	/// Sprite of the empty part of the gauge, its size never change.
	/// </summary>
	RectangleShape mGaugeEmpty;

	/// <summary>
	/// Sprite of the gauge value, its size is based on the current fill value of the gauge.
	/// </summary>
	RectangleShape mGaugeValue;

	/// <summary>
	/// Sprite of the background of the gauge.
	/// </summary>
	RectangleShape mGaugeBackground;

	/// <summary>
	/// Position of the gauge
	/// </summary>
	Vector2f mPosition;

	/// <summary>
	/// Size of the gauge
	/// </summary>
	Vector2f mSize;

	/// <summary>
	/// Tell if the gauge is horizontal or vertical
	/// </summary>
	bool mHorizontal = false;
};

