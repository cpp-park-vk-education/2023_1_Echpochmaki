#ifndef GAME_BSPTREE_H
#define GAME_BSPTREE_H

#include "IRoomGenerator.h"
#include "IMapGenerator.h"

#include <memory>

inline const int minLeafSize = 6;
inline const int maxLeafSize = 20;

struct RoomDescription : RoomDescriptionBase {
    int x;
    int y;
};

struct Hall {
    int x;
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

        RoomDescription room;
        std::vector<Hall> halls;

        std::shared_ptr<class Leaf> leftChild;
        std::shared_ptr<class Leaf> rightChild;
    };


public:
    using leaf = class Leaf;

    std::vector<std::shared_ptr<leaf>> getLeafs(int width, int height);
};

#endif //GAME_BSPTREE_H
