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

int tree_insert(struct node_st **root, const struct node_st *d)
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

	if ((*root)->data.id <= d->data.id) {
		tree_insert(&(*root)->right, d);	
	} else {
		tree_insert(&(*root)->left, d);
	}
}




