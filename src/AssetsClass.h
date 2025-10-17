//Asstes and models
#pragma once
#include <stdint.h>


class AssetsClass {
public:
    AssetsClass();
    AssetsClass(const AssetsClass&);
    ~AssetsClass();
    bool Init();

private:
    bool SaveOctNode();

    struct OctreeNode {
        uint8_t Nodes[8];
        uint8_t Average;
    };

    struct OctreeObj {
        uint64_t Block;
        struct Slice {
            uint32_t S1;
            uint32_t S2;
        };
        struct Voxel {
            uint8_t V0;
            uint8_t V1;
            uint8_t V2;
            uint8_t V3;
            uint8_t V4;
            uint8_t V5;
            uint8_t V6;
            uint8_t V7;
        }; 
    };


};