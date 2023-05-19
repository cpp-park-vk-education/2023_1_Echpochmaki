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

void Tree::Leaf::createRooms() {
    if (leftChild || rightChild) {
        if (leftChild) {
            leftChild->createRooms();
        }
        if (rightChild) {
            rightChild->createRooms();
        }

        if (leftChild && rightChild) {
            createHall(leftChild->getRoom(), rightChild->getRoom());
        }

    } else {
        room = std::unique_ptr<RoomDescription>(new RoomDescription);

        room->width = getRand(minRoomSize, width - 2);
        room->height = getRand(minRoomSize, height - 2);

        room->x = getRand(1, width - room->width - 1) + x;
        room->y = getRand(1, height - room->height - 1) + y;
    }
}

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

    root->createRooms();

    return leafs;
}

void Tree::Leaf::createHall(std::shared_ptr<RoomDescription> l, std::shared_ptr<RoomDescription> r) {

    Point point1 = Point(getRand(l->x + 1, l->x + l->width - 2), getRand(l->y + 1, l->y + l->height - 2));
    Point point2 = Point(getRand(r->x + 1, r->x + r->width - 2), getRand(r->y + 1, r->y + r->height - 2));

    int w = point2.x - point1.x;
    int h = point2.y - point1.y;

    if (w < 0) {

        if (h < 0) {

            if (getRand() < 0.5) {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point1.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, 1, std::abs(h))));
            } else {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point2.y, 1, std::abs(h))));
            }
        } else if (h > 0) {
            if (getRand() < 0.5) {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point1.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point1.y, 1, std::abs(h))));
            } else {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, 1, std::abs(h))));
            }
        } else {
            halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, std::abs(w), 1)));
        }
    } else if (w > 0) {
        if (h < 0) {
            if (getRand() < 0.5) {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point2.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point2.y, 1, std::abs(h))));
            } else {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, 1, std::abs(h))));
            }
        } else if (h > 0) {
            if (getRand() < 0.5) {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point1.y, 1, std::abs(h))));
            } else {
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point2.y, std::abs(w), 1)));
                halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, 1, std::abs(h))));
            }
        } else {
            halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, std::abs(w), 1)));
        }
    } else {
        if (h < 0) {
            halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point2.x, point2.y, 1, std::abs(h))));
        } else if (h > 0) {
            halls.push_back(std::make_shared<RoomDescription>(RoomDescription(point1.x, point1.y, 1, std::abs(h))));
        }
    }
}


std::shared_ptr<RoomDescription> Tree::Leaf::getRoom() {

    if (room)
        return room;
    else {
        auto lRoom = std::make_shared<RoomDescription>(RoomDescription());
        auto rRoom = std::make_shared<RoomDescription>(RoomDescription());
        if (leftChild) {
            lRoom = leftChild->getRoom();
        }
        if (rightChild) {
            rRoom = rightChild->getRoom();
        }
        if (!lRoom && !rRoom)
            return nullptr;
        else if (!rRoom)
            return lRoom;
        else if (!lRoom)
            return rRoom;
        else if (getRand() > 0.5)
            return lRoom;
        else
            return rRoom;
    }
}