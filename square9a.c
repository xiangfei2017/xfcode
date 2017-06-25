#include "stdio.h"

int a[9] = { 0 };
int b[10] = { 0 };

void prnt(void)
{
	int i;
	static int c=0;

	printf("\r\n---%d---",++c);
	for (i = 0; i < 7; i += 3)
	{
		printf("\r\n%d %d %d", a[i], a[i + 1], a[i + 2]);
	}
	return;
}

void clrflag(void)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		b[i] = 0;
	}
	return;
}

int chk(void)
{
	int r1, r2, r3;
	int c1, c2, c3;
	int s1, s2;

	r1 = ((a[0] + a[1] + a[2]) == 15);
	r2 = ((a[3] + a[4] + a[5]) == 15);
	r3 = ((a[6] + a[7] + a[8]) == 15);

	c1 = ((a[0] + a[3] + a[6]) == 15);
	c2 = ((a[1] + a[4] + a[7]) == 15);
	c3 = ((a[2] + a[5] + a[8]) == 15);

	s1 = ((a[0] + a[4] + a[8]) == 15);
	s2 = ((a[2] + a[4] + a[6]) == 15);

	// prnt();
	if (r1 && r2 && r3 && c1 && c2 && c3 && s1 && s2)
	{
		return 1;
	}
	return 0;
}


int main(void)
{
	int i0, i1, i2, i3, i4, i5, i6, i7, i8;
	int flag = 0;
	int count = 0;

	clrflag();
	for (i0 = 1; i0 < 10; i0++)
	{
		if (b[i0])
			continue;
		a[0] = i0;
		b[i0] = 1;
		for (i1 = 1; i1 < 10; i1++)
		{
			if (b[i1])
				continue;
			a[1] = i1;
			b[i1] = 1;
			for (i2 = 1; i2 < 10; i2++)
			{
				if (b[i2])
					continue;
				a[2] = i2;
				b[i2] = 1;
				for (i3 = 1; i3 < 10; i3++)
				{
					if (b[i3])
						continue;
					a[3] = i3;
					b[i3] = 1;
					for (i4 = 1; i4 < 10; i4++)
					{
						if (b[i4])
							continue;
						a[4] = i4;
						b[i4] = 1;
						for (i5 = 1; i5 < 10; i5++)
						{
							if (b[i5])
								continue;
							a[5] = i5;
							b[i5] = 1;
							for (i6 = 1; i6 < 10; i6++)
							{
								if (b[i6])
									continue;
								a[6] = i6;
								b[i6] = 1;
								for (i7 = 1; i7 < 10; i7++)
								{
									if (b[i7])
										continue;
									a[7] = i7;
									b[i7] = 1;
									for (i8 = 1; i8 < 10; i8++)
									{
										if (b[i8])
											continue;
										a[8] = i8;
										b[i8] = 1;
										if (chk())
										{
											flag = 1;
											prnt();
											//goto lbl;
										}
										count++;
										b[i8] = 0;
									}
									b[i7] = 0;
								}
								b[i6] = 0;
							}
							b[i5] = 0;
						}
						b[i4] = 0;
					}
					b[i3] = 0;
				}
				b[i2] = 0;
			}
			b[i1] = 0;
		}
		b[i0] = 0;
	}

	if (!flag)
	{
		printf("\r\nfailed");
		return 0;
	}
  lbl:
	//prnt();
	printf("\r\nTry count:%d", count);
	return 0;
}