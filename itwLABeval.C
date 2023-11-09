#include <stdio.h>
#include <stdlib.h>
// Structure for a splay tree node
typedef struct Node {
char key;
struct Node* left;
struct Node* right;
} Node;
// Function to perform a right rotation
Node* rightRotate(Node* x) {
Node* y = x->left;
x->left = y->right;
y->right = x;
return y;
}
// Function to perform a left rotation
Node* leftRotate(Node* x) {
Node* y = x->right;
x->right = y->left;
y->left = x;
return y;
}
// Function to splay a node with the given key to the root
Node* splay(Node* root, char key) {
if (root == NULL || root->key == key)
return root;
if (key < root->key) {
if (root->left == NULL)
return root;
// Zig-Zig (Left Left)
if (key < root->left->key) {
root->left->left = splay(root->left->left, key);
root = rightRotate(root);
}
// Zig-Zag (Left Right)
else if (key > root->left->key) {
root->left->right = splay(root->left->right, key);

if (root->left->right != NULL)
root->left = leftRotate(root->left);
}
return (root->left == NULL) ? root : rightRotate(root);
} else {
if (root->right == NULL)
return root;
// Zag-Zig (Right Left)
if (key < root->right->key) {
root->right->left = splay(root->right->left, key);
if (root->right->left != NULL)
root->right = rightRotate(root->right);
}
// Zag-Zag (Right Right)
else if (key > root->right->key) {
root->right->right = splay(root->right->right, key);
root = leftRotate(root);
}
return (root->right == NULL) ? root : leftRotate(root);
}
}
// Function to insert a key into the splay tree
Node* insert(Node* root, char key) {
if (root == NULL) {
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->key = key;
newNode->left = newNode->right = NULL;
return newNode;
}
// Splay the node to be inserted to the root
root = splay(root, key);
// If key is already present, return the root
if (root->key == key)
return root;
Node* newNode = (Node*)malloc(sizeof(Node));
newNode->key = key;
// Insert the new node at the appropriate position
if (key < root->key) {
newNode->left = root->left;
newNode->right = root;
root->left = NULL;

} else {
newNode->right = root->right;
newNode->left = root;
root->right = NULL;
}
return newNode;
}
// Function to print the splay tree in inorder traversal
void inorder(Node* root) {
if (root != NULL) {
inorder(root->left);
printf("%c ", root->key);
inorder(root->right);
}
}
// Function to free the memory allocated for the splay tree
void freeTree(Node* root) {
if (root != NULL) {
freeTree(root->left);
freeTree(root->right);
free(root);
}
}
int main() {
Node* root = NULL;
char keys[] = {'F', 'S', 'Q', 'K', 'C', 'L', 'H', 'T', 'V', 'W', 'M', 'R',
'N', 'P', 'A', 'B', 'X', 'Y', 'D', 'Z', 'E'};
for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
root = insert(root, keys[i]);
printf("Inserting %c: ", keys[i]);
inorder(root);
printf("\n");
}
freeTree(root);
return 0;
}