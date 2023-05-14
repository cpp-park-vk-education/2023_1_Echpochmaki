#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Network.hpp"

TEST(NetworkTest, checkIsHostBeforeRunHost) {
    Network net;
    EXPECT_FALSE(net.isHost());
}

TEST(NetworkTest, checkNetworkRunHost) {
    Network net;
    std::weak_ptr host = net.runHost();
    EXPECT_FALSE(host.expired());
}

TEST(NetworkTest, checkIsHostAfterRunHost) {
    Network net;
    net.runHost();
    EXPECT_TRUE(net.isHost());
}

TEST(NetworkTest, checkIsClientBeforeConnectToHost) {
    Network net;
    EXPECT_FALSE(net.isClient());
}

TEST(NetworkTest, checkNetworkConnectToHost) {
    Network net;
    EXPECT_TRUE(net.connectToHost());
}

TEST(NetworkTest, checkNetworkCloseHostBeforeRunning) {
    Network net;
    EXPECT_FALSE(net.closeHost());
}

TEST(NetworkTest, checkNetworkCloseHostAfterRunning) {
    Network net;
    net.runHost();
    EXPECT_TRUE(net.closeHost());
}

TEST(NetworkTest, checkNetworkCloseHostAfterRunning) {
    Network net;
    net.runHost();
    EXPECT_TRUE(net.closeHost());
}

TEST(NetworkTest, checkNetworkSendPacket) {
    Network net;
    sf::Packet packet;
    packet << "hello world!\n";
    EXPECT_TRUE(net.sen(packet));
}
