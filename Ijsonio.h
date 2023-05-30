#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Ijsonio
{
public:
	virtual void fromJson(json json) = 0;
	virtual json toJson() = 0;
	virtual ~Ijsonio() {};
};