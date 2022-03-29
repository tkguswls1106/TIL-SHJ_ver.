#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101

typedef struct
{
	int row;  // �� '�ε���'
	int col;  // �� '�ε���'
	int value;  // �ش� �ε����� '��'
} element;  // {?, ?, ?}


typedef struct SparseMatrix
{
	element data[MAX_TERMS];  // {?, ?, ?}
	int rows;	// ���� '����'
	int cols;	// ���� '����'
	int terms; 	// ���� '����'
} SparseMatrix;

SparseMatrix transpose(int a[][10])  // (1) ������ �迭�� ����� �������� SparseMatrix ������ �����ϴ� �Լ�
{
	SparseMatrix b;

	int index = 0;
	b.rows = 8;
	b.cols = 10;
	b.terms = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (a[i][j] != 0)  // �������� ���� 0�� �ƴѰ��
			{
				b.data[index].row = i;
				b.data[index].col = j;
				b.data[index].value = a[i][j];

				index++;
			}
		}
	}

	b.terms = index;  // 0���� ���ǿ� �´� ������ŭ index�� ++���־����Ƿ�, ���� '����'�� �־��ִ°��� �´�.

	return b;
}

SparseMatrix Matrix_add(SparseMatrix a, SparseMatrix b)  // (2) �� ���� SparseMatrix�� �Ű������� �޾Ƽ� ������ ����� SparseMatrix�� ��ȯ�ϴ� �Լ�
{
	SparseMatrix c;
	c.cols = a.cols;
	c.rows = a.rows;
	int index1 = 0;  // a ����� �ٷ궧 ����� �ε���
	int index2 = 0;  // b ����� �ٷ궧 ����� �ε���
	int index3 = 0;  // c ����� �ٷ궧 ����� �ε���
	for (int i = 0; i < a.rows; i++)
	{
		for (int j = 0; j < a.cols; j++)
		{
			if (a.data[index1].row == i && a.data[index1].col == j && b.data[index2].row == i && b.data[index2].col == j)
			{
				c.data[index3].value = a.data[index1].value + b.data[index2].value;
				c.data[index3].row = a.data[index1].row;  // ������ a��İ� b����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, a�� �ִ��� b�� �ִ��� �����ϴ�.
				c.data[index3].col = a.data[index1].col;  // ������ a��İ� b����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, a�� �ִ��� b�� �ִ��� �����ϴ�.
				index1++;
				index2++;
				index3++;
			}
			else if (a.data[index1].row == i && a.data[index1].col == j)
			{
				c.data[index3].value = a.data[index1].value;
				c.data[index3].row = a.data[index1].row;  // a����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, a�� �־���Ѵ�.
				c.data[index3].col = a.data[index1].col;  // a����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, a�� �־���Ѵ�.
				index1++;
				index3++;
			}
			else if (b.data[index2].row == i && b.data[index2].col == j)
			{
				c.data[index3].value = b.data[index2].value;
				c.data[index3].row = b.data[index2].row;  // b����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, b�� �־���Ѵ�.
				c.data[index3].col = b.data[index2].col;  // b����� �� �ε����� for���� �ε����� ���� ��� �̹Ƿ�, b�� �־���Ѵ�.
				index2++;
				index3++;
			}
		}
	}
	c.terms = index3;  // 0���� ���ǿ� �´� ������ŭ index�� ++���־����Ƿ�, ���� '����'�� �־��ִ°��� �´�.

	return c;
}

void printfuc(SparseMatrix a)  // (3) SparseMatrix�� ����� ������ 0�� ������ ������ ��� ���·� ����ϴ� �Լ�
{
	printf("=======================================\n");

	int index = 0;
	for (int i = 0; i < a.rows; i++)  // �� ������ŭ �ݺ��� ����.
	{
		for (int j = 0; j < a.cols; j++)  // �� ������ŭ �ݺ��� ����.
		{
			if (a.data[index].row == i && a.data[index].col == j)
			{
				printf("%-4d", a.data[index].value);
				index++;
			}
			else
			{
				printf("0   ");
			}
		}
		printf("\n");
	}
	printf("=======================================\n");
}

int main(void)
{
	int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },  // 8, 10, 4
						 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // 8, 10, 3
							 { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };

	int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },  // 8, 10, 5
							 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };


	printf("�� �迭 a[][], b[][], c[][]�� (1)�� �̿��Ͽ� ���� SparseMatrix A, B, C�� ��ȯ �Ϸ�. A,B,C�� rows, cols, terms�� ���ʷ� ���:\n");
	SparseMatrix A = transpose(a);
	printf("%d %d %d\n", A.rows, A.cols, A.terms);
	SparseMatrix B = transpose(b);
	printf("%d %d %d\n", B.rows, B.cols, B.terms);
	SparseMatrix C = transpose(c);
	printf("%d %d %d\n\n", C.rows, C.cols, C.terms);

	printf("A+B�� (2)�� ����ϰ�,��ȯ�� ��� SparseMatrix�� (3)�� �̿��Ͽ� ����ϱ�:\n");
	printfuc(Matrix_add(A, B));
	printf("\n");

	printf("A+C�� (2)�� ����Ͽ� ��ȯ�� ��� SparseMatrix�� (3)�� �̿��Ͽ� ����ϱ�:\n");
	printfuc(Matrix_add(A, C));
	printf("\n");

	printf("B+C�� (2)�� ����Ͽ� ��ȯ�� ��� SparseMatrix�� (3)�� �̿��Ͽ� ����ϱ�:\n");
	printfuc(Matrix_add(B, C));
	printf("\n");

	return 0;
}