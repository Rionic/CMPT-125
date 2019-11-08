#include <stdio.h>

// Post: Returns 1 iff target is in arr[0..len-1], 0 otherwise. 
int RecBinarySearch(int arr[], int len, int target){
    if(len <= 0) 
        return -1;

    int mid = len / 2;

    if(arr[mid] == target)
        return mid;
    if(target<arr[mid]){
        int left = RecBinarySearch(arr, mid, target);
        if (left==-1)
            return -1;
        else
            return left;
    } 
    else{
        int right = RecBinarySearch(arr+mid+1, len-mid-1, target);
        if (right==-1)
            return -1;
        else
            return mid+right+1;
    }
}