/*	TestMatrix.cpp

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


#include "stdio.h"
#include "stdlib.h"

extern "C"
{
	#include "Matrix.h"
}

void TestMatrixPerformance(const unsigned int& size)
{
	Matrix* A = create_matrix(size,size);
	Matrix* B = create_matrix(size,size);
	Matrix* C = create_matrix(size,size);
	
	mat_rand(A,-10.0,10.0,0);
	mat_rand(B,-10.0,10.0,0);
	mat_mult(A,B,C);
	printf("%e\n",mat_get(C,0,0));
	destroy_matrix(A);
	destroy_matrix(B);
	destroy_matrix(C);
}

void TestArnoldiIteration(unsigned int size)
{
	Matrix* A = create_matrix(size,size);
	Matrix* rhs = create_matrix(size,1);
	Matrix* Q = create_matrix(size,size);
	Matrix* H = create_matrix(size,size);
	Matrix* L = create_matrix(size,size);
	Matrix* R = create_matrix(size,size);
	Matrix* D = create_matrix(size,size);
	Matrix* Qt = create_matrix(size,size);
	mat_rand(A,-10.0,10.0,0);
	mat_rand(rhs,-10.0,10.0,0);
	init_arnoldi_iteration(rhs,Q);
	for(unsigned int i = 1 ; i <= size ; i++)
	{
		printf("iter = %u\n",i);
		mat_mult(A,Q,L);
		run_arnoldi_iteration(A,Q,H,i);
		mat_mult(Q,H,R);
		mat_diff(L,R,D);
		printf("iter error = %e\n",mat_norm2(D));
	}
	mat_transpose(Q,Qt);

	mat_mult(Q,H,L);
	mat_mult(L,Qt,R);
	mat_diff(R,A,L);
	destroy_matrix(A);
	destroy_matrix(rhs);
	destroy_matrix(Q);
	destroy_matrix(H);
	destroy_matrix(L);
	destroy_matrix(R);
	destroy_matrix(D);
	destroy_matrix(Qt);
}

void TestGMRES(unsigned int size)
{
	Matrix* A = create_matrix(size,size);
	Matrix* b = create_matrix(size,1);
	Matrix* x = create_matrix(size,1);
	Matrix* v = create_matrix(size,1);
	Matrix* D = create_matrix(size,1);
	mat_rand(A,-10.0,10.0,0);
	mat_rand(b,-3.0,3.0,0);
	mat_solve_gmres(A,b,x);
	mat_mult(A,x,v);
	mat_diff(b,v,D);
	printf("solution squared error = %e\n",mat_norm2(D));

	destroy_matrix(A);
	destroy_matrix(b);
	destroy_matrix(x);
	destroy_matrix(v);
	destroy_matrix(D);
}

int main(int argc,char** argv)
{
	if(argc < 3)
	{
		printf("error: missing run arguments\n");
		printf("usage:testmatrix test_size test_count\n");
		return 1;
	}
	unsigned int eq_count = atoi(argv[1]);
	unsigned int test_count = atoi(argv[2]);
	printf("running %u matrix tests of size %u\n",test_count,eq_count);
	if(test_mat(eq_count,1.0e-9,test_count))	printf("matrix library test passed\n");
	else 										printf("matrix library test failed\n");
	printf("testing matrix GMRES solver for %u systems of size %u\n",test_count,eq_count);
	for(unsigned int i = 0 ; i < test_count ; i++)
	{
		TestGMRES(eq_count);
	}
	return 0;
}

