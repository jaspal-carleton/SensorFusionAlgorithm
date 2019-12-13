#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// helper function to get file size
int getfilesize(char *fname)
{
  FILE *fp = fopen(fname, "r");
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fclose(fp);
  return size;
}
 
// reads csv file into a local buffer
// tokenize string at comma or new line, 
// convert text data to integer and write it into 2D buffer
#define COL 3
void read2darray(char *fname, float (*array)[COL], int rows)
{
  // allocate memory buffer for file read 
  // and read csv file into buffer
  int size = getfilesize(fname);
  char *buf = malloc(size +1);
 
  FILE *fp = fopen(fname, "r");
  fread(buf, size, 1, fp);
  fclose(fp) ;
  
  //tokenize at comma or new line
  char *tok = strtok(buf, ",\n");
  for(int i=0;i<rows;i++)
  {
    for(int j=0;j<COL;j++)
    {
      if(tok == NULL)
      {
        break;
      }
      // convert text numeral to integer
      float val = atof(tok);
      array[i][j] = val;
      //printf("%d ", val);
 
      // tokenize at comma or newline
      tok = strtok(NULL, ",\n");
    }
    
  }
  free(buf);
}
 
// dummy function to create csv file and 
// write comma seperated sequence as 4x6 array (0,1,2..,22,23) 
void writedata(char *fname, int rows)
{
  FILE *fp = fopen(fname, "w");
  int index = 0;
  for(int i=0; i< rows; i++)
  {
    fprintf(fp, "%f,%f,%f,%f\n", index, index+1, index+2, index+3, index+4, index+5);
    index += COL;
  }
  fclose(fp);
}
// #define ROWS 10
int main()
{
  int count=0;
  char line[1024];
  FILE *lp;
  
  
  lp = fopen("sample.csv", "r");
    while (fgets(line, 1024, lp )) {
        count++;
    }
	// printf("Rows is %d", count);
	int ROWS = count;
  float arr[ROWS][COL];
  for(int i=0;i<ROWS;i++)
  {
    for(int j=0;j<COL;j++)
    {
      arr[i][j]=0;
    }
  }
  char *fname = "sample.csv";
 
  // write some dummy data into csv file
  // it's not needed if you already have csv file
  // writedata(fname, ROWS);
 
  // read file into 2D into array
  read2darray(fname, (float(*)[COL])arr, ROWS);
  printf("\nCSV File is:\n");
 
  // print 2d array
  for(int i=0;i<ROWS;i++)
  {
    for(int j=0;j<COL;j++)
    {
      printf("%f ", arr[i][j]);
    }
    printf("\n");
  }

   float result1[10] = {0};  
   float result2[10] = {0};
   float result3[10] = {0};
   float result4[10] = {0};
   int m=0;
   int n=0;
   int o=0;
   int p=0;
   
   
   for(int i=0;i<ROWS;i++)
  {
	  if (arr[i][0]== arr[0][0])
	  {
		  result1[i] = arr[i][2];
		  //printf("%f is %f \n\n", arr[i][0],result1[i]);
		  m++;  
	  }
	  else break;
  }
  
    for(int i=0;i<ROWS;i++)
  {
	  if (arr[i][0]== arr[0][0])
	  {
		  result1[i] = arr[i][2];
		  //printf("%f is %f \n\n", arr[i][0],result1[i]);
		  m++;  
	  }
	  else break;
  }
  
	  if (arr[i][0]== arr[m][0])
	  {
		  result2[n] = arr[i][2];
		  //printf("%f is %f \n\n", arr[i][0],result2[i]);
		  n++;
	  }
      else if (arr[i][0]== arr[m+n][0])
	  {
		  result3[o] = arr[i][2];
		  //printf("%f is %f \n\n", arr[i][0],result3[i]);
		  o++;
	  }
	  else if (arr[i][0]== arr[m+n+o][0])
	  {
		  result4[p] = arr[i][2];
		  //printf("%f is %f \n\n", arr[i][0],result4[i]);
		  p++;
	  }
	  else break; 
  }
  
  printf("\nSensor readings for timestamp1 stored in result1 array is\n");
  for(int i=0;i<m;i++)
  {
	  printf("%f \n",result1[i]);
  }
  
  printf("\nSensor readings for timestamp2 stored in result2 array is\n");
  for(int i=0;i<n;i++)
  {
	  printf("%f \n",result2[i]);
  }
  
  printf("\nSensor readings for timestamp3 stored in result3 array is\n");
  for(int i=0;i<o;i++)
  {
	  printf("%f \n",result3[i]);
  }
  
  printf("\nSensor readings for timestamp4 stored in result4 array is\n");
  for(int i=0;i<p;i++)
  {
	  printf("%f \n",result4[i]);
  }
  
  
}