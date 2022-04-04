#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node *Nodeptr;
typedef struct Node
{
	int data;
	Nodeptr left, right;
} Node;

typedef struct stack
{
	Nodeptr arr[MAX];
	int top;
} stack;

void init(stack *s)
{
	s->top = -1;
}

void push(stack *s, Nodeptr x)
{
	(s->top)++;
	s->arr[s->top] = x;
}

Nodeptr pop(stack *s)
{
	Nodeptr x = s->arr[s->top];
	(s->top)--;
	return x;
}

struct stck
{
	Nodeptr n;
	int flag;
} s[MAX];

int search(Nodeptr temp, int key)
{
	while (temp != NULL)
	{
		if (key > temp->data)
			temp = temp->right;
		else if (key < temp->data)
			temp = temp->left;
		else
			return 1;
	}

	return 0;
}

Nodeptr newNode(int data)
{
	Nodeptr temp = (struct Node *)malloc(sizeof(struct Node));

	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

Nodeptr insert(Nodeptr root, int data)
{
	Nodeptr temp = root;
	Nodeptr newnode = newNode(data);

	if (root == NULL)
		return newnode;

	while (temp != NULL)
	{
		if (data > temp->data)
		{
			if (temp->right == NULL)
			{
				temp->right = newnode;
				return root;
			}
			else
				temp = temp->right;
		}
		else
		{
			if (temp->left == NULL)
			{
				temp->left = newnode;
				return root;
			}
			else
				temp = temp->left;
		}
	}
	return root;
}

void iterin(Nodeptr ptr)
{
	stack s;
	init(&s);

	while (ptr != NULL)
	{
		while (ptr != NULL)
		{
			if (ptr->right != NULL)
				push(&s, ptr->right);
			push(&s, ptr);
			ptr = ptr->left;
		}

		ptr = pop(&s);

		while (s.top != -1 && ptr->right == NULL)
		{
			printf("%d ", ptr->data);
			ptr = pop(&s);
		}

		printf("%d ", ptr->data);
		ptr = (s.top != -1) ? pop(&s) : NULL;
	}
}

void iterpre(Nodeptr ptr)
{
	stack s;
	init(&s);
	push(&s, ptr);

	while (s.top != -1)
	{
		ptr = pop(&s);
		printf("%d ", ptr->data);

		if (ptr->right != NULL)
			push(&s, ptr->right);
		if (ptr->left != NULL)
			push(&s, ptr->left);
	}
}

void iterpost(Nodeptr root)
{
	if (root == NULL)
	{
		printf("Empty tree!\n");
		return;
	}

	int top = -1;

	while (1)
	{
		while (root != NULL)
		{
			top++;
			s[top].n = root;
			s[top].flag = 1;
			root = root->left;
		}

		while (s[top].flag == 0)
		{
			root = s[top].n;
			top--;
			printf("%d ", root->data);

			if (top == -1)
				return;
		}

		root = s[top].n;
		s[top].flag = 0;
		root = root->right;
	}
}

int main()
{
	Nodeptr root = NULL;
	int ele, key;

	printf("Enter root element : ");
	scanf("%d", &ele);
	root = insert(root, ele);

	while (ele != -1)
	{
		printf("Enter no. to insert (-1 to exit) : ");
		scanf("%d", &ele);
		if (ele != -1)
			insert(root, ele);
	}

	printf("Enter the search element:\n");
	scanf("%d", &key);

	if (search(root, key) == 1)
		printf("Element %d is found in BST\n", key);
	else
	{
		printf("Element %d is inserted in BST\n", key);
		insert(root, key);
	}
	printf("\nIterative Inorder traversal is   : ");
	iterin(root);

	printf("\nIterative Preorder traversal is  : ");
	iterpre(root);

	printf("\nIterative Postorder traversal is : ");
	iterpost(root);

	printf("\n");
}