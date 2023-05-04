#include "LevelManager.h"

tileMap RoomGenerator::generateRoom(const roomDescriptionBase &parameters) {
    // Принимает размер области для комнаты, вписывает комнату и заполняет ее тайлами
    // Возвращает кусочек тайл мапы, который описывает только одну комнату
    return {};
};

tileMap MapGenerator::generateMap(const mapDescriptionBase &parameters) {
    // Cоздание карты, внутри вызов roomGenerator

    return roomGenerator->generateRoom();
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

    return mapGenerator->generateMap();
}

int LevelManager::getSeed() {
    // Возврат сида, возможно потребуется для записи на сервер

    return seed;
}