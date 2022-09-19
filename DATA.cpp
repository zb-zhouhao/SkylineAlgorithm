//
// Created by 周昊 on 2022/9/19.
//

#include "DATA.h"
#include "utils.h"

void DATA::initREC() {
    for (int i = 0; i < D.size(); i++) {
        for (int j = i + 1; j < D.size(); j++) {
            int res1 = 1, res2 = 0, rres1 = 1, rres2 = 0;
            vector<int> p = this->getPi(i);
            vector<int> q = this->getPi(j);
            for (int s = 0; s < SPACESIZE; s++) {
                res1 &= (p[s] >= q[s]);
                res2 |= (p[s] > q[s]);
                rres1 &= (q[s] >= p[s]);
                rres2 |= (q[s] > p[s]);
            }
            REC.insert(make_pair( i * DATASIZE + j, res1 & res2));
            REC.insert(make_pair(j * DATASIZE + i, rres1 & rres2));
        }
    }
}

DATA::DATA() {
    D = vector<Item>(DATASIZE, Item(0, vector<int>(SPACESIZE, 0)));
}

void DATA::dataLoader() {
    fstream df;
    df.open("./data/data_set.txt");

    if (!df.is_open()) {
        cout << "open error" << endl;
    }

    string line;
    vector<string> lines;
    int i = 0, j = 0;
    while (getline(df, line)) {
//        lines.push_back(line);
        for (int k = 0; k < line.length(); k++) {
            int s = k, e = k;
            while (line[k] != ' ') {
                k++;
            }
            e = k;
            D[i].id = i;
            D[i].v[j++] = stoi(line.substr(s, e));
//            stoi(line.substr(s, e));
        }
        i++;
        j = 0;
    }
}

vector<int> & DATA::getPi(int i) {
    return ref(D[i].v);
}

void DATA::printD() {
    for (int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D[0].v.size(); j++) {
            cout << D[i].v[j] << " ";
        }
        cout << endl;
    }
//    cout << "id:" << endl;
//    for (int i = 0; i < D.size(); i++) {
//        cout << D[i].id + 1 << " ";
//    }
//    cout << endl;
}

int getSum(vector<int>& v) {
    int sum = 0;
    for (auto e : v) {
        sum += e;
    }
    return sum;
}

bool cmp(Item& I1, Item& I2) {
    int sum1 = getSum(I1.v), sum2 = getSum(I2.v);
    return (sum1 > sum2);
}

void DATA::SortD() {
    sort(D.begin(), D.end(), cmp);
    this->initREC();
}

bool DATA::dominant(int pid, int qid) {
    return REC[pid * DATASIZE + qid];
}


void DATA::combine(int m, int n, int src, int N, vector<int>& rec, vector<int>& vis, int pid, int qid) {
    if (find) {
        return;
    }
    if (n == 0) {
        assert(rec.size() == N);
        //判断是否k-d
        int res1 = 1, res2 = 0, rres1 = 1, rres2 = 0;
        vector<int> p = this->getPi(pid);
        vector<int> q = this->getPi(qid);
        for (int i = 0; i < rec.size(); i++) {
            int s = rec[i];
            res1 &= (p[s] >= q[s]);
            res2 |= (p[s] > q[s]);
            rres1 &= (q[s] >= p[s]);
            rres2 |= (q[s] > p[s]);
        }
        if (res1 & res2) {
            this->find = true;
        }
        if (KREC.find(pid * DATASIZE + qid) == KREC.end()) {
            KREC.insert(make_pair(pid * DATASIZE + qid, res1 & res2));
        }
        if ((res1 & res2) && KREC[pid * DATASIZE + qid] == 0) {
            KREC[pid * DATASIZE + qid] = 1;
        }
        if (KREC.find(qid * DATASIZE + pid) == KREC.end()) {
            KREC.insert(make_pair(qid * DATASIZE + pid, rres1 & rres2));
        }
        if ((rres1 & rres2) && KREC[qid * DATASIZE + pid] == 0) {
            KREC[qid * DATASIZE + pid] = 1;
        }
        return;
    }
    for (int i = src; i < m; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            rec.push_back(i);
            combine(m, n-1, i + 1, N, rec, vis, pid, qid);
            rec.pop_back();
            vis[i] = 0;
        }
    }
}

bool DATA::kDominant(int pid, int qid) {
    vector<int> vis(SPACESIZE, 0);
    vector<int> rec;
    assert(SPACESIZE >= K);
    this->find = false;

    combine(SPACESIZE, K, 0, K, rec, vis, pid, qid);
    printf("确定p%d和p%d之间的k-dominant关系 k1=%d v1=%d k2=%d v2=%d\n", this->getRealId(pid), this->getRealId(qid), pid * DATASIZE + qid, KREC[pid * DATASIZE + qid], qid * DATASIZE + pid, KREC[qid * DATASIZE + pid]);
    cout << this->find << endl;
    return this->find;
}

int DATA::getRealId(int fake_id) {
    return D[fake_id].id + 1;
}

void DATA::printRECAndKREC() {
    cout << "print REC" << endl;
    for (int i = 0; i < DATASIZE; i++) {
        for (int j = i + 1; j < DATASIZE; j++) {
            if (REC[i * DATASIZE + j]) {
                printf("p%d dominant p%d\n", this->getRealId(i), this->getRealId(j));
            }
            if (REC[j * DATASIZE + i]) {
                printf("p%d dominant p%d\n", this->getRealId(j), this->getRealId(i));
            }
        }
    }
    cout << "print KREC" << endl;
    for (int i = 0; i < DATASIZE; i++) {
        for (int j = i + 1; j < DATASIZE; j++) {
            if (KREC[i * DATASIZE + j]) {
                printf("p%d %d-dominant p%d\n", this->getRealId(i), K, this->getRealId(j));
            }
            if (KREC[j * DATASIZE + i]) {
                printf("p%d %d-dominant p%d\n", this->getRealId(j), K, this->getRealId(i));
            }
        }
    }
}
