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
 
//-----------堆的构建等等方法
int size(MH *mh);//返回堆大小
int isEmpty(MH *mh);//判空
void initMaxHeap(MH* mh, int size);//初始化堆

void AdjustUp(MH* mh, int k);//上移元素
void AdjustDown(MH* mh, int k);//下移操作
void insertMaxHeap(MH* mh, HeapDataType value);//插入元素
HeapDataType TopK(MH* mh);//弹出元素

 
 

 
//返回堆大小
int size(MH *mh){
	return mh->count;
}
 
//判断空堆 
int isEmpty(MH *mh){
	return 0 == mh->count;
}
 
//下移元素 
void AdjustDown(MH* mh, int k){
	while (k * 2 <= mh->count)
	{
		int j = k * 2;
		if (j + 1 <= mh->count && mh->data[j] < mh->data[j + 1])//如果右孩子存在且右孩子比左孩子大
		{
			j = j + 1;
		}
		if (mh->data[k] > mh->data[j])//如果节点比孩子大
		{
			break;
		}
		//否则交换k和j
		int tmp = mh->data[k];
		mh->data[k] = mh->data[j];
		mh->data[j] = tmp;
 
		k = j;
	}
}
 
 
//初始化堆
void initMaxHeap(MH* mh, int size){
	mh->MaxSize = size;
	mh->data = (HeapDataType*)malloc((mh->MaxSize + 1) * sizeof(HeapDataType));//从1开始存储
	mh->count = 0;
}
 
 
//上移元素
void AdjustUp(MH* mh, int k){
	while (1 < k && mh->data[k / 2] < mh->data[k])
	{
		int tmp = mh->data[k / 2];
		mh->data[k / 2] = mh->data[k];
		mh->data[k] = tmp;
		k /= 2;
	}
}
 
//插入元素
void insertMaxHeap(MH* mh, HeapDataType value){
	//看看有没有满
	assert(mh->count + 1 <= mh->MaxSize);
 
	//count为最后一个元素
	mh->data[mh->count + 1] = value;
	mh->count++;
	AdjustUp(mh,mh->count);//上移到合适位置
}
 
//弹出元素
HeapDataType TopK(MH* mh){
	assert(mh->count > 0);
 
	//获得顶端元素
	HeapDataType res = mh->data[1];
 
	//把最后的赋值给顶端
	mh->data[1] = mh->data[mh->count];
	//最后的元素置0，并且count--
	mh->data[(mh->count)--] = 0;
 
	//把顶端元素下移到合适位置
	AdjustDown(mh, 1);
	return res;
}
 
 
//输入限制模块：最最最重要的模块，抵挡师兄的第一道防线，也是最后一道（-——-） 
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
            printf("输入错误，请重新输入！\n");
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
		printf("\t\t\t|      QG第四周——堆              |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----初始化堆               |\n");
		printf("\t\t\t|      2----堆的大小               |\n");
		printf("\t\t\t|      3----判断堆是否为空         |\n");
		printf("\t\t\t|      4----弹出所有元素(由大到小) |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      5---退出                    |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp——蒋卓然造|\n");
		printf("\t\t\t|----------------------------------|\n");		
		printf("\n请选择操作:\n");
		checkinput(&num_check);
		if (num_check >= 1 && num_check <= 5) {
			switch (num_check) {
			
		
		case 1: {
	printf("请输入计划添加的元素个数：");
	while(!(scanf("%d", &num) && num > 0 && getchar() == '\n'))	
   	{
		while(getchar() != '\n');//清空缓存区
		printf("元素个数只能是正整数喔！\n");//温馨提醒一下
	}
	//初始化堆 
	initMaxHeap(&mh, num);
	
	//开始创建元素	   
    int arr[num];    
  	for (int i = 0; i < num; i++) {
	printf("请输入第%d个整数：",i+1);
	while(!(scanf("%d", &arr[i]) && getchar() == '\n'))
	{
		while(getchar() != '\n');//清空缓存区
		printf("储存的数据只能是整数喔！\n");//温馨提醒一下
	}
		insertMaxHeap(&mh, arr[i]);
}
    	break;
		}
		
			
		case 2: {
		//返回堆的大小 
		printf("\n堆的大小为%d\n",size(&mh)); 
		break;
		}
			
			
	
			
		case 3: {
		//判空 
	if(isEmpty(&mh)) 
	printf("堆是空的！\n");
	else{
	printf("堆不是空的！\n");
	} 
	break;
}
			
		case 4: {
 	//弹出元素 
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
			printf("\n请输入正确的数字。\n");    //错误提醒
		}
		system("PAUSE");
	}
	return 0;
	
}
