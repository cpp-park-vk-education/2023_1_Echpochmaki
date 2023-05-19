#include "../inc/LevelManager.h"
#include "BSPTree.h"


tileMap RoomGenerator::generateRoom(const RoomDescriptionBase &parameters) {
    // Принимает размер области для комнаты, вписывает комнату и заполняет ее тайлами
    // Возвращает кусочек тайл мапы, который описывает только одну комнату

    tileMap map(parameters.height, std::vector<EntityTileBase>(parameters.width, floorTile));

    for (int i = 0; i < parameters.width; ++i) {
        map[0][i] = wallTile;
        map[parameters.height - 1][i] = wallTile;
    }

    for (int i = 1; i < parameters.height - 1; ++i) {
        map[i][0] = wallTile;
        map[i][parameters.width - 1] = wallTile;
    }

    map[parameters.height / 2][parameters.width / 2] = enemyTile;

    return map;
};

tileMap MapGenerator::generateMap(const MapDescriptionBase &parameters) {
    // Cоздание карты, внутри вызов roomGenerator

    std::vector<tileMap> rooms;

    tileMap map(parameters.height, std::vector<EntityTileBase>(parameters.width, floorTile));

    for (int i = parameters.width / 3; i <= parameters.width; i += parameters.width / 3) {
        for (int j = parameters.height / 3; j <= parameters.height; j += parameters.height / 3) {
            RoomDescriptionBase roomDescription = {parameters.width / 3, parameters.height / 3};
            tileMap room = roomGenerator->generateRoom(roomDescription);
            rooms.push_back(room);
        }
    }

    // Place rooms on map
    size_t currentX = 0;
    size_t currentY = 0;
    for (auto &room: rooms) {
        for (size_t y = 0; y < room.size(); ++y) {
            for (size_t x = 0; x < room[0].size(); ++x) {
                map[x + currentX][y + currentY] = room[x][y];
            }
        }

        currentX += room[0].size();
        if (currentX >= parameters.width) {
            currentX = 0;
            currentY += room.size();
        }
    }

    // Place doors
    for (size_t i = rooms[0].size() / 2; i < parameters.height; i += rooms[0].size()) {
        for (int j = 1; j < parameters.width - 1; ++j) {
            if (map[i][j].objectId == wallTile.objectId && map[i][j + 1].objectId == wallTile.objectId) {
                map[i][j] = doorTile;
                map[i][j + 1] = doorTile;
            }
        }
    }


    for (size_t i = rooms[0][0].size() / 2; i < parameters.width; i += rooms[0][0].size()) {
        for (int j = 1; j < parameters.height - 1; ++j) {
            if (map[j][i].objectId == wallTile.objectId && map[j + 1][i].objectId == wallTile.objectId) {
                map[j][i] = doorTile;
                map[j + 1][i] = doorTile;
            }
        }
    }


    return map;
}

void MapGenerator::setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) {
    // Замена реализации генератора комнаты
    roomGenerator.swap(generator);
}


tileMap MapGeneratorBSP::generateMap(const MapDescriptionBase &parameters) {
    // Cоздание карты, внутри вызов roomGenerator

    Tree t;
    auto leafs = t.getLeafs(parameters.width - 1, parameters.height - 1);

    tileMap map(parameters.height, std::vector<EntityTileBase>(parameters.width, fakeTile));

    for (auto l: leafs) {
        if (!l->rightChild && !l->leftChild) {
            for (int i = l->room->y; i < l->room->height + l->room->y; ++i) {
                for (int j = l->room->x; j < l->room->width + l->room->x; ++j) {
                    map[i][j] = floorTile;
                }
            }
        }
    }

    drawWalls(map);

    return map;
}

void MapGeneratorBSP::drawWalls(tileMap &map) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (map[i][j].objectId == floorTile.objectId) {
                if (map[i][j - 1].objectId == fakeTile.objectId)
                    map[i][j - 1] = wallTile;
                
                if (map[i - 1][j - 1].objectId == fakeTile.objectId)
                    map[i - 1][j - 1] = wallTile;

                if (map[i - 1][j].objectId == fakeTile.objectId)
                    map[i - 1][j] = wallTile;

                if (map[i - 1][j + 1].objectId == fakeTile.objectId)
                    map[i - 1][j + 1] = wallTile;

                if (map[i][j + 1].objectId == fakeTile.objectId)
                    map[i][j + 1] = wallTile;

                if (map[i + 1][j + 1].objectId == fakeTile.objectId)
                    map[i + 1][j + 1] = wallTile;

                if (map[i + 1][j].objectId == fakeTile.objectId)
                    map[i + 1][j] = wallTile;

                if (map[i + 1][j - 1].objectId == fakeTile.objectId)
                    map[i + 1][j - 1] = wallTile;
            }
        }
    }
}

void MapGeneratorBSP::setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) {
    // Замена реализации генератора комнаты
    roomGenerator.swap(generator);
}


LevelManager::LevelManager() {
    // Создает конкретный MapGenerator и помещает в него конкретный RoomGenerator
    // Генерация сида

    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    mapGenerator = std::unique_ptr<IMapGenerator>(new MapGeneratorBSP());
    mapGenerator->setRoomGenerator(std::move(roomGen));

    seed = 42;
}

tileMap LevelManager::createMap() {
    // Вызов функции generateMap у mapGenerator и передача в него сида с размером, т.е. создание
    // и заполнение структур с параметрами

    srand(seed);

    MapDescriptionBase map = {30, 30};

    auto m = mapGenerator->generateMap(map);

    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[0].size(); ++j) {
            std::cout << m[i][j].objectId << " ";
        }
        std::cout << std::endl;
    }

    return m;
}

int LevelManager::getSeed() {
    // Возврат сида, возможно потребуется для записи на сервер

    return seed;
}