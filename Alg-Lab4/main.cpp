#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>

struct node // структура дл€ представлени€ узлов дерева
{
	int key;
	int size;
	node* left;
	node* right;
	node(int k) { key = k; left = right = 0; size = 1; }
};

node* find(node* p, int k);
node* insert(node* p, int k);
int getsize(node* p);
void fixsize(node* p);
node* rotateright(node* p);
node* rotateleft(node* q);
node* insertroot(node* p, int k);
node* insertroot(node* p, int k);
node* join(node* p, node* q);
int height(node* p);

node* find(node* p, int k) // поиск ключа k в дереве p
{
    if (!p) return 0; // в пустом дереве можно не искать
    if (k == p->key)
        return p;
    if (k < p->key)
        return find(p->left, k);
    else
        return find(p->right, k);
}

node* insert(node* p, int k) // рандомизированна€ вставка нового узла с ключом k в дерево p
{
	if (!p) return new node(k);
	if (rand() % (p->size + 1) == 0)
		return insertroot(p, k);
	if (p->key > k)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	fixsize(p);
	return p;
}

int getsize(node* p) // обертка дл€ пол€ size, работает с пустыми деревь€ми (t=NULL)
{
	if (!p) return 0;
	return p->size;
}

void fixsize(node* p) // установление корректного размера дерева
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

node* rotateright(node* p) // правый поворот вокруг узла p
{
	node* q = p->left;
	if (!q) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг узла q
{
	node* p = q->right;
	if (!p) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, int k) // вставка нового узла с ключом k в корень дерева p 
{
	if (!p) return new node(k);
	if (k < p->key)
	{
		p->left = insertroot(p->left, k);
		return rotateright(p);
	}
	else
	{
		p->right = insertroot(p->right, k);
		return rotateleft(p);
	}
}

node* join(node* p, node* q) // объединение двух деревьев
{
	if (!p) return q;
	if (!q) return p;
	if (rand() % (p->size + q->size) < p->size)
	{
		p->right = join(p->right, q);
		fixsize(p);
		return p;
	}
	else
	{
		q->left = join(p, q->left);
		fixsize(q);
		return q;
	}
}

int height(node* p) // вычисление высоты дерева
{
	if (!p) return 0;
	int left_height = height(p->left);
	int right_height = height(p->right);
	return 1 + (left_height > right_height ? left_height : right_height);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL)); // инициализаци€ генератора случайных чисел

	int num_elements[] = { 10, 100, 1000 }; // массив дл€ количества элементов
	for (int i = 0; i < 3; i++)
	{
		node* root = NULL; // начальное пустое дерево
		for (int j = 0; j < num_elements[i]; j++)
		{
			root = insert(root, rand() % 1000000); // вставка случайного элемента
		}

		printf("¬ысота дерева с %d элементами: %d\n", num_elements[i], height(root));
	}

	return 0;
}
