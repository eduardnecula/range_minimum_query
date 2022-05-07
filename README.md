@ 2021
Necula Eduard-Ionut 332CA
Polytechnic, Automation and Computers, CTI

Topic: Range Minimum Query

The test files (from the in file) have the following structure:

N - number of elements
M - number of pairs
N numbers
M pairs of numbers (x, y)
(X, Y) represents the pair for the starting point and the end point where
we are looking for the element

After running the tests are displayed in the .out file

Tests:
1 - 10
31 - 40
I generated tests with the above structure for the case
when N >> M

Tests:
11-20
41 - 50
I am for the case when N = M

Tests:
21 - 30
51 - 60
I am for the case when N <= M

    I generated the random numbers for N with the link below,
and the pairs (x, y) were generated with a site, link below.

    The code was taken from geeksforgeeks, except for reading in .in tests and writing
in the specific .out files for each algorithm.

    The code written in var1.cpp represents the implementation of the range minimum query code,
using tree segment.
    The code written in var2.cpp represents the implementation of the range minimum query code,
using square root decomposition
    The code written in var3.cpp represents the implementation of the range minimum query code,
using scattered sheets.

    The "make run-best" command is for the code that uses the tree segment (var1.cpp), being the most efficient code.
I tested it with "time make run-best", everything runs on my car in a second.

    The "make run-p1" command is for the code that uses square root decomposition (var2.cpp), being the least
efficient code, running on personal car in 7 seconds.

    The "make run-p2" command is for code that uses sparse tables (var3.cpp), it is very close to execution
with var1.cpp, running the code in 1.5 seconds.

The used car has 4 cores with 8 threads, an i7 from the 7th generation, with 4 gb of ram.

! The code generates a test0.out file, ignore it.

Code used in the tree segment:
https://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/

The code used for square root decomposition:
https://www.geeksforgeeks.org/range-minimum-query-for-static-array/

Code used for sparse tables:
https://www.geeksforgeeks.org/sparse-table/

To generate pairs of numbers:
https://onlineintegertools.com/generate-integer-pairs

For random numbers:
https://numbergenerator.org/randomnumbergenerator#!numbers=30&low=1&high=1000000&unique=true&csv=nl&oddeven=&oddqty=0&sorted=false&addfilters=