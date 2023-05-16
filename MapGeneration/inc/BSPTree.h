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

class Tree {
private:
    struct Leaf {
        Leaf(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) {};

        Leaf() = default;

        bool split();

        void createRooms();

        std::unique_ptr<RoomDescription> room;

        int x;
        int y;

        int width;
        int height;

        std::shared_ptr<class Leaf> leftChild;
        std::shared_ptr<class Leaf> rightChild;
    };

    using leaf = struct Leaf;
    
public:
    void getLeafs(const MapDescriptionBase &parameters);

    std::vector<std::shared_ptr<leaf>> leafs;
};


#endif //GAME_BSPTREE_H
