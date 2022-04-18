#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Nodeptr;
typedef struct Node
{
    int data;
    Nodeptr left, right;
} Node;

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

static int count = 0;

int countnodes(Nodeptr root)
{
    if(root != NULL)
    {
        countnodes(root->left);
        count++;
        countnodes(root->right);
    }
    return count;
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

    printf("Number of nodes in tree = %d\n",countnodes(root));
    return 0;
    
}