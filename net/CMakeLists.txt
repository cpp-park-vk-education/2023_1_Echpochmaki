add_library(net src/Network.cpp src/Client.cpp src/Host.cpp src/Packets.cpp)
target_include_directories(net PUBLIC inc)

