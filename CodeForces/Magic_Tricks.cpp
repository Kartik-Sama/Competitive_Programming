#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;

//Note this problem needs to solved only Kotlin language but the code here is in C++
//However the solution has been checked with the problem setter's tutorial.
/*
The brute force of this solution would be very expensive. You can choose any combination of moves giving 2ᵐ possiblities.
But we can observe some particular features here.
    1. For a position to have special ball, it should swap with some position that already holds the special ball.
    2. The ordering of swaps is important and is crucial in realising dp strategy here.
    3. Any index involving a swap with position k is sure to have a solution. (Say you can remove all the other moves in worst case).
    4. Any swap of the form i,k if is to be part of optimal solution all the swaps involving k before this swap must be ommited and all
       swaps involving k after this swap must be ommitted.
    5. Lastly coming to the general dp recursive relation we look at two cases at each swap (i,j). 
        i) The swap is faked.
        ii) The swap isn't faked. (Exhaustive cases)
       If it is the case swap is faked. The cost of bringing the special ball to the iᵗʰ position will be cost of bringing the special to iᵗʰ position
       + 1. As this move was faked. So is the case with jᵗʰ position.
       Else If it is the case swap isn't faked. Then the ball at position j comes to i. So the cost of bringing the special ball to position i would
       be cost of bringing the ball to postion to j till that point. And vice versa as iᵗʰ position ball is also moved to jᵗʰ position.
       Now for i and j position we take min(these both cases separately). That is, it might be the case faking the swap may be better for iᵗʰ position
       but that may not be the case with jᵗʰ position. 
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> costs(n+1,m+1);
    costs[k] = 0;
    for(int i = 0 ; i < m ; i++) {
        int v1,v2;
        cin >> v1 >> v2;
        int temp_v1 = min(costs[v1]+1,costs[v2]);
        int temp_v2 = min(costs[v2]+1,costs[v1]);
        costs[v1] = temp_v1;
        costs[v2] = temp_v2;
    }
    for(ll i = 1 ; i <= n; i++) {
        cout << (costs[i] < m+1 ? costs[i] : -1) << " ";
    }
    cout << '\n';
    return 0;
}