#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEBUG 1

void create_matrix(double **A, int rows, int cols){
	double * mat;
	mat = (double *)calloc(rows*cols,sizeof(double));
	*A = mat;
}

void set_element(double **A,int row, int col,int width,double val){
	double *mat = *A;
	mat[row*width + col] = val;
	*A = mat;
}

double get_element(double **A,int row,int col,int width){
	double *mat = *A;
	return mat[row*width + col];
}

void init_matrix(double **A, int* size){
	FILE *fp;
	double * mat = *A;
	int from_node, to_node;
	if ((fp = fopen("data_input","r")) == NULL){
        	printf("Fail to open file. \n");
        	exit(1);
    	}
	fscanf(fp,"%d\n",size);
	create_matrix(A,*size,*size);

	if (DEBUG) printf("Malloc Complete\n");
	if (DEBUG) printf("Importing edges into edge matrix\n");
	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
				set_element(A,
					 from_node,
					 to_node,*size,
					 get_element(A,from_node,to_node,*size)+1);
    	}
	if (DEBUG) printf("Edge import complete\n");
	fclose(fp);
}
