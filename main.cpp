#include "utils.h"
#include "DATA.h"

//One-Scan算法

unordered_set<int> R;
unordered_set<int> T;

int main() {
    //init
    DATA data = DATA();
    data.dataLoader();
    //sort
    data.printD();
    data.SortD();
    cout << "-------sorting-------" << endl;
    data.printD();

    //算法流程
    for (int p_id = 0; p_id < DATASIZE; p_id++) {
        bool isUniqueSkyline = true;
        cout << "consider p" << data.getRealId(p_id) << endl;
        for (auto it = T.begin(); it != T.end(); it++) {
            int q_id = *it;
            if (data.dominant(p_id, q_id)) {
                printf("delete p%d from T\n", data.getRealId(q_id));
                T.erase(it);
            } else if (data.dominant(q_id, q_id) or p_id == q_id) {
                isUniqueSkyline = false;
                break;
            }
        }
        if (isUniqueSkyline) {
            bool isDominant = true;
            for (auto it = R.begin(); it != R.end(); it++) {
                int q_id = *it;
                int real_pid = data.getRealId(p_id);
                int real_qid = data.getRealId(q_id);
                if (data.kDominant(q_id, p_id)) {
                    printf("p%d %d-dominate p%d\n", data.getRealId(q_id), K, data.getRealId(p_id));
                    isDominant = false;
                }
                if (data.kDominant(p_id, q_id)) {
                    printf("delete p%d from R\n", data.getRealId(q_id));
                    R.erase(it);
                    printf("insert p%d to T\n", data.getRealId(q_id));
                    T.insert(q_id);
                }
            }
            if (isDominant) {
                printf("insert p%d to R\n", data.getRealId(p_id));
                R.insert(p_id);
            } else {
                printf("insert p%d to T\n", data.getRealId(p_id));
                T.insert(p_id);
            }
        }
    }

//    data.printRECAndKREC();
    cout << K << "-dominant is:" << endl;
    for (auto e : R) {
        cout << "p" << data.getRealId(e) << " ";
    }
    cout << endl;
    cout << "free skyline is:" << endl;
    for (auto e : R) {
        cout << "p" << data.getRealId(e) << " ";
    }
    for (auto e : T) {
        cout << "p" << data.getRealId(e) << " ";
    }
    cout << endl;
    return 0;
}

