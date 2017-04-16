#include "fibnacci.h"

void Fibonacci::insert(int index, int dist) {
	FibNode *tmp = queue[index];
	tmp->distance = dist;
	if (root == NULL) {
		root = tmp;
	}
	else {
		tmp->left = root->left;
		root->left->right = tmp;
		tmp->right = root;
		root->left = tmp;
		if (tmp->distance < root->distance)root = tmp;
	}
}
void Fibonacci::merge(FibNode *r) {
	FibNode *tmp;

	if (root == NULL) {
		root = r;
		return;
	}
	if (r == NULL)return;

	if (r->distance < root->distance)swap<FibNode>(r, root);
	tmp = root->right;
	root->right = r->right;
	r->right->left = root;
	r->right = tmp;
	tmp->left = r;
}
void Fibonacci::remove(FibNode *r) {
	r->left->right = r->right;
	r->right->left = r->left;
	if (r->parent)r->parent->degree--;
	r->parent = NULL;
}
void Fibonacci::link(FibNode *r1, FibNode *r2) {
	if (r1->child == NULL) {
		r1->child = r2;
		r2->parent = r1;
		r1->degree++;
		return;
	}
	r2->left = r1->child->left;
	r2->right = r1->child;
	r1->child->left->right = r2;
	r1->child->left = r2;
	r2->parent = r1;
	r1->degree++;
}
void Fibonacci::consolidate() {
	int i, d, maxRoot = 0;
    FibNode *x, *y, *tmp;
	memset(cons, 0, MAX_ROOT * sizeof(FibNode *));
    while (root != NULL) {
		x = root;
		if (root->right == root) {
			root = NULL;
		}
		else {
			root = root->right;
			tmp = root->left;
			remove(root->left);
			tmp->left = tmp;
			tmp->right = tmp;
		}
        d = x->degree;
        while (cons[d] != NULL) {
			y = cons[d];
			if (x->distance > y->distance)swap<FibNode *>(&x, &y);
			link(x, y);
			cons[d] = NULL;
			d++;
		}
		cons[d] = x;
		if (d > maxRoot)maxRoot = d;
	}
	for (i = 0; i < maxRoot+1; i++) {
		if (cons[i] != NULL) {
			if (root == NULL)root = cons[i];
			else insert(cons[i]->index, cons[i]->distance);
		}
	}
}
void Fibonacci::cascade(FibNode *p) {
	FibNode *parent = p->parent;
	if (parent == NULL)return;
	if (p->mark == 0)p->mark = 1;
	else {
		remove(p);
		if (p->right == p)parent->child = NULL;
		else parent->child = p->right;

		p->left = p->right = p;
		p->mark = false;
		insert(p->index, p->distance);
		cascade(parent);
	}
}

FibNode Fibonacci::get() {
	if (root == NULL)return FibNode(-1);
	if (root->child == NULL) {
		FibNode ret = *root;
		remove(root);
		if (root->right == root) {
			root = NULL;
		}
		else {
			root = root->right;
			int start = root->index;
			FibNode *minNode = root;
			do {
				root = root->right;
				if (root->distance < minNode->distance)minNode = root;
			} while (root->index != start);
			root = minNode;
			consolidate();
		}
		return ret;
	}

	FibNode *min = root;
	root->child->parent = NULL;
	merge(root->child);
	remove(root);
	if (root->right == root) {
		root = NULL;
		return FibNode(-1);
	}
	root = root->right;

	int start = root->index;
	FibNode *minNode = root;
	do {
		root->parent = NULL;
		root = root->right;
		if (root->distance < minNode->distance)minNode = root;
	} while (root->index != start);
	root = minNode;

	consolidate();
	totalNum--;

	return *min;
}
void Fibonacci::decrease(int index, int dist) {
	FibNode *tmp = queue[index];
	if (tmp->distance < 0) {
		insert(index, dist);
		totalNum++;
	}
	else {
		FibNode *parent;
		if (tmp->distance < dist)return;
		tmp->distance = dist;
		parent = tmp->parent;
		if (parent != NULL && tmp->distance < parent->distance) {
			remove(tmp);
			if (tmp->right == tmp)parent->child = NULL;
			else parent->child = tmp->right;
			
			tmp->left = tmp->right = tmp;
			tmp->mark = false;
			insert(tmp->index, tmp->distance);
			cascade(parent);
		}

		if (tmp->distance < root->distance)root = tmp;
	}
}