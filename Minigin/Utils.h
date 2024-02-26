#pragma once
#include <unordered_map>
#include <vector>

class Utils
{
public:

	template <typename Key, typename Value>
	static std::vector<Value>& FindOrAdd(std::unordered_map<Key, std::vector<Value>>& map, const Key& key)
	{
		if (!map.contains(key))
		{
			map.emplace(key);
		}

		return map[key];
	}
};
