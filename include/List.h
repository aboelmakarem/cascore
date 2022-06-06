/*	List.h
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

#ifndef LIST_H_
#define LIST_H_


typedef struct ListItem
{
	void* data;
	struct ListItem* previous;
	struct ListItem* next;
} ListItem;

typedef struct List
{
	ListItem* start;
	ListItem* end;
	unsigned int size;
	unsigned int data_size;
	int pointers;
} List;

List* create_list(unsigned int data_size,int pointers);
void reset_list(List* list);
void destroy_list(List* list);
int copy_list(const List* source,List* target);
void* list_front(List* list);
void* list_back(List* list);
ListItem* list_drop_item(List* list,ListItem* item);
void list_pushfront(List* list,void* data);
void list_pushback(List* list,void* data);
void list_popfront(List* list);
void list_popback(List* list);
int list_empty(const List* list);
ListItem* list_insert_before(List* list,ListItem* item,void* data);
ListItem* list_insert_after(List* list,ListItem* item,void* data);
ListItem* list_circular_next(const List* list,const ListItem* item);
ListItem* list_circular_previous(const List* list,const ListItem* item);

#endif

