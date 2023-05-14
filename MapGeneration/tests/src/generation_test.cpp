#include <gtest/gtest.h>
#include "../../LevelManager.h"

TEST(RoomGeneration, RoomWithZeroWidth) {
    RoomGenerator generator;
    RoomDescriptionBase params = {0, 10};
    EXPECT_THROW(generator.generateRoom(params), std::exception);
}

TEST(RoomGeneration, RoomWithZeroHeight) {
    RoomGenerator generator;
    RoomDescriptionBase params = {10, 0};
    EXPECT_THROW(generator.generateRoom(params), std::exception);
}

TEST(RoomGeneration, RoomWithZeroSize) {
    RoomGenerator generator;
    RoomDescriptionBase params = {0, 0};
    EXPECT_THROW(generator.generateRoom(params), std::exception);
}

TEST(RoomGeneration, RoomWithNegSize) {
    RoomGenerator generator;
    RoomDescriptionBase params = {-10, 100};
    EXPECT_THROW(generator.generateRoom(params), std::exception);
}

TEST(RoomGeneration, RoomBasicGeneration) {
    RoomGenerator generator;
    RoomDescriptionBase params = {10, 10};
    tileMap actual = generator.generateRoom(params);

    EXPECT_EQ(actual.size(), 10);
    EXPECT_EQ(actual[0].size(), 10);
}

// ---------------------- MAP --------------------------------


TEST(MapGeneration, MapWithZeroWidth) {
    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    MapGenerator generator;
    generator.setRoomGenerator(std::move(roomGen));

    MapDescriptionBase params = {0, 10};
    EXPECT_THROW(generator.generateMap(params), std::exception);
}

TEST(MapGeneration, MapWithZeroHeight) {
    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    MapGenerator generator;
    generator.setRoomGenerator(std::move(roomGen));

    MapDescriptionBase params = {10, 0};
    EXPECT_THROW(generator.generateMap(params), std::exception);
}

TEST(MapGeneration, MapWithZeroSize) {
    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    MapGenerator generator;
    generator.setRoomGenerator(std::move(roomGen));

    MapDescriptionBase params = {0, 0};
    EXPECT_THROW(generator.generateMap(params), std::exception);
}

TEST(MapGeneration, MapWithNegSize) {
    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    MapGenerator generator;
    generator.setRoomGenerator(std::move(roomGen));

    MapDescriptionBase params = {-10, 10};
    EXPECT_THROW(generator.generateMap(params), std::exception);
}


TEST(MapGeneration, MapGenerationWithoutRoomGenerator) {
    MapGenerator generator;

    MapDescriptionBase params = {100, 100};
    EXPECT_THROW(generator.generateMap(params), std::exception);
}

struct MockRoomGenerator : IRoomGenerator{
    tileMap generateRoom(const RoomDescriptionBase &parameters) override{
        ++roomsCount;
    }

    int roomsCount = 0;
};

struct MapParams : MapDescriptionBase{
    int roomsCount;
};

TEST(MapGeneration, MapRoomsCountCheck) {
    MockRoomGenerator *temp = new MockRoomGenerator();
    auto roomGen = std::unique_ptr<IRoomGenerator>(temp);

    MapGenerator generator;

    generator.setRoomGenerator(std::move(roomGen));

    MapParams params = {100, 100, 5};
    generator.generateMap(params);

    EXPECT_EQ(temp->roomsCount, 5);
}


TEST(MapGeneration, MapGenerationBasic) {
    auto roomGen = std::unique_ptr<IRoomGenerator>(new RoomGenerator());
    MapGenerator generator;
    generator.setRoomGenerator(std::move(roomGen));

    MapDescriptionBase params = {100, 100};

    tileMap actual = generator.generateMap(params);

    EXPECT_EQ(actual.size(), 100);
    EXPECT_EQ(actual[0].size(), 100);
}

