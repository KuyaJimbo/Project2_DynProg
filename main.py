def min_abs_difference(sequence: list, matrix: list) -> int:
    """
    Given a sequence of integers and a 2D matrix of integers, find the minimum absolute difference
    """
    # m = number of rows, n = number of columns, k = length of sequence
    m, n, k = len(matrix), len(matrix[0]), len(sequence)
    # dp[i][j][l] = minimum absolute difference for a path of length l ending at (i, j)
    dp = [[[(float('inf'),[])] * (k + 1) for _ in range(n)] for _ in range(m)]
    
    # Base case: Fill in for l = 1
    for i in range(m):
        for j in range(n):
            dp[i][j][1] = (abs(sequence[0] - matrix[i][j]), [(i, j)])
    
    # Build up the solution for each l from 2 to k
    for l in range(2, k + 1):
        for i in range(m):
            for j in range(n):
                min_dif = float('inf')
                for di, dj in [(-1, 0), (1, 0), (0, -1), (0, 1)]: # Up, Down, Left, Right
                    ni, nj = i + di, j + dj
                    if 0 <= ni < m and 0 <= nj < n: # Check bounds
                        if dp[ni][nj][l-1][0] + abs(sequence[l-1] - matrix[i][j]) < min_dif:
                            min_dif = dp[ni][nj][l-1][0] + abs(sequence[l-1] - matrix[i][j])
                            dp[i][j][l] = (min_dif, dp[ni][nj][l-1][1] + [(i, j)])
    
    # Find the minimum value for l = k
    min_diff = float('inf')
    for i in range(m):
        for j in range(n):
            if dp[i][j][k][0] < min_diff:
                min_diff = dp[i][j][k][0]
                path = dp[i][j][k][1]
    
    # Convert path to string
    path_list = ""
    for i in range(len(path) - 1):
        if (path[i][0] + 0, path[i][1] + 1) == path[i+1]:
            path_list += 'R '
        elif (path[i][0] + 0, path[i][1] - 1) == path[i+1]:
            path_list += 'L '
        elif (path[i][0] + 1, path[i][1] + 0) == path[i+1]:
            path_list += 'D '
        else:
            path_list += 'U '
        
    return min_diff, (path[0][0] + 1, path[0][1] + 1), path_list

sequence = [1, 4, 1, 16, 20]

matrix = [
    [4, 1, 20, 16, 1],
    [1, 5, 16, 5, 8],
    [1, 8, 1, 4, 19],
    [4, 20, 5, 1, 16],
    [14, 5, 4, 4, 1]
]

# sequence = [2, 1, 14, 1, 14, 1]
# matrix = [[2, 1, 14]]
print(min_abs_difference(sequence, matrix))
