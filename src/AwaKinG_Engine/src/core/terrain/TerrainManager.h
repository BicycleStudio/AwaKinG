#pragma once
#include "../Parser.h"
#include "../../render/D3dRender.h"

class TerrainManager
{
#pragma region singleton
public:
	std::string ErrorMessage;
	static TerrainManager& getInstance()
	{
		static TerrainManager engine;
		return engine;
	};

private:
	TerrainManager();
	TerrainManager(const TerrainManager&);
#pragma endregion


};

