#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>

struct node // ��������� ��� ������������� ����� ������
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

node* find(node* p, int k) // ����� ����� k � ������ p
{
    if (!p) return 0; // � ������ ������ ����� �� ������
    if (k == p->key)
        return p;
    if (k < p->key)
        return find(p->left, k);
    else
        return find(p->right, k);
}

node* insert(node* p, int k) // ����������������� ������� ������ ���� � ������ k � ������ p
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

int getsize(node* p) // ������� ��� ���� size, �������� � ������� ��������� (t=NULL)
{
	if (!p) return 0;
	return p->size;
}

void fixsize(node* p) // ������������ ����������� ������� ������
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

node* rotateright(node* p) // ������ ������� ������ ���� p
{
	node* q = p->left;
	if (!q) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ ���� q
{
	node* p = q->right;
	if (!p) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

node* insertroot(node* p, int k) // ������� ������ ���� � ������ k � ������ ������ p 
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

node* join(node* p, node* q) // ����������� ���� ��������
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

int height(node* p) // ���������� ������ ������
{
	if (!p) return 0;
	int left_height = height(p->left);
	int right_height = height(p->right);
	return 1 + (left_height > right_height ? left_height : right_height);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL)); // ������������� ���������� ��������� �����

	int num_elements[] = { 10, 100, 1000 }; // ������ ��� ���������� ���������
	for (int i = 0; i < 3; i++)
	{
		node* root = NULL; // ��������� ������ ������
		for (int j = 0; j < num_elements[i]; j++)
		{
			root = insert(root, rand() % 1000000); // ������� ���������� ��������
		}

		printf("������ ������ � %d ����������: %d\n", num_elements[i], height(root));
	}

	return 0;
}
