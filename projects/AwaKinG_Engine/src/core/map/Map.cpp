#include "Map.h"

Map::Map() {
	errorMessage = ED_UNDEFINED;
}
void Map::shutdown() {
	for(uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
	_entities.clear();
}
void Map::update() {
}
bool Map::initialize() {
	return true;
}
