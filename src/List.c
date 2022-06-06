/*	List.c

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

#include "List.h"
#include "stdlib.h"
#include "string.h"

ListItem* create_listitem(unsigned int data_size,int pointer_data)
{
	ListItem* item = (ListItem*)malloc(sizeof(ListItem));
	item->data = 0;
	if(pointer_data == 0)		item->data = calloc(1,data_size);
	item->previous = 0;
	item->next = 0;
	return item;
}
void reset_listitem(ListItem* item,int pointer_data)
{
	if((pointer_data == 0) && (item->data != 0))  			free(item->data);
	item->data = 0;
	item->previous = 0;
	item->next = 0;
}
void destroy_listitem(ListItem* item,int pointer_data)
{
	if(item == 0)		return;
	reset_listitem(item,pointer_data);
	free(item);
}

void list_init(List* list)
{
	list->start = 0;
	list->end = 0;
	list->size = 0;
}
List* create_list(unsigned int data_size,int pointers)
{
	List* list = (List*)malloc(sizeof(List));
	list_init(list);
	list->data_size = data_size;
	list->pointers = pointers;
	return list;
}
void reset_list(List* list)
{
	while(list->size > 0)
	{
		list_popfront(list);
	}
	list_init(list);
}
void destroy_list(List* list)
{
	if(list == 0)		return;
	reset_list(list);
	free(list);
}
int copy_list(const List* source,List* target)
{
	if(source->data_size != target->data_size)		return 0;
	if(source->pointers != target->pointers)		return 0;
	reset_list(target);
	ListItem* item = source->start;
	while(item != 0)
	{
		list_pushback(target,item->data);
		item = item->next;
	}
	return 1;
}
void* list_front(List* list){return list->start->data;}
void* list_back(List* list){return list->end->data;}
ListItem* list_drop_item(List* list,ListItem* item)
{
	// This function drops the item pointed at by the passed item from the 
	// list and returns a pointer to the item following it if any. 
	if(item == 0)				return 0;
	if(list->size == 0)			return 0;
	if(list->size == 1)
	{
		// the list has only one item and the item points to it
		if(list->start == 0)			return 0;
		if(list->start != list->end)	return 0;
		if(list->start != item)			return 0;
		destroy_listitem(item,list->pointers);
		list_init(list);
		return 0;
	}
	ListItem* previous = item->previous;
	ListItem* next = item->next;
	// free the item and fix the remaining list item pointers
	destroy_listitem(item,list->pointers);
	if(previous == 0)
	{
		next->previous = 0;
		list->start = next;
	}
	else if(next == 0)
	{
		previous->next = 0;
		list->end = previous;
	}
	else
	{
		next->previous = previous;
		previous->next = next;
	}
	list->size--;
	return next;
}
void list_pushfront(List* list,void* data){list->start = list_insert_before(list,list->start,data);}
void list_pushback(List* list,void* data){list->end = list_insert_after(list,list->end,data);}
void list_popfront(List* list){list_drop_item(list,list->start);}
void list_popback(List* list){list_drop_item(list,list->end);}
int list_empty(const List* list){return (list->size == 0);}
ListItem* list_insert_before(List* list,ListItem* item,void* data)
{
	// This function inserts an item to the list before the item 
	// pointed at by the item argument. If the list is empty, 
	// it inserts it at the beginning regardless of where item 
	// points. It returns a pointer to the newly inserted item. 
	if((list->size > 0) && (item == 0))		return 0;
	ListItem* new_item = create_listitem(list->data_size,list->pointers);
	if(list->pointers)			new_item->data = data;
	else  						memcpy(new_item->data,data,list->data_size);
	if(list->size == 0)
	{
		// empty list, this is the first item to be inserted
		list->start = new_item;
		list->end = new_item;
	}
	else
	{
		new_item->previous = item->previous;
		new_item->next = item;
		item->previous = new_item;
		if(new_item->previous != 0)			new_item->previous->next = new_item;
		else 								list->start = new_item;
	}
	list->size++;
	return new_item;
}
ListItem* list_insert_after(List* list,ListItem* item,void* data)
{
	// This function inserts an item to the list after the item 
	// pointed at by the item argument. If the list is empty, 
	// it inserts it at the beginning regardless of where item 
	// points. It returns a pointer to the newly inserted item. 
	if((list->size > 0) && (item == 0))		return 0;
	ListItem* new_item = create_listitem(list->data_size,list->pointers);
	if(list->pointers)			new_item->data = data;
	else  						memcpy(new_item->data,data,list->data_size);
	if(list->size == 0)
	{
		// empty list, this is the first item to be inserted
		list->start = new_item;
		list->end = new_item;
	}
	else
	{
		new_item->next = item->next;
		new_item->previous = item;
		item->next = new_item;
		if(new_item->next != 0)			new_item->next->previous = new_item;
		else 							list->end = new_item;
	}
	list->size++;
	return new_item;
}
ListItem* list_circular_next(const List* list,const ListItem* item)
{
	if(item->next != 0)			return item->next;
	if(item != list->end)		return 0;
	return list->start;
}
ListItem* list_circular_previous(const List* list,const ListItem* item)
{
	if(item->previous != 0)			return item->previous;
	if(item != list->start)			return 0;
	return list->end;
}

