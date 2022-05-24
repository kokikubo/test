#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define datafile1 "city022"		//テンプレート		//元ファイル	//ファイル名を変えることで比較するものを変える
#define datafile2 "city011"		//未知入力			//比較ファイル	//同上
  
struct city{
	char file[50];					//ファイル名
	double data[200][15];				//行数:200,フレーム数:15
	char filename[30];						//txtファイルの1行目=ファイル名
	int N;								//txtファイルの2行目の地名
	char frame[20];						//3行目の分析フレーム数
};

//ファイルの読み込み
	
void fileread(struct city *A){
	int i,j;
	FILE *fp;
	fp=fopen(A->file,"r");					//  -> アロー演算子:ポインタ変数から呼び出し
	fgets(A->filename,30,fp);
	fgets(A->frame,20,fp);
	fscanf(fp,"%d",&A->N);
	for(i=0;i<A->N;i++)	for(j=0;j<15;j++)fscanf(fp,"%lf",&A->data[i][j]);
	fclose(fp);
}

//↓最小値の計算(比較)

double min(double a,double b,double c){			//a,b,cのうちで最小のものを選択
	double n;
	if(a<b){							//aとbを比較
		n=a;
	}else{
		n=b;
	}
	if(n>c){							//aかbとcを比較
		n=c;
	}
	return n;							//結果を返す
}

//↓単語間距離について

double distance(struct city dav,struct city B){		//最適距離について
	double datak[200][200],g[200][200],ret;
	int i,j,k;
	double d;
	d=2;			//重み 					
	
//↓局所距離の計算

	for(i=0;i<dav.N;i++){ 
		for(j=0;j<B.N;j++){
				datak[i][j]=0;
			for(k=0;k<15;k++){
				datak[i][j]+=(dav.data[i][k]-B.data[j][k])*(dav.data[i][k]-B.data[j][k]);
			}  
		}	
	}
	
	//局所距離について終了

//↓境界条件について
	
	datak[i][j] = sqrt(datak[i][j]); 
	g[0][0]=datak[0][0];
	for(i=1;i<dav.N;i++)g[i][0]=g[i-1][0]+datak[i][0];
	for(i=1;i<B.N;i++)g[0][i]=g[0][i-1]+datak[0][i];
	
	//境界条件について終了
	
//格子点
	
	for(i=1;i<dav.N;i++){
		for(j=1;j<B.N;j++){
			g[i][j]=min(g[i][j-1]+datak[i][j],g[i-1][j-1]+d*datak[i][j],g[i-1][j]+datak[i][j]);			//d使う
		}
	}
	ret=g[dav.N-1][B.N-1];
	return ret/(dav.N+B.N);					//distanceの結果を返す
}

	//格子点終了


/////////////↑宣言終了↑/////////////////


/////////////↓ 本文   ↓/////////////////

int main(void){
	
	struct city A;
	struct city B;
	int i,i2=0,j;
	double M,M2;
	int T=0,F=0;
	int f;
	sprintf(B.file,"%s/%s_001.txt",datafile2,datafile2);			//文字列に格納
	for(j=0;j<100;j++){
		sprintf(A.file,"%s/%s_001.txt",datafile1,datafile1);
		fileread(&B);
		for(i=0;i<100;i++){
			fileread(&A);
			if(M2>(M=distance(A,B))){
				M2=M;
				i2=i;
			}
			if(i==0)M2=M;
			sprintf(A.file,"%s/%s_%03d.txt",datafile1,datafile1,i+2);
		}
		sprintf(B.file,"%s/%s_%03d.txt",datafile2,datafile2,j+2);
		if(i2==j){
			printf("○ ");
			T++;
		}else{
			F++;
			printf("× ");
		}
		printf("%s適合率%d%\n\n",B.frame,100-F);
	}
	printf("%sと%sの比較\n適合率%d％\n",datafile1,datafile2,T);
	if(T==100){
	printf("完璧！！\n");
	}else{
		f=100-T;
	printf("%dコ認識できてない\n",f);	
	}
}