#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

//Using two-dimension array to dp
int knapsackProblemCompleteness(const vector<vector<int>>& stuffs, int capacity){
    int rowLen = stuffs.size();
    vector<vector<int>> dp(rowLen, vector<int>(capacity + 1, 0));

    //pay attention to make knapsack full, that's "stuffs[0][1] * floor(j / stuffs[0][0])"
    for(int j = 0; j <= capacity; j++)
        dp[0][j] = j >= stuffs[0][0] ? stuffs[0][1] * floor(j / stuffs[0][0]) : 0;

    for(int i = 1; i < rowLen; i++)
        /*
            In zeroOne, we use dp[i - 1][j - stuffs[i][0]]
            But in completeness, the i of "dp[i][j - stuffs[i][0]]" represents the idea that
        you pick up in many times.
        */
        for(int j = 1; j <= capacity; j++)
            if(j < stuffs[i][0])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - stuffs[i][0]] + stuffs[i][1]);

    return dp[rowLen - 1][capacity];
}

//Using one-dimension array to dp
int knapsackProblemCompleteness(const vector<vector<int>>& stuffs, int capacity){
    int rowLen = stuffs.size();
    vector<int> dp(capacity + 1, 0);

    for(int j = 0; j <= capacity; j++)
        dp[j] = j >= stuffs[0][0] ? stuffs[0][1] * floor(j / stuffs[0][0]) : 0;
    
    for(int i = 1; i < rowLen; i++)
        for(int j = stuffs[i][0]; j <= capacity; j++)
            dp[j] = max(dp[j], dp[j - stuffs[i][0]] + stuffs[i][1]);

    return dp[capacity];
}


int main(){
    vector<vector<int>> v = {{2, 3}, {4, 7}, {3, 6}};
    for(int i = 0; i < 10; i++)
        cout<< i<< ": "<< knapsackProblemCompleteness(v, i)<< '\n';

    /*  Outputs:
        0: 0
        1: 0
        2: 3
        3: 6
        4: 7
        5: 9
        6: 12
        7: 13
        8: 15
        9: 18
     */
    return 0;
}