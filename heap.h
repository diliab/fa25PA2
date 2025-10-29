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
        upheap(size,weightArr);
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
        // making a temp value at the root
        int temp = weightArr[0];
        weightArr[0] = weightArr[size - 1];
        size --;
        downheap (0, weightArr);
        return temp;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int parentpos = (pos-1) / 2 ;
        while ( (weightArr[pos] < weightArr[parentpos]) && (pos != 0) ) {
            swap(weightArr[pos] , weightArr[parentpos]);
            pos = parentpos;
            parentpos = (pos - 1) / 2 ;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

        if (size <= 1) {
            return;
        }


        //establish the left and right child
        int leftchild = (2 * pos) + 1;
        int rightchild = (2 * pos) + 2;
        int smallestchild = pos;
        int tmp;

        while (true) {
            //establish the left and right child
            int leftchildpos = (2 * pos) + 1;
            int rightchildpos = (2 * pos) + 2;
            smallestchild = pos;

            //determine which child is the smallest
            if (leftchild < size && weightArr[leftchild] > weightArr[smallestchild]) {
                smallestchild = leftchild;
            }
            //checking right now
            if (rightchild < size && weightArr[rightchild] > weightArr[smallestchild]) {
                smallestchild = rightchild;
            }
            //check if smallest child is where pos is right now
            if (smallestchild == pos) {
                return;
            }
            swap(weightArr[pos] , weightArr[smallestchild]);
            pos = smallestchild;
            }
        }
    };

#endif