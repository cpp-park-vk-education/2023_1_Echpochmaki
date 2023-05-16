#ifndef GAME_BSPTREE_H
#define GAME_BSPTREE_H

#include "IRoomGenerator.h"
#include "IMapGenerator.h"

#include <memory>

inline const int minLeafSize = 6;
inline const int maxLeafSize = 20;


class Leaf {
public:
    Leaf(int x_, int y_, int width_, int height_) : x(x_), y(y_), width(width_), height(height_) {};

    Leaf() = default;

    bool split();

    std::vector<std::shared_ptr<class Leaf>> getLeafs(const MapDescriptionBase &parameters);


    RoomDescriptionBase size;
    int x;
    int y;

    int width;
    int height;

    std::shared_ptr<class Leaf> leftChild;
    std::shared_ptr<class Leaf> rightChild;
};


#endif //GAME_BSPTREE_H
