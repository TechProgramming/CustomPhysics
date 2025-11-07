#pragma once

template<typename TEnum>

inline TEnum operator | (TEnum Lefthandside, TEnum Righthandside)
{
	static_assert(std::is_enum<TEnum>::value, "Template parameter is not an enum type.");

	using Underlying = typename std::underlying_type<TEnum>::type;

	return static_cast<TEnum>(static_cast<Underlying>(Lefthandside) | static_cast<Underlying>(Righthandside));
}