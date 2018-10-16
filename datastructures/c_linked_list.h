#pragma once
#include <memory>
struct cnode {
	struct cnode* next;
	int data;
};

cnode* create_node(int num) {
	cnode* node = (cnode*)malloc(sizeof(cnode));
	if (node == NULL)
	{
		printf("%s \n", " error, no memory ** ");
	}
	node->data = num;
	node->next = NULL;
	return node;
}

void free_node(cnode*& node)
{
	free(node);
	node = NULL;
}


void append(cnode*& list, int num) {
	cnode* new_node = create_node(num);
	if (list == NULL)
	{
		list = new_node;
	}
	else
	{
		cnode* current = list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}

}

void add_at_beg(cnode*& list, int num)
{
	
	cnode* newnode = create_node(num);
	if (list == NULL)
	{
		list = newnode;
		return;
	}
	else
	{
		cnode* node = list;
		newnode->next = node;
		list = newnode;
	}
	return;
}

int count(cnode* list)
{
	int count = 0;
	cnode* current = list;
	while (current != NULL)
	{
		current = current->next;
		++count;
	}
	return count;
}

void add_after(cnode*& list,int loc, int num) {
	if (count(list) < loc)
	{
		printf("%s \n", " error, not valid location to insert ** ");
		return;
	}

	cnode* new_node = create_node(num);
	if (list == NULL )
	{
		list = new_node;
	}
	else
	{
		cnode* current = list;
		int count = 0;
		while (current->next != NULL && ++count != loc)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}

}

void delete_num(cnode*& list, int num)
{
	if (list == NULL)
	{
		printf("%s \n", " error, number not found to delete ** ");
		return;
	}
	else
	{
		cnode* current = list;
		cnode* prev = NULL;
		while (current != NULL)
		{
			if (current->data == num)
			{
				cnode* to_delete = current;
				if (prev != NULL) {
					// if it is not the first node
					prev->next = current->next;
				}
				else {
					list = NULL;
				}
				free_node(to_delete);
				return;
			}
			prev = current;
			current = current->next;
		}
		
	}
}

void reverse(cnode*& list)
{
	cnode* current = list;
	cnode* next = NULL;
	cnode* prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	list = prev;
}

void print_list(cnode*& list)
{
	cnode* current = list;
	if (current == NULL)
	{
		printf("%s\n", "list is empty");
		return;
	}
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("%s \n", " ** ");
	return;
}

void testCList()
{
	struct cnode* list = NULL;
	print_list(list);
	add_after(list,3,9);

	delete_num(list, 3);
	append(list, 3);
	delete_num(list, 3);

	for (int i = 10; i < 20; ++i) {
		append(list, i);
	}
	
	for (int i = 8; i >= 0; --i) {
		add_at_beg(list, i);
	}
	print_list(list);
	add_after(list, 9, 9);
	delete_num(list, 17);
	print_list(list);

	reverse(list);
	print_list(list);

}

