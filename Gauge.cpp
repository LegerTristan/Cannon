#include "Gauge.h"

Gauge::Gauge(bool _isHorizontal, Vector2f _position)
{
	mHorizontal = _isHorizontal;

	mGaugeBackground.setPosition(_position);
	mGaugeEmpty.setPosition(_position + TO_CENTER);

	mSize = { GAUGE_WIDTH, GAUGE_HEIGHT };

	mGaugeValue.setFillColor(Color::Red);
	mGaugeBackground.setFillColor(Color::Black);

	mGaugeBackground.setSize(Vector2f(mSize.x, mSize.y) + BACKGROUND_MARGIN);
	mGaugeEmpty.setSize({ mSize.x, mSize.y });

	mHorizontal ? mGaugeValue.setSize({ 0.0f, mSize.y }) : mGaugeValue.setSize({ mSize.x, 0.0f });
	mHorizontal ? mGaugeValue.setPosition(_position + TO_CENTER) : mGaugeValue.setPosition(_position + VERTICAL_OFFSET);
}

Gauge::Gauge(bool _isHorizontal, Vector2f _position, Vector2f _size, Color _gaugeColor)
{
	mHorizontal = _isHorizontal;

	mGaugeBackground.setPosition(_position);
	mGaugeEmpty.setPosition(_position + TO_CENTER);

	mSize = { _size.x, _size.y };

	mGaugeValue.setFillColor(_gaugeColor);
	mGaugeBackground.setFillColor(Color::Black);

	mGaugeBackground.setSize(Vector2f(mSize.x, mSize.y) + BACKGROUND_MARGIN);
	mGaugeEmpty.setSize({ mSize.x, mSize.y });

	mHorizontal ? mGaugeValue.setSize({ 0.0f, mSize.y }) : mGaugeValue.setSize({ mSize.x, 0.0f });
	mHorizontal ? mGaugeValue.setPosition(_position + TO_CENTER) : mGaugeValue.setPosition(_position + VERTICAL_OFFSET);
}

void Gauge::DrawGauge(RenderWindow* _window) const
{
	_window->draw(mGaugeBackground);
	_window->draw(mGaugeEmpty);
	_window->draw(mGaugeValue);
}

void Gauge::FillGauge(const float& _fillValue)
{
	const Vector2f newSize = mHorizontal ? Vector2f(_fillValue * mSize.x, mSize.y) : Vector2f(mSize.x, -_fillValue * mSize.y);

	mGaugeValue.setSize(newSize);
}
