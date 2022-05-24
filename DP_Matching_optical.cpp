#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define dataname1 "city011"//ここを書き換える
#define dataname2 "city021"//ここを書き換え得る２
struct city{
	char filename[50];
	double data[200][15];
	char Na[30];
	int N;
	char name[20];
};
double min(double a,double b,double c){//最小値を返す
	double n;
	if(a<b){
		n=a;
	}else{
		n=b;
	}
	if(n>c){
		n=c;
	}
	return n;
}


double kyori(struct city dav,struct city B){
	double datak[100][100],g[100][100],ret,n;
	int i,j,k;
	FILE *cd;
	for(i=0;i<dav.N;i++){
		for(j=0;j<B.N;j++){
				datak[i][j]=0;
			for(k=0;k<15;k++){
				datak[i][j]+=(dav.data[i][k]-B.data[j][k])*(dav.data[i][k]-B.data[j][k]);
			}
			datak[i][j] = sqrt(datak[i][j]);
		}
	}
	
	g[0][0]=datak[0][0];
	for(i=1;i<dav.N;i++)g[i][0]=g[i-1][0]+datak[i][0];
	for(i=1;i<B.N;i++)g[0][i]=g[0][i-1]+datak[0][i];
	for(i=1;i<dav.N;i++){
		for(j=1;j<B.N;j++){
			g[i][j]=min(g[i][j-1]+datak[i][j],g[i-1][j-1]+sqrt(2)*datak[i][j],g[i-1][j]+datak[i][j]);
		}
	}
	ret=g[dav.N-1][B.N-1];
	
	cd=fopen("最適距離.csv","w");
	
	j=1;i=1;
	while((i < dav.N) || (j < B.N)){
		if(B.N <= j){
			n = g[i+1][j];
		}
		else if(dav.N <= i){
			n = g[i][j+1];
		}
		else{
			n = min(g[i][j+1],g[i+1][j+1],g[i+1][j]);
		}
		if(n == g[i+1][j+1] && j < B.N && i < dav.N){
			i++;
			j++;
		}
		else if(n == g[i][j+1] && j < B.N && i <= dav.N)j++;
		else if(n == g[i+1][j] && j <= B.N && i < dav.N)i++;
		fprintf(cd,"%d %d\n",i,j);
	}
	
	fclose(cd);
	return ret/(dav.N + B.N);
}
//////////////////////////////ファイル読み込み//////////////////////////////////////////
void fileread(struct city *A){
	int i,j;
	FILE *fp;
	fp=fopen(A->filename,"r");
	fgets(A->Na,30,fp);
	fgets(A->name,20,fp);
	fscanf(fp,"%d",&A->N);
	for(i=0;i<A->N;i++)	for(j=0;j<15;j++)fscanf(fp,"%lf",&A->data[i][j]);
	fclose(fp);
}
int main(void){
	struct city A;
	struct city B;
	int i,i2=0,j;
	double dist,sdist=0;
	int F=0;
	sprintf(B.filename,"%s/%s_001.txt",dataname2,dataname2);
	printf("   %s:横軸,%s:縦軸 \n",dataname1,dataname2);
	for(j=0;j<1;j++){
		sprintf(A.filename,"%s/%s_001.txt",dataname1,dataname1);
		fileread(&B);
		for(i=0;i<1;i++){
			fileread(&A);
			if(sdist > (dist=kyori(A,B)) ){
				sdist=dist;
				i2=i;
			}
			if(i==0)sdist=dist;
			sprintf(A.filename,"%s/%s_%03d.txt",dataname1,dataname1,i+2);
		}
		sprintf(B.filename,"%s/%s_%03d.txt",dataname2,dataname2,j+2);
}}