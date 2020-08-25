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

// 返回指向与key匹配的结点指针变量的地址
static struct node_st **find_node(struct node_st **root, int key)
{
	if (*root == NULL)
		return NULL;
	if ((*root)->data.id == key)
		return root;
	if ((*root)->data.id > key)
		find_node(&(*root)->left, key);
	else
		find_node(&(*root)->right, key);
}

// 找到最大结点
static struct node_st *find_max(const struct node_st *root)
{
	if (root == NULL)
		return NULL;
	if (root->right == NULL)
		return (void *)root;
	find_max(root->right);
}

// 求得一颗树中的最小结点
static struct node_st *find_min(const struct node_st *root)
{
	if (root == NULL)
		return NULL;
	if (root->left == NULL)
		return (void *)root;
	find_min(root->left);
}

// 删除指定结点
static void delete_node(struct node_st **f)
{
	struct node_st *cur, *l, *r;	

	cur = *f;
	l = cur->left;
	r = cur->right;

	if (l != NULL) {
		*f = l;
		find_max(l)->right = r;
	} else {
		*f = r;
	}
	cur->left = cur->right = NULL;
	free(cur);
}


// 删除指定结点
int remove_node(struct node_st **root, int key)
{
	// 找到指向待删除结点的指针	
	struct node_st **f = find_node(root, key);
	if (f == NULL)
		return -1;
	// *f就是待删除的结点--->左子树为根
	delete_node(f);	

	return 0;
}

// 销毁
void destroy_tree(struct node_st **root)
{
	if (*root == NULL)	
		return ;
	destroy_tree(&(*root)->left);
	destroy_tree(&(*root)->right);

//	printf("%d will be destroyed\n", (*root)->data.id);
	free(*root);
	*root = NULL;
}

// 调式 打印树
void draw_tree(struct node_st *root, int col)
{
	if (root == NULL)		
		return ;
	draw_tree(root->right, col+1);
	for (int i = 0; i < col; i++) {
		printf("    ");
	}
	printf("%d\n", root->data.id);
	draw_tree(root->left, col+1);
}

// 树的结点的个数
int tree_nodes(const struct node_st *root)
{
	if (root == NULL)
		return 0;
	return tree_nodes(root->left) + tree_nodes(root->right) + 1;
}

static void tree_turn_right(struct node_st **root)
{
	struct node_st *cur, *l;

	cur = *root;
	l = cur->left;

	*root = l;
	cur->left = NULL;
	find_max(l)->right = cur;
}

static void tree_turn_left(struct node_st **root)
{
	struct node_st *cur, *r;

	cur = *root;
	r = cur->right;

	*root = r;
	cur->right = NULL;
	find_min(r)->left = cur;
}
// 平衡二叉树
void tree_balance(struct node_st **root)
{
	int n;

	if (*root == NULL)	
		return ;
	while (1) {
		n = tree_nodes((*root)->left) - tree_nodes((*root)->right);
		if (n > 1) {
			// 向右转
			tree_turn_right(root);
		}
		if (n < -1) {
			// 向左转
			tree_turn_left(root);
		} else 
			break;
	}
	tree_balance(&(*root)->left);
	tree_balance(&(*root)->right);
}

int main(void)
{
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	struct node_st *tree = NULL;
	struct data_st n;

	for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		n.id = arr[i];	
		tree_insert(&tree, &n);
	}

	traval_mid(tree);

#if 0
	// 删除
	printf("****************删除*****************\n");
	remove_node(&tree, 6);
	traval_mid(tree);
	printf("****************删除*****************\n");
	remove_node(&tree, 5);
	traval_mid(tree);
	printf("****************删除*****************\n");
	remove_node(&tree, 2);
	traval_mid(tree);
#endif
	draw_tree(tree, 0);

	printf("***************平衡******************\n");
	tree_balance(&tree);
	draw_tree(tree, 0);

	destroy_tree(&tree);

	return 0;
}




