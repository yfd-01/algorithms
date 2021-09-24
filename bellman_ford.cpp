/*
    Bellman_ford

    Note
    ----
    The algorithm is able to detect negative cycles.
*/
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#define MAX 10
#define INF 99999
using namespace std;

float map[MAX][MAX] = {
        {0, 1, 12, INF, INF, INF},
        {INF, 0, 9, 3, INF, INF},
        {INF, INF, 0, INF, 5, INF},
        {INF, INF, 4, 0, 13, 15},
        {INF, INF, INF, INF, 0, 4},
        {INF, INF, INF, INF, INF, 0}
};

struct Edge{
    int from;
    int to;
    float cost;
};

void Bellman_ford(int len, int s){
    //initialization
    float* dis = new float[len];
    int* pre = new int[len];
    vector<Edge> edges;

    s -= 1;

    //count the every edges from graph
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            if(map[i][j] && map[i][j] != INF){
                Edge edge = {i, j, map[i][j]};
                edges.push_back(edge);
            }
        }
    }

    for(int i = 0; i < len; i++) {
        dis[i] = INF;
        pre[i] = -1;
    }

    dis[s] = 0;

    //relax the number of nodes minus 1 times
    for(int i = 1; i < len; i++){
        bool relaxed = false;
        //relax each edges if it is satisfied
        for(int j = 0; j < edges.size(); j++){
            if(dis[edges[j].to] > dis[edges[j].from] + edges[j].cost){
                dis[edges[j].to] = dis[edges[j].from] + edges[j].cost;
                pre[edges[j].to] = edges[j].from;   //record previous node
                relaxed = true; //break in advance
            }
        }

        if(!relaxed)
            break;
    }

    //detect which nodes are part of a negative cycle
    for(int i = 0; i < len; i++){
        bool relaxed = false;
        for(int j = 0; j < edges.size(); j++){
            if(dis[edges[j].to] > dis[edges[j].from] + edges[j].cost){
                dis[edges[j].to] = -INF;
                relaxed = true;
            }
        }

        if(!relaxed)
            break;
    }

    //print shortest distance from s to each nodes
    for_each(dis, dis + len, [](float d){
        cout<< d<< ' ';
    });
    cout<< '\n';

    //print path
    stack<int> st;
    for(int i = 0; i < len; i++){
        if(i == s || dis[i] == INF || dis[i] == -INF)
            continue;

        //push node in stack in order to print by positive forward
        st.push(i + 1);
        int p = i;
        while(pre[p] != -1) {
            st.push(pre[p] + 1);
            p = pre[p];
        }

        if(int(st.size()) == 1)
            st.push(s + 1);

        while(!st.empty()){
            cout<< st.top()<< (int(st.size()) > 1 ? "-->" : "");
            st.pop();
        }
        cout<< '\n';
    }

    delete[] dis;
    delete[] pre;
}

int main(){
    for(int i = 0; i < 6; i++) {
        Bellman_ford(6, i + 1);
    }

    /*  Output:
        0 1 8 4 13 17
        1-->2
        1-->2-->4-->3
        1-->2-->4
        1-->2-->4-->3-->5
        1-->2-->4-->3-->5-->6
        99999 0 7 3 12 16
        2-->4-->3
        2-->4
        2-->4-->3-->5
        2-->4-->3-->5-->6
        99999 99999 0 99999 5 9
        3-->5
        3-->5-->6
        99999 99999 4 0 9 13
        4-->3
        4-->3-->5
        4-->3-->5-->6
        99999 99999 99999 99999 0 4
        5-->6
        99999 99999 99999 99999 99999 0
     */

    return 0;
}
