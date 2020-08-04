#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;

/* 
First we rule out the possibility that optimal value for iᵗʰ level can't be achived by visiting it from a above floor. Carefully thinking about this, we can always find a redundant cycle that only increases the cost.
So we can conclude that if we get to iᵗʰ level then we must have come to it from (i-1)ᵗʰ level thus leaving us two choices was it by stairs or from lift. We cam answer this by using dp algorithm to look at all cases.
So here we define opt[i] as the optimum cost to reach level i and optL[i] as the optimum cost to reach level i in a lift.
Breaking our two cases:
    1) Reaching the iᵗʰ level by using lift the optimum value would be:
        opt1 = min( optL[i-1] + bᵢ , opt[i-1] + c + bᵢ) //Note that even opt[i-1] ended being from lift we add c to account for the stairs case... as if we actually reached there by lift the 1ˢᵗ term wouild account for it.
    2) Reaching the iᵗʰ level by using stairs the optimum value would be:
        opt2 = opt[i-1] + aᵢ //Note there is no switching cost when we shift from lift to stairs
    opt[i] = min(opt1,opt2)
Analysing the base case is left for you to think.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,c;
    cin >> n >> c;
    ll opt_overall[n+1];
    ll opt_lift[n+1];
    opt_overall[0] = 0;
    opt_lift[0] = c;
    ll stairs[n];
    ll lift[n];
    for(int i = 0 ; i < n-1 ; i++) 
        cin >> stairs[i];
    for(int i = 0 ; i < n-1 ; i++)
        cin >> lift[i];
    for(int i = 1 ; i < n ; i++) {
        opt_lift[i] = min(opt_overall[i-1]+c+lift[i-1],opt_lift[i-1]+lift[i-1]);
        opt_overall[i] = min(opt_overall[i-1]+stairs[i-1],opt_lift[i]);
    }
    for(int i = 0 ; i < n ; i++) 
        cout << opt_overall[i] << " ";
    cout << "\n";
    return 0;
}