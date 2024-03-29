7. Give pseudocode for an iterative algorithm for the problem.
Input: 
- A matrix with m rows and n columns. 
- A sequence with length k
Output: 
The minimum absolute difference between the sum of each pair of elements in the sequence and the elements in the matrix.
function min_absolute_different
    let m be the number of rows in the matrix
    let n be the number of columns in the matrix
    let k be the length of the sequence

    let dp be a 3D array of size m x n x k

    dp[m][n][k] is the minimum absolute difference of the alignment of the sequence with the matrix that has the length k and end at (m,n)
    
    initialize dp with infinity

    base case: dp[m][n][1] = abs(matrix[m][n] - sequence[0]) for all m, n because the minimum absolute difference of the alignment of the sequence with the matrix that has the length 1 and end at (m,n) is the absolute difference between the element in the matrix and the element in the sequence

    for l from 2 to k:
        we go through all the neighbor of the cell (i,j) in the matrix and check its minimum absolute difference with the sequence of the length l - 1
                dp[i][j][l] = minimum of dp[i][j][l-1] + abs(matrix[i][j] - sequence[l-1]) or dp[i][j][l] for all i, j
    
    go through all the cells in the matrix and find the minimum absolute difference of the alignment of the sequence with the matrix that has the length k and end at (m,n)

8. How could you modify your solution to problem of identifying the minimum absolute differ- ence to actually locate the alignment in the grid? You may answer this question by giving pseudocode for an algorithm that computes and returns the alignment, or you may describe (in English) how to modify the iterative or memoized algorithm.

To locate the alignment in the grid, we can keep track of the previous cell that gives the minimum absolute difference for the alignment of the sequence with the matrix that has the length k and end at (m,n). We can store the previous cell in a 3D array called prev. We can then backtrack from the end cell to the start cell to find the alignment.

For example in the iterative algorithm, we can modify the algorithm as follows:
- instead of dp[m][n][k] = 0, we set dp[m][n][k] = (0, [(1,2), (2,3), (3,4), (4,5)]) where 0 is the minimum absolute difference and [(1,2), (2,3), (3,4), (4,5)] is the alignment of the sequence with the matrix that has the length k and end at (m,n)

9. Can the space complexity of your iterative solution for finding the minimum score or alignment be reduced? Why or why not?

The space complexity of the iterative solution is O(mnk), where m is the number of rows in the matrix, n is the number of columns, and k is the length of the sequence. This is because we're storing the minimum absolute difference (or the alignment in the modified version) for each possible length of sequence for each cell in the matrix.

Reducing this space complexity is challenging because each state in our dynamic programming solution is dependent on multiple previous states. For example, the state at dp[i][j][l] depends on the states at dp[ni][nj][l-1] for all neighboring cells (ni, nj). This means we can't easily discard previous states after using them, as we might need them again for future states.