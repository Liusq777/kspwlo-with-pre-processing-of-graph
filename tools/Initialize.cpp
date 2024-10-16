#include "graph.hpp"

void removeDegreeOneNodes(RoadNetwork* rN) {
    // ɾ������Ϊһ�Ķ���
    for (NodeID i = 0; i < rN->numNodes; ++i) {
        // ����ڵ� i �Ķ���Ϊһ����ֻ��һ���ھӽڵ�
        if (rN->adjListOut[i].size() == 1 && rN->adjListInc[i].size() == 1) {
            NodeID neighbor = rN->adjListOut[i].begin()->first; // ��ȡ�ھӽڵ�ı��
            rN->adjListOut[i].clear(); // ��սڵ� i �ĳ����б�
            rN->adjListInc[neighbor].erase(i); // ���ھӽڵ������б���ɾ���ڵ� i
        }
    }
}