#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//Using two-dimension array to dp
int knapsackProblemZeroOne(const vector<vector<int>>& stuffs, int capacity){
    int rowLen = stuffs.size();
    vector<vector<int>> dp(rowLen, vector<int>(capacity + 1, 0));

    //initialize the dp's values when first item put in
    for(int j = 0; j <=capacity; j++)
        dp[0][j] = j >= stuffs[0][0] ? stuffs[0][1] : 0;

    for(int i = 1; i < rowLen; i++)
        for(int j = 1; j <= capacity; j++)
            if(j < stuffs[i][0])
                //the space is NOT able to put stuffs[i] in
                dp[i][j] = dp[i - 1][j];
            else
                //do a comparison
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - stuffs[i][0]] + stuffs[i][1]);

    return dp[rowLen - 1][capacity];
}

//Using one-dimension array to dp
int knapsackProblemZeroOne(const vector<vector<int>>& stuffs, int capacity){
    int rowLen = stuffs.size();
    vector<int> dp(capacity + 1, 0);

    for(int j = 0 ; j < capacity; j++)
        dp[j] = j >= stuffs[0][0] ? stuffs[0][1] : 0;

    for(int i = 1; i < rowLen; i++)
        /*
            The reason using a reverse iteration for j is that we hope dp[j-stuffs[i][0]]
        remains its old value, which means we wanna the dp[j] still from last round when we use
        dp[j - stuffs[i][0]] + stuffs[i][1] to cover dp[j]
        */
        for(int j = capacity; j >= stuffs[i][0]; j--)
            dp[j] = max(dp[j], dp[j - stuffs[i][0]] + stuffs[i][1]);

    return dp[capacity];
}

int main(){
    vector<vector<int>> v = {{4, 3000}, {3, 2000}, {1, 1500}};
    for(int i = 0; i < 10; i++)
        cout<< i<< ": "<< knapsackProblemZeroOne(v, i)<< '\n';

    /*  Outputs:
        0: 0
        1: 1500
        2: 1500
        3: 2000
        4: 3500
        5: 4500
        6: 4500
        7: 5000
        8: 6500
        9: 6500
    */

    return 0;
}
