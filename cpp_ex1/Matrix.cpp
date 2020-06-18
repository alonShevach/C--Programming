#include <cstring>
#include <iostream>
#include "Matrix.h"

/**
 * a method that initalizing the values of the matrix to 0.
 */
void Matrix :: _initValues()
{
    for (int i = 0; i < _matSize; ++i)
    {
        _myMat[i] = 0;
    }
}

/**
 * a method that initalizing the values of the matrix to 0.
 * @param m a new matrix to copy to the current matrix.
 */
void Matrix :: _cpyMatVals(const Matrix &m)
{
    _myMat = new float [_matSize];
    for (int i = 0; i < _matSize; ++i)
    {
        this->_myMat[i] = m._myMat[i];
    }
}

/**
 * a method that deletes the allocated memory of Matrix class.
 */
void Matrix :: _delMatVals() const
{
    delete[] (this->_myMat);
}

/**
 * A default constructor for class Matrix.
 */
Matrix :: Matrix() : Matrix(BASE_MAT_SIZE, BASE_MAT_SIZE)
{
}

/**
 * Constructor for Matrix class
 * @param rows the num of rows in the matrix
 * @param cols the num of cols in the matrix
 */
Matrix :: Matrix(const int rows, const int cols) : matDims{.rows = rows, .cols = cols}, _matSize(rows*cols)
{
    if (rows <= 0 || cols <= 0)
    {
        std::cerr << NEG_MAT_SIZE_ERROR;
        exit(EXIT_FAILURE);
    }
    _myMat = new float [_matSize];
    _initValues();
}

/**
 * a copy constructor of the class
 * @param m a matrix to copy.
 */
Matrix :: Matrix(const Matrix &m) : matDims{.rows = m.getRows(), .cols = m.getCols()}, _matSize(m.getRows()*m.getCols())
{
    _cpyMatVals(m);
}

/**
 * the class destructor.
 */
Matrix :: ~Matrix()
{
    _delMatVals();
}

/**
 * a getter for the number of rows in the matrix
 * @return the number of rows.
 */
int Matrix :: getRows() const
{
    return matDims.rows;
}

/**
 * a getter for the number of cols in the matrix
 * @return the number of cols.
 */
int Matrix :: getCols() const
{
    return matDims.cols;
}

/**
 * A method that creates a vector from the current matrix
 * @return reference for the vectorize matrix.
 */
Matrix& Matrix :: vectorize()
{
    matDims.rows = _matSize;
    matDims.cols = BASE_MAT_SIZE;
    return *this;
}

/**
 * a method that prints the current matrix according to the instructions.
 */
void Matrix :: plainPrint() const
{
    for (int i = 0; i < matDims.rows; ++i)
    {
        for (int j = 0; j < matDims.cols; ++j)
        {
            std::cout << (*this)[i*matDims.cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * overriding the operator = for the matrix class, comparing two matrices.
 * @param m1 a matrix to init = on.
 * @return a reference to the new matrix.
 */
Matrix& Matrix :: operator=(const Matrix &m1)
{
    if (this == &m1)
    {
        return *this;
    }
    matDims.rows = m1.getRows();
    matDims.cols = m1.getCols();
    this->_matSize = m1._matSize;
    _delMatVals();
    _cpyMatVals(m1);
    return *this;
}

/**
 * a constant method for the operator + on a matrices, add all the coordinates 1 by 1.
 * @param m1 a matrix to add to the current
 * @return the sum of the adding.
 */
Matrix Matrix :: operator+(const Matrix &m1) const
{
    if (matDims.rows != m1.getRows() || matDims.cols != m1.getCols())
    {
        std::cerr << MAT_SIZE_DOES_NOT_MATCH_ADD_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix newMat = Matrix(m1);
    newMat += *this;
    return newMat;
}

/**
* a non-constant method for the operator + on a matrices, add all the coordinates 1 by 1.
* @param m1 a matrix to add to the current
* @return a reference to the sum of the adding.
*/
Matrix& Matrix :: operator+=(const Matrix &m1)
{
    if (matDims.rows != m1.getRows() || matDims.cols != m1.getCols())
    {
        std::cerr << MAT_SIZE_DOES_NOT_MATCH_ADD_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < this->_matSize; ++i)
    {
        (*this)[i] += m1[i];
    }
    return *this;
}

/**
 * override method the the () operator, returning the (i,j) position of the function, where
 * i is the row, and j is the colomn.
 * @param row the row index
 * @param col the col index
 * @return a reference to the (i,j) float of the matrix.
 */
float& Matrix :: operator()(int row, int col)
{
    if (row < 0 || col < 0 || row >= matDims.rows || col >= matDims.cols)
    {
        std::cerr << BAD_MAT_INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    int index = (row* matDims.cols) + col;
    return (*this)[index];
}

/**
 * a const method, overrides the () operator, returning the (i,j) position of the function, where
 * i is the row, and j is the colomn.
 * @param row the row index
 * @param col the col index
 * @return the (i,j) float of the matrix.
 */
float Matrix :: operator()(int row, int col) const
{
    if (row < 0 || col < 0 || row >= matDims.rows || col >= matDims.cols)
    {
        std::cerr << BAD_MAT_INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    int index = (row* matDims.cols) + col;
    return (*this)[index];
}

/**
 * a const method, overrides the [] operator, returning the position in the matrix,
 * while the position = row*cols + col.
 * @param position the index for the float in the matrix
 * @return the [i] float of the matrix.
 */
float Matrix :: operator[](int position) const
{
    if (position < 0 || position >= this->_matSize)
    {
        std::cerr << BAD_MAT_INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_myMat[position];
}

/**
 * a non-const method, overrides the [] operator, returning the position in the matrix,
 * while the position = row*cols + col.
 * @param position the index for the float in the matrix
 * @return a reference to the [i] float of the matrix.
 */
float& Matrix :: operator[](int position)
{
    if (position < 0 || position >= this->_matSize)
    {
        std::cerr << BAD_MAT_INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return this->_myMat[position];
}

/**
 * a const override method for the operator *, representing a matrix multiplication.
 * @param b a matrix to multiply from right to this.
 * @return a matrix , the multiplication of this*b.
 */
Matrix Matrix :: operator*(const Matrix &b) const
{
    if (matDims.cols != b.getRows())
    {
        std::cerr << MAT_SIZE_DOES_NOT_MATCH_MULT_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix newMat = Matrix(matDims.rows, b.getCols());
    for(int i = 0; i < matDims.rows; i++)
    {
        for(int j = 0; j<b.getCols(); j++)
        {
            float sum = 0;
            for(int k = 0; k < matDims.cols; k++)
            {
                sum += this->_myMat[i * matDims.cols + k] * b._myMat[k * b.getCols() + j];
            }
            newMat._myMat[i * b.getCols() + j] = sum;
        }
    }
    return newMat;
}

/**
 * a const override method for the operator *, representing a matrix and float from right.
 * @param c a float to multiply from right to this.
 * @return a matrix , the multiplication of this*c.
 */
Matrix Matrix :: operator*(float c) const
{
    Matrix cMat = Matrix(*this);
    for (int i = 0; i < matDims.rows; ++i)
    {
        for (int j = 0; j < matDims.cols; ++j)
        {
            cMat(i, j) *= c;
        }
    }
    return cMat;
}

/**
 * a non-const override method for the operator *, representing a matrix and float from right.
 * @param c a float to multiply from right to this.
 * @return a matrix ,the multiplication of this*c.
 */
Matrix Matrix :: operator*(float c)
{
    Matrix cMat = Matrix(*this);
    for (int i = 0; i < matDims.rows; ++i)
    {
        for (int j = 0; j < matDims.cols; ++j)
        {
            cMat(i, j) *= c;
        }
    }
    return cMat;
}

/**
 * a const override friend function for the operator *, representing a matrix and float from left.
 * @param c a float to multiply from left to a.
 * @param a a matrix to multiply by c.
 * @return a matrix , the multiplication of this*c.
 */
Matrix operator *(float c, Matrix a)
{
    return a * c;
}

/**
 * a friend method overriding the >> operator, getting the floats to get in the matrix from the is input.
 * if the input is too short, returns an error.
 * @param is an istream to read from.
 * @param a a reference to matrix, to insert the object from "is" to.
 */
void operator>>(std::istream & is, Matrix &a)
{
    if (is.good())
    {
        for (int i = 0; i < a.getRows() * a.getCols(); i++)
        {
            is.read((char *) &a[i], sizeof(float));
        }
    }
    else
    {
        std::cerr << BAD_FILE_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * a friend method overriding the << operator, printing to the os according to the ex instructions.
 * @param os an ostream to print to from the matrix
 * @param a a reference to a matrix.
 * @return a reference to the os stream.
 */
std::ostream & operator<<(std::ostream & os, const Matrix &a)
{
    for (int i = 0; i < a.getRows(); ++i)
    {
        for (int j = 0; j < a.getCols(); ++j)
        {
            if (a(i, j) <= 0.1f)
            {
                os << "  ";
            }
            else
            {
                os << "**";
            }
        }
        os << std::endl;
    }
    return os;
}