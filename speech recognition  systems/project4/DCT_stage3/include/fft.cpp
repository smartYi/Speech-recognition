#include"stdafx.h"

typedef struct 
{
	double real;
	double image;
}complex;

complex* fft(short* data, int length)
{
	// zero padding
	int z = 1;
	while (pow(2.0, z) < length)
	{
		z++;
	}
	int paddingLength = pow(2.0,z);
	// real 2 complex
	complex *TD = new complex[paddingLength];

	int i = 0;

	for (i = 0; i < paddingLength; i++)
	{
		TD[i].real = 0;
		TD[i].image = 0;
	}

	for (i = 0; i < length; i++)
	{
		TD[i].real = data[i];
		TD[i].image = 0;
	}

	int x, nv2, j, k, le, l, le1, ip, nm1;
	complex t, u, w;  //复数
	int ntemp = paddingLength;
	for(x = 0; paddingLength>1; x++)
		paddingLength /= 2;

	paddingLength = ntemp;

	nv2 = paddingLength/2;
	nm1 = paddingLength-1;

	j=1;

	for(i=1; i<=nm1; i++)
	{
		if(i<j)  //i是前一个点，j是后一个点
		{
			t.real = TD[i-1].real;
			t.image = TD[i-1].image;
			TD[i-1].real = TD[j-1].real; 
			TD[i-1].image = TD[j-1].image;
			TD[j-1].real = t.real;
			TD[j-1].image = t.image;  //后一个点被前一个点代替
		}
		k = nv2;
		while(k < j)
		{
			j -= k;
			k /= 2;
		}
		j += k;
	}

	le = 1;
	for(l = 1; l <= x; l++)
	{
		le *= 2;
		le1 = le / 2;
		u.real = 1.0f;
		u.image = 0.0f;
		w.real = (float)cos(PI/le1);
		w.image = (float)-sin(PI/le1);
		for(j=1; j <= le1; j++)
		{
			for(i=j; i <= paddingLength; i += le)
			{
				ip = i+le1;
				t.real = TD[ip-1].real*u.real-TD[ip-1].image*u.image;
				t.image = TD[ip-1].real*u.image+TD[ip-1].image*u.real;
				TD[ip-1].real = TD[i-1].real-t.real;
				TD[ip-1].image = TD[i-1].image-t.image;
				TD[i-1].real = t.real+TD[i-1].real;
				TD[i-1].image = t.image+TD[i-1].image;
			}
			t.real = u.real*w.real-u.image*w.image;
			t.image = u.image*w.real+u.real*w.image;
			u.real = t.real;
			u.image = t.image;
		}
	}

	return TD;
}