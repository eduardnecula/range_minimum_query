// segment tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <fstream>
#include <iostream>

using namespace std;
#define NR_TESTE 60

// A utility function to get minimum of two numbers
int minVal(int x, int y) { return (x < y)? x: y; }
 
// A utility function to get the
// middle index from corner indexes.
int getMid(int s, int e) { return s + (e -s)/2; }
 
/* A recursive function to get the
minimum value in a given range
of array indexes. The following
are parameters for this function.
 
    st --> Pointer to segment tree
    index --> Index of current node in the
           segment tree. Initially 0 is
           passed as root is always at index 0
    ss & se --> Starting and ending indexes
                of the segment represented
                by current node, i.e., st[index]
    qs & qe --> Starting and ending indexes of query range */
int RMQUtil(int *st, int ss, int se, int qs, int qe, int index)
{
    // If segment of this node is a part
    // of given range, then return
    // the min of the segment
    if (qs <= ss && qe >= se)
        return st[index];
 
    // If segment of this node
    // is outside the given range
    if (se < qs || ss > qe)
        return INT_MAX;
 
    // If a part of this segment
    // overlaps with the given range
    int mid = getMid(ss, se);
    return minVal(RMQUtil(st, ss, mid, qs, qe, 2*index+1),
                RMQUtil(st, mid+1, se, qs, qe, 2*index+2));
}
 
// Return minimum of elements in range
// from index qs (query start) to
// qe (query end). It mainly uses RMQUtil()
int RMQ(int *st, int n, int qs, int qe)
{
    // Check for erroneous input values
    if (qs < 0 || qe > n-1 || qs > qe)
    {
        return -1;
    }
 
    return RMQUtil(st, 0, n-1, qs, qe, 0);
}
 
// A recursive function that constructs
// Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int constructSTUtil(int arr[], int ss, int se,
                                int *st, int si)
{
    // If there is one element in array,
    // store it in current node of
    // segment tree and return
    if (ss == se)
    {
        st[si] = arr[ss];
        return arr[ss];
    }
 
    // If there are more than one elements,
    // then recur for left and right subtrees
    // and store the minimum of two values in this node
    int mid = getMid(ss, se);
    st[si] = minVal(constructSTUtil(arr, ss, mid, st, si*2+1),
                    constructSTUtil(arr, mid+1, se, st, si*2+2));
    return st[si];
}

/* Function to construct segment tree
from given array. This function allocates
memory for segment tree and calls constructSTUtil() to
fill the allocated memory */
int *constructST(int arr[], int n)
{
    // Allocate memory for segment tree
 
    //Height of segment tree
    int x = (int)(ceil(log2(n)));
 
    // Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1;
 
    int *st = new int[max_size];
 
    // Fill the allocated memory st
    constructSTUtil(arr, 0, n-1, st, 0);
 
    // Return the constructed segment tree
    return st;
}

int main () {
    ifstream input_file;
    ofstream output_file;
    int *arr;

    for (int i = 0; i <= NR_TESTE; i++) {
        std::string aux = std::to_string(i);

        string a1 = "./in/test";
        string a2 = ".in";
        string final = a1 + aux + a2;

        //  deschidere fisier intrare
        input_file.open(final);
        
        string a3 = "./out/best/test";
        string a4 = ".out";
        string final_out = a3 + aux + a4;

        //  deschidere fisier iesire
        output_file.open(final_out);
        
        // //  cod pe care il voi apela
        int n = 0, qs, qe, aux2 = 0, m;
        input_file >> n;  //  nr elemente
        input_file >> m;  //  nr interogari
        
        arr = (int *) malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            input_file >> aux2;
            arr[i] = aux2;
        }
        //  m interogari
        if (n > 0 && m > 0) {
            for (int i = 0; i < m; i++) {
                input_file >> qs;
                input_file >> qe;

                int *st = constructST(arr, n);
                output_file << RMQ(st, n, qs, qe) << endl;
            }
        }

        //  inchidere fisiere deschise
        input_file.close();
        output_file.close();

        //  eliberare memorie
        free(arr);
    }

    return 0;
}
