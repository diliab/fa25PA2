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
        if (size >= 64) {
            return;
        }

        data[size] = idx;
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
        int smallestind = data[0];
        //move the last element into the root spot
        data[0] = data[size-1];
        size --;
        downheap (0, weightArr);
        return smallestind;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (pos == 0 ) {
            return;
        }
        //using the node index
        while (pos > 0) {
            int parentpos = (pos - 1) / 2 ;
            if ( (weightArr[data[pos]] < weightArr[data[parentpos]]) ) {
                swap(data[pos] , data[parentpos]);
                pos = parentpos;
            } else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

        while (true) {
            //establish the left and right child
            int leftchild = (2 * pos) + 1;
            int rightchild = (2 * pos) + 2;

            int smallestchild = pos;
            int tmp;

            //determine which child is the smallest
            if (leftchild < size && weightArr[data[leftchild]] < weightArr[data[smallestchild]]) {
                smallestchild = leftchild;
            }
            //checking right child
            if (rightchild < size && weightArr[data[rightchild]] < weightArr[data[smallestchild]]) {
                smallestchild = rightchild;
            }
            //check if smallest child is where pos is right now
            if (smallestchild == pos) {
                return;
            }
            swap(data[pos] , data[smallestchild]);
            pos = smallestchild;
            }
        }
    };

#endif