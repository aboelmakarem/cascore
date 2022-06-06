/*	TestContainers.cpp

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
	#include "List.h"
	#include "Matrix.h"
}

void TestBasicType()
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	List* fib_list = create_list(sizeof(double),0);
	x = 1.0;
	y = 1.0;
	for(unsigned int i = 0 ; i < 20 ; i++)
	{
		z = x + y;
		list_pushback(fib_list,&z);
		x = y;
		y = z;
	}
	
	for(ListItem* item = fib_list->start ; item != 0 ; item = item->next)
	{
		printf("%e,",*((double*)item->data));
	}
	printf("\n");
	destroy_list(fib_list);
}

void TestObject()
{
	List* mat_list = create_list(sizeof(Matrix),0);
	
	Matrix* m1;
	for(unsigned int i = 0 ; i < 3 ; i++)
	{
		m1 = create_matrix(3,3);
		mat_rand(m1,-10.0,10.0,0);
		printf("%u : %u : in mat entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		list_pushback(mat_list,m1);
		// m1 holds a chunk of memory that has been allocated but now is copied in a 
		// list item, free the memory pointed to by m1 (since we don't need it anymore 
		// and we will lose reference to it in the next iteration).
		free(m1);
	}
	unsigned int i = 0;
	List* mat_list2 = create_list(sizeof(Matrix),0);
	copy_list(mat_list,mat_list2);
	for(ListItem* item = mat_list->start ; item != 0 ; item = item->next)
	{
		m1 = (Matrix*)item->data;
		printf("%u : %u : out mat1 entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		// reset, but do not destroy, the matrix since it will be destroyed when the 
		// list is destroyed
		//reset_matrix(m1);
		i++;
	}
	i = 0;
	for(ListItem* item = mat_list2->start ; item != 0 ; item = item->next)
	{
		m1 = (Matrix*)(item->data);
		printf("%u : %u : out mat2 entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		// reset, but do not destroy, the matrix since it will be destroyed when the 
		// list is destroyed
		//reset_matrix(m1);
		i++;
	}
	for(ListItem* item = mat_list->start ; item != 0 ; item = item->next)
	{
		reset_matrix((Matrix*)(item->data));
	}
	printf("\n");
	destroy_list(mat_list);
	destroy_list(mat_list2);
}

void TestObjectPointer()
{
	List* mat_list = create_list(sizeof(Matrix*),1);
	
	Matrix* m1 = 0;
	for(unsigned int i = 0 ; i < 10 ; i++)
	{
		m1 = create_matrix(3,3);
		mat_rand(m1,-10.0,10.0,0);
		printf("%u : %u : in mat entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		list_pushback(mat_list,m1);
	}
	unsigned int i = 0;
	List* mat_list2 = create_list(sizeof(Matrix*),1);
	copy_list(mat_list,mat_list2);
	for(ListItem* item = mat_list->start ; item != 0 ; item = item->next)
	{
		m1 = (Matrix*)(item->data);
		printf("%u : %u : out mat1 entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		//destroy_matrix(m1);
		i++;
	}
	for(ListItem* item = mat_list2->start ; item != 0 ; item = item->next)
	{
		m1 = (Matrix*)(item->data);
		printf("%u : %u : out mat2 entry 2,2 = %e\n",i,m1->rows,mat_get(m1,1,1));
		//destroy_matrix(m1);
		i++;
	}
	for(ListItem* item = mat_list->start ; item != 0 ; item = item->next)
	{
		destroy_matrix((Matrix*)(item->data));
	}
	printf("\n");
	destroy_list(mat_list);
	destroy_list(mat_list2);
}

int main(int argc,char** argv)
{
	//TestBasicType();
	TestObject();
	//TestObjectPointer();
	return 0;
}

