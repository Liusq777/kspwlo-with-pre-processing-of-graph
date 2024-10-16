/*
Copyright (c) 2017 Theodoros Chondrogiannis
*/

#include "graph.hpp" // 包含自定义的头文件 graph.hpp

// RoadNetwork类的构造函数，根据传入的文件名filename读取文件信息构建RoadNetwork对象
/*RoadNetwork::RoadNetwork(const char* filename) {

    FILE* fp;
    NodeID lnode, rnode, tmp;
    int w;
    char c;

    fp = fopen(filename, "r"); // 以只读方式打开文件
    //fscanf(fp, "%c\n", &c); // 读取一个字符并跳过
    fscanf(fp, "%u %u\n", &this->numNodes, &this->numEdges); // 读取顶点数和边数
    this->adjListOut = vector<EdgeList>(this->numNodes); // 初始化出边邻接表
    this->adjListInc = vector<EdgeList>(this->numNodes); // 初始化入边邻接表

    // 循环读取文件中的边信息
    while (fscanf(fp, "%u %u %d %u\n", &lnode, &rnode, &w, &tmp) != EOF) {
        this->adjListOut[lnode].insert(make_pair(rnode, w)); // 添加边到出边邻接表
        this->adjListInc[rnode].insert(make_pair(lnode, w)); // 添加边到入边邻接表
    }
    fclose(fp); // 关闭文件      
}*/


RoadNetwork::RoadNetwork(const std::vector<std::vector<std::pair<int, int>>>& graph) {
        this->numNodes = graph.size(); // 顶点数
        this->numEdges = 0; // 边数初始化为0
        this->adjListOut = vector<EdgeList>(this->numNodes); // 初始化出边邻接表
        this->adjListInc = vector<EdgeList>(this->numNodes); // 初始化入边邻接表

        // 遍历输入的图，构建出边和入边邻接表
        for (int u = 0; u < graph.size(); ++u) {
            for (const auto& edge : graph[u]) {
                int v = edge.first;  // 目标顶点
                int w = edge.second; // 边的权重
                this->adjListOut[u].insert(make_pair(v, w)); // 添加边到出边邻接表
                this->adjListInc[v].insert(make_pair(u, w)); // 添加边到入边邻接表
                this->numEdges++; // 更新边的数量
            }
        }
    }



/*int count_deletetimes = 6666;
void RoadNetwork::removeDegreeOneNodes()
{
    count_deletetimes=1000;
    // 删除度数为一的顶点
    for (NodeID i = 1; i < this->numNodes - 1; ++i) {
        // 如果节点 i 的度数为一，即只有一个邻居节点
        if (this->adjListOut[i].size() == 1 && this->adjListInc[i].size() == 1) {
            count_deletetimes++;
            NodeID neighbor = this->adjListOut[i].begin()->first; // 获取邻居节点的编号
            this->adjListOut[i].clear(); // 清空节点 i 的出边列表
            this->adjListInc[neighbor].erase(i); // 从邻居节点的入边列表中删除节点 i
        }
    }
}*/


// 获取边的权重
int RoadNetwork::getEdgeWeight(NodeID lnode, NodeID rnode) {
    return this->adjListOut[lnode][rnode]; // 返回边(lnode, rnode)的权重
}

// RoadNetwork类的析构函数，清空出边和入边邻接表
RoadNetwork::~RoadNetwork() {
    this->adjListOut.clear(); // 清空出边邻接表
    this->adjListInc.clear(); // 清空入边邻接表
}

// 重载全局运算符==，用于判断两个边是否相等
bool operator==(const Edge& le, const Edge& re) {
    return (le.first == re.first && le.second == re.second) || (le.second == re.first && le.first == re.second);
}

// Path类的方法，判断路径是否包含指定的边
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

// Path类的方法，计算路径与另一条路径的重叠比率
double Path::overlap_ratio(RoadNetwork* rN, Path& path2) {
    double sharedLength = 0;

    for (unsigned int i = 0;i < path2.nodes.size() - 1;i++) {
        Edge e = make_pair(path2.nodes[i], path2.nodes[i + 1]);
        if (this->containsEdge(e))
            sharedLength += rN->getEdgeWeight(path2.nodes[i], path2.nodes[i + 1]);
    }

    return sharedLength / path2.length;
}

// 重载全局运算符==，验证两条路径是否相等
bool operator==(const Path& lp, const Path& rp) {
    if (lp.length != rp.length || lp.nodes.size() != rp.nodes.size())
        return false;
    for (int i = 0;i < lp.nodes.size();i++) {
        if (lp.nodes[i] != rp.nodes[i])
            return false;
    }
    return true;
}
