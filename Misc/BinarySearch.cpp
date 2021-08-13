/****************************************************/
// Filename: BinarySearch.cpp
// Created: Ryan Liao
// Date 8/13/2021
/****************************************************/

/**
 * This is a general binary search algorithm, which can be efficiently used to search
 * for the maximun valid number given a check function. Note that binary search only
 * works when the function is strictly increasing.
 */

/*
 * @brief checks whether a value is valid
 * @param val value to be checked
 */
bool check(int val){
    // To be implemented
}

/*
 * @brief binary searches the range [0, n)
 * @param n the maximun value to be checked
 * @return the maximun index that is valid
 */
int binarySearch(int n){
    int l = 0, r = n;
    while(l + 1 != r){
        int mid = (l + r) / 2;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid;
        }
    }

    return l;  
}