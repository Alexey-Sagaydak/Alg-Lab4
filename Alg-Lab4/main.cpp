#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* create_node(int key) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else {
        root->right = insert(root->right, key);
    }
    return root;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
    return max(left_height, right_height) + 1;
}

void random_binary_tree(int keys[], int num_elements, struct TreeNode** root) {
    *root = NULL;
    for (int i = 0; i < num_elements; i++) {
        *root = insert(*root, keys[i]);
    }
}

int experiment(int num_elements) {
    int* keys = (int*)malloc(num_elements * sizeof(int));
    if (keys == NULL) {
        return -1;
    }
    for (int i = 0; i < num_elements; i++) {
        keys[i] = rand() % (num_elements * 10) + 1;
    }
    struct TreeNode* root;
    random_binary_tree(keys, num_elements, &root);
    free(keys);
    return height(root);
}

int main() {
    int num_elements_list[] = { 10, 100, 1000 };
    int num_experiments = sizeof(num_elements_list) / sizeof(num_elements_list[0]);

    for (int i = 0; i < num_experiments; i++) {
        int num_elements = num_elements_list[i];
        int tree_height = experiment(num_elements);
        printf("For %d elements, tree height: %d\n", num_elements, tree_height);
    }

    return 0;
}
