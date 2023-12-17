#include <bits/stdc++.h>
using namespace std;
class ExamRoom {
public:
    ExamRoom(int n) {
        this->n = n;
        vector<int> initial = {-1, n};
        pq = new set<vector<int>, Compare>(Compare(n));
        pq->insert(initial);
        startPoint[-1] = initial;
        endPoint[n] = initial;
    }
    
    int seat() {
        vector<int> longest = *pq->begin();
        // find which seat to sit in
        int seat;
        if(longest[0] == -1) seat = 0;
        else if(longest[1] == n) seat = n-1;
        else seat = longest[0] + (longest[1] - longest[0])/2;
        // split the longest interval into 2
        removeInterval(longest);
        insertInterval({longest[0], seat});
        insertInterval({seat, longest[1]});
        return seat;
    }
    
    void leave(int p) {
        // merge the two interval into one
        int end = startPoint[p][1];
        int start = endPoint[p][0];
        removeInterval({start, p});
        removeInterval({p, end});
        insertInterval({start,end});
    }
private:
    int n;
    unordered_map<int, vector<int>> startPoint;
    unordered_map<int, vector<int>> endPoint;
    struct Compare {
        int N;
        Compare(int n): N(n){};
        bool operator()(const vector<int>& a, const vector<int>& b) const {
            int dis1, dis2;
                if(a[0] == -1) dis1 = a[1];
                else if(a[1] == N) dis1 = a[1] - a[0] - 1;
                else dis1 = (a[1] - a[0])/2;
                if(b[0] == -1) dis2 = b[1];
                else if(b[1] == N) dis2 = b[1] - b[0] - 1;
                else dis2 = (b[1] - b[0])/2;
                if(dis1 == dis2) return a[0] < b[0];
                return dis1 > dis2;
        }
    };
    set<vector<int>, Compare>* pq = nullptr;

    void insertInterval(vector<int> interval){
        pq->insert(interval);
        startPoint[interval[0]] = interval;
        endPoint[interval[1]] = interval;
    }
    void removeInterval(vector<int> interval){
        pq->erase(interval);
        startPoint.erase(interval[0]);
        endPoint.erase(interval[1]);
    }
};



int main(){
    ExamRoom room(10);
    room.seat();
    room.seat();
    room.seat();
    room.leave(4);
    room.seat();

}
/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */