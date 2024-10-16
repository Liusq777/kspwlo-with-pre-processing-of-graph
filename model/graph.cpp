/*
Copyright (c) 2017 Theodoros Chondrogiannis
*/

#include "graph.hpp" // �����Զ����ͷ�ļ� graph.hpp

// RoadNetwork��Ĺ��캯�������ݴ�����ļ���filename��ȡ�ļ���Ϣ����RoadNetwork����
/*RoadNetwork::RoadNetwork(const char* filename) {

    FILE* fp;
    NodeID lnode, rnode, tmp;
    int w;
    char c;

    fp = fopen(filename, "r"); // ��ֻ����ʽ���ļ�
    //fscanf(fp, "%c\n", &c); // ��ȡһ���ַ�������
    fscanf(fp, "%u %u\n", &this->numNodes, &this->numEdges); // ��ȡ�������ͱ���
    this->adjListOut = vector<EdgeList>(this->numNodes); // ��ʼ�������ڽӱ�
    this->adjListInc = vector<EdgeList>(this->numNodes); // ��ʼ������ڽӱ�

    // ѭ����ȡ�ļ��еı���Ϣ
    while (fscanf(fp, "%u %u %d %u\n", &lnode, &rnode, &w, &tmp) != EOF) {
        this->adjListOut[lnode].insert(make_pair(rnode, w)); // ���ӱߵ������ڽӱ�
        this->adjListInc[rnode].insert(make_pair(lnode, w)); // ���ӱߵ�����ڽӱ�
    }
    fclose(fp); // �ر��ļ�      
}*/


RoadNetwork::RoadNetwork(const std::vector<std::vector<std::pair<int, int>>>& graph) {
        this->numNodes = graph.size(); // ������
        this->numEdges = 0; // ������ʼ��Ϊ0
        this->adjListOut = vector<EdgeList>(this->numNodes); // ��ʼ�������ڽӱ�
        this->adjListInc = vector<EdgeList>(this->numNodes); // ��ʼ������ڽӱ�

        // ���������ͼ���������ߺ�����ڽӱ�
        for (int u = 0; u < graph.size(); ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;  // Ŀ�궥��
                int w = edge.second; // �ߵ�Ȩ��
                this->adjListOut[u].insert(make_pair(v, w)); // ���ӱߵ������ڽӱ�
                this->adjListInc[v].insert(make_pair(u, w)); // ���ӱߵ�����ڽӱ�
                this->numEdges++; // ���±ߵ�����
            }
        }
    }



/*int count_deletetimes = 6666;
void RoadNetwork::removeDegreeOneNodes()
{
    count_deletetimes=1000;
    // ɾ������Ϊһ�Ķ���
    for (NodeID i = 1; i < this->numNodes - 1; ++i) {
        // ����ڵ� i �Ķ���Ϊһ����ֻ��һ���ھӽڵ�
        if (this->adjListOut[i].size() == 1 && this->adjListInc[i].size() == 1) {
            count_deletetimes++;
            NodeID neighbor = this->adjListOut[i].begin()->first; // ��ȡ�ھӽڵ�ı��
            this->adjListOut[i].clear(); // ��սڵ� i �ĳ����б�
            this->adjListInc[neighbor].erase(i); // ���ھӽڵ������б���ɾ���ڵ� i
        }
    }
}*/


// ��ȡ�ߵ�Ȩ��
int RoadNetwork::getEdgeWeight(NodeID lnode, NodeID rnode) {
    return this->adjListOut[lnode][rnode]; // ���ر�(lnode, rnode)��Ȩ��
}

// RoadNetwork���������������ճ��ߺ�����ڽӱ�
RoadNetwork::~RoadNetwork() {
    this->adjListOut.clear(); // ��ճ����ڽӱ�
    this->adjListInc.clear(); // �������ڽӱ�
}

// ����ȫ�������==�������ж��������Ƿ����
bool operator==(const Edge& le, const Edge& re) {
    return (le.first == re.first && le.second == re.second) || (le.second == re.first && le.first == re.second);
}

// Path��ķ������ж�·���Ƿ����ָ���ı�
bool Path::containsEdge(Edge e) {
    bool res = false;

    for (unsigned int i = 0;i < this->nodes.size() - 1;i++) {
        if (this->nodes[i] == e.first && this->nodes[i + 1] == e.second) {
            res = true;
            break;
        }
    }

    return res;
}

// Path��ķ���������·������һ��·�����ص�����
double Path::overlap_ratio(RoadNetwork* rN, Path& path2) {
    double sharedLength = 0;

    for (unsigned int i = 0;i < path2.nodes.size() - 1;i++) {
        Edge e = make_pair(path2.nodes[i], path2.nodes[i + 1]);
        if (this->containsEdge(e))
            sharedLength += rN->getEdgeWeight(path2.nodes[i], path2.nodes[i + 1]);
    }

    return sharedLength / path2.length;
}

// ����ȫ�������==����֤����·���Ƿ����
bool operator==(const Path& lp, const Path& rp) {
    if (lp.length != rp.length || lp.nodes.size() != rp.nodes.size())
        return false;
    for (int i = 0;i < lp.nodes.size();i++) {
        if (lp.nodes[i] != rp.nodes[i])
            return false;
    }
    return true;
}