/*
    Dijkstra

    Note
    ----
    The algorithm is NOT able to detect negative cycles
*/
#include <iostream>
#include <algorithm>
#include <stack>
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


void Dijkstra(int len, int s){
    float* dis = new float[len];	//the shortest distance from s to each nodes
    int* vis = new int[len];		//the status of each nodes if it has been visited
    int* pre = new int[len];		//the record of previous path

    s -= 1;

    //initialization
    for(int i = 0; i < len; i++){
        dis[i] = map[s][i];
        vis[i] = 0;
        pre[i] = -1;
    }

    //forward greedy algorithm
    for(int i = 0; i < len; i++){
        int min = INF;
        int n = -1;

        //get the node which has minimum distance and is not visited
        for(int j = 0; j < len; j++){
            if(dis[j] < min && !vis[j]){
                min = dis[j];
                n = j;
            }
        }

        if(n == -1)
            break;

        //visit it
        vis[n] = 1;

        //update distance
        for(int j = 0; j < len; j++){
            if(dis[j] > dis[n] + map[n][j] && !vis[j]){
                dis[j] = dis[n] + map[n][j];
                pre[j] = n;
            }
        }
    }

    for_each(dis, dis + len, [](float d){
        cout<< d<< ' ';
    });
    cout<< '\n';

    //print paths from s to each nodes
    stack<int> st;
    for(int i = 0; i < len; i++){
        if(i == s || dis[i] == INF)
            continue;

        //record nodes in path to stack enable a positive forward print
        st.push(i + 1);
        int p = i;
        while(pre[p] != -1){
            st.push(pre[p] + 1);
            p = pre[p];
        }
        st.push(s + 1);

        //print path in positive forward
        while(!st.empty()){
            cout<< st.top()<< (int(st.size()) > 1 ? "-->" : "");
            st.pop();
        }
        cout<< '\n';
    }

    delete[] dis;
    delete[] vis;
    delete[] pre;
}

int main(){
    for(int i = 0; i < 6; i++)
        Dijkstra(6, i + 1);

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

