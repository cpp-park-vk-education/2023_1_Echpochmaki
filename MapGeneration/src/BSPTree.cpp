//
// Created by User on 16.05.2023.
//

#include "BSPTree.h"

double getRand(double a = 0, double b = 1) {
    return a + ((double) rand() / (RAND_MAX)) * (b - a);
}

bool Tree::Leaf::split() {
    if (leftChild || rightChild)
        return false;

    bool splitH = (getRand() > 0.5);

    if (width > height && (double) width / height >= 1.25)
        splitH = false;
    else if (height > width && (double) height / width >= 1.25)
        splitH = true;

    int maxSize = (splitH ? height : width) - minLeafSize;

    if (maxSize <= minLeafSize)
        return false;

    int split = getRand(minLeafSize, maxSize);
    if (splitH) {
        leftChild = std::make_shared<leaf>(Leaf(x, y, width, split));
        rightChild = std::make_shared<leaf>(Leaf(x, y + split, width, height - split));
    } else {
        leftChild = std::make_shared<leaf>(Leaf(x, y, split, height));
        rightChild = std::make_shared<leaf>(Leaf(x + split, y, width - split, height));
    }
    return true;
};

/*void Tree::Leaf::createRooms() {
    if (leftChild || rightChild) {
        if (leftChild) {
            leftChild->createRooms();
        }
        if (rightChild) {
            rightChild->createRooms();
        }
    } else {
        room = std::unique_ptr<RoomDescription>(new RoomDescription);

        room->width = 1 + rand() % (width - 2);
        room->height = 1 + rand() % (height - 2);

        room->x = 1 + rand() % (width - room->width + 1);
        room->y = 1 + rand() % (height - room->height + 1);
    }
}*/

std::vector<std::shared_ptr<Tree::leaf>> Tree::getLeafs(int width, int height) {
    auto root = std::make_shared<leaf>(0, 0, width, height);

    std::vector<std::shared_ptr<leaf>> leafs;
    leafs.push_back(root);

    bool did_split = true;

    while (did_split) {
        did_split = false;
        for (auto l: leafs) {
            if (!l)
                continue;

            if (l->width > maxLeafSize || l->height > maxLeafSize || getRand() > 0.25) {
                if (l->split()) {
                    leafs.push_back(l->rightChild);
                    leafs.push_back(l->leftChild);
                    did_split = true;
                }
            }
        }
    }

    // root->createRooms();

    return leafs;
}