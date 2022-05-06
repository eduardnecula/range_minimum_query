// square root decomposition
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <fstream>
#include <iostream>

using namespace std;

#define NR_TESTE 60
#define MAX 11000
 
// lookup[i][j] is going to
// store index of minimum value in
// arr[i..j]. Ideally lookup
// table size should not be fixed
// and should be determined using
// n Log n. It is kept
// constant to keep code simple.
int lookup[MAX][MAX];
 
// Structure to represent a query range
struct Query {
    int L, R;
};
 
// Fills lookup array
// lookup[][] in bottom up manner.
void preprocess(int arr[], int n)
{
    // Initialize M for the
    // intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i][0] = i;
 
    // Compute values from smaller
    // to bigger intervals
    for (int j = 1; (1 << j) <= n; j++)
    {
        // Compute minimum value for
        // all intervals with size
        // 2^j
        for (int i = 0; (i + (1 << j) - 1) < n; i++)
        {
            // For arr[2][10], we
            // compare arr[lookup[0][3]]
            // and arr[lookup[3][3]]
            if (arr[lookup[i][j - 1]]
                < arr[lookup[i + (1 << (j - 1))][j - 1]])
                lookup[i][j] = lookup[i][j - 1];
            else
                lookup[i][j]
                    = lookup[i + (1 << (j - 1))][j - 1];
        }
    }
}
 
// Returns minimum of arr[L..R]
int query(int arr[], int L, int R)
{
    // For [2,10], j = 3
    int j = (int)log2(R - L + 1);
 
    // For [2,10], we compare arr[lookup[0][3]] and
    // arr[lookup[3][3]],
    if (arr[lookup[L][j]]
        <= arr[lookup[R - (1 << j) + 1][j]])
        return arr[lookup[L][j]];
 
    else
        return arr[lookup[R - (1 << j) + 1][j]];
}
 
// Prints minimum of given
// m query ranges in arr[0..n-1]
int RMQ(int arr[], int n, Query q[], int m)
{
    // Fills table lookup[n][Log n]
    preprocess(arr, n);
 
    // One by one compute sum of all queries
    for (int i = 0; i < m; i++)
    {
        // Left and right boundaries
        // of current range
        int L = q[i].L, R = q[i].R;
        return query(arr, L, R);
    }
    return -1;
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
        
        string a3 = "./out/p1/test";
        string a4 = ".out";
        string final_out = a3 + aux + a4;

        //  deschidere fisier iesire
        output_file.open(final_out);

        // //  cod pe care il voi apela
        int n = 0, qs, qe, aux2 = 0, m = 0;
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
                if (qs > 0 && qe > 0) {
                    Query q[m / 2] = {0, 0};
                    for (int i = 0; i < m / 2; i++) {
                        q[i].L = qs;
                        q[i].R = qe;
                    }
                    if (arr != NULL && q != NULL) {
                        output_file << RMQ(arr, n, q, m / 2) << endl;
                    }
                }
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
