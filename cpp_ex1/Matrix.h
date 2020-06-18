// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#define BAD_FILE_ERROR "Error: bad file input"
#define NEG_MAT_SIZE_ERROR "Error: size of matrix cant be negative!"
#define MAT_SIZE_DOES_NOT_MATCH_ADD_ERROR "Error: cant add those matrices"
#define BAD_MAT_INDEX_ERROR "Error: bad mat index"
#define MAT_SIZE_DOES_NOT_MATCH_MULT_ERROR "Error: cant multiply those matrices"
#define BASE_MAT_SIZE 1

#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;

} MatrixDims;

/**
 * a class represnts a matrix.
 */
class Matrix
{
private:

    MatrixDims matDims{};
    int _matSize;
    float *_myMat;

    /**
     * a method that initalizing the values of the matrix to 0.
     */
    void _initValues();

    /**
     * a method that initalizing the values of the matrix to 0.
     * @param m a new matrix to copy to the current matrix.
     */
    void _cpyMatVals(const Matrix &m);

    /**
     * a method that deletes the allocated memory of Matrix class.
     */
    void _delMatVals() const;

public:

    /**
     * A default constructor for class Matrix.
     */
    Matrix();

    /**
     * Constructor for Matrix class
     * @param rows the num of rows in the matrix
     * @param cols the num of cols in the matrix
     */
    Matrix(int rows, int cols);

    /**
     * a copy constructor of the class
     * @param m a matrix to copy.
     */
    Matrix(const Matrix &m);

    /**
     * the class destructor.
     */
    ~Matrix();

    /**
     * a getter for the number of rows in the matrix
     * @return the number of rows.
     */
    int getRows() const;

    /**
     * a getter for the number of cols in the matrix
     * @return the number of cols.
     */
    int getCols() const;

    /**
     * A method that creates a vector from the current matrix
     * @return reference for the vectorize matrix.
     */
    Matrix &vectorize();

    /**
     * a method that prints the current matrix according to the instructions.
     */
    void plainPrint() const;

    /**
     * overriding the operator = for the matrix class, comparing two matrices.
     * @param m1 a matrix to init = on.
     * @return a reference to the new matrix.
     */
    Matrix &operator=(const Matrix &m1);

    /**
     * a constant method for the operator + on a matrices, add all the coordinates 1 by 1.
     * @param m1 a matrix to add to the current
     * @return the sum of the adding.
     */
    Matrix operator+(const Matrix &m1) const;

    /**
    * a non-constant method for the operator + on a matrices, add all the coordinates 1 by 1.
    * @param m1 a matrix to add to the current
    * @return a reference to the sum of the adding.
    */
    Matrix &operator+=(const Matrix &m1);

    /**
     * override method the the () operator, returning the (i,j) position of the function, where
     * i is the row, and j is the colomn.
     * @param row the row index
     * @param col the col index
     * @return a reference to the (i,j) float of the matrix.
     */
    float& operator()(int row, int col);

    /**
     * a const method, overrides the () operator, returning the (i,j) position of the function, where
     * i is the row, and j is the colomn.
     * @param row the row index
     * @param col the col index
     * @return the (i,j) float of the matrix.
     */
    float operator()(int row, int col) const;

    /**
     * a const method, overrides the [] operator, returning the position in the matrix,
     * while the position = row*cols + col.
     * @param position the index for the float in the matrix
     * @return the [i] float of the matrix.
     */
    float operator[](int position) const;

    /**
     * a non-const method, overrides the [] operator, returning the position in the matrix,
     * while the position = row*cols + col.
     * @param position the index for the float in the matrix
     * @return a reference to the [i] float of the matrix.
     */
    float& operator[](int position);

    /**
     * a const override method for the operator *, representing a matrix multiplication.
     * @param b a matrix to multiply from right to this.
     * @return a matrix , the multiplication of this*b.
     */
    Matrix operator*(const Matrix &b) const;

    /**
     * a const override method for the operator *, representing a matrix and float from right.
     * @param c a float to multiply from right to this.
     * @return a matrix ,the multiplication of this*c.
     */
    Matrix operator*(float c) const;

    /**
     * a non-const override method for the operator *, representing a matrix and float from right.
     * @param c a float to multiply from right to this.
     * @return a matrix ,the multiplication of this*c.
     */
    Matrix operator*(float c);
    /**
     * a const override friend function for the operator *, representing a matrix and float from left.
     * @param c a float to multiply from left to a.
     * @param a a matrix to multiply by c.
     * @return a matrix , the multiplication of this*c.
     */
    friend Matrix operator*(float c, Matrix a);

    /**
     * a friend method overriding the >> operator, getting the floats to get in the matrix from the is input.
     * if the input is too short, returns an error.
     * @param is an istream to read from.
     * @param a a reference to matrix, to insert the object from "is" to.
     */
    friend void operator>>(std::istream & is, Matrix &a);

    /**
     * a friend method overriding the << operator, printing to the os according to the ex instructions.
     * @param os an ostream to print to from the matrix
     * @param a a reference to a matrix.
     * @return a reference to the os stream.
     */
    friend std::ostream & operator<<(std::ostream & os, const Matrix &a);

};
#endif //MATRIX_H
