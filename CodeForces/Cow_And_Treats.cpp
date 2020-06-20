#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;

/*
    First we observe that no more than two cows of who like the same type of grass can be put in a solution.
    We can prove this by contraditon. Say if a cow k which likes type i grass enters from left.
    We consider k is satisfied and thus eats is last grass at position m and sleeps at position m. Now if another cow entered
    from left, which likes the same type i grass then it wouldn't find any grass till position m and seeing the cow k asleep it
    is disatisfied. Hence from one direction atmost one cow which likes particular type of grass can enter. We have two directions
    thus no more than two cows which like same type of grass can enter.
    We now notice that the complexity of solution can't be O(n²)
    Thus we develope an iterative algorithm on grass positions. 
    Say at position p the type of grass is i accounting the following :
        -> Maintain count of how many cows liking grass i can now be allowed. And updating the max count based on it.
            Note : The hunger of the cows won't matter as we can always find some arrangement (Please think through this)
        -> If the count equals max count or exceeds max count we compute the new ways generated by adding the position i based on
           the data we store in dp table.
        -> Update the total ways and count variables that can be used by further positions that come.

    Initialization: Here we assume all cows can come only in one direction and in that way initialize aur max_count and number of
    ways variables.
*/

// Code for finding divison with modulo taken from GeeksForGeeks. Please refer to GeeksForGeeks in how it works.
int gcdExtended(int a, int b, int *x, int *y) 
{ 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    int x1, y1; 
    int gcd = gcdExtended(b%a, a, &x1, &y1); 

    *x = y1 - (b/a) * x1; 
    *y = x1; 
  
    return gcd; 
}
int modInverse(int b, int m) 
{ 
    int x, y; 
    int g = gcdExtended(b, m, &x, &y); 
    if (g != 1) 
        return -1; 
    return (x%m + m) % m; 
}
// Code for divison with modulo ends here
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<int>grass(n+1);
    vector<int> grass_sweet(n+1,0);
    for(int i = 1 ; i <= n ; i++) {
        int sweet;    
        cin >> sweet;
        grass[i] = sweet;
        grass_sweet[sweet]++;
    }
    vector<vector<int> >cows(n+1);
    for(int i = 1 ; i <= m ; i++) {
        int favourite,hunger;
        cin >> favourite >> hunger;
        cows[favourite].push_back(hunger);
    }
    for(int i = 1 ; i <= n ; i++) {
        if(!cows[i].empty()) 
            sort(cows[i].begin(),cows[i].end());
    }
    vector<int> cur_s(n+1,0);
    vector<int> cows_s(n+1,0);
    vector<ll> ways(n+1,0);
    vector<ll> ways_fav(n+1,0);
    ways[0] = 1;
    bool check = false;

    ll total_cows = 0;

    for(int i = 1; i <= n ; i++) {
        int u = grass_sweet[i];
        if(!cows[i].empty() && u && cows[i][0] <= u) {
            check = true;
            auto it = upper_bound(cows[i].begin(),cows[i].end(),u);
            int num = it - cows[i].begin();
            ways[0] = (ways[0]*num)%prime;
            total_cows++;
            cows_s[i] = 1; 
            ways_fav[i] = num;
        }
    }

    if(!check) {
        cout << 0 << " " << 1;
        return 0;
    }    

    ll res_ways = ways[0];
    ll max_cows = total_cows;

    for(int i = 1; i <= n ; i++) {
        int cur_shift = grass[i];
        cur_s[cur_shift] = cur_s[cur_shift]+1;
        int m = grass_sweet[cur_shift];
        if(!cows[cur_shift].empty() && m && cows[cur_shift][0] <= m) {
            ll cur_cows_count = total_cows - cows_s[cur_shift];
            ll cur_ways_total = (ways[i-1]*modInverse(ways_fav[cur_shift],prime))%prime;
            auto it = cows[cur_shift].begin();
            auto it1 = upper_bound(cows[cur_shift].begin(),cows[cur_shift].end(),cur_s[cur_shift]);
            ll l = it1 - cows[cur_shift].begin();
            auto it2 = upper_bound(cows[cur_shift].begin(),cows[cur_shift].end(),m-cur_s[cur_shift]);
            ll u = it2 - cows[cur_shift].begin();
            if(binary_search(cows[cur_shift].begin(),cows[cur_shift].end(),cur_s[cur_shift])){
                ll new_ways = u; 
                if(new_ways >= l)
                    new_ways--;
                ll update_cows = cur_cows_count + (new_ways > 0 ? 2 : 1);
                new_ways = (new_ways ? new_ways : 1);
                new_ways = (cur_ways_total*new_ways)%prime;
                if(update_cows > max_cows) {
                    max_cows = update_cows;
                    res_ways = new_ways;
                }
                else if(update_cows == max_cows){
                    res_ways = (res_ways + new_ways)%prime;
                }
            }
            ll cur_ways;
            cur_ways = ((l*u)%prime - min(u,l) + prime)%prime;
            ll check_2 = l + u;
            if(cur_ways > 0) {
                cows_s[cur_shift] = 2;
                ways_fav[cur_shift] = cur_ways;
            }
            else if(check_2 > 0) {
                cows_s[cur_shift] = 1;
                ways_fav[cur_shift] = check_2;
            }
            else {
                cows_s[cur_shift] = 0;
                ways_fav[cur_shift] = 1;
            }
            total_cows = cur_cows_count + cows_s[cur_shift];
            ways[i] = (cur_ways_total*ways_fav[cur_shift])%prime;
        }
        else
            ways[i] = ways[i-1];
    }

    cout << max_cows << " " << res_ways << '\n';
    return 0;
}