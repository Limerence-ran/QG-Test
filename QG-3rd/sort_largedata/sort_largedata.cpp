#include<stdio.h> 
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<ctime>
#include<assert.h>
#include<string.h>
#include<stack>

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


//ð������                                       ��������������������+���ͣ��� 
void bubbleSort(int a[], int n)
{
  for(int i =0 ; i< n-1; ++i)
  {
    for(int j = 0; j < n-i-1; ++j)
    {
      if(a[j] > a[j+1])
      {
        int tmp = a[j] ;  //����
        a[j] = a[j+1] ;
        a[j+1] = tmp;
      }
    }
  }
} 

//ѡ������                                      ��������������������+���ͣ��� 
void selectionSort(int arr[], int n) {
    int minIndex, temp; 
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {     // Ѱ����С����
                minIndex = j;                 // ����С������������
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

}

//�������� 
void InsertSort(int a[], int n)
{
  for(int i= 1; i<n; i++){
    if(a[i] < a[i-1]){   //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������
      int j= i-1;
      int x = a[i];     //����Ϊ�ڱ������洢������Ԫ��
      a[i] = a[i-1];           //�Ⱥ���һ��Ԫ��
      while(x < a[j]){   //�����������Ĳ���λ��
        a[j+1] = a[j];
        j--;     //Ԫ�غ���
      }
      a[j+1] = x;     //���뵽��ȷλ��
    }
         
  }

}

//��������
void QuickSort(int v[], int low, int high) {
    if (low >= high)  // ������־
        return;
    int first = low;  // ��λ�±�
    int last = high;  // ��λ�±�
    int key = v[first];  // ���һ��Ϊ��׼

    while (first < last)
    {
        // ���ȵ�һ��С���Ƶ�ǰ��
        while (first < last && v[last] >= key)
            last--;
        if (first < last)
            v[first++] = v[last];

        // ���ȵ�һ������Ƶ�����
        while (first < last && v[first] <= key)
            first++;
        if (first < last)
            v[last--] = v[first];
    }
    //
    v[first] = key;
    // ǰ��ݹ�
    QuickSort(v, low, first - 1);
    // ���ݹ�
    QuickSort(v, first + 1, high);
    
} 

void swap(int p1,int p2){//����ķ��������ã��Ƕ�ԭ�������� 
		int temp = p1;
		p1=p2;
		p2=temp;	
	}  

//������
void max_heapify(int arr[], int start, int end) {
    //�������ڵ�ָ����ӽڵ�ָ��
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { //���ӽڵ��ڷ�Χ�ڲ����Ƚ�
        if (son + 1 <= end && arr[son] < arr[son + 1]) //�ȱȽ������ӽڵ�ָ�꣬ѡ������
            son++;
        if (arr[dad] > arr[son]) //������ڵ�����ӽڵ���������ɣ�ֱ����������
            return;
        else { //���򽻻����Ӄ����ټ����ӽڵ�����ڵ���^
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int arr[], int len) {
    //��ʼ����i�����һ�����ڵ㿪ʼ����
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    //�Ƚ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ���������ٴ��µ���(�յ�����Ԫ��֮ǰ��Ԫ��)��ֱ���������
    for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
} 


int min(int x, int y) {
    return x < y ? x : y;
}

//�鲢����
void merge_sort(int arr[], int len) {
    int* a = arr;
    int* b = (int*) malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg + seg) {
            int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

//ϣ������
void shell_sort(int arr[], int length) {
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                std::swap(arr[j], arr[j - h]);
            }
        }
        h = h / 3;
    }
} 


//��������
void CountSort(int a[], int len)
{
	assert(a);
	//ͨ��max��min�������ʱ��������Ҫ���ٵĿռ��С
	int max = a[0], min = a[0];
	for (int i = 0; i < len; i++){
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//ʹ��calloc�����鶼��ʼ��Ϊ0
	int range = max - min + 1;
	int *b = (int *)calloc(range, sizeof(int));
	//ʹ����ʱ�����¼ԭʼ������ÿ�����ĸ���
	for (int i = 0; i < len; i++){
		//ע�⣺�����ڴ洢��Ҫ��ԭʼ������ֵ�ϼ�ȥmin�Ų������Խ������
		b[a[i] - min] += 1;
	}
	int j = 0;
	//����ͳ�ƽ�������¶�Ԫ�ؽ��л���
	for (int i = 0; i < range; i++){
		while (b[i]--){
			//ע�⣺Ҫ��i��ֵ����min���ܻ�ԭ��ԭʼ����
			a[j++] = i + min;
		}
	}
	//�ͷ���ʱ����
	free(b);
	b = NULL;
}



//���δ��������������һ��Ԫ��ֵ
int GetMaxVal(int arr[], int len)
{
    
    int maxVal = arr[0]; //�������Ϊarr[0]
    
    for(int i = 1; i < len; i++)  //�����Ƚϣ��ҵ���ľ͸�ֵ��maxVal
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    
    return maxVal;  //�������ֵ
}
 
//Ͱ����   ���������鼰�䳤��
void BucketSort(int arr[] , int len)
{
    int tmpArrLen = GetMaxVal(arr , len) + 1;
    int tmpArr[tmpArrLen];  //��ÿ�Ͱ��С
    int i, j;
    
    for( i = 0; i < tmpArrLen; i++)  //��Ͱ��ʼ��
        tmpArr[i] = 0;
    
    for(i = 0; i < len; i++)   //Ѱ�����У����Ұ���Ŀһ��һ���ŵ���Ӧ��Ͱ��ȥ��
        tmpArr[ arr[i] ]++;
    
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) //��ÿ�����ǿյ�Ͱ�ӽ�������
        {
            arr[j ] = i;  //�Ӳ��ǿյ�Ͱ�������Ŀ�ٷŻ�ԭ���������С�
            j++;
            tmpArr[i]--;
        }
    }
}


 

int maxbit(int data[], int n) //���������������ݵ����λ��
{
    int maxData = data[0];  ///< �����
    /// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
/*    int d = 1; //��������λ��
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;*/
}
void radixsort(int data[], int n) //��������
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //����d������
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for(j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}


//ð������-�Ż���(�Ż���ѭ���� 
void BubbleSort2(int arr[], int size)
{
	assert(arr);
	int i = 0, j = 0;
 
	for (i = 0; i < size - 1; i++)//һ��Ҫ����size-1��
	{
		//ÿ�α�����־λ��Ҫ����Ϊ0�������жϺ����Ԫ���Ƿ����˽���
		int flag = 0;
 
		for (j = 0; j < size - 1 - i; j++)//ѡ��������������ֵ�����ƶ�
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//ֻҪ�з����˽�����flag����Ϊ1
			}
		}
 
		//�жϱ�־λ�Ƿ�Ϊ0�����Ϊ0��˵�������Ԫ���Ѿ����򣬾�ֱ��return
		if (flag == 0)
		{
			return;
		}
	}
 
}

//ð������-�Ż���(�Ż���ѭ���� 
void BubbleSort3(int arr[], int size)
{
	assert(arr);
	int i = 0, j = 0;
	int k = size - 1,pos = 0;//pos�����������ѭ�������һ�ν�����λ��  
	
	for (i = 0; i < size - 1; i++)//һ��Ҫ����size-1��
	{
		//ÿ�α�����־λ��Ҫ����Ϊ0�������жϺ����Ԫ���Ƿ����˽���
		int flag = 0;
 
		for (j = 0; j <k; j++)//ѡ��������������ֵ�����ƶ�
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//ֻҪ�з����˽�����flag����Ϊ1
				pos = j;//ѭ�������һ�ν�����λ�� j����pos
			}
		}
 
		k = pos;
		//�жϱ�־λ�Ƿ�Ϊ0�����Ϊ0��˵�������Ԫ���Ѿ����򣬾�ֱ��return
		if (flag == 0)
		{
			return;
		}
	}
 
}


//����-�ǵݹ��--�������
//Ҫȡ��[a,b]�����������ʹ��(rand() % (b-a+1))+ a;
 
void QuickSort_random(int a[],int low,int high){
 
    if(low<high){
 
           int random = ((rand()%(high-low+1))+low);
 
           int l = low,h = high,flag = a[random];
 
           swap(a[random],a[low]);
 
           while(l<h){
 
                  while(l<h&&a[h]>=flag) h--;
 
                  a[l] = a[h];
 
                  while(l<h&&a[l]<=flag) l++;
 
                  a[h] = a[l];
 
           }
 
           a[l] = flag;
 
           QuickSort_random(a,low,l-1);
 
           QuickSort_random(a,l+1,high);
 
    }
 
}

//����-�ǵݹ��--������
//ȡ��������ؼ���ȡ��ֵ�ļ�¼Ϊ����
 
void quick_sort_three(int s[], int l, int r) {//ȡ�����Ϊ��Ŧ
 
    if (l < r)
 
    {
 
         int x = 0;
 
         int x1 = s[l], x2 = s[r], x3 = s[(l + r) >> 1];
 
         if (x1 <= x2&&x2 <= x3) {
 
              x = x2;
 
             swap(s[r], s[l]);
 
         }
 
         else if (x2 <= x1&&x1 <= x3) {
 
              x = x1;
 
             swap(s[l], s[l]);
 
         }
 
         else {
 
              x = x3;
 
             swap(s[(l+r)/2], s[l]);
 
         }
 
         int i = l, j = r;
 
         while (i < j)
 
         {
 
             while (i < j && s[j] >= x) // ���������ҵ�һ��С��x���� 
 
                 j--;
 
             if (i < j)
 
                 s[i++] = s[j];
 
 
 
             while (i < j && s[i] <= x) // ���������ҵ�һ�����ڵ���x���� 
 
                 i++;
 
             if (i < j)
 
                 s[j--] = s[i];
 
         }
 
         s[i] = x;
 
         quick_sort_three(s, l, i - 1); // �ݹ����  
 
         quick_sort_three(s, i + 1, r);
 
    }
 
}










int main(){
	//ѡ������ 
	int num = 0;
	//������ 
	int max = 0;	
	//��ʱ�� 
	clock_t startTime, endTime;
	
	
	//�ж������� 
	
	system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|           ��ѡ��������           |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----10000                  |\n");
		printf("\t\t\t|      2----50000                  |\n");
		printf("\t\t\t|      3----200000                 |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp������׿Ȼ��|\n");
		printf("\t\t\t|----------------------------------|\n");	
	//��ʼ�ж� 
	printf("\t\t\t��ѡ���в²�ʦ�ܵ�ͷ����ʣ��������ѡ�Ļ�����Ҫ�ؿ���Ŷ��\n");
		loop:checkinput(&num);
		if (num >= 1 && num <= 3) {
			switch (num) {
			case 1: {//10000
			max = 10000;
				break;
			}
			case 2: {//50000
			max = 50000; 
				break;
			}
			case 3: {//200000
			max = 200000; 
				break;
			}
			}
		}
		else
		{  
			printf("\n��������ȷ�����֡�\n");    //��������
			goto loop;
		}

	
 
 	//�������� 
 	//������д���ݣ�������д�뵽data.txt�ļ���
	FILE *fpWrite=fopen("data.txt","w");
	if(fpWrite==NULL)
	{
		return 0;
	}
	for(int i=0;i<=max;i++){
	int random = rand();
	fprintf(fpWrite,"%d ",random);}
	fclose(fpWrite);
	//�����Ƕ����ݣ������������ݴ浽������
	int array[max]={0};
	FILE *fpRead=fopen("data.txt","r");
	if(fpRead==NULL)
	{
		return 0;
	}
	for(int i=0;i<=max;i++)
	{
		fscanf(fpRead,"%d ",&array[i]);		
	}
 
 
 	
	
	//��������
	int arrayTest[max];
	//��ֵ
	for(int i=0;i<=max;i++)
	{
		arrayTest[i] = array[i];	
	}
	 
	//���鳤�� 
	int length = sizeof(arrayTest) / sizeof(arrayTest[0]);
	

	while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG�����ܡ���ʮ������        |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----ð������               |\n");
		printf("\t\t\t|      2----ѡ������               |\n");
		printf("\t\t\t|      3----��������               |\n");
		printf("\t\t\t|      4----��������-�ݹ��        |\n");
		printf("\t\t\t|      5----������                 |\n");
		printf("\t\t\t|      6----�鲢����               |\n");
		printf("\t\t\t|      7----ϣ������               |\n");
		printf("\t\t\t|      8----��������               |\n");
		printf("\t\t\t|      9----Ͱ����                 |\n");
		printf("\t\t\t|      10---��������               |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      11---ð������-�Ż���ѭ��    |\n");
		printf("\t\t\t|      12---ð������-�Ż���ѭ��    |\n");
		printf("\t\t\t|----------------------------------|\n");	
		printf("\t\t\t|      13---����-�ǵݹ��--�������|\n");
		printf("\t\t\t|      14---����-�ǵݹ��--������  |\n");
		printf("\t\t\t|      15---�˳�                   |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp������׿Ȼ��|\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\n��ѡ�����:\n");
		checkinput(&num);
		if (num >= 1 && num <= 16) {
			switch (num) {
			case 1: {
			//ð��
			startTime = clock();
			bubbleSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f s",time);
				break;
			}
			case 2: {
			//ѡ��
			startTime = clock();
			selectionSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 3: {
			//����
			startTime = clock();
			InsertSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time); 
				break;
			}
			case 4: {
			//����
			startTime = clock();
			QuickSort(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 5: {
			//�� 
			startTime = clock();
			heap_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				
				break;
			}
			case 6: {
			//�鲢 				
			startTime = clock();
			merge_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 7: {				
			//ϣ�� 
			startTime = clock();
			shell_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 8: {
			//���� 			
			startTime = clock();
			CountSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 9: {
				//Ͱ
			startTime = clock();
			BucketSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 10: {
				//����
			startTime = clock();
			radixsort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			
			
			case 11: {
				//ð������-�Ż���ѭ�� 
			startTime = clock();
			BubbleSort3(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 12: {
				//ð������-�Ż���ѭ�� 
			startTime = clock();
			BubbleSort2(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 13: {
				//����-�ǵݹ��--�������
			startTime = clock();
			QuickSort_random(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			case 14: {
				//����-�ǵݹ��--������
			startTime = clock();
			quick_sort_three(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("�˴���������ʱ�䣺%f",time);
				break;
			}
			
			
			case 15:{
			
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t���кܶ಻��֮���������ָ��!\n\n\n\n\n\n");
				exit(0);
				break;
			}
		}
	}
		else
		{
			printf("\n��������ȷ�����֡�\n");    //��������
		}
		system("pause");
	}
	return 0;
} 
