#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
 
typedef int HeapDataType;
 
typedef struct MaxHeap{
	HeapDataType* data;
	int count;
	int MaxSize;
}MH;
 
//-----------�ѵĹ����ȵȷ���
int size(MH *mh);//���ضѴ�С
int isEmpty(MH *mh);//�п�
void initMaxHeap(MH* mh, int size);//��ʼ����

void AdjustUp(MH* mh, int k);//����Ԫ��
void AdjustDown(MH* mh, int k);//���Ʋ���
void insertMaxHeap(MH* mh, HeapDataType value);//����Ԫ��
HeapDataType TopK(MH* mh);//����Ԫ��

 
 

 
//���ضѴ�С
int size(MH *mh){
	return mh->count;
}
 
//�жϿն� 
int isEmpty(MH *mh){
	return 0 == mh->count;
}
 
//����Ԫ�� 
void AdjustDown(MH* mh, int k){
	while (k * 2 <= mh->count)
	{
		int j = k * 2;
		if (j + 1 <= mh->count && mh->data[j] < mh->data[j + 1])//����Һ��Ӵ������Һ��ӱ����Ӵ�
		{
			j = j + 1;
		}
		if (mh->data[k] > mh->data[j])//����ڵ�Ⱥ��Ӵ�
		{
			break;
		}
		//���򽻻�k��j
		int tmp = mh->data[k];
		mh->data[k] = mh->data[j];
		mh->data[j] = tmp;
 
		k = j;
	}
}
 
 
//��ʼ����
void initMaxHeap(MH* mh, int size){
	mh->MaxSize = size;
	mh->data = (HeapDataType*)malloc((mh->MaxSize + 1) * sizeof(HeapDataType));//��1��ʼ�洢
	mh->count = 0;
}
 
 
//����Ԫ��
void AdjustUp(MH* mh, int k){
	while (1 < k && mh->data[k / 2] < mh->data[k])
	{
		int tmp = mh->data[k / 2];
		mh->data[k / 2] = mh->data[k];
		mh->data[k] = tmp;
		k /= 2;
	}
}
 
//����Ԫ��
void insertMaxHeap(MH* mh, HeapDataType value){
	//������û����
	assert(mh->count + 1 <= mh->MaxSize);
 
	//countΪ���һ��Ԫ��
	mh->data[mh->count + 1] = value;
	mh->count++;
	AdjustUp(mh,mh->count);//���Ƶ�����λ��
}
 
//����Ԫ��
HeapDataType TopK(MH* mh){
	assert(mh->count > 0);
 
	//��ö���Ԫ��
	HeapDataType res = mh->data[1];
 
	//�����ĸ�ֵ������
	mh->data[1] = mh->data[mh->count];
	//����Ԫ����0������count--
	mh->data[(mh->count)--] = 0;
 
	//�Ѷ���Ԫ�����Ƶ�����λ��
	AdjustDown(mh, 1);
	return res;
}
 
 
//��������ģ�飺��������Ҫ��ģ�飬�ֵ�ʦ�ֵĵ�һ�����ߣ�Ҳ�����һ����-����-�� 
void checkinput(int* r) {
    int error, i = 0;
    char c[50] = { 0 };
    do {
        gets(c);
        error = 0;
        for (i = 0; c[i] != '\0'; i++) {
            if (i == 0 && c[i] == '-')
            {
                continue;
            }
            if (c[i] < '0' || c[i]>'9')
                error = 1;
        }
        if (error) {
            printf("����������������룡\n");
        }
    } while (error);
    *r = atoi(c);
} 
 
 
 
 
 
int main()
{

	MH mh;
	int num,num_check;
		
while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG�����ܡ�����              |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----��ʼ����               |\n");
		printf("\t\t\t|      2----�ѵĴ�С               |\n");
		printf("\t\t\t|      3----�ж϶��Ƿ�Ϊ��         |\n");
		printf("\t\t\t|      4----��������Ԫ��(�ɴ�С) |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      5---�˳�                    |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp������׿Ȼ��|\n");
		printf("\t\t\t|----------------------------------|\n");		
		printf("\n��ѡ�����:\n");
		checkinput(&num_check);
		if (num_check >= 1 && num_check <= 5) {
			switch (num_check) {
			
		
		case 1: {
	printf("������ƻ���ӵ�Ԫ�ظ�����");
	while(!(scanf("%d", &num) && num > 0 && getchar() == '\n'))	
   	{
		while(getchar() != '\n');//��ջ�����
		printf("Ԫ�ظ���ֻ����������ร�\n");//��ܰ����һ��
	}
	//��ʼ���� 
	initMaxHeap(&mh, num);
	
	//��ʼ����Ԫ��	   
    int arr[num];    
  	for (int i = 0; i < num; i++) {
	printf("�������%d��������",i+1);
	while(!(scanf("%d", &arr[i]) && getchar() == '\n'))
	{
		while(getchar() != '\n');//��ջ�����
		printf("���������ֻ��������ร�\n");//��ܰ����һ��
	}
		insertMaxHeap(&mh, arr[i]);
}
    	break;
		}
		
			
		case 2: {
		//���ضѵĴ�С 
		printf("\n�ѵĴ�СΪ%d\n",size(&mh)); 
		break;
		}
			
			
	
			
		case 3: {
		//�п� 
	if(isEmpty(&mh)) 
	printf("���ǿյģ�\n");
	else{
	printf("�Ѳ��ǿյģ�\n");
	} 
	break;
}
			
		case 4: {
 	//����Ԫ�� 
	for (int i = 0; i < num; i++)
	{
		int x = TopK(&mh);
		printf("%d  ", x);
	}	
		break;
		}
			
			
		
		case 5:{	
		system("cls");
		exit(0);
		break;
			}
		}
	}
		else
		{
			printf("\n��������ȷ�����֡�\n");    //��������
		}
		system("PAUSE");
	}
	return 0;
	
}
