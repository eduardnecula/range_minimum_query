//  sparse table
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
 
// lookup[i][j] is going to store minimum
// value in arr[i..j]. Ideally lookup table
// size should not be fixed and should be
// determined using n Log n. It is kept
// constant to keep code simple.
int lookup[MAX][MAX];
 
// Fills lookup array lookup[][] in bottom up manner.
void buildSparseTable(int arr[], int n)
{
    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i][0] = arr[i];
 
    // Compute values from smaller to bigger intervals
    for (int j = 1; (1 << j) <= n; j++) {
 
        // Compute minimum value for all intervals with
        // size 2^j
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
 
            // For arr[2][10], we compare arr[lookup[0][7]]
            // and arr[lookup[3][10]]
            if (lookup[i][j - 1] <
                        lookup[i + (1 << (j - 1))][j - 1])
                lookup[i][j] = lookup[i][j - 1];
            else
                lookup[i][j] =
                         lookup[i + (1 << (j - 1))][j - 1];
        }
    }
}
 
// Returns minimum of arr[L..R]
int query(int L, int R)
{
    // Find highest power of 2 that is smaller
    // than or equal to count of elements in given
    // range. For [2, 10], j = 3
    int j = (int)log2(R - L + 1);
 
    // Compute minimum of last 2^j elements with first
    // 2^j elements in range.
    // For [2, 10], we compare arr[lookup[0][3]] and
    // arr[lookup[3][3]],
    if (lookup[L][j] <= lookup[R - (1 << j) + 1][j])
        return lookup[L][j];
 
    else
        return lookup[R - (1 << j) + 1][j];
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
        
        string a3 = "./out/p2/test";
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
                    if (arr != NULL) {
                       buildSparseTable(arr, n);
                       output_file << query(qs, qe) << endl;
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
