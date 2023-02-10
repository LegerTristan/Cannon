#pragma once

/// <summary>
/// Contains some utility function that are static and can be used anywhere
/// </summary>
class Utilities
{
public:

	/// <summary>
	/// Template function that takes a value, a min and a max.
	/// Clamp the value between the min and the max.
	/// </summary>
	/// <typeparam name="T">Type of the value, min and max</typeparam>
	/// <param name="value">Value to clamp</param>
	/// <param name="min">Minimum value</param>
	/// <param name="max">Maximum value</param>
	/// <returns>Return the value clamped between the min and the max</returns>
	template<typename T>
	static T Clamp(const T& value, const T& min, const T& max);
};

template<typename T>
inline T Utilities::Clamp(const T& _value, const T& _min, const T& _max)
{
	if (_value < _min)
		return _min;
	if (_value > _max)
		return _max;

	return _value;
}
