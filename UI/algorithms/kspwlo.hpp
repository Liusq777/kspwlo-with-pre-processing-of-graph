#ifndef KSPWLO_HPP
#define KSPWLO_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

#include "../model/graph.hpp"
#include "../tools/tools.hpp"

using namespace std;


vector<Path> svp_plus(RoadNetwork *rN, NodeID source, NodeID target, unsigned int k, double theta);

#endif
