#pragma once
#include <string>
#include <vector>

struct Key
{
	float time;
};

class Animation
{
	std::vector<Key> keys;

	float duration;
	float tickPerSeconds;

public:

	Animation(const std::string& pPath);
};
