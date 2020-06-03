#pragma once

template<class Data>
struct node
{
	int key;
	Data data;
	unsigned char height;
	node* left;
	node* right;
	node(int k, Data d) { key = k; data = d; left = right = 0; height = 1; }
};



template<class Data>
class AVLTree
{
protected:
	node<Data>* tree;

	unsigned char height(node<Data>* p);
	int bfactor(node<Data>* p);
	void fixheight(node<Data>* p);
	node<Data>* rotateright(node<Data>* p); // правый поворот вокруг p
	node<Data>* rotateleft(node<Data>* q); // левый поворот вокруг q
	node<Data>* balance(node<Data>* p); // балансировка узла p
	node<Data>* findmin(node<Data>* p); // поиск узла с минимальным ключом в дереве p 
	node<Data>* removemin(node<Data>* p); // удаление узла с минимальным ключом из дерева p
	node<Data>* insertRecur(node<Data>* p, int k, Data d); // вставка ключа k в дерево с корнем p
	node<Data>* removeRecur(node<Data>* p, int k); // удаление ключа k из дерева p

public:
	AVLTree(int key = 0, Data d = NULL) { tree = new node<Data>(key, d); }
	void insert(int k, Data d) { insertRecur(tree, k, d);	 } 
	void remove(int k) {	removeRecur(tree, k);	} 
	Data& find(int k);
};



template<class Data>
unsigned char AVLTree<Data>::height(node<Data>* p)
{
	return p ? p->height : 0;
}

template<class Data>
int AVLTree<Data>::bfactor(node<Data>* p)
{
	return height(p->right) - height(p->left);
}

template<class Data>
void AVLTree<Data>::fixheight(node<Data>* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

template<class Data>
node<Data>* AVLTree<Data>::rotateright(node<Data>* p) // правый поворот вокруг p
{
	node<Data>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

template<class Data>
node<Data>* AVLTree<Data>::rotateleft(node<Data>* q) // левый поворот вокруг q
{
	node<Data>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

template<class Data>
node<Data>* AVLTree<Data>::balance(node<Data>* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

template<class Data>
node<Data>* AVLTree<Data>::findmin(node<Data>* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

template<class Data>
node<Data>* AVLTree<Data>::removemin(node<Data>* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

template<class Data>
node<Data>* AVLTree<Data>::insertRecur(node<Data>* p, int k, Data d) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node<Data>(k, d);
	if (k < p->key)
		p->left = insertRecur(p->left, k, d);
	else
		p->right = insertRecur(p->right, k, d);
	return balance(p);
}

template<class Data>
node<Data>* AVLTree<Data>::removeRecur(node<Data>* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = removeRecur(p->left, k);
	else if (k > p->key)
		p->right = removeRecur(p->right, k);
	else //  k == p->key 
	{
		node<Data>* q = p->left;
		node<Data>* r = p->right;
		delete p;
		if (!r) return q;
		node<Data>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

template<class Data>
Data& AVLTree<Data>::find(int k)
{
	node<Data>* temp = tree;
	while (k != temp->key)
	{
		if (k <= temp->key)
			temp = temp->left;
		else temp = temp->right;
	}
	return temp->data;
}
