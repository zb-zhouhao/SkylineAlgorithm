//
// Created by 周昊 on 2022/9/19.
//
#include "utils.h"

#ifndef KDS_BASELINE_DATA_H
#define KDS_BASELINE_DATA_H



class DATA
{
    private:
        vector<Item> D;
        unordered_map<int, int> REC;
        unordered_map<int, int> KREC;
        bool find = false;
        void initREC();

    public:
        DATA();
        void dataLoader();
        vector<int>& getPi(int i);
        void printD();
        void SortD();
        bool dominant(int pid, int qid);
        void combine(int m, int n, int src, int N, vector<int>& rec, vector<int>& vis, int pid, int qid);
        bool kDominant(int pid, int qid);
        int getRealId(int fake_id);
        void printRECAndKREC();
};


#endif //KDS_BASELINE_DATA_H
