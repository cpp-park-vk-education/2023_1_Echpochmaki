#ifndef MAP_GENERATION_LEVELMANAGER_H
#define MAP_GENERATION_LEVELMANAGER_H

#include "IMapGenerator.h"
#include "IRoomGenerator.h"
#include "../../ECS/inc/Tile.h"
#include "BSPTree.h"

#include <memory>

class RoomGenerator : public IRoomGenerator {
public:
    tileMap generateRoom(const RoomDescriptionBase &parameters) override;
};

class MapGenerator : public IMapGenerator {
public:
    tileMap generateMap(const MapDescriptionBase &parameters) override;

    void setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) override;

private:
    std::unique_ptr<IRoomGenerator> roomGenerator;
};

class MapGeneratorBSP : public IMapGenerator {
public:
    tileMap generateMap(const MapDescriptionBase &parameters) override;

    std::vector<std::shared_ptr<class Leaf>> getLeafs(const MapDescriptionBase &parameters);
    
    void setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) override;

private:
    std::unique_ptr<IRoomGenerator> roomGenerator;
};


class LevelManager {
public:
    LevelManager();

    tileMap createMap();

    int getSeed();

private:
    std::unique_ptr<IMapGenerator> mapGenerator;
    int seed;
};

#endif //MAP_GENERATION_LEVELMANAGER_H
