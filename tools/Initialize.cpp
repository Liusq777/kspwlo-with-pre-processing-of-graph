#include "graph.hpp"

void removeDegreeOneNodes(RoadNetwork* rN) {
    // 删除度数为一的顶点
    for (NodeID i = 0; i < rN->numNodes; ++i) {
        // 如果节点 i 的度数为一，即只有一个邻居节点
        if (rN->adjListOut[i].size() == 1 && rN->adjListInc[i].size() == 1) {
            NodeID neighbor = rN->adjListOut[i].begin()->first; // 获取邻居节点的编号
            rN->adjListOut[i].clear(); // 清空节点 i 的出边列表
            rN->adjListInc[neighbor].erase(i); // 从邻居节点的入边列表中删除节点 i
        }
    }
}