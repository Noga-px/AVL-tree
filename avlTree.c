#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* left;
	struct node* right;
	int ht;//height of node
};
struct node* root = NULL;

struct node* rotate_left(struct node* root)
{
    struct node* right_child = root->right;
    root->right = right_child->left;
    right_child->left = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    right_child->ht = height(right_child);
 
    // return the new node after rotation
    return right_child;
}

struct node* rotate_right(struct node* root)
{
    struct node* left_child = root->left;
    root->left = left_child->right;
    left_child->right = root;
 
    // update the heights of the nodes
    root->ht = height(root);
    left_child->ht = height(left_child);
 
    // return the new node after rotation
    return left_child;
}

int balance_factor(struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	return lh - rh;
}


int height (struct node* root){
	int lh, rh;
	
	if (root == NULL){
		return 0;
	}
	if (root->left == NULL){
		lh = 0;
	}
	else{
		lh = 1 + root->left->ht;
	}
	if (root->right == NULL){
		rh = 0;
	}
	else {
		rh = 1 + root->right->ht;
	}
	if (lh > rh)
		return lh;
	return rh;
}


struct node* create_node(int data){
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	new_node->data = data;
	new_node->right = NULL;
	new_node->left = NULL;
	
	return new_node;
}

struct node* delete_node(struct node* root, int data) {
    if (root == NULL) {
		return root;
	}

    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // node found, delete it
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        } else {
            // node has two children, find the inorder successor
            struct node* temp = root->right;
            while (temp->left!= NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        	}
    	}
    }

struct node* search(struct node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

struct node* insert (struct node* root, int data){
	if(root == NULL){
		struct node* new_node = create_node(data);
		root = new_node;
	}
	else if ( data > root->data){
		root->right = insert(root->right, data);
		
		//if unbalanced, rotate!
		if (balance_factor(root) == -2){
			if (data > root->right->data){//case RR
				root = rotate_left(root);
			}
			else{ //case RL
				root->right = rotate_right(root->right);
				root = rotate_left(root);
			}			
		}		
	}
	else{
		root->left = insert(root->left, data);
		
		if (balance_factor(root) == 2){
			//CASE LL
			if (data < root->left->data){ 
				root = rotate_right(root);
			}
			//CASE LR
			else{
				root->left = rotate_left(root->left);
				root = rotate_right(root);

			}
		}
	}
	
	//get height of node
	root->ht = height(root);
	return root;
}



// inorder traversal of the tree
void inorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
 
// preorder traversal of the tree
void preorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
 
// postorder traversal of the tree
void postorder(struct node* root)
{
    if (root == NULL)
    {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main(){

	root = insert(root, 10);
	root = insert(root, 15); 
	root = insert(root, 20); 
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 16);
	root = insert(root, 17);
	root = insert(root, 8);
	root = insert(root, 6);
	
	//Soal
	//terapkan deletion dengan memberikan 4 kasus rotation(LL, RR, LR, RL)
	//lengkapi juga searching pada AVL tree ini
	
	printf("Before Deletion");
	preorder(root);
	printf("\n");
	
	printf("After deletion");
	root = delete_node(root, 15);
	preorder(root);
	printf("\n");
	
	struct node* found = search(root, 20);
	if(found != NULL){
		printf("Found node: %d\n", found->data);
	} else {
		printf("Node not found\n");
	}
	
	return 0;
}
