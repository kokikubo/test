#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define datafile1 "city022"		//�e���v���[�g		//���t�@�C��	//�t�@�C������ς��邱�ƂŔ�r������̂�ς���
#define datafile2 "city011"		//���m����			//��r�t�@�C��	//����
  
struct city{
	char file[50];					//�t�@�C����
	double data[200][15];				//�s��:200,�t���[����:15
	char filename[30];						//txt�t�@�C����1�s��=�t�@�C����
	int N;								//txt�t�@�C����2�s�ڂ̒n��
	char frame[20];						//3�s�ڂ̕��̓t���[����
};

//�t�@�C���̓ǂݍ���
	
void fileread(struct city *A){
	int i,j;
	FILE *fp;
	fp=fopen(A->file,"r");					//  -> �A���[���Z�q:�|�C���^�ϐ�����Ăяo��
	fgets(A->filename,30,fp);
	fgets(A->frame,20,fp);
	fscanf(fp,"%d",&A->N);
	for(i=0;i<A->N;i++)	for(j=0;j<15;j++)fscanf(fp,"%lf",&A->data[i][j]);
	fclose(fp);
}

//���ŏ��l�̌v�Z(��r)

double min(double a,double b,double c){			//a,b,c�̂����ōŏ��̂��̂�I��
	double n;
	if(a<b){							//a��b���r
		n=a;
	}else{
		n=b;
	}
	if(n>c){							//a��b��c���r
		n=c;
	}
	return n;							//���ʂ�Ԃ�
}

//���P��ԋ����ɂ���

double distance(struct city dav,struct city B){		//�œK�����ɂ���
	double datak[200][200],g[200][200],ret;
	int i,j,k;
	double d;
	d=2;			//�d�� 					
	
//���Ǐ������̌v�Z

	for(i=0;i<dav.N;i++){ 
		for(j=0;j<B.N;j++){
				datak[i][j]=0;
			for(k=0;k<15;k++){
				datak[i][j]+=(dav.data[i][k]-B.data[j][k])*(dav.data[i][k]-B.data[j][k]);
			}  
		}	
	}
	
	//�Ǐ������ɂ��ďI��

//�����E�����ɂ���
	
	datak[i][j] = sqrt(datak[i][j]); 
	g[0][0]=datak[0][0];
	for(i=1;i<dav.N;i++)g[i][0]=g[i-1][0]+datak[i][0];
	for(i=1;i<B.N;i++)g[0][i]=g[0][i-1]+datak[0][i];
	
	//���E�����ɂ��ďI��
	
//�i�q�_
	
	for(i=1;i<dav.N;i++){
		for(j=1;j<B.N;j++){
			g[i][j]=min(g[i][j-1]+datak[i][j],g[i-1][j-1]+d*datak[i][j],g[i-1][j]+datak[i][j]);			//d�g��
		}
	}
	ret=g[dav.N-1][B.N-1];
	return ret/(dav.N+B.N);					//distance�̌��ʂ�Ԃ�
}

	//�i�q�_�I��


/////////////���錾�I����/////////////////


/////////////�� �{��   ��/////////////////

int main(void){
	
	struct city A;
	struct city B;
	int i,i2=0,j;
	double M,M2;
	int T=0,F=0;
	int f;
	sprintf(B.file,"%s/%s_001.txt",datafile2,datafile2);			//������Ɋi�[
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
			printf("�� ");
			T++;
		}else{
			F++;
			printf("�~ ");
		}
		printf("%s�K����%d%\n\n",B.frame,100-F);
	}
	printf("%s��%s�̔�r\n�K����%d��\n",datafile1,datafile2,T);
	if(T==100){
	printf("�����I�I\n");
	}else{
		f=100-T;
	printf("%d�R�F���ł��ĂȂ�\n",f);	
	}
}