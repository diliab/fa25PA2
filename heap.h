//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() {
        size = 0;
    }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        weightArr[size] = idx;
        upheap(size , weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()

        // base case 0
        if (size <= 0) {
            return -1;
        }
        // deleting first index in array
        int temp = weightArr[size-1];


        downheap(size , weightArr);

    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int parentpos = (pos-1) / 2 ;
        while ( (weightArr[pos] < weightArr[parentpos]) && (parentpos != 0) ) {
            swap(weightArr[pos] , weightArr[parentpos]);
            pos = parentpos;
            parentpos = (pos - 1) / 2 ;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int leftchild = (2 * 0) + 1;
        int rightchild = (2 * 0) + 2;
        if (size >= 1) {
            return;
        }
        // if two elelmtents
        if (weightArr[leftchild] > weightArr[pos]) {
            swap(weightArr[leftchild] , weightArr[pos]);
        }


        while (leftchild < size && weightArr[leftchild] > weightArr[leftchild]) {
            if (weightArr[leftchild] > weightArr[rightchild]) {
                swap(weightArr[leftchild] , weightArr[pos]);
            } else if (weightArr[rightchild] > weightArr[leftchild]) {
                swap(weightArr[rightchild] , weightArr[pos]);
            }

        }
    }
};

#endif