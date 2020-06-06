#include<bits/stdc++.h>
#define prime 1000000007
typedef long long ll;
using namespace std;

/*
    In this problem we need to assign quantifiers ∀('A') and ∃('E') to a conjuntion of n variables
    x₁,x₂,x₃ ... xₙ. Inequalities being of the form xᵢ < xⱼ where i,j in [1,n]. The order in which
    quantifiers are assigned are in the order of x₁,x₂ .. xₙ itself and this doesn't change.
    We want to maximise the universal quantifiers if assigning quantifiers is possible.

    We first construct a graph based on each predicate of the form xᵢ < xⱼ → there is an directed edge 
    from iᵗʰ vertex to jᵗʰ vertex. If a cycle exists in the graph then assigning quantifiers is not possible.
    Why? Because aggregating all the inequalities over such a cycle will lead to xᵢ < xᵢ for any variable in
    the cycle , and thus leading to a contradiction.

    Now if we don't have cycles we need to assign quantifiers. We look at the only scenario in which 
    universal quantification is possible. Firstly, xᵢ and xⱼ are comparable if there exists a directed path 
    "either" from i to j "or" from j to i. Now let's say there exists a predicate xᵢ < xⱼ or xⱼ < xᵢ for i < j. 
    We should quantify xᵢ before xⱼ as per given constraints. Thus, if we were to assign universal quantification
    it can be done only to the xᵢ as once if we quantify xᵢ we cannot have all xⱼ's satisfying the inequality.

    So the problem boils down to finding the least index vertex reachable from every vertex and checking if that
    least index is greater than the index of vertex we are looking at. If it is greater we can assign a universal 
    quantifcation to such a vertex as it would be quantified before quantifying any of it's reachable vertex.
*/

/*
Implementation:
    For detection of cycle we check for back edges in DFS. O(V+E) time complexity.
    For finding the minimum index vertex reachable we find the topological order in the DFS itself. 
    Visiting edges of vertices in topological order ensures that we have covered all the incoming edges of the iᵗʰ
    vertex before considering the edges out of iᵗʰ vertex. 
    To also account for the reachability in other direction we also tranverse in the reverse topological sort order
    on the edges of our graph's transpose.
    The minimum index vertex reachable for every vertex will thus be calculated as minimum index of the results of 
    the above mentioned iterations.
*/

//returns true if cycle exits
bool dfs_cycle_util(vector<int> &vertex_list,vector<vector<int> > &adj_list,int start_vertex,vector<int> &top_sort) {
    bool res = false;
    auto it = adj_list[start_vertex].begin();
    for(it ; it < adj_list[start_vertex].end() ; it++) {
        if(vertex_list[*it] == 1)
            return res = true;
        else if(vertex_list[*it] == 0) {
            vertex_list[*it] = 1;
            res = res | dfs_cycle_util(vertex_list,adj_list,*it,top_sort);
        }
    }
    top_sort.push_back(start_vertex);
    vertex_list[start_vertex] = 2;
    return res;
}

bool dfs_cycle_exists(vector<int> &vertex_list,vector<vector<int> > &adj_list,vector<int> &top_sort) {
    for(int i = 1; i <= vertex_list.size()-1 ; i++) { //Vertices are labelled 1,2,3 .. n
        if(vertex_list[i] == 0) {
            vertex_list[i] = 1;
            if(dfs_cycle_util(vertex_list,adj_list,i,top_sort)) 
                return true;
        }
    }
    reverse(top_sort.begin(),top_sort.end());
    return false;
}

void dp_get_minimum_vertex_reachable(vector<int> &top_sort_list,vector<vector<int> >adj_list, vector<int> &minimum_vertex_reachable) {
    for(int i = 0; i < top_sort_list.size(); i++) {
        int vertex = top_sort_list[i];
        auto edge = adj_list[vertex].begin();
        while(edge < adj_list[vertex].end()) {
            minimum_vertex_reachable[*edge] = min({minimum_vertex_reachable[*edge],minimum_vertex_reachable[vertex],vertex});
            edge++;
        }
    }
    return ;
}

//For ease of indexing we have considered data structres of size (n+1) leaving out the 0 index.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<vector<int> > edge_list(n+1);
    vector<vector<int> > image_edge_list(n+1);
    vector<int> v_list(n+1,0);
    while(m--) {
        int v1,v2;
        cin >> v1 >> v2;
        edge_list[v1].push_back(v2);
        image_edge_list[v2].push_back(v1); //G transpose
    }

    vector<int> top_sort;
    if(dfs_cycle_exists(v_list,edge_list,top_sort)) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> min_vertex_reachable(n+1,n); //Initialise minimum index reachable to every vertex with n(max value)
    dp_get_minimum_vertex_reachable(top_sort,edge_list,min_vertex_reachable);

    reverse(top_sort.begin(),top_sort.end());
    vector<int> min_vertex_reachable_reverse(n+1,n); //Initialise minimum index reachable to every vertex with n(max value)
    dp_get_minimum_vertex_reachable(top_sort,image_edge_list,min_vertex_reachable_reverse);
    
    int max_universal_count = 0;
    string res = "";
    for(int i = 1 ; i <= n ; i++) {
        if(min(min_vertex_reachable[i],min_vertex_reachable_reverse[i]) >= i) {
            max_universal_count++;
            res.append("A");
        }
        else
            res.append("E");
    }
    cout << max_universal_count << '\n' << res << '\n';
    return 0;
}