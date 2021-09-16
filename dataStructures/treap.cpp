// no tengo idea como funciona treap xD, el de benq es mejor si se aprende a usar
struct node {
    node *left, *right;
    int weight, size;
    char value;
    node(char v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
    }
};

int size(node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}

void split(node *treap, node *&left, node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    }
    else {
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left) - 1);
            left = treap;
        }
        else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void merge(node *&treap, node *left, node *right) {
    if (left == NULL) treap = right;
    else if (right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        }
        else {
            merge(right->left, left, right->left);
            treap = right;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void print(node *treap) {
    if (treap == NULL) return;
    print(treap->left);
    cout << treap->value;
    print(treap->right);
}
