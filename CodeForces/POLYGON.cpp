#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;
/*
The basic idea behind solving this problem was to observe the fact that any 1 that is not
on the border must have atleast a 1 below it and to it's right.
First , it is easy to realise that if the 1 is not on border it must have a 1 below it or
to it's right other when the 1 was shot it should have slided further right or bottom.
Second , why is sufficient ? Suppose not, the given matrix is valid but there exists no such
cell with 1 satisfying the above condition. But then that would mean we always atleast one 
cell with 1 below or rightwards, for every non border cell which has 1. Which means we already
have an ordering from that for the matrix to be valid. Which is a contradiction.
*/

//Code
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        bool res = true;
        int n;
        cin >> n;
        bool mat[n][n]; //Input final layout
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < n ; j++) {
                char c;
                cin >> c;
                mat[i][j] = c-'0'; //Inputting char by char and using ascii values to store booleans
            }
        }
        for(int i = 0 ;i < n-1 ; i++) {
            for(int j = 0 ; j < n-1 ; j++) {
                if(mat[i][j])
                    res = res & (mat[i+1][j] | mat[i][j+1]); //Bitwise 'and' , 'or'
            }
        }
        cout << (res ? "YES\n" : "NO\n"); // << has precedence over ? thus it is neccesary to pur brackets
    }
    return 0;
}