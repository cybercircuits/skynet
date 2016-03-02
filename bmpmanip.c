#include <stdio.h>
#include <stdlib.h>
int matrix[128][128];

unsigned char info1[56];
int* filehand() {
 
    char *filename="/home/dhyandeepak/Desktop/second.bmp";
  
	FILE *f = fopen(filename, "rb");

	fread(info1,1,56,f); // read the 54-byte headr
	int width1 = *(int*)&info1[18];
	int height1 = *(int*)&info1[22];
	int bits1 = *(int*)&info1[34];
	int offset=*(int*)&info1[10];
	int size = width1 * height1;
	unsigned char data[16384],rmng[2000];
	
	fread(rmng,1,offset-56,f);
	fread(data,1,size,f);
	
	int i=0,j=0;
	printf("file:n");
	for(i=0;i<16384;i++)
	{
		if(((i!=0)&&(i%128))==0)
		{
			j++;
			printf("\n");
			
		}
		matrix[j][i%128]=data[i];
		printf("%d ",matrix[j][i%128]);
	}

	fclose(f);
    return *matrix;   
}
void filewrite()
{
	int i,j;
	  char *outputname="/home/dhyandeepak/Desktop/out.pgm";
	FILE *outfile= fopen(outputname, "a+");
	 char *header="P2\n128 128\n255\n";
	 fwrite(header,1,15,outfile);
	 //printf("output\n");
	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		{
			//printf("%d ",matrix[i][j]);
			
			char* space=" ";
			
			char ch[3];
			int myInt = matrix[i][j];
			sprintf(ch,"%d",myInt);
			fwrite(ch,sizeof(ch),1,outfile);
			
			//printf("%s ",ch);
			fwrite(space,1,1,outfile);
			
			
		}
		char* nline="\n";
		fwrite(nline,1,1,outfile);
		//printf("\n");

	}
	fclose(outfile);
}
