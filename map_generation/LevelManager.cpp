#include "LevelManager.h"

tileMap RoomGenerator::generateRoom(const RoomDescriptionBase &parameters) {
    // Принимает размер области для комнаты, вписывает комнату и заполняет ее тайлами
    // Возвращает кусочек тайл мапы, который описывает только одну комнату

    tileMap map(3, std::vector<EntityTileBase>(3));
    return map;
};

tileMap MapGenerator::generateMap(const MapDescriptionBase &parameters) {
    // Cоздание карты, внутри вызов roomGenerator

    RoomDescriptionBase room = {10, 10};
    return roomGenerator->generateRoom(room);
}

void MapGenerator::setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) {
    // Замена реализации генератора комнаты
    roomGenerator.swap(generator);
}


LevelManager::LevelManager() {
    // Создает конкретный MapGenerator и помещает в него конкретный RoomGenerator
    // Генерация сида

    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    mapGenerator = std::make_unique<MapGenerator>(MapGenerator());
    mapGenerator->setRoomGenerator(std::move(roomGen));

    seed = rand();
}

tileMap LevelManager::createMap() {
    // Вызов функции generateMap у mapGenerator и передача в него сида с размером, т.е. создание
    // и заполнение структур с параметрами

    srand(seed);

    MapDescriptionBase map = {100, 100};

    return mapGenerator->generateMap(map);
}

int LevelManager::getSeed() {
    // Возврат сида, возможно потребуется для записи на сервер

    return seed;
}