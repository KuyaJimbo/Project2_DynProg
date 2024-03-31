// Created by: James Ocampo

// Run with:
// g++ -o align FinalRecursiveMethod.cpp
// OR g++ -std=c++11 -o align FinalRecursiveMethod.cpp
// ./align

#include <iostream> // For cin, cout
#include <fstream> // For ifstream (file input), ofstream (file output)
#include <vector> // For vector (dynamic array)
#include <cmath> // For abs (absolute value)
#include <utility> // For pair (pair of values)
#include <algorithm> // For min (minimum value)
#include <cstdlib> // For exit (exit program)

using namespace std;
#define INF 1000000 // For infinity

// The Cell class holds is stored on the 3D array and holds the
// the minimum alignment value and the moves to get to that value
class Cell {
    public:
        int value; // The minimum alignment value
        vector<char> moves; // The moves to get to the minimum alignment value
};

ifstream SetUpInputFile() {
    ifstream inputFile("input.txt");
    
    // Check if the file is opened successfully
    if (!inputFile) {
        cout << "Unable to open file input.txt" << endl;
        exit(1);
    }
    return inputFile;
}

ofstream SetUpOutputFile() {
    ofstream outputFile("output.txt");
    return outputFile;
}

// TestPrintFinal is a function that prints the 3D array to the console
void TestPrintFinal(vector<vector<vector<Cell>>> Array_3D, int k, int m, int n) {
    // display 2D arrays that show the Cell value and the moves for each cell at each move number
    for (int move = 0; move < k; ++move) {
        cout << "Move: " << move << endl;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                cout << "Array_3D[" << r << "][" << c << "][" << move << "]: ";
                cout << "Value: "<< Array_3D[r][c][move].value << " Moves: ";
                for (char move_char : Array_3D[r][c][move].moves) {
                    cout << move_char << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}

Cell CalculateCell(int r, int c, int move, int k, int m, int n, vector<vector<int>>& matrix, vector<int>& sequence, vector<vector<vector<Cell>>>& Array_3D) {
    // Base case: if the value is already calculated, return the value
    if (Array_3D[r][c][move].value != -1) {
        return Array_3D[r][c][move];
    }
    // Calculate the absolute difference between the matrix value and the sequence value
    int start_diff = abs(matrix[r][c] - sequence[k-1-move]);
    // If it is the last move, set the value to the absolute difference
    if (move == 0) {
        Array_3D[r][c][move].value = start_diff;
        return Array_3D[r][c][move];
    }
    // Recursive case: if the value is not calculated, calculate the value
    char best_move_char; // Keep track of the best move character
    int best_move_value = INF; // Set the best move value to infinity for comparison
    // Define the directions and their corresponding move characters
    std::pair<int, int> directions[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    // NOTE: D is {1, 0} because adding to the row moves down
    char direction_chars[] = {'D', 'L', 'U', 'R'};
    // Loop over each direction to find the best move
    for (int i = 0; i < 4; ++i) {
        int new_r = r + directions[i].first;
        int new_c = c + directions[i].second;
        // Check if the move is possible
        if (new_r >= 0 && new_r < m && new_c >= 0 && new_c < n) {
            // Check if the move is better than the current best move
            int new_value = CalculateCell(new_r, new_c, move - 1, k, m, n, matrix, sequence, Array_3D).value;
            if (new_value < best_move_value) {
                best_move_char = direction_chars[i]; // Update the best move character
                best_move_value = new_value; // Update the best move value
            }
        }
    }
    // update the cell value with the sum of the start_diff and the best move value
    // this ensures that at each move, the cell value is the minimum alignment value
    // if we start at the current cell
    Array_3D[r][c][move].value = start_diff + best_move_value;
    // add the best move to the moves vector
    Array_3D[r][c][move].moves.push_back(best_move_char);
    // Find the cell with the best move and copy the moves to the current cell
    for (int i = 0; i < 4; ++i) {
        if (best_move_char == direction_chars[i]) {
            int new_r = r + directions[i].first;
            int new_c = c + directions[i].second;
            // copy the moves from the best move cell to the current cell
            for (char move_char : CalculateCell(new_r, new_c, move - 1, k, m, n, matrix, sequence, Array_3D).moves) {
                Array_3D[r][c][move].moves.push_back(move_char);
            }
        }
    }
    return Array_3D[r][c][move];
}

int main() {
    // ----------------- Set up the input file -----------------
    ifstream inputFile = SetUpInputFile();
    
    // -------------- Set up the output file --------------
    ofstream outputFile = SetUpOutputFile();

    // -------------- Read the input from the file --------------
    int k; // Length of the sequence
    int m; // Number of rows in the matrix
    int n; // Number of columns in the matrix

    // First three integers from inputFile are read as k, m, and n
    inputFile >> k >> m >> n;
    
    // sequence is stored in a vector with length k
    vector<int> sequence(k);
    // The next k integers in the inputFile are stored in the sequence vector
    for (int i = 0; i < k; ++i) {
        inputFile >> sequence[i];
    }

    // matrix is a 2D vector m rows and n columns storing the matrix values
    vector<vector<int>> matrix(m, vector<int>(n));
    // The next m*n integers in the inputFile are stored in the matrix vector
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    // -------------- Close the Input File --------------
    inputFile.close();

    // -------------- Create the 3D Array --------------
    // Create the 3D array as [row][column][move] which contains a Cell object
    vector<vector<vector<Cell>>> Array_3D(m, vector<vector<Cell>>(n, vector<Cell>(k)));

    // -------------- Calculate the alignment for each cell and move recursively --------------
    // initialize the 3D array with the base case values of all -1
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            for (int move = 0; move < k; ++move) {
                Array_3D[r][c][move].value = -1;
            }
        }
    }

    int best_r = 0;
    int best_c = 0;
    int best_value = INF;
    // Calculate alignment for each cell and move recursively
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            Array_3D[r][c][k-1] = CalculateCell(r, c, k - 1, k, m, n, matrix, sequence, Array_3D);
            // Keep track of the cell with the minimum value in the last move
            if (Array_3D[r][c][k-1].value < best_value) {
                best_r = r;
                best_c = c;
                best_value = Array_3D[r][c][k-1].value;
            }
        }
    }

    // -------------- TestPrintFinal --------------
    // TestPrintFinal(Array_3D, k, m, n);

    // -------------- Output the results to the file --------------
    // output the minimum value in the last move
    outputFile << best_value << endl;
    // output the row and column of the minimum value in the last move
    outputFile << best_r+1 << " " << best_c+1 << endl;
    // output the sequence of moves to get to the minimum value in the last move
    for (char best_move : Array_3D[best_r][best_c][k-1].moves) {
        outputFile << best_move << " ";
    }
    outputFile << endl;

    // -------------- Close the Output File --------------
    outputFile.close();

    return 0;
}
