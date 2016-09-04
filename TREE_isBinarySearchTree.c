#include <stdio.h>
#include <stdlib.h>

#define MIN_INT 0
#define MAX_INT 1000000

struct Node{
	int val;
	struct Node *left;
	struct Node *right;
};

struct Node* buildBST(int a[], int start, int end){
	if(start <= end){
		int mid = (start+end)/2;
		struct Node* root = (struct Node*)malloc(sizeof(struct Node));
		root->val = a[mid];
		root->left = buildBST(a, start, mid-1);
		root->right = buildBST(a, mid+1, end);
		return root;
	}
	return NULL;
}

// Inorder traversal
void inorder_traversal(struct Node* root){
	if(root == NULL) return;
	inorder_traversal(root->left);
	printf("%d ", root->val);
	inorder_traversal(root->right);
}


/* Returns true if the given tree is a BST and its
   values are >= min and <= max. */
int isBSTUtil(struct Node* node, int min, int max)
{
  if (node==NULL) return 1;

  if (node->val < min || node->val > max)
     return 0;

  int leftIsBST = isBSTUtil(node->left, min, node->val-1);
  int rightIsBST = isBSTUtil(node->right, node->val+1, max);
  return leftIsBST && rightIsBST;
}


int isBST(struct Node* root){
	return isBSTUtil(root, MIN_INT, MAX_INT);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct Node* newNode(int data)
{
  struct Node* node = (struct Node*)
                       malloc(sizeof(struct Node));
  node->val = data;
  node->left = NULL;
  node->right = NULL;

  return(node);
}

int main(){
	int a[8] = {1, 2, 3, 4, 5, 7, 6, 8};

	struct Node *root = buildBST(a, 0, 7);
	inorder_traversal(root);
	int result = isBST(root);
	printf("\nIsBinarySearchTree: %s\n", result?"True":"False");

	return 0;
}
