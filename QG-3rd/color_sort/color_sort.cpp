#include<stdio.h>
#include<stdlib.h>
 void exchange(int nums[],int a,int b){
	int tmp = nums[a];
	nums[a] = nums[b];
	nums[b] = tmp;
}




/*ֻ�ܱ���һ�飬�������ұ���*/
void sortarray(int nums[],int length){
	int i=-1;
	int j=-1;
	int k=-1;
	for(int p=0;p<length;p++){
		if(nums[p] == 0){
			if(i == -1)
				i = 0;//��һ��0��λ��
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
	printf("���������Ԫ�ش�ӡ����:\n\n"); 
	for (i = 0; i<length; i++)
		printf("%d\t", nums[i]);
}




// Driver program to test above methods
int main()
{   printf("-----QG 3rd home-work-----\n");
 	printf("---written by Jiang Zhuoran---\n");

  	//input a ���� 
	printf("����������ĳ���(ע��ֻ������0��1��2Ŷ)��\n"); 
	// 1���û���������ĳ���
	int length;
	scanf("%d",&length);
	printf("ȷ������������鳤��Ϊ��%d\n",length);
	
	// 2�������û�����ĳ��ȴ�������
	int array[length];
	
	// 3�����û�������������ֵ
	int i;
	for(i=0;i<length;i++){
		printf("������array[%d]��ֵ:\n",i);
		// scanf("%d",&iArray[i]);//(ʹ�����֣���������� scanf("%d",iArray+i); ���ǵȼ۵�)
		scanf("%d",array+i);
	}
	sortarray(array,length);
    printf("-------------------------------------------");
    printf("���β��Խ�����֤����������,���򼴽��ر�");
    system("pause");
     return 0;
}
















