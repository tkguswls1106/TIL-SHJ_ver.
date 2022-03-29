#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101

typedef struct
{
	int row;  // 행 '인덱스'
	int col;  // 열 '인덱스'
	int value;  // 해당 인덱스의 '값'
} element;  // {?, ?, ?}


typedef struct SparseMatrix
{
	element data[MAX_TERMS];  // {?, ?, ?}
	int rows;	// 행의 '개수'
	int cols;	// 열의 '개수'
	int terms; 	// 항의 '개수'
} SparseMatrix;

SparseMatrix transpose(int a[][10])  // (1) 이차원 배열에 저장된 희소행렬을 SparseMatrix 구조로 저장하는 함수
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
			if (a[i][j] != 0)  // 희소행렬의 값이 0이 아닌경우
			{
				b.data[index].row = i;
				b.data[index].col = j;
				b.data[index].value = a[i][j];

				index++;
			}
		}
	}

	b.terms = index;  // 0부터 조건에 맞는 개수만큼 index를 ++해주었으므로, 항의 '개수'로 넣어주는것이 맞다.

	return b;
}

SparseMatrix Matrix_add(SparseMatrix a, SparseMatrix b)  // (2) 두 개의 SparseMatrix를 매개변수로 받아서 덧셈한 결과로 SparseMatrix를 반환하는 함수
{
	SparseMatrix c;
	c.cols = a.cols;
	c.rows = a.rows;
	int index1 = 0;  // a 행렬을 다룰때 사용할 인덱스
	int index2 = 0;  // b 행렬을 다룰때 사용할 인덱스
	int index3 = 0;  // c 행렬을 다룰때 사용할 인덱스
	for (int i = 0; i < a.rows; i++)
	{
		for (int j = 0; j < a.cols; j++)
		{
			if (a.data[index1].row == i && a.data[index1].col == j && b.data[index2].row == i && b.data[index2].col == j)
			{
				c.data[index3].value = a.data[index1].value + b.data[index2].value;
				c.data[index3].row = a.data[index1].row;  // 어차피 a행렬과 b행렬의 행 인덱스가 for문의 인덱스와 같을 경우 이므로, a로 넣던지 b로 넣던지 동일하다.
				c.data[index3].col = a.data[index1].col;  // 어차피 a행렬과 b행렬의 열 인덱스가 for문의 인덱스와 같을 경우 이므로, a로 넣던지 b로 넣던지 동일하다.
				index1++;
				index2++;
				index3++;
			}
			else if (a.data[index1].row == i && a.data[index1].col == j)
			{
				c.data[index3].value = a.data[index1].value;
				c.data[index3].row = a.data[index1].row;  // a행렬의 행 인덱스만 for문의 인덱스와 같을 경우 이므로, a로 넣어야한다.
				c.data[index3].col = a.data[index1].col;  // a행렬의 열 인덱스만 for문의 인덱스와 같을 경우 이므로, a로 넣어야한다.
				index1++;
				index3++;
			}
			else if (b.data[index2].row == i && b.data[index2].col == j)
			{
				c.data[index3].value = b.data[index2].value;
				c.data[index3].row = b.data[index2].row;  // b행렬의 행 인덱스만 for문의 인덱스와 같을 경우 이므로, b로 넣어야한다.
				c.data[index3].col = b.data[index2].col;  // b행렬의 열 인덱스만 for문의 인덱스와 같을 경우 이므로, b로 넣어야한다.
				index2++;
				index3++;
			}
		}
	}
	c.terms = index3;  // 0부터 조건에 맞는 개수만큼 index를 ++해주었으므로, 항의 '개수'로 넣어주는것이 맞다.

	return c;
}

void printfuc(SparseMatrix a)  // (3) SparseMatrix에 저장된 내용을 0을 포함한 이차원 행렬 형태로 출력하는 함수
{
	printf("=======================================\n");

	int index = 0;
	for (int i = 0; i < a.rows; i++)  // 행 개수만큼 반복문 돌림.
	{
		for (int j = 0; j < a.cols; j++)  // 열 개수만큼 반복문 돌림.
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


	printf("위 배열 a[][], b[][], c[][]를 (1)을 이용하여 각각 SparseMatrix A, B, C로 변환 완료. A,B,C의 rows, cols, terms를 차례로 출력:\n");
	SparseMatrix A = transpose(a);
	printf("%d %d %d\n", A.rows, A.cols, A.terms);
	SparseMatrix B = transpose(b);
	printf("%d %d %d\n", B.rows, B.cols, B.terms);
	SparseMatrix C = transpose(c);
	printf("%d %d %d\n\n", C.rows, C.cols, C.terms);

	printf("A+B를 (2)로 계산하고,반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기:\n");
	printfuc(Matrix_add(A, B));
	printf("\n");

	printf("A+C를 (2)로 계산하여 반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기:\n");
	printfuc(Matrix_add(A, C));
	printf("\n");

	printf("B+C를 (2)로 계산하여 반환된 결과 SparseMatrix를 (3)을 이용하여 출력하기:\n");
	printfuc(Matrix_add(B, C));
	printf("\n");

	return 0;
}