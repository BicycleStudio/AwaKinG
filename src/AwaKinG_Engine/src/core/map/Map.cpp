#include "Map.h"

Map::Map() {
}
void Map::shutdown() {
	for(int i = 0; i < _entities.size(); i++)
		delete _entities[i];
	_entities.clear();
}
void Map::update() {
}
bool Map::initialize() {
	return true;
}
