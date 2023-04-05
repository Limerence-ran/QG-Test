#include<stdio.h>
#include<stdlib.h>
 void exchange(int nums[],int a,int b){
	int tmp = nums[a];
	nums[a] = nums[b];
	nums[b] = tmp;
}




/*只能遍历一遍，从左向右遍历*/
void sortarray(int nums[],int length){
	int i=-1;
	int j=-1;
	int k=-1;
	for(int p=0;p<length;p++){
		if(nums[p] == 0){
			if(i == -1)
				i = 0;//第一个0的位置
			if(j != -1){
				for(int t=p;t>j;t--)
					nums[t] = nums[t-1];
				nums[j] = 0;
				j++;
				if(k != -1)k++;
			}
			else if(k != -1){
				for(int t=p;t>k;t--)
					nums[t] = nums[t-1];
				nums[k] = 0;
				k++;
			}
			else
				;
		}
		else if(nums[p] == 1){
			if(j == -1){
				if(k != -1) j = k;
				else j = p;
			}
			if(k != -1){
				exchange(nums,p,k);
				k++;
			}
			else
				;
		}
		else if(nums[p] == 2){
			if(k == -1)
				k = p;
		}
		else
			;
	}
	printf("排序后数组元素打印如下:\n\n"); 
	for (i = 0; i<length; i++)
		printf("%d\t", nums[i]);
}




// Driver program to test above methods
int main()
{   printf("-----QG 3rd home-work-----\n");
 	printf("---written by Jiang Zhuoran---\n");

  	//input a 数组 
	printf("请输入数组的长度(注意只能输入0、1、2哦)：\n"); 
	// 1、用户输入数组的长度
	int length;
	scanf("%d",&length);
	printf("确认您输入的数组长度为：%d\n",length);
	
	// 2、根据用户输入的长度创建数组
	int array[length];
	
	// 3、让用户依次填充数组的值
	int i;
	for(i=0;i<length;i++){
		printf("请输入array[%d]的值:\n",i);
		// scanf("%d",&iArray[i]);//(使用这种，或者下面的 scanf("%d",iArray+i); 都是等价的)
		scanf("%d",array+i);
	}
	sortarray(array,length);
    printf("-------------------------------------------");
    printf("本次测试结束，证明函数可用,程序即将关闭");
    system("pause");
     return 0;
}
















