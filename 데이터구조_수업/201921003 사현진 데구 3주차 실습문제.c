#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101
#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101

typedef struct { // 다항식 구조체 타입 선언
	int degree; // 다항식의 차수
	float coef[MAX_DEGREE]; // 다항식의 계수
} polynomial;

typedef struct { // 다항식 구조체 타입 선언
	int degree; // 다항식의 차수
	float coef[MAX_DEGREE]; // 다항식의 계수
} polynomial2;

typedef struct {
	int coef;
	int expon;
} polynomial3;

polynomial3 terms[MAX_TERMS];

typedef struct {
	int coef;
	int expon;
} polynomial4;

void attach(int coef, int expon);
char compare(int a, int b);

int avail = 0;

polynomial poly_minus(polynomial A, polynomial B)
{
	polynomial C; // 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수

	while (Apos <= A.degree && Bpos <= B.degree)
	{
		if (degree_a > degree_b)  // A항 > B항
		{
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}

		else if (degree_a == degree_b)  // A항 == B항
		{
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--; degree_b--;
		}

		else  // B항 > A항
		{
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}

	return C;
}

void poly_minus2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)  // C = A + B
{
	int tempcoef;

	avail = *Cs;
	int a = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon))
		{
		case '>': // A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++;
			break;

		case '=': // A의 차수 == B의 차수
			tempcoef = terms[As].coef - terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++;
			Bs++;
			break;

		case '<': // A의 차수 < B의 차수
			attach(-1 * terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}

	for (; As <= Ae; As++)  // A의 나머지 항들을 이동함
		attach(terms[As].coef, terms[As].expon);

	for (; Bs <= Be; Bs++)  // B의 나머지 항들을 이동함
		attach(-1 * terms[Bs].coef, terms[Bs].expon);
	if (avail == a)
		avail++;
	*Ce = avail - 1;
}

void print_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);

	printf("%3.1f \n", p.coef[p.degree]);
}

void print_poly2(polynomial2 p)
{
	for (int i = p.degree; i > 0; i--)
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);

	printf("%3.1f \n", p.coef[p.degree]);
}

void print_poly3(int s, int e)
{
	if (terms[s].coef == 0 && terms[s].expon == 0)
		printf("");
	else {
		for (int i = s; i < e; i++)
			printf("%dx^%d + ", terms[i].coef, terms[i].expon);
		printf("%dx^%d\n", terms[e].coef, terms[e].expon);
	}
}

void problem1_1()
{
	polynomial a, b, c;

	printf("<첫번째 다항식>\n");
	printf("첫번째 다항식의 최고 차수: ");
	scanf_s("%d", &a.degree);
	printf("각 항의 계수를 차례로 입력 : ");
	for (int i = 0; i <= a.degree; i++)
		scanf_s("%f", &a.coef[i]);
	printf("첫번째 다항식 출력: ");
	print_poly(a);
	printf("\n\n");

	printf("<두번째 다항식>\n");
	printf("두번째 다항식의 최고 차수 : ");
	scanf_s("%d", &b.degree);
	printf("각 항의 계수를 차례로 입력: ");
	for (int i = 0; i <= b.degree; i++)
		scanf_s("%f", &b.coef[i]);
	printf("두번째 다항식 출력: ");
	print_poly(b);

	printf("\n<두 다항식의 뺄셈>\n");
	print_poly(a);
	print_poly(b);
	c = poly_minus(a, b);
	printf("----------------------------------------------------------\n");
	printf("뺄셈 결과: ");
	print_poly(c);

	printf("\n");

	return 0;
}

int eval(polynomial2 P, int x)
{
	int hamsu = 0;
	int chasu = P.degree;
	for (int i = 0; i <= P.degree; i++)
	{
		hamsu += P.coef[i] * pow(x, chasu);
		chasu--;
	}

	return hamsu;
}

int eval2(polynomial4 P, int x)
{
	int hamsu = P.coef * pow(x, P.expon);
	return hamsu;
}

void problem1_2()
{
	polynomial2 a;

	printf("<다항식 입력>\n");
	printf("다항식의 최고 차수: ");
	scanf_s("%d", &a.degree);
	printf("각 항의 계수를 차례로 입력 : ");
	for (int i = 0; i <= a.degree; i++)
		scanf_s("%f", &a.coef[i]);
	printf("다항식 출력: A(x) = ");
	print_poly2(a);

	printf("\n\nA(x) 함수에 대입할 x값을 입력하시오: ");
	int x;
	scanf("%d", &x);

	printf("A(%d) = %d\n", x, eval(a, x));

	printf("\n");

	return 0;
}

char compare(int a, int b)
{
	if (a > b) return '>';
	else if (a == b) return '=';
	else return '<';
}

void attach(int coef, int expon)  // 새로운 항을 다항식에 추가한다.
{
	if (avail > MAX_TERMS)
	{
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}

	terms[avail].coef = coef;
	terms[avail].expon = expon;

	avail++;
}

void problem2_1()
{
	int As = 0, Ae, Bs, Be, Cs, Ce = 0;  // 인덱스명으로 지정

	printf("<첫번째 다항식>\n");
	printf("첫번째 다항식의 항을 몇 개 입력받을것인가?: ");
	scanf("%d", &Ae);  // 예를들어 3 입력
	Ae = Ae - 1;  // Aend 인덱스는 2

	printf("첫번째 다항식의 각 항의 계수와 차수를 차례로 번갈아가며 입력하시오:\n");
	for (int i = 0; i <= Ae; i++)  // 0~2 인덱스 포문
	{
		printf("각 항의 {계수, 차수}: ");
		scanf("%d %d", &terms[i].coef, &terms[i].expon);
	}

	printf("첫번째 다항식 출력: ");
	print_poly3(As, Ae);  // 인덱스를 매개변수로 넣음

	printf("\n");

	printf("<두번째 다항식>\n");
	printf("두번째 다항식의 항을 몇 개 입력받을것인가?: ");
	scanf("%d", &Be);  // 예를들어 4 입력
	Be = Ae + Be;  // Be = 2+4 = 6, Bend 인덱스는 6

	Bs = Ae + 1;  // Bstart 인덱스는 Ae인덱스+1 = 2+1 = 3

	avail = Be + 1;  // avail 인덱스는 6+1=7

	printf("두번째 다항식의 각 항의 계수와 차수를 차례로 번갈아가며 입력하시오:\n");
	for (int i = Bs; i <= Be; i++)
	{
		printf("각 항의 {계수, 차수}: ");
		scanf("%d %d", &terms[i].coef, &terms[i].expon);
	}

	printf("두번째 다항식 출력: ");
	print_poly3(Bs, Be);

	printf("\n<두 다항식의 뺄셈>\n");
	print_poly3(As, Ae);
	print_poly3(Bs, Be);
	printf("----------------------------------------------------------\n");
	printf("뺄셈 결과: ");
	Cs = Be + 1;
	poly_minus2(As, Ae, Bs, Be, &Cs, &Ce);

	print_poly3(Cs, Ce);

	printf("\n");

	return 0;
}

void problem2_2()
{
	int As = 0, Ae;  // 인덱스명으로 지정

	polynomial4 terms[MAX_TERMS];

	printf("다항식의 항을 몇 개 입력받을것인가?: ");
	scanf("%d", &Ae);  // 예를들어 3 입력
	Ae = Ae - 1;  // Aend 인덱스는 2


	printf("다항식의 각 항의 계수와 차수를 차례로 번갈아가며 입력하시오:\n");
	for (int i = 0; i <= Ae; i++)  // 0~2 인덱스 포문
	{
		printf("각 항의 {계수, 차수}: ");
		scanf("%d %d", &terms[i].coef, &terms[i].expon);
	}

	printf("다항식 출력: ");
	for (int i = As; i < Ae; i++)
		printf("%dx^%d + ", terms[i].coef, terms[i].expon);
	printf("%dx^%d\n", terms[Ae].coef, terms[Ae].expon);

	printf("\n");

	printf("\nA(x) 함수에 대입할 x값을 입력하시오: ");
	int x;
	scanf("%d", &x);

	int sum = 0;
	for (int i = As; i <= Ae; i++)
	{
		sum += eval2(terms[i], x);
	}

	printf("A(%d) = %d\n", x, sum);

	printf("\n");

	return 0;
}

int menu()
{
	int n;
	printf("1. 1-1번 문제\n");
	printf("2. 1-2번 문제\n");
	printf("3. 2-1번 문제\n");
	printf("4. 2-2번 문제\n");
	printf("5. exit\n\n");
	printf("번호를 입력하세요.\n\n");
	scanf("%d", &n);
	printf("\n");
	return n;
}

int main(void)
{
	int n = 0;

	while (1) {
		n = menu();
		switch (n)
		{
		case 1:
			problem1_1();
			break;
		case 2:
			problem1_2();
			break;
		case 3:
			problem2_1();
			break;
		case 4:
			problem2_2();
			break;
		case 5:
			return 0;
		}
	}
}
