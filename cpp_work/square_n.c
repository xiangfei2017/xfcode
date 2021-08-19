#include <stdio.h>
#include <stdlib.h>

int chk(int *a, int n, int v);
void prnt(int *a, int n);
void init(int *a, int n);
int ismax(int *a, int n);
int calc(int *a, int n);

int main(void)
{
	int n, *a;
	int n2;

	printf("\r\n请输入方格的阶数:");
	scanf("%d", &n);
	n2 = n * n;

	a = malloc(n2 * sizeof(int));

	init(a, n);

	if (calc(a, n))
	{
		prnt(a, n);
	}
	else
	{
		printf("\r\nFailed");
	}

	free(a);
	printf("\r\n");
	return 0;
}

int calc(int *a, int n)
{
	int i, flag = 0, n2, flag2 = 0, v;
	n2 = n * n;
	v = n * (n * n + 1) / 2;
	// while (!ismax(a, n))
	do
	{
		if (chk(a, n, v))
		{
			flag = 1;
			break;
		}
		a[0]++;
		for (i = 0; i < n2; i++)
		{
			if (a[i] > n2)		// 溢出
			{
				a[i] = 1;
				if (i < n2 - 1)
					a[i + 1]++;
				else
				{
					flag2 = 1;	// 最高位溢出
					break;
				}
			}
			else
				break;
		}
	}
	while (flag2 != 1);

	if (flag)
		return 1;
	else
		return 0;
}

int ismax(int *a, int n)
{
	int i, n2;
	int flag = 0;

	n2 = n * n;
	for (i = 0; i < n2; i++)
	{
		if (a[i] != n2)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
		return 0;
	else
		return 1;
}

int chk(int *a, int n, int v)
{
	int i, j, s;
	int flag = 0;

	// prnt(a,n);
	s = 0;
	for (j = 0; j < n; j++)
	{
		s += a[j * n + j];
	}
	if (s != v)
		return 0;

	s = 0;
	for (j = 0; j < n; j++)
	{
		s += a[j * n + n - 1 - j];
	}
	if (s != v)
		return 0;
	
	for (i = 0; i < n; i++)
	{
		s = 0;
		for (j = 0; j < n; j++)
		{
			s += a[i * n + j];
		}
		if (s != v)
		{
			flag = 1;
			break;
		}
	}

	if (flag)
		return 0;

	for (i = 0; i < n; i++)
	{
		s = 0;
		for (j = 0; j < n; j++)
		{
			s += a[j * n + i];
		}
		if (s != v)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
		return 0;



	return 1;
}


void init(int *a, int n)
{
	int i;
	int n2;

	n2 = n * n;
	for (i = 0; i < n2; i++)
	{
		a[i] = n2 - i;
	}

	return;
}

void prnt(int *a, int n)
{
	int i, j;

	printf("\r\n");
	for (i = 0; i < n; i++)
	{
		printf("\r\n");
		for (j = 0; j < n; j++)
		{
			printf("%3d", a[i * n + j]);
		}
	}

	return;
}