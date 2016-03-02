#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "/home/dhyandeepak/Desktop/fft/bmpmanip.h"
#define N 8
#define LENGTH 128

static inline void fdct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        const float x00 = src[0*src_stridea] + src[7*src_stridea];
        const float x01 = src[1*src_stridea] + src[6*src_stridea];
        const float x02 = src[2*src_stridea] + src[5*src_stridea];
        const float x03 = src[3*src_stridea] + src[4*src_stridea];
        const float x04 = src[0*src_stridea] - src[7*src_stridea];
        const float x05 = src[1*src_stridea] - src[6*src_stridea];
        const float x06 = src[2*src_stridea] - src[5*src_stridea];
        const float x07 = src[3*src_stridea] - src[4*src_stridea];
        const float x08 = x00 + x03;
        const float x09 = x01 + x02;
        const float x0a = x00 - x03;
        const float x0b = x01 - x02;
        const float x0c = 1.38703984532215*x04 + 0.275899379282943*x07;
        const float x0d = 1.17587560241936*x05 + 0.785694958387102*x06;
        const float x0e = -0.785694958387102*x05 + 1.17587560241936*x06;
        const float x0f = 0.275899379282943*x04 - 1.38703984532215*x07;
        const float x10 = 0.353553390593274 * (x0c - x0d);
        const float x11 = 0.353553390593274 * (x0e - x0f);
        dst[0*dst_stridea] = 0.353553390593274 * (x08 + x09);
        dst[1*dst_stridea] = 0.353553390593274 * (x0c + x0d);
        dst[2*dst_stridea] = 0.461939766255643*x0a + 0.191341716182545*x0b;
        dst[3*dst_stridea] = 0.707106781186547 * (x10 - x11);
        dst[4*dst_stridea] = 0.353553390593274 * (x08 - x09);
        dst[5*dst_stridea] = 0.707106781186547 * (x10 + x11);
        dst[6*dst_stridea] = 0.191341716182545*x0a - 0.461939766255643*x0b;
        dst[7*dst_stridea] = 0.353553390593274 * (x0e + x0f);
        dst += dst_strideb;
        src += src_strideb;
    }
}

static void fdct(float *dst, const float *src)
{
    float tmp[N*N];
    fdct_1d(tmp, src, 1, N, 1, N);
    fdct_1d(dst, tmp, N, 1, N, 1);
}

static inline void idct_1d(float *dst, const float *src,
                           int dst_stridea, int dst_strideb,
                           int src_stridea, int src_strideb)
{
    int i;

    for (i = 0; i < N; i++) {
        const float x00 = 1.4142135623731*src[0*src_stridea];
        const float x01 = 1.38703984532215*src[1*src_stridea] + 0.275899379282943*src[7*src_stridea];
        const float x02 = 1.30656296487638*src[2*src_stridea] + 0.541196100146197*src[6*src_stridea];
        const float x03 = 1.17587560241936*src[3*src_stridea] + 0.785694958387102*src[5*src_stridea];
        const float x04 = 1.4142135623731*src[4*src_stridea];
        const float x05 = -0.785694958387102*src[3*src_stridea] + 1.17587560241936*src[5*src_stridea];
        const float x06 = 0.541196100146197*src[2*src_stridea] - 1.30656296487638*src[6*src_stridea];
        const float x07 = -0.275899379282943*src[1*src_stridea] + 1.38703984532215*src[7*src_stridea];
        const float x09 = x00 + x04;
        const float x0a = x01 + x03;
        const float x0b = 1.4142135623731*x02;
        const float x0c = x00 - x04;
        const float x0d = x01 - x03;
        const float x0e = 0.353553390593274 * (x09 - x0b);
        const float x0f = 0.353553390593274 * (x0c + x0d);
        const float x10 = 0.353553390593274 * (x0c - x0d);
        const float x11 = 1.4142135623731*x06;
        const float x12 = x05 + x07;
        const float x13 = x05 - x07;
        const float x14 = 0.353553390593274 * (x11 + x12);
        const float x15 = 0.353553390593274 * (x11 - x12);
        const float x16 = 0.5*x13;
        const float x08 = -x15;
        dst[0*dst_stridea] = 0.25 * (x09 + x0b) + 0.353553390593274*x0a;
        dst[1*dst_stridea] = 0.707106781186547 * (x0f - x08);
        dst[2*dst_stridea] = 0.707106781186547 * (x0f + x08);
        dst[3*dst_stridea] = 0.707106781186547 * (x0e + x16);
        dst[4*dst_stridea] = 0.707106781186547 * (x0e - x16);
        dst[5*dst_stridea] = 0.707106781186547 * (x10 - x14);
        dst[6*dst_stridea] = 0.707106781186547 * (x10 + x14);
        dst[7*dst_stridea] = 0.25 * (x09 + x0b) - 0.353553390593274*x0a;
        dst += dst_strideb;
        src += src_strideb;
    }
}

static void idct(float *dst, const float *src)
{
    float tmp[N*N];
    idct_1d(tmp, src, 1, N, 1, N);
    idct_1d(dst, tmp, N, 1, N, 1);
}


//slow reference dct code 

static float dct_matrix    [N*N];
static float dct_trp_matrix[N*N];

void init_dct(void)
{
    int i, j;

    // dct matrix
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (i == 0)
                dct_matrix[i*N + j] = 1 / sqrt(N);
            else
                dct_matrix[i*N + j] = sqrt(2./N) * cos(((2*j+1)*i*M_PI) / (2*N));

    // dct matrix transposed
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            dct_trp_matrix[i*N + j] = dct_matrix[j*N + i];
}

static void dct_1d_ref(float *dst, const float *src,
                       int stridea, int strideb,
                       const float *matrix)
{
    int x;
    for (x = 0; x < N; x++) {
        int i, j;
        for (j = 0; j < N; j++) {
            float sum = 0.;
            for (i = 0; i < N; i++)
                sum += matrix[j*N + i] * src[i*stridea];
            dst[j*stridea] = sum;
        }
        dst += strideb;
        src += strideb;
    }
}

static void fdct_ref(float *dst, const float *src)
{
    float tmp[N*N];
    dct_1d_ref(tmp, src, 1, N, dct_matrix);
    dct_1d_ref(dst, tmp, N, 1, dct_matrix);
}

static void idct_ref(float *dst, const float *src)
{
    float tmp[N*N];
    dct_1d_ref(tmp, src, 1, N, dct_trp_matrix);
    dct_1d_ref(dst, tmp, N, 1, dct_trp_matrix);
}



int main()
{
    int i;
    float src[N*N];
	
    float out_fdct[N*N], out_idct[N*N],results[LENGTH*LENGTH];
	int *m=filehand();
	
	int l=0,j,k,res=0,p;
	init_dct();
   for(j=0;j<LENGTH/8;j++)
   {
	   for(i=0;i<LENGTH/8;i++)
	   {
		   for(k=0;k<8;k++)
			{
				for(l=0;l<8;l++)
				{
					src[l+8*k]=matrix[8*j+k][l+8*i];//store 8X8 image block into an array
					printf("%f ",src[l+8*k]);
				}
				printf("\n");
			}
			printf("\n");
			
			fdct_ref(out_fdct, src);//find fast dct for each 8X8 blocks
			idct_ref(out_idct, out_fdct);
			for(k=0;k<8;k++)
			{
				for(l=0;l<8;l++)
				{
					//if(out_fdct[l+8*k]<0)
					//out_fdct[l+8*k]=0;
					matrix[8*j+k][l+8*i]=out_idct[l+8*k];//store 8X8  block's compressed values into the matrix itself
					//printf("%f ",src[l+8*k]);
				}
				//printf("\n");
			}
	   }
	   
   }
    


    filewrite();

    return 0;
}
