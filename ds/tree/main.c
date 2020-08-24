#include <stdio.h>
#include <stdlib.h>


struct data_st {
	int id;
};

// 树的结点数据类型
struct node_st {
	struct data_st data;
	struct node_st *left;
	struct node_st *right;
};

int tree_insert_r(struct node_st **root, const struct data_st *d)
{
	struct node_st *new;

	if (*root == NULL) {
		new = malloc(sizeof(struct node_st));	
		if (NULL == new)
			return -1;
		// memcpy(&new->data, d, sizeof(struct data_st));
		new->data = *d;
		new->left = new->right = NULL;
		*root = new;
		return 0;
	}

	if ((*root)->data.id <= d->id) {
		tree_insert_r(&(*root)->right, d);	
	} else {
		tree_insert_r(&(*root)->left, d);
	}
}

int tree_insert(struct node_st **root, const struct data_st *d)
{
	struct node_st *new;
	struct node_st **p;
	
	new = malloc(sizeof(struct node_st));	
	if (NULL == new)
		return -1;
	// memcpy(&new->data, d, sizeof(struct data_st));
	new->data = *d;
	new->left = new->right = NULL;

	p = root;
	while (*p != NULL) {
		if ((*p)->data.id >= d->id) {
			p = &(*p)->left;
		} else {
			p = &(*p)->right;
		}
	}
	*p = new;

	return 0;
}

void traval_mid(const struct node_st *root)
{
	if (root == NULL)	
		return;
	traval_mid(root->left);
	printf("%d\n", root->data.id);
	traval_mid((void *)root->right);
}

int main(void)
{
	int arr[] = {5,4,8,10,6,9,7,3,1,2};
	struct node_st *tree = NULL;
	struct data_st n;

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		n.id = arr[i];	
		tree_insert(&tree, &n);
	}

	traval_mid(tree);

	return 0;
}




