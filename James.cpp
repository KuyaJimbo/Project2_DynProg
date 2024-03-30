// g++ -o align *.cpp
#include <iostream> // For cin, cout
#include <fstream> // For ifstream (file input)
#include <vector> // For vector (dynamic array)

using namespace std;

#define INF 1000000

// create a class called cell which as an int for the value and a vector of char for the moves
class Cell {
    public:
        int value;
        vector<char> moves;
};

void verify_input(int k, int m, int n, vector<int> sequence, vector<vector<int>> matrix) {
    cout << "Input verification:" << endl;
    cout << "k (length of the sequence): " << k << endl;
    cout << "m (number of rows in the matrix): " << m << endl;
    cout << "n (number of columns in the matrix): " << n << endl;

    cout << "Sequence: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Matrix:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl << endl;
    }
}

void verify_3D_array(vector<vector<vector<int>>> Array_3D) {
    cout << "3D Array:" << endl;
    for (int r = 0; r < Array_3D.size(); ++r) {
        for (int c = 0; c < Array_3D[r].size(); ++c) {
            for (int seq = 0; seq < Array_3D[r][c].size(); ++seq) {
                cout << Array_3D[r][c][seq] << " ";
            }
            cout << "| ";
        }
        cout << endl;
    }
}


int main() {

    // ----------------- Set up the input file -----------------
    
    // cout << "Enter the file name: ";
    // string fileName;
    // cin >> fileName;

    // ifstream inputFile(fileName);
    ifstream inputFile("sample-input1.txt");
    //ifstream inputFile("sample-input2.txt");

    // Check if the file is opened successfully
    if (!inputFile) {
        cout << "Unable to open file input.txt" << endl;
        return 1;
    }

    // -------------- Read the input from the file --------------

    // Create variables to store the input values
    int k; // Length of the sequence
    int m; // Number of rows in the matrix
    int n; // Number of columns in the matrix
    inputFile >> k >> m >> n; // Reads the first three integers from inputFile as k, m, and n
    
    // Create a vector to store the sequence with length k
    vector<int> sequence(k);
    // Read the next k integers in the file and store them in the sequence vector
    for (int i = 0; i < k; ++i) {
        inputFile >> sequence[i];
    }

    // Create a 2D vector to store the matrix with m rows and n columns
    vector<vector<int>> matrix(m, vector<int>(n));
    // Read the next m*n integers in the file and store them in the matrix vector
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }
    // -------------- Output the input for verification --------------

    // verify_input(k, m, n, sequence, matrix);
    // cout << "**********************************************" << endl;

    // -------------- Close the file --------------
    
    inputFile.close();
    
    // -------------- Create the 3D Array --------------

    // Create the 3D array as [row][column][move] which contains a Cell object
    vector<vector<vector<Cell>>> Array_3D(m, vector<vector<Cell>>(n, vector<Cell>(k)));
    for (int move = 0; move < k; ++move) {
        // check the move number
        // cout << "Move: " << move << endl;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                // check the row and column
                // cout << "Row: " << r << " Column: " << c << endl;    
                int start_diff = abs(matrix[r][c] - sequence[k-1-move]);
                
                // check the start_diff value
                // cout << "Start diff: " << start_diff << endl;
                
                if (move == 0) {
                    Array_3D[r][c][move].value = start_diff;
                    // check the value of the cell
                    // cout << "Value: " << Array_3D[r][c][move].value << " ";
                    
                    Array_3D[r][c][move].moves.push_back('E');
                    // check the moves vector
                    // cout << "Moves: S" << endl;
                } else {
                    char best_move_char;
                    int best_move_value = INF;

                    // check if up is possible
                    if (r+1 < m) {
                        if (Array_3D[r+1][c][move-1].value < best_move_value) {
                            best_move_char = 'U';
                            best_move_value = Array_3D[r+1][c][move-1].value;
                        }
                    }
                    // check if left is possible
                    if (c-1 >= 0) {
                        if (Array_3D[r][c-1][move-1].value < best_move_value) {
                            best_move_char = 'L';
                            best_move_value = Array_3D[r][c-1][move-1].value;
                        }
                    }
                    // check if down is possible
                    if (r-1 >= 0) {
                        if (Array_3D[r-1][c][move-1].value < best_move_value) {
                            best_move_char = 'D';
                            best_move_value = Array_3D[r-1][c][move-1].value;
                        }
                    }
                    // check if right is possible
                    if (c+1 < n) {
                        if (Array_3D[r][c+1][move-1].value < best_move_value) {
                            best_move_char = 'R';
                            best_move_value = Array_3D[r][c+1][move-1].value;
                        }
                    }
                    // update the cell with the best move
                    Array_3D[r][c][move].value = start_diff + best_move_value;

                    // check the value of the cell
                    // cout << "Array_3D[" << r << "][" << c << "][" << move << "].value: " << Array_3D[r][c][move].value << endl;
                    
                    // add the best move to the moves vector
                    Array_3D[r][c][move].moves.push_back(best_move_char);
                    // add the moves from the best move cell
                    if (best_move_char == 'U') {
                        for (char prev_move : Array_3D[r+1][c][move-1].moves) {
                            Array_3D[r][c][move].moves.push_back(prev_move);
                        }
                    }
                    if (best_move_char == 'L') {
                        for (char prev_move : Array_3D[r][c-1][move-1].moves) {
                            Array_3D[r][c][move].moves.push_back(prev_move);
                        }
                    }
                    if (best_move_char == 'D') {
                        for (char prev_move : Array_3D[r-1][c][move-1].moves) {
                            Array_3D[r][c][move].moves.push_back(prev_move);
                        }
                    }
                    if (best_move_char == 'R') {
                        for (char prev_move : Array_3D[r][c+1][move-1].moves) {
                            Array_3D[r][c][move].moves.push_back(prev_move);
                        }
                    }
                    
                    // check the moves vector
                    // cout << "Array_3D[" << r << "][" << c << "][" << move << "].moves: ";
                    // for (char move_char : Array_3D[r][c][move].moves) {
                    //     cout << move_char << " ";
                    // }
                    // cout << endl;
                    

                }
            }
        }
        cout << endl;
    }

    // -------------- TestPrint --------------
    // display 2D arrays that show the Cell value and the moves for each cell at each move number
    for (int move = 0; move < k; ++move) {
        cout << "Move: " << move << endl;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                cout << "Array_3D[" << r << "][" << c << "][" << move << "]: " << Array_3D[r][c][move].value << " ";
                for (char move_char : Array_3D[r][c][move].moves) {
                    cout << move_char << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    

    return 0;
}
