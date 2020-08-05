#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;
/*
    If it was only the units place that changed the problem is reltively easy isn't it? Because the sum of digits could only increase by 1 and thus in 4 consecutive numbers starting from 'a' we are sure to find the required n.
    But when the ten's digit changes the sum might reduce i.e. like 9 -> 10  958 -> 959 -> 960 etc. But then again the property holds that from that number in which the ten's digit changed in the next four number we will surely find our 'n'.
    Thus we can check for the next 8 numbers starting from our 'a' to find the minimal interesting number 'n'.
*/

ll digit_sum(int n){
    ll sum = 0;
    while(n) {
        sum += n%10;
        n /= 10;
    }
    return sum;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int a;
    cin >> a;
    for(int i = 0 ; i < 9 ; i++) {
        if(!(digit_sum(a+i)%4)) {
            cout << a+i << endl;
            return 0;
        }
    }
    return 0;
}