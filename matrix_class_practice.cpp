#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
private:
    int** mat;  //pointer to a pointer that points to an integer // Pointer to dynamically allocate a 2D array
    int rows, cols; // Dimensions of the matrix

public:
    // Constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        mat = new int*[rows]; //in heap, create an array of int pointers(pointing to ints) & size of array is the number of rows
        //this array contains pointers in each index, mat[i] is a POINTER
        for (int i = 0; i < rows; ++i) {
            mat[i] = new int[cols](); // () --> Initialize with zeros
        }
        //this loop creates columns of ints for each pointer in the row 
        cout << "Matrix (" << rows << "x" << cols << ") created.\n";
    }

    // Destructor
    ~Matrix() {//INSTEAD USE VECTORS, handels it dynamically and deletes it itself so dont need deconstructor
        for (int i = 0; i < rows; ++i) {
            delete[] mat[i]; // Delete each row
        }
        delete[] mat; // Delete the array of row pointers
        mat = nullptr;
        cout << "Matrix (" << rows << "x" << cols << ") destroyed.\n";
    }

    // Fill the matrix with user input
    void fill_matrix() {
        cout << "Enter (" << rows << "x" << cols << ") elements of the matrix use space after each:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> mat[i][j]; //cin equivalent to cin.get, captures all characters from keyboard until it reaches a character (stops capturing automatically if nothing specific is given when it sees a space)
                //example when we made it stop reading when it saw a comma
            }
        }
    }

    #include <iomanip>

    // Display the matrix
    void display_matrix() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << setw(5) << mat[i][j]; //setw configures the printing, sets the width of the display to 5 characters (must include library at top)
            } //mat[i][j] is the element the pointers are pointing to
            cout << endl;
        }
    }

    // Overload the + operator for matrix addition

    Matrix operator+(const Matrix& other) const { //add two matrices together
        if (rows != other.rows || cols != other.cols) {
            throw "Matrix dimensions must match for addition."; //if an error happens, we throw the error
            //REMEBER CATCH const char* e; (a pointer to the array, catch must point to the error)
            //Best way just use a direct string of characters, doesnt continue code if error occured
        }

        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.mat[i][j] = this->mat[i][j] + other.mat[i][j]; //can also just do mat[i][j] (an attribute of the class)
            }
        }
        return result;
    }
    
    friend Matrix operator*(const Matrix& other, const Matrix& other2);

};

//start for matrix multiplication overloaded operator as a friend function
    Matrix operator*(const Matrix& other, const Matrix& other2){ //dont use friend outside the function, friend just established connection inside the function
        if(other.cols != other2.rows){
            throw "Matrices cannot be multiplied";
        }

        else{
            Matrix result(other.rows, other2.cols); //creates new matrix with same size as ros of first and colums of second
            // for(int i);

        }
    }

// Main application
int main() {

    // Create two matrices
    int rows1, cols1;
    cout << "Enter the number of rows and columns for the matrix one, use space between them: ";
    cin >> rows1 >> cols1;
    Matrix mat1(rows1, cols1);
    
    // Fill the matrices
    cout << "Fill first matrix:\n";
    mat1.fill_matrix();

    int rows2, cols2;
    cout << "Enter the number of rows and columns for the matrix two, use space between them: ";
    cin >> rows2 >> cols2;
    Matrix mat2(rows2, cols2);

    cout << "Fill second matrix:\n";
    mat2.fill_matrix();

    // Display the matrices
    cout << "\nMatrix 1:\n";
    mat1.display_matrix();
    cout << "\nMatrix 2:\n";
    mat2.display_matrix();

    try{
        // Add the matrices
        Matrix result = mat1 + mat2; //if error is thrown doesnt continue the remaining code until catch part, prints the error message

        // Display the result
        cout << "\nResult of Matrix Addition:\n";
        result.display_matrix();
    } catch (const char* e) {
        cout << "Error: " << e << endl;
    }

    return 0;
}
