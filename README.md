# lib_matrix

## Introduction

- Implementation of the matrix library on language C.

- This library implements basic mathematical operations with matriсes, which are then used in various algorithms.

## Matrix structure in C language:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```
## Matrix operations

All operations (except matrix comparison) should return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)

### Creating matrices (create_matrix)

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

### Cleaning of matrices (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Matrix comparison (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

The matrices A, B are equal |A = B| if they have the same dimensions and the corresponding elements are identical, thus for all i and j: A(i,j) = B(i,j)

The comparison must be up to and including 7 decimal places.

### Adding (sum_matrix) and subtracting matrices (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

The sum of two matrices A = m × n and B = m × n of the same size is a matrix C = m × n = A + B of the same size whose elements are defined by the equations C(i,j) = A(i,j) + B(i,j).

The difference of two matrices A = m × n and B = m × n of the same size is a matrix C = m × n = A - B of the same size whose elements are defined by the equations C(i,j) = A(i,j) - B(i,j).


```
            1 2 3   1 0 0   2 2 3
С = A + B = 0 4 5 + 2 0 0 = 2 4 5
            0 0 6   3 4 1   3 4 7
```

### Matrix multiplication by scalar (mult_number). Multiplication of two matrices (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

The product of the matrix A = m × n by the number λ is the matrix B = m × n = λ × A whose elements are defined by the equations B = λ × A(i,j).

```
                1 2 3   2 4 6   
B = 2 × A = 2 × 0 4 2 = 0 8 4 
                2 3 4   4 6 8   
```

The product of A = m × k by B = k × n is a matrix C = m × n = A × B of size m × n whose elements are defined by the equation C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + ... + A(i,k) × B(k,j).

```
            1 4    1 -1  1    9 11 17   
C = A × B = 2 5  × 2  3  4 = 12 13 22
            3 6              15 15 27
```
The components of matrix C are calculated as follows:

```
C(1,1) = A(1,1) × B(1,1) + A(1,2) × B(2,1) = 1 × 1 + 4 × 2 = 1 + 8 = 9
C(1,2) = A(1,1) × B(1,2) + A(1,2) × B(2,2) = 1 × (-1) + 4 × 3 = (-1) + 12 = 11
C(1,3) = A(1,1) × B(1,3) + A(1,2) × B(2,3) = 1 × 1 + 4 × 4 = 1 + 16 = 17
C(2,1) = A(2,1) × B(1,1) + A(2,2) × B(2,1) = 2 × 1 + 5 × 2 = 2 + 10 = 12
C(2,2) = A(2,1) × B(1,2) + A(2,2) × B(2,2) = 2 × (-1) + 5 × 3 = (-2) + 15 = 13
C(2,3) = A(2,1) × B(1,3) + A(2,2) × B(2,3) = 2 × 1 + 5 × 4 = 2 + 20 = 22
C(3,1) = A(3,1) × B(1,1) + A(3,2) × B(2,1) = 3 × 1 + 6 × 2 = 3 + 12 = 15
C(3,2) = A(3,1) × B(1,2) + A(3,2) × B(2,2) = 3 × (-1) + 6 × 3 = (-3) + 18 = 15
C(3,3) = A(3,1) × B(1,3) + A(3,2) × B(2,3) = 3 × 1 + 6 × 4 = 3 + 24 = 27			
```

### Matrix transpose (transpose)

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

The transpose of matrix A is in switching its rows with its columns with their numbers retained

```
          1 4   1 2 3
A = A^T = 2 5 = 4 5 6
          3 6
```
### Minor of matrix and matrix of algebraic complements (calc_complements)
```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

Minor M(i,j) is a (n-1)-order determinant obtained by deleting out the i-th row and the j-th column from the matrix A.

For the following matrix:

```
    1 2 3
A = 0 4 2
    5 2 1
```

The minor of the first element of the first row is:

```
M(1,1) = 4 2
         2 1

|M| = 4 - 4 = 0
```

The minors of matrix will look like this:

```
     0 -10 -20
M = -4 -14  -8
    -8   2   4
```

The algebraic complement of a matrix element is the value of the minor multiplied by -1^(i+j).

The matrix of algebraic complement will look like this:

```
      0  10 -20
M. =  4 -14   8
     -8  -2   4
```

### Matrix determinant

```c
int s21_determinant(matrix_t *A, double *result);
```

The determinant is a number that is associated to each square matrix and calculated from the elements using special formulas. \

The determinant of a matrix equals the sum of the products of elements of the row (column) and the corresponding algebraic complements.

Finding the determinant of matrix A by the first row:

```
    1 2 3
A = 4 5 6
    7 8 9
	
|A| = 1 × 5 6 - 2 × 4 6 + 3 × 4 5 = 1 × (5 × 9 - 8 × 6) - 2 × (4 × 9 - 6 × 7) + 3 × (4 × 8 - 7 × 5)
          8 9       7 9       7 8
|A| = 1 × (45 - 48) - 2 × (36 - 42) + 3 × (32 - 35) = -3 + 12 + (-9) = 0
|A| = 0
```

### Inverse of the matrix (inverse_matrix)

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

A matrix A to the power of -1 is called the inverse of a square matrix A if the product of these matrices equals the identity matrix.

If the determinant of the matrix is zero, then it does not have an inverse.

The formula to calculate the inverse of matrix is $`A^{-1}=\frac{1} {|A|} × A_*^T`$

The following matrix is given:

```
     2  5  7
A =  6  3  4
     5 -2 -3
```

Finding the determinant:

``` |A| = -1 ```

Determinant |A| != 0 -> matrix has an inverse.

Construction of minor matrix:

```
    -1 -38 -27
М = -1 -41 -29
    -1 -34 -24
```


The matrix of algebraic complements:

```
     -1  38 -27
М. =  1 -41  29
     -1  34 -24
```

The transpose of matrix of algebraic complements:

```
        -1   1  -1
М^T. =  38 -41  34
       -27  29 -24
```

The inverse matrix will look like this:

```
                           1  -1   1
A^(-1) =  1/|A| * M^T. = -38  41 -34
                          27 -29  24 
```

## Information about implemented library

- The library developed in C language of C11 standard using gcc compiler 
- I do not use outdated and legacy language constructions and library functions. I use the POSIX.1-2017 standard.
- Functions developed as a static library (with the s21_matrix.h header file)
- The library developed according to the principles of structured programming;
- I use prefix s21_ before each function
- The gcov_report target generate a gcov report in the form of an html page. Unit tests run with gcov flags to do this 
- The matrix implemented as the structure described [above](#matrix-structure-in-c-language)
- Verifiable accuracy of the fractional part is up to 6 decimal places
- Library functions have full coverage with unit-tests with the check.h library
- Unit-tests check the results of my implementation by comparing them with the implementation of the standard string.h library
- Unit tests cover at least 90% of each function (checked using gcovr)
- Use Makefile for building the library and tests (the targets: _all, clean, test, s21_math.a, gcov_report_) 

All code is the property of Anton Tuzov.
