#include "../inc/LevelManager.h"
#include "BSPTree.h"

using leaf = class Leaf;


bool Leaf::split() {
    if (leftChild || rightChild)
        return false;

    bool splitH = (((double) rand() / (RAND_MAX)) > 0.5);

    if (width > height && (double) width / height >= 1.25)
        splitH = false;
    else if (height > width && (double) height / width >= 1.25)
        splitH = true;

    int maxSize = (splitH ? height : width) - minLeafSize;

    if (maxSize <= minLeafSize)
        return false;

    int split = minLeafSize + rand() % (maxSize - minLeafSize + 1);
    if (splitH) {
        leftChild = std::make_shared<leaf>(Leaf(x, y, width, split));
        rightChild = std::make_shared<leaf>(Leaf(x, y + split, width, height - split));
    } else {
        leftChild = std::make_shared<leaf>(Leaf(x, y, split, height));
        rightChild = std::make_shared<leaf>(Leaf(x + split, y, width - split, height));
    }
    return true;
};

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

std::vector<std::shared_ptr<class Leaf>> MapGeneratorBSP::getLeafs(const MapDescriptionBase &parameters) {
    std::vector<std::shared_ptr<leaf>> leafs;
    auto root = std::make_shared<leaf>(0, 0, parameters.width, parameters.height);
    leafs.push_back(root);

    bool did_split = true;

    while (did_split) {
        did_split = false;
        for (auto l: leafs) {
            if (!l)
                continue;

            if (l->width > maxLeafSize || l->height > maxLeafSize || ((double) rand() / (RAND_MAX)) > 0.25) {
                if (l->split()) {
                    leafs.push_back(l->rightChild);
                    leafs.push_back(l->leftChild);
                    did_split = true;
                }
            }
        }
    }

    return leafs;
}


tileMap MapGeneratorBSP::generateMap(const MapDescriptionBase &parameters) {
    // Cоздание карты, внутри вызов roomGenerator
    tileMap map(parameters.height, std::vector<EntityTileBase>(parameters.width, floorTile));

    auto leafs = getLeafs(parameters);

    for (auto l: leafs) {
        if (l) {
            for (int i = l->x; i < l->width; ++i) {
                map[0][i] = wallTile;
                map[l->y + l->height - 1][i] = wallTile;
            }

            for (int j = l->y; j < l->height; ++j) {
                map[j][0] = wallTile;
                map[j][l->x + l->width - 1] = wallTile;
            }
        }
    }

    return map;
}

void MapGeneratorBSP::setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) {
    // Замена реализации генератора комнаты
    roomGenerator.swap(generator);
}


LevelManager::LevelManager() {
    // Создает конкретный MapGenerator и помещает в него конкретный RoomGenerator
    // Генерация сида

    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    mapGenerator = std::make_unique<MapGeneratorBSP>(MapGeneratorBSP());
    mapGenerator->setRoomGenerator(std::move(roomGen));

    seed = rand();
}

tileMap LevelManager::createMap() {
    // Вызов функции generateMap у mapGenerator и передача в него сида с размером, т.е. создание
    // и заполнение структур с параметрами

    srand(seed);

    MapDescriptionBase map = {30, 30};

    return mapGenerator->generateMap(map);
}

int LevelManager::getSeed() {
    // Возврат сида, возможно потребуется для записи на сервер

    return seed;
}