/*
    Floyd

    Note
    ----
    The algorithm is able to detect negative cycles.
*/
#include <iostream>
#include <algorithm>
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

void floyd(int len){
    float** dis = new float*[len];

    for(int i = 0; i < len; i++)
        dis[i] = new float[len];

    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            dis[i][j] = map[i][j];
        }
    }

    for(int k = 0; k < len; k++)
        for(int i = 0; i < len; i++)
            for(int j = 0; j < len; j++){
                if(dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
            }

    for_each(dis, dis + len, [len](float* disRow){
       for_each(disRow, disRow + len, [](float d){
           cout<< d<< ' ';
       }) ;
       cout<< '\n';
    });

    for(int i = 0; i < len; i++)
        delete[] dis[i];

    delete[] dis;
}

int main(){
    floyd(6);

    /*  Output:
        0 1 8 4 13 17
        99999 0 7 3 12 16
        99999 99999 0 99999 5 9
        99999 99999 4 0 9 13
        99999 99999 99999 99999 0 4
        99999 99999 99999 99999 99999 0
     */

    return 0;
}
