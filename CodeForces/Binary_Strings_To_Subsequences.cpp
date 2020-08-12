#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;

/* 
For this problem we maintain all groups of sub-strings that end with zero and one separately. If the incoming character happens to be 0 we can add this character to any substringthat ends with one.
If no such sub string existed we add a new group with the incoming 0 as it's first bit. And similarly if incoming bit is 1.
Note we upon adding a character to a substring the last digit it accpets changes now and thus we make corresponding changes.
This approach covers accounts all exhausive cases as we keep track of every substring we made and added a new group(substring) only if none of the existing sub-strings could handle the incoming characeter.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int group[n], num_groups = 0;
        queue<int> expect_zero_queue;
        queue<int> expect_one_queue;
        for(ll i=0 ; i<n ; i++) {
            char bit;
            cin >> bit;
            if(bit == '0') {
                if(expect_zero_queue.empty()) {
                    num_groups++;
                    group[i] = num_groups;
                    expect_one_queue.push(num_groups);
                }
                else {
                    int cur_group = expect_zero_queue.front();
                    expect_zero_queue.pop();
                    expect_one_queue.push(cur_group);
                    group[i] = cur_group;
                }
            }
            else {
                if(expect_one_queue.empty()) {
                    num_groups++;
                    group[i] = num_groups;
                    expect_zero_queue.push(num_groups);
                }
                else {
                    int cur_group = expect_one_queue.front();
                    expect_one_queue.pop();
                    expect_zero_queue.push(cur_group);
                    group[i] = cur_group;
                }                
            }
        }
        cout << num_groups  << "\n";
        for(ll i=0 ; i<n ; i++) {
            cout << group[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}