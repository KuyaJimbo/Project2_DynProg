def min_abs_difference(sequence: list, matrix: list) -> int:
    """
    Given a sequence of integers and a 2D matrix of integers, find the minimum absolute difference
    """
    # m = number of rows, n = number of columns, k = length of sequence
    m, n, k = len(matrix), len(matrix[0]), len(sequence)
    # dp[i][j][l] = minimum absolute difference for a path of length l ending at (i, j)
    dp = [[[float('inf')] * (k + 1) for _ in range(n)] for _ in range(m)]
    
    # Base case: Fill in for l = 1
    for i in range(m):
        for j in range(n):
            dp[i][j][1] = abs(sequence[0] - matrix[i][j])
    
    # Build up the solution for each l from 2 to k
    for l in range(2, k + 1):
        for i in range(m):
            for j in range(n):
                for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]: # Up, Down, Left, Right
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n: # Check bounds
                        dp[i][j][l] = min(dp[i][j][l], dp[ni][nj][l-1] + abs(sequence[l-1] - matrix[i][j]))
    
    # Find the minimum value for l = k
    min_diff = min(dp[i][j][k] for i in range(m) for j in range(n))
    return min_diff

sequence = [1, 4, 1, 16, 20]
matrix = [
    [4, 1, 20, 16, 1],
    [1, 5, 16, 5, 8],
    [1, 8, 1, 4, 19],
    [4, 20, 5, 1, 16],
    [14, 5, 4, 4, 1]
]
print(min_abs_difference(sequence, matrix))
