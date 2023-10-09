#include <iostream>
#include <queue>
using namespace std;

struct node {
    string key;
    struct node *left, *right;
};

struct node *newNode(string key) {
    auto *temp = new node;
    temp->key = key;
    temp->left = temp->right = nullptr;
    return temp;
}


void simmetric(node *root){
    if (root != nullptr) {
        simmetric(root->left);
        cout << root->key << " -> ";
        simmetric(root->right);
    }
}
void straight(node *root){
    if (root != nullptr){
        cout << root->key << " -> ";
        simmetric(root->left);
        simmetric(root->right);
    }
}

struct node *insert(node *node, string key) {
    if (node == nullptr) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return node;
}

void depth(node* root, string k){
    if(root == nullptr) return;
    int depth = -1;
    queue<node*> q;
    q.push(root);
    int level = 0;
    while(!q.empty()){
        int n = q.size();
        for(int i = 0; i<n; i++){
            node* frontNode = q.front();
            q.pop();
            if(frontNode->key == k) depth = level;
            if(frontNode->left) q.push(frontNode->left);
            if(frontNode->right) q.push(frontNode->right);
        }
        level++;
    }
    cout<<"Depth of node with key " << k << " is " <<depth<<endl;
}
struct node *minValueNode(struct node *node) {
    struct node *current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

struct node *deleteNode(struct node *root, string key) {
    if (root == nullptr) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            struct node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            struct node *temp = root->left;
            delete root;
            return temp;
        }

        struct node *temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main() {
    struct node *root = nullptr;
    root = insert(root, "moscow");
    root = insert(root, "peterburg");
    root = insert(root, "tula");
    root = insert(root, "yaroslavl");
    root = insert(root, "samara");
    root = insert(root, "tambov");
    root = insert(root, "rostov");
    root = insert(root, "kazan");

    cout << "Отсортированный обход: ";
    simmetric(root);

    cout << "\nПосле удаления moscow\n";
    root = deleteNode(root, "moscow");

    cout << "Прямой обход: ";
    straight(root);
    cout << endl;
    depth(root, "rostov");
}
