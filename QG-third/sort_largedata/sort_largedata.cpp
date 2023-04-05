#include<stdio.h> 
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<ctime>
#include<assert.h>
#include<string.h>
#include<stack>

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


//冒泡排序                                       【传入两个参数（数组+整型）】 
void bubbleSort(int a[], int n)
{
  for(int i =0 ; i< n-1; ++i)
  {
    for(int j = 0; j < n-i-1; ++j)
    {
      if(a[j] > a[j+1])
      {
        int tmp = a[j] ;  //交换
        a[j] = a[j+1] ;
        a[j+1] = tmp;
      }
    }
  }
} 

//选择排序                                      【传入两个参数（数组+整型）】 
void selectionSort(int arr[], int n) {
    int minIndex, temp; 
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {     // 寻找最小的数
                minIndex = j;                 // 将最小数的索引保存
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

}

//插入排序 
void InsertSort(int a[], int n)
{
  for(int i= 1; i<n; i++){
    if(a[i] < a[i-1]){   //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
      int j= i-1;
      int x = a[i];     //复制为哨兵，即存储待排序元素
      a[i] = a[i-1];           //先后移一个元素
      while(x < a[j]){   //查找在有序表的插入位置
        a[j+1] = a[j];
        j--;     //元素后移
      }
      a[j+1] = x;     //插入到正确位置
    }
         
  }

}

//快速排序
void QuickSort(int v[], int low, int high) {
    if (low >= high)  // 结束标志
        return;
    int first = low;  // 低位下标
    int last = high;  // 高位下标
    int key = v[first];  // 设第一个为基准

    while (first < last)
    {
        // 将比第一个小的移到前面
        while (first < last && v[last] >= key)
            last--;
        if (first < last)
            v[first++] = v[last];

        // 将比第一个大的移到后面
        while (first < last && v[first] <= key)
            first++;
        if (first < last)
            v[last--] = v[first];
    }
    //
    v[first] = key;
    // 前半递归
    QuickSort(v, low, first - 1);
    // 后半递归
    QuickSort(v, first + 1, high);
    
} 

void swap(int p1,int p2){//这里的符号是引用，是对原变量操作 
		int temp = p1;
		p1=p2;
		p2=temp;	
	}  

//堆排序
void max_heapify(int arr[], int start, int end) {
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { //若子节点在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点指标，选择最大的
            son++;
        if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完成，直接跳出函数
            return;
        else { //否则交换父子內容再继续子节点与孙节点比較
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int arr[], int len) {
    //初始化，i从最后一个父节点开始调整
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    //先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完成
    for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
} 


int min(int x, int y) {
    return x < y ? x : y;
}

//归并排序
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

//希尔排序
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


//计数排序
void CountSort(int a[], int len)
{
	assert(a);
	//通过max和min计算出临时数组所需要开辟的空间大小
	int max = a[0], min = a[0];
	for (int i = 0; i < len; i++){
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	//使用calloc将数组都初始化为0
	int range = max - min + 1;
	int *b = (int *)calloc(range, sizeof(int));
	//使用临时数组记录原始数组中每个数的个数
	for (int i = 0; i < len; i++){
		//注意：这里在存储上要在原始数组数值上减去min才不会出现越界问题
		b[a[i] - min] += 1;
	}
	int j = 0;
	//根据统计结果，重新对元素进行回收
	for (int i = 0; i < range; i++){
		while (b[i]--){
			//注意：要将i的值加上min才能还原到原始数据
			a[j++] = i + min;
		}
	}
	//释放临时数组
	free(b);
	b = NULL;
}



//获得未排序数组中最大的一个元素值
int GetMaxVal(int arr[], int len)
{
    
    int maxVal = arr[0]; //假设最大为arr[0]
    
    for(int i = 1; i < len; i++)  //遍历比较，找到大的就赋值给maxVal
    {
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }
    
    return maxVal;  //返回最大值
}
 
//桶排序   参数：数组及其长度
void BucketSort(int arr[] , int len)
{
    int tmpArrLen = GetMaxVal(arr , len) + 1;
    int tmpArr[tmpArrLen];  //获得空桶大小
    int i, j;
    
    for( i = 0; i < tmpArrLen; i++)  //空桶初始化
        tmpArr[i] = 0;
    
    for(i = 0; i < len; i++)   //寻访序列，并且把项目一个一个放到对应的桶子去。
        tmpArr[ arr[i] ]++;
    
    for(i = 0, j = 0; i < tmpArrLen; i ++)
    {
        while( tmpArr[ i ] != 0) //对每个不是空的桶子进行排序。
        {
            arr[j ] = i;  //从不是空的桶子里把项目再放回原来的序列中。
            j++;
            tmpArr[i]--;
        }
    }
}


 

int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int maxData = data[0];  ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
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
/*    int d = 1; //保存最大的位数
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
void radixsort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete []tmp;
    delete []count;
}


//冒泡排序-优化版(优化外循环） 
void BubbleSort2(int arr[], int size)
{
	assert(arr);
	int i = 0, j = 0;
 
	for (i = 0; i < size - 1; i++)//一共要排序size-1次
	{
		//每次遍历标志位都要先置为0，才能判断后面的元素是否发生了交换
		int flag = 0;
 
		for (j = 0; j < size - 1 - i; j++)//选出该趟排序的最大值往后移动
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//只要有发生了交换，flag就置为1
			}
		}
 
		//判断标志位是否为0，如果为0，说明后面的元素已经有序，就直接return
		if (flag == 0)
		{
			return;
		}
	}
 
}

//冒泡排序-优化版(优化内循环） 
void BubbleSort3(int arr[], int size)
{
	assert(arr);
	int i = 0, j = 0;
	int k = size - 1,pos = 0;//pos变量用来标记循环里最后一次交换的位置  
	
	for (i = 0; i < size - 1; i++)//一共要排序size-1次
	{
		//每次遍历标志位都要先置为0，才能判断后面的元素是否发生了交换
		int flag = 0;
 
		for (j = 0; j <k; j++)//选出该趟排序的最大值往后移动
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;//只要有发生了交换，flag就置为1
				pos = j;//循环里最后一次交换的位置 j赋给pos
			}
		}
 
		k = pos;
		//判断标志位是否为0，如果为0，说明后面的元素已经有序，就直接return
		if (flag == 0)
		{
			return;
		}
	}
 
}


//快排-非递归版--随机枢轴
//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
 
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

//快排-非递归版--三枢轴
//取三者中其关键宇取中值的记录为枢轴
 
void quick_sort_three(int s[], int l, int r) {//取随机数为枢纽
 
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
 
             while (i < j && s[j] >= x) // 从右向左找第一个小于x的数 
 
                 j--;
 
             if (i < j)
 
                 s[i++] = s[j];
 
 
 
             while (i < j && s[i] <= x) // 从左向右找第一个大于等于x的数 
 
                 i++;
 
             if (i < j)
 
                 s[j--] = s[i];
 
         }
 
         s[i] = x;
 
         quick_sort_three(s, l, i - 1); // 递归调用  
 
         quick_sort_three(s, i + 1, r);
 
    }
 
}










int main(){
	//选择数字 
	int num = 0;
	//数据量 
	int max = 0;	
	//计时器 
	clock_t startTime, endTime;
	
	
	//判断数据量 
	
	system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|           请选择数据量           |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----10000                  |\n");
		printf("\t\t\t|      2----50000                  |\n");
		printf("\t\t\t|      3----200000                 |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp——蒋卓然造|\n");
		printf("\t\t\t|----------------------------------|\n");	
	//开始判断 
	printf("\t\t\t从选项中猜猜师弟的头发还剩几根，乱选的话就又要重开了哦：\n");
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
			printf("\n请输入正确的数字。\n");    //错误提醒
			goto loop;
		}

	
 
 	//生成数据 
 	//下面是写数据，将数字写入到data.txt文件中
	FILE *fpWrite=fopen("data.txt","w");
	if(fpWrite==NULL)
	{
		return 0;
	}
	for(int i=0;i<=max;i++){
	int random = rand();
	fprintf(fpWrite,"%d ",random);}
	fclose(fpWrite);
	//下面是读数据，将读到的数据存到数组中
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
 
 
 	
	
	//储存数组
	int arrayTest[max];
	//赋值
	for(int i=0;i<=max;i++)
	{
		arrayTest[i] = array[i];	
	}
	 
	//数组长度 
	int length = sizeof(arrayTest) / sizeof(arrayTest[0]);
	

	while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG第三周——十大排序        |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----冒泡排序               |\n");
		printf("\t\t\t|      2----选择排序               |\n");
		printf("\t\t\t|      3----插入排序               |\n");
		printf("\t\t\t|      4----快速排序-递归版        |\n");
		printf("\t\t\t|      5----堆排序                 |\n");
		printf("\t\t\t|      6----归并排序               |\n");
		printf("\t\t\t|      7----希尔排序               |\n");
		printf("\t\t\t|      8----计数排序               |\n");
		printf("\t\t\t|      9----桶排序                 |\n");
		printf("\t\t\t|      10---基数排序               |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      11---冒泡排序-优化内循环    |\n");
		printf("\t\t\t|      12---冒泡排序-优化外循环    |\n");
		printf("\t\t\t|----------------------------------|\n");	
		printf("\t\t\t|      13---快排-非递归版--随机枢轴|\n");
		printf("\t\t\t|      14---快排-非递归版--三枢轴  |\n");
		printf("\t\t\t|      15---退出                   |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp——蒋卓然造|\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\n请选择操作:\n");
		checkinput(&num);
		if (num >= 1 && num <= 16) {
			switch (num) {
			case 1: {
			//冒泡
			startTime = clock();
			bubbleSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f s",time);
				break;
			}
			case 2: {
			//选择
			startTime = clock();
			selectionSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 3: {
			//插入
			startTime = clock();
			InsertSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time); 
				break;
			}
			case 4: {
			//快速
			startTime = clock();
			QuickSort(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 5: {
			//堆 
			startTime = clock();
			heap_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				
				break;
			}
			case 6: {
			//归并 				
			startTime = clock();
			merge_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 7: {				
			//希尔 
			startTime = clock();
			shell_sort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 8: {
			//计数 			
			startTime = clock();
			CountSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 9: {
				//桶
			startTime = clock();
			BucketSort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 10: {
				//基数
			startTime = clock();
			radixsort(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			
			
			case 11: {
				//冒泡排序-优化内循环 
			startTime = clock();
			BubbleSort3(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 12: {
				//冒泡排序-优化外循环 
			startTime = clock();
			BubbleSort2(arrayTest,length);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 13: {
				//快排-非递归版--随机枢轴
			startTime = clock();
			QuickSort_random(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			case 14: {
				//快排-非递归版--三枢轴
			startTime = clock();
			quick_sort_three(arrayTest,0,length-1);
			endTime = clock();
			double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
			printf("此次排序所用时间：%f",time);
				break;
			}
			
			
			case 15:{
			
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t尚有很多不足之处，望多多指教!\n\n\n\n\n\n");
				exit(0);
				break;
			}
		}
	}
		else
		{
			printf("\n请输入正确的数字。\n");    //错误提醒
		}
		system("pause");
	}
	return 0;
} 
