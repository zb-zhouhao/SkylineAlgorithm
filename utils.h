//
// Created by 周昊 on 2022/9/19.
//

#ifndef KDS_BASELINE_UTILS_H
#define KDS_BASELINE_UTILS_H
#include <iostream>
#include <utility>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Item {
    int id;
    vector<int> v;
    Item(int _id, vector<int> _v) : id(_id), v(std::move(_v)) {}
};

//param
#define DATASIZE 5
#define SPACESIZE 6
#define K 5


#endif //KDS_BASELINE_UTILS_H
