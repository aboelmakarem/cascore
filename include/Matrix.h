/* 	Matrix.h

Copyright (c) 2013 Ahmed M. Hussein (amhussein4@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct Matrix
{
	unsigned int rows;
	unsigned int columns;
	double* entries;
} Matrix;

void init_matrix(Matrix* matrix);
Matrix* create_matrix(unsigned int rows,unsigned int columns);
unsigned int allocate_matrix(Matrix* matrix,unsigned int rows,unsigned int columns);
void reset_matrix(Matrix* matrix);
void destroy_matrix(Matrix* matrix);
int copy_matrix(const Matrix* source,Matrix* target);
double mat_get(const Matrix* matrix,unsigned int row,unsigned int column);
void mat_set(Matrix* matrix,unsigned int row,unsigned int column,double value);
void mat_sum(const Matrix* A,const Matrix* B,Matrix* C);
void mat_diff(const Matrix* A,const Matrix* B,Matrix* C);
void mat_inc(Matrix* A,const Matrix* B);
void mat_dec(Matrix* A,const Matrix* B);
void mat_scale(Matrix* A,double factor);
void mat_mult(const Matrix* A,const Matrix* B,Matrix* C);
int mat_solve(const Matrix* A,const Matrix* b,Matrix* x);
int mat_solve_jacobi(const Matrix* A,const Matrix* b,Matrix* x);
int mat_solve_relaxed_jacobi(const Matrix* A,const Matrix* b,Matrix* x,double relaxation_factor);
int mat_solve_ge(const Matrix* A,const Matrix* b,Matrix* x);
int mat_solve_gmres(const Matrix* A,const Matrix* b,Matrix* x);
int dgmat_premult(const Matrix* matrix,const Matrix* diagonal,Matrix* product);
int dgmat_postmult(const Matrix* matrix,const Matrix* diagonal,Matrix* product);
int mat_inv(const Matrix* matrix,Matrix* inverse);
void mat_rand(Matrix* matrix,double start,double end,int diagonally_dominant);
void mat_nrand(Matrix* matrix,double mean,double standard_deviation);
double mat_norm2(const Matrix* matrix);
void mat_print(const Matrix* matrix);
void mat_zero(Matrix* matrix);
void mat_identity(Matrix* matrix);
void mat_transpose(const Matrix* matrix,Matrix* transpose);
int init_arnoldi_iteration(const Matrix* b,Matrix* Q);
int run_arnoldi_iteration(const Matrix* A,Matrix* Q,Matrix* H,unsigned int order);
void mat_reshape(const Matrix* source,Matrix* target);
int test_mat(unsigned int size,double tolerance,unsigned int paranoia);

#endif

