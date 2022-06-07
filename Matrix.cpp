#include "Matrix.h"

using namespace std;

Matrix::Matrix(): numRows{DEFAULT_SIZE}, numCols{DEFAULT_SIZE} { // Default construcotr, constructs a 3x3 matrix

  values = new double*[DEFAULT_SIZE];
  for (int row = 0; row < numRows; ++row) {
    values[row] = new double[numCols];
  }

  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      values[row][col] = 0;
    }
  }
}

Matrix::Matrix(int numRows, int numCols) // Constructor with passed number of rows and columnds, 
{                                        // a matrix with that number of columns and rows
  this->numRows = numRows;
  this->numCols = numCols;
  if ((numRows <= 0) || (numCols <= 0)) // checks if the entries are valid
  {
    throw runtime_error("the number of rows and columns both have to be larger than 0.");
  }
  values = new double*[numCols];
  for (int row = 0; row < numRows; row++)
  {
    values[row] = new double[numCols]; // create an empty 2D matrix
  }

  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      values[row][col] = 0; // fill all the matrix spaces with 0
    }
  }
}

Matrix::Matrix(const Matrix& other)
{
  this->numRows = other.numRows;
  this->numCols = other.numCols; // copy the number of rows and columns
  this->values = new double*[numCols]; 
  for (int row = 0; row < numRows; row++)
  {
    values[row] = new double[numCols];
  }

  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      values[row][col] = other.values[row][col]; // copy all the values from one to another
    }
  }
}

Matrix& Matrix::operator=(const Matrix& other)
{
  if (this == &other)
  {
    return *this;
  }
  numRows = other.numRows;
  numCols = other.numCols;
  values = new double*[numCols];
  for (int row = 0; row < numRows; row++)
  {
    values[row] = new double[numCols];
  }

  for (int row = 0; row < numRows; row++)
  {
    for (int col = 0; col < numCols; col++)
    {
      values[row][col] = other.values[row][col];
    }
  }
  return *this;
}

Matrix::Matrix(Matrix&& other)noexcept
{
  numRows = other.numRows;
  numCols = other.numCols;
  values = other.values; // copy all the variables
  other.numRows = 0;
  other.numCols = 0;
  other.values = nullptr; // put the original into the move-from state
}

Matrix& Matrix::operator=(Matrix&& other)noexcept
{
  if (this == &other)
  {
    return *this;
  }
  delete[] values;
  numRows = other.numRows;
  numCols = other.numCols;
  values = other.values;
  other.numRows = 0;
  other.numCols = 0;
  other.values = nullptr;
  return *this;
}

Matrix Matrix::operator+(const Matrix& other)
{
  if ((this->numRows != other.numRows) || (this->numCols != other.numCols)) // checks if the matrices are of the same size
  {
    throw runtime_error("can not add matrices of different sizes.");
  }
  Matrix matrix(other.numRows, other.numCols); // create a new matrix
  for (int row = 0; row < other.numRows; row++)
  {
    for (int col = 0; col < other.numCols; col++)
    {
      matrix.values[row][col] = this->values[row][col] + other.values[row][col]; // add all the entries
    }
  }
  return matrix; // return the new matrix, result of addition
}

Matrix& Matrix::operator+=(const Matrix& other)
{
  if ((this->numRows != other.numRows) || (this->numCols != other.numCols)) // checks if the matrices are of the same size
  {
    throw runtime_error("can not add matrices of different sizes.");
  }
  for (int row = 0; row < other.numRows; row++)
  {
    for (int col = 0; col < other.numCols; col++)
    {
      this->values[row][col] = this->values[row][col] + other.values[row][col]; // add all the entries
    }
  }
  return *this;
}

Matrix::~Matrix() {
  // First delete each row (every row is an array)
  for (int row = 0; row < numRows; ++row) {
    delete[] values[row];
  }
  // Then delete the array or pointers to arrays 
  delete[] values;
}


double Matrix::get(int row, int col)
{
  if((row >= numRows) || (row < 0) || (col >= numCols) || (col < 0)) // checks if the entries are valid
  {
    throw runtime_error("invalid entries.");
  }
  return this->values[row][col]; // returns the value at those indices
}

int Matrix::getNumRows()
{
  return this->numRows; // returns the number of rows
}

int Matrix::getNumCols()
{
  return this->numCols; // returns the number of columns
}

void Matrix::set(int row, int col, double value)
{
  if((row >= numRows) || (row < 0) || (col >= numCols) || (col < 0)) // checks if the entries are valid
  {
    throw runtime_error("invalid entries.");
  }
  this->values[row][col] = value; // sets the value at the indices to the new value
}

void Matrix::print() {
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      cout << values[row][col] << " ";
    }
    cout << endl;
  }
}