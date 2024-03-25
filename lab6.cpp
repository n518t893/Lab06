#include <iostream>
#include <fstream>

using namespace std;

// Function to read in matrix
bool readmatrix(int** matrix, const int n, ifstream& file) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> matrix[i][j])) {
                cerr << "Error reading element at position (" << i+1 << "," << j+1 << ")\n";
                return false;
            }
        }
    }
    return true;
}
// Function to get the max value of the matrix
int getMaxValue(int** matrix, const int n) {
    int maxVal = matrix[0][0];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
    }
    return maxVal;
}

// Function to print matrix
void printMatrix(int** matrix, const int n) {
    // Find the maximum element in the matrix
    int max_val = getMaxValue(matrix, n);

    // Calculate the width of the maximum element
    int max_width = 1;
    int temp = max_val;
    while (temp /= 10) {
        max_width++;
    }

    // Print the matrix with fixed width
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Print the element with padding
            cout << matrix[i][j];
            // Calculate the padding needed for alignment
            int width = 1;
            int num = matrix[i][j];
            while (num /= 10) {
                width++;
            }
            int padding = max_width - width + 1;
            for (int k = 0; k < padding; k++) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Function to add matrices
int** addMatrices(int** matrix1, int** matrix2, const int n) {
    int** res = new int*[n];
    for (int i = 0; i < n; ++i) {
        res[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            res[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return res;
}

// Function to subtract matrices
int** subtractMatrices(int** matrix1, int** matrix2, const int n) {
    int** res = new int*[n];
    for (int i = 0; i < n; ++i) {
        res[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            res[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return res;
}

// Function to multiply matrices
int** multiplyMatrices(int** matrix1, int** matrix2, const int n) {
    int** result = new int*[n];
    for (int i = 0; i < n; ++i) {
        result[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

// Function to update an element of the matrix
void updateElement(int** matrix, const int n, int row, int col, int newValue) {
    if (row < 1 || row > n || col < 1 || col > n) {
        cerr << "Error: Invalid row or column index.\n";
        exit(1);
    }
    matrix[row-1][col-1] = newValue;
}



// Function to transpose the matrix
int** transposeMatrix(int** matrix, const int n) {
    int** transposed = new int*[n];
    for (int i = 0; i < n; ++i) {
        transposed[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            transposed[i][j] = matrix[j][i];
        }
    }
    return transposed;
}

int main() {
    ifstream fileinput("matrix_input.txt");
    if (!fileinput.is_open()) { //handling error for file input
        cerr << "Error opening file matrix_input.txt\n";
        return 1;
    }
    int size;
    if (!(fileinput >> size)) {//wrong format for size of matrix
        cerr << "Error reading matrix size.\n";
        return 1;
    }
    const int n = size;
    int** matrix1 = new int*[n];//using dynamically allocates memory
    int** matrix2 = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix1[i] = new int[n];
        matrix2[i] = new int[n];
    }

    if (!readmatrix(matrix1, n, fileinput)) {//invalid inputs for matrix
        cerr << "Error reading matrix 1.\n";
        return 1;
    }
    if (!readmatrix(matrix2, n, fileinput)) {
        cerr << "Error reading matrix 2.\n";
        return 1;
    }
    fileinput.close();
    cout << "Matrix 1:\n";
    printMatrix(matrix1, n);
    cout << "\nMatrix 2:\n";
    printMatrix(matrix2, n);

    // Add matrices
    int** result_add = addMatrices(matrix1, matrix2, n);
    cout << "SUM OF MATRICES:" << endl;
    printMatrix(result_add, n);

    // Multiply matrices
    int** result_multiply = multiplyMatrices(matrix1, matrix2, n);
    cout << "\nPRODUCT OF MATRICES:\n";
    printMatrix(result_multiply, n);

    // Subtract matrices
    int** result_subtract = subtractMatrices(matrix1, matrix2, n);
    cout << "\nSUBTRACT MATRIX1-MATRIX2:\n";
    printMatrix(result_subtract, n);

    //Update an element
    int updateRow, updateCol, newValue;
    cout << "\nEnter the row index you want to update(row start at 1): ";
    cin >> updateRow;
    cout << "Enter the column(column count from 1): ";
    cin >> updateCol;
    cout << "Enter the new value you want to update: ";
    cin >> newValue;
    updateElement(matrix1, n, updateRow, updateCol, newValue);
    cout << "\nUpdated Matrix 1:\n";
    printMatrix(matrix1, n);

    // Get max value of Matrix 1
    cout << "\nMax Value of Matrix 1: " << getMaxValue(matrix1, n) << endl;

    // Transpose Matrix 1
    int** transposed_matrix = transposeMatrix(matrix1, n);
    cout << "\nTransposed Matrix 1:\n";
    printMatrix(transposed_matrix, n);

    // Free memory
    for (int i = 0; i < n; ++i) {
        delete[] matrix1[i];
        delete[] matrix2[i];
        delete[] result_add[i];
        delete[] result_subtract[i];
        delete[] result_multiply[i];
        delete[] transposed_matrix[i];
    }
    delete[] matrix1;
    delete[] matrix2;
    delete[] result_add;
    delete[] result_subtract;
    delete[] result_multiply;
    delete[] transposed_matrix;

    return 0;
}
