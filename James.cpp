// g++ -o align *.cpp
#include <iostream> // For cin, cout
#include <fstream> // For ifstream (file input), ofstream (file output)
#include <vector> // For vector (dynamic array)

using namespace std;

#define INF 1000000

class Cell {
    public:
        int value;
        vector<char> moves;
};

// return both the input file
ifstream SetUpInputFile() {
    cout << "Enter the file name: ";
    string fileName;
    cin >> fileName;
    ifstream inputFile(fileName);
    // ifstream inputFile("sample-input1.txt");
    // ifstream inputFile("sample-input2.txt");

    // Check if the file is opened successfully
    if (!inputFile) {
        cout << "Unable to open file input.txt" << endl;
        exit(1);
    }
    return inputFile;
}

// create an output file
ofstream SetUpOutputFile() {
    cout << "Enter the output file name: ";
    string fileName;
    cin >> fileName;
    ofstream outputFile(fileName);

    //ofstream outputFile("output.txt");
    return outputFile;
}

void TestPrintFinal(vector<vector<vector<Cell>>> Array_3D, int k, int m, int n) {
    // display 2D arrays that show the Cell value and the moves for each cell at each move number
    for (int move = 0; move < k; ++move) {
        cout << "Move: " << move << endl;
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                cout << "Array_3D[" << r << "][" << c << "][" << move << "]: " << "Value: "<< Array_3D[r][c][move].value << " Moves: ";
                for (char move_char : Array_3D[r][c][move].moves) {
                    cout << move_char << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}


int main() {
    // ----------------- Set up the input file -----------------
    ifstream inputFile = SetUpInputFile();

    // -------------- Set up the output file --------------
    ofstream outputFile = SetUpOutputFile();

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

    // Create a 2D vector to store the matrix with m rows and n columns storing the matrix values
    vector<vector<int>> matrix(m, vector<int>(n));
    // Read the next m*n integers in the file and store them in the matrix vector
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
    for (int move = 0; move < k; ++move) {
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                int start_diff = abs(matrix[r][c] - sequence[k-1-move]);

                if (move == 0) {
                    Array_3D[r][c][move].value = start_diff;

                } else {
                    char best_move_char;
                    int best_move_value = INF;

                    // Define the directions and their corresponding move characters
                    std::pair<int, int> directions[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
                    // NOTEEEE
                    char direction_chars[] = {'D', 'L', 'U', 'R'};

                    // Loop over each direction
                    for (int i = 0; i < 4; ++i) {
                        int new_r = r + directions[i].first;
                        int new_c = c + directions[i].second;

                        // Check if the move is possible
                        if (new_r >= 0 && new_r < m && new_c >= 0 && new_c < n) {
                            if (Array_3D[new_r][new_c][move-1].value < best_move_value) {
                                best_move_char = direction_chars[i];
                                best_move_value = Array_3D[new_r][new_c][move-1].value;
                            }
                        }
                    }
                    // update the cell with the best move
                    Array_3D[r][c][move].value = start_diff + best_move_value;

                    // add the best move to the moves vector
                    Array_3D[r][c][move].moves.push_back(best_move_char);

                    // Loop over each direction
                    for (int i = 0; i < 4; ++i) {
                        if (best_move_char == direction_chars[i]) {
                            int new_r = r + directions[i].first;
                            int new_c = c + directions[i].second;

                            // Check if the move is possible
                            if (new_r >= 0 && new_r < m && new_c >= 0 && new_c < n) {
                                for (char prev_move : Array_3D[new_r][new_c][move-1].moves) {
                                    Array_3D[r][c][move].moves.push_back(prev_move);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // -------------- TestPrintFinal --------------
    // TestPrintFinal(Array_3D, k, m, n);

    // -------------- Write the output to the file --------------
    // find the row and column of the minimum value in the last move
    int best_r = 0;
    int best_c = 0;
    int best_value = INF;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (Array_3D[r][c][k-1].value < best_value) {
                best_r = r;
                best_c = c;
                best_value = Array_3D[r][c][k-1].value;
            }
        }
    }
    // output the minimum value in the last move
    outputFile << best_value << endl;
    // output the row and column of the minimum value in the last move
    outputFile << best_r+1 << " " << best_c+1 << endl;
    // output the sequence of moves to get to the minimum value in the last move
    for (char best_move : Array_3D[best_r][best_c][k-1].moves) {
        outputFile << best_move << " ";
    }

    // -------------- Close the Output File --------------
    outputFile.close();

    return 0;
}
