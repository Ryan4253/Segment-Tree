/****************************************************/
// Filename: SegmentTree_LazyTag.cpp
// Created: Ryan Liao
// Date 8/13/2021
// Question: https://neoj.sprout.tw/problem/367/
/****************************************************/
   
/**
 * By using a niche technique called lazy propagation, it is possible to make segment tree
 * support modification within a range (usually adding a constant value n between the range)
 * and still have good time complexity. Essentially, it stores each modification on the top
 * node as a special "tag", and the changes will be pushed further down the segment tree each
 * time the node is called. This is possible since max, min and sum changes can all be calculated
 * when the range is modified together with one number.
 * 
 * Range Sum -> value += tag * (r - l) (you may want to use long long for val and tag)
 * Range max / min -> value += tag
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
 * @param tag current tag (values to be modified) of the node
 * @param l, r left bound & right bound of the segment
 * @param lson, rson index of the left and right child of the tree
 */
struct Node{
    int val, tag;
    int l, r;
    int lson, rson;
};

const int N = 100000 + 5;
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

    st[index].val = max(st[st[index].lson].val, st[st[index].rson].val);
}

/**
 * @brief updates lazy propagation data into value, and pushes the data downward
 * @param index the segment tree index to update
 * @Time Complexity O(1)
 */
void push(int index){
    st[index].val += st[index].tag;
    if(st[index].l + 1 != st[index].r){
        st[st[index].lson].tag += st[index].tag;
        st[st[index].rson].tag += st[index].tag;
    }
    st[index].tag = 0;
}

/**
 * @brief adds val to every value in the segment [l, r)
 * @param l left bound
 * @param r right bound
 * @param val value to add
 * @param index current index in the array
 * @Time Complexity O(logN)
 */
void modify(int l, int r, int val, int index){
    push(index);
    if(st[index].l == l && st[index].r == r){
        st[index].tag = val;
        return;
    }

    int mid = (st[index].l + st[index].r) / 2;

    if(l >= mid){
        modify(l, r, val, st[index].rson);
    }
    else if(mid >= r){
        modify(l, r, val, st[index].lson);
    }
    else{
        modify(l, mid, val, st[index].lson);
        modify(mid, r, val, st[index].rson);
    }

    st[index].val = max(st[st[index].lson].val + st[st[index].lson].tag, st[st[index].rson].val + st[st[index].rson].tag);
}

/**
 * @brief queries the segment tree and find the maximun value in range [l, r)
 * @param l left bound
 * @param r right value
 * @param index current index in the array
 * @return maximun value in range [l, r)
 * @Time Complexity O(logN)
 */
int query(int l, int r, int index){
    push(index);
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
        return max(query(l, mid, st[index].lson), query(mid, r, st[index].rson));
    }
}

// driver function
void solve(){
    int n, q; cin >> n >> q;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    build(0, n, 0);
 
    for(int i = 0; i < q; i++){
        int s, l, r; cin >> s >> l >> r;
        if(s == 2){
            cout << query(l-1, r, 0) << endl;
        }
        else{
            int x; cin >> x;
            modify(l-1, r, x, 0);
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