/****************************************************/
// Filename: SegmentTree.cpp
// Created: Ryan Liao
// Date 8/13/2021
// Question: https://neoj.sprout.tw/problem/80/
/****************************************************/

/**
 * Segment Tree is a powerful data structure generally used to allow
 * range queries for array sum or max / min value. The sample code here
 * is written to range minimun queries. To modify the code to allow 
 * range sum or range maximun, simply change every line that has a min
 * between 2 values to max or sum between 2 values. For array length N, 
 * there will be a maximun of 2 * N nodes.
 */

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define F first;
#define S second;

/**
 * @brief Node struct for segment tree
 * @param val minimun value in the range [l, r)
 * @param l, r left bound & right bound of the segment
 * @param lson, rson index of the left and right child of the tree
 */
struct Node{
    int val;
    int l, r;
    int lson, rson;
};

const int N = 1000000 + 5;
int a[N];
Node st[2 * N];
int st_ptr = 0;

/**
 * @brief generates the segment in range [l, r)
 * @param l left bound
 * @param r right bound
 * @param index current index in the array
 * @Time Complexity O(N)
 */
void build(int l, int r, int index){
    st[index].l = l; st[index].r = r;
    if(l + 1 == r){
        st[index].val = a[l];
        return;
    }

    int mid = (st[index].l + st[index].r) / 2;
    st[index].lson = ++st_ptr;
    st[index].rson = ++st_ptr;

    build(l, mid, st[index].lson);
    build(mid, r, st[index].rson);

    st[index].val = min(st[st[index].lson].val, st[st[index].rson].val);
}

/**
 * @brief modifies the value within the segment tree
 * @param pos target index
 * @param nVal new value
 * @param index current index in the array
 * @Time Complexity O(logN)
 */
void modify(int pos, int nVal, int index){
    if(st[index].l + 1 == st[index].r){
        st[index].val = nVal;
        return;
    }

    int mid = (st[index].l + st[index].r) / 2;

    if(pos >= mid){
        modify(pos, nVal, st[index].rson);
    }
    else{
        modify(pos, nVal, st[index].lson);
    }

    st[index].val = min(st[st[index].lson].val, st[st[index].rson].val);
}

/**
 * @brief queries the segment tree and find the minimun value in range [l, r)
 * @param l left bound
 * @param r right value
 * @param index current index in the array
 * @return minimun value in range [l, r)
 * @Time Complexity O(logN)
 */
int query(int l, int r, int index){
    if(st[index].l == l && st[index].r == r){
        return st[index].val;
    }
    int mid = (st[index].l + st[index].r) / 2;

    if(l >= mid){
        return query(l, r, st[index].rson);
    }
    else if(r <= mid){
        return query(l, r, st[index].lson);
    }
    else{
        return min(query(l, mid, st[index].lson), query(mid, r, st[index].rson));
    }
}

// driver function
void solve(){
    int n, q; cin >> q >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    build(0, n, 0);
 
    for(int i = 0; i < q; i++){
        int s, x, y; cin >> s >> x >> y;
        if(s == 1){
            cout << query(x, y+1, 0) << endl;
        }
        else{
            modify(x, y, 0);
        }
    }   
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n = 1;
  while(n--){
    solve();
  }
}