#ifndef GAME_BSPTREE_H
#define GAME_BSPTREE_H

#include "IRoomGenerator.h"
#include "IMapGenerator.h"

#include <memory>

inline const int minLeafSize = 12;
inline const int maxLeafSize = 20;

inline const int minRoomSize = 6;

struct RoomDescription : RoomDescriptionBase {
    int x;
    int y;
};

struct Hall {
    std::vector<std::pair<int, int>> points;
};

class Tree {
private:
    class Leaf {
    public:
        Leaf(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) {};

        Leaf() = default;

        bool split();

        void createRooms();



//    std::unique_ptr<RoomDescription> room;

        int x;
        int y;

        int width;
        int height;

        std::unique_ptr<RoomDescription> room;
        std::vector<Hall> halls;

        std::shared_ptr<class Leaf> leftChild;
        std::shared_ptr<class Leaf> rightChild;
    };


public:
    using leaf = class Leaf;

    std::vector<std::shared_ptr<leaf>> getLeafs(int width, int height);
};

#endif //GAME_BSPTREE_H
