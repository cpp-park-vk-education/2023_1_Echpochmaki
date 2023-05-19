#ifndef GAME_BSPTREE_H
#define GAME_BSPTREE_H

#include "IRoomGenerator.h"
#include "IMapGenerator.h"

#include <memory>

inline const int minLeafSize = 6;
inline const int maxLeafSize = 20;

inline const int minRoomSize = 3;

struct RoomDescription : RoomDescriptionBase {
    int x;
    int y;

    RoomDescription(int x_, int y_, int width_, int height_) : x(x_), y(y_), RoomDescriptionBase(width_, height_) {};

    RoomDescription() = default;
};

struct Point {
    int x;
    int y;

    Point(int x_, int y_) : x(x_), y(y_) {};
};

class Tree {
private:
    class Leaf {
    public:
        Leaf(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) {};

        Leaf() = default;

        bool split();

        void createRooms();

        void createHall(std::shared_ptr<RoomDescription> l, std::shared_ptr<RoomDescription> r);

        std::shared_ptr<RoomDescription> getRoom();

//    std::unique_ptr<RoomDescription> room;

        int x;
        int y;

        int width;
        int height;

        std::shared_ptr<RoomDescription> room;
        std::vector<std::shared_ptr<RoomDescription>> halls;

        std::shared_ptr<class Leaf> leftChild;
        std::shared_ptr<class Leaf> rightChild;
    };


public:
    using leaf = class Leaf;

    std::vector<std::shared_ptr<leaf>> getLeafs(int width, int height);
};

#endif //GAME_BSPTREE_H
