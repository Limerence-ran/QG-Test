#include"AQueue.h"
#include<stdio.h>
#include<stdlib.h>
void InitAQueue(AQueue* Q)
{
    int i;
    Q->front = Q->rear = 0;
    for (i = 0; i < MAXQUEUE; i++) {
        Q->data[i] = (void*)malloc(21);
        if(i< MAXQUEUE-1)
        CheckType(Q);
    }
    printf("\n队列创建成功！\n");
}

void DestoryAQueue(AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return;
    }
    else {
        for (int i = 0; i < MAXQUEUE; i++)
            free(Q->data[i]);
        Q->data[0]= NULL;
        printf("队列销毁成功！\n");
    }
}

Status IsFullAQueue(const AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    if (Q->length == 0) {
        return FALSE;
    }
    if (Q->length == MAXQUEUE - 1)
    {
        printf("这是一个满队列！\n");
        return TRUE;
    }
    else {
        printf("这不是一个满队列！\n");
        return FALSE;
    }
}

Status IsEmptyAQueue(const AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if(Q->length == 0) {
        printf("这是一个空队列！\n");
        return TRUE;
    }
    else{
        printf("这不是一个空队列！\n");
        return FALSE;
    }
}

Status GetHeadAQueue(AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length==0)
    {
        printf("队列为空！没有队头！\n");
        return FALSE;
    }
    else {
        if (Q->type[Q->front] == 8)
            printf("队头元素是：【%lf】\n", *(double*)Q->data[Q->front]);
        if (Q->type[Q->front] == 1)
            printf("队头元素是：【%c】\n", *(char*)Q->data[Q->front]);
        if (Q->type[Q->front] == 4)
            printf("队头元素是：【%d】\n", *(int*)Q->data[Q->front]);
        if (Q->type[Q->front] == 20)
            printf("队头元素是：【%s】\n", (char*)Q->data[Q->front]);
        return TRUE;
    }
}

void LengthAQueue(AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return ;
    }
    else {
        printf("队列长度为:%d\n", Q->length);
        return ;
    }
}

Status EnAQueue(AQueue* Q, void* data,int s)
{ 
    if(Q->length==0)
    {
        Q->data[Q->front]=data;
        Q->rear = (Q->rear + 1) %MAXQUEUE;
        Q->type[Q->front] = s;
        Q->length++;
        printf("\n入队成功！\n");
        TraverseAQueue(Q);
        return TRUE;
    }
    else {
        Q->data[Q->rear]=data;
        Q->type[Q->rear] = s;
        Q->rear = (Q->rear + 1) %MAXQUEUE;
        Q->length++;
        printf("\n入队成功！\n");
        TraverseAQueue(Q);
        return TRUE;
    }
}

Status DeAQueue(AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length==0)
    {
        printf("队列是空的！出不了队！\n");
        return FALSE;
    }
    else{
        Q->front = (Q->front + 1) %MAXQUEUE;
        Q->length--;
        printf("\n出队成功！\n");
        TraverseAQueue(Q);
        return TRUE;
    }
}

void ClearAQueue(AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return ;
    }
    else if (Q->length==0)
    {
        printf("队列已经是空的了！\n");
        return;
    }
    else {
        Q->front = Q->rear = 0;
        Q->length = 0;
        printf("队列清空成功！\n");
    }
}

Status TraverseAQueue(const AQueue* Q)
{
    if (Q->data[0] == NULL)
    {
        printf("请先输入【1】创建队列\n");
        return FALSE;
    }
    else if (Q->length==0)
    {
        printf("队列里面什么都没有!\n");
        return FALSE;
    }
    else {
        printf("\n队列为：\n");
        printf("【head】 -> ");
        for (int i = Q->front; i < Q->front+Q->length;i++) {
            if (Q->type[i] == 8)
                printf("【%lf】", *(double*)Q->data[i]);
            if (Q->type[i] == 1)
                printf("【%c】", *(char*)Q->data[i]);
            if (Q->type[i] == 4)
                printf("【%d】", *(int*)Q->data[i]);
            if (Q->type[i] == 20)
                printf("【%s】", (char*)Q->data[i]);
            printf(" -> ");
        }
        printf("【rear】\n");
        return TRUE;
    }
}

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

void CheckType(AQueue* Q) {
    printf("\t\t\t|--------------------------------|\n");

    printf("\t\t\t|           数据类型选择         |\n");
    printf("\t\t\t|--------------------------------|\n");
    printf("\t\t\t|          1---整型              |\n");
    printf("\t\t\t|          2---字符型            |\n");
    printf("\t\t\t|          3---浮点型            |\n");
    printf("\t\t\t|          4---字符串            |\n");
    printf("\t\t\t|--------------------------------|\n");
    int t = 1, s;
    printf("\n你想入队哪种类型？:\n");
    checkinput(&t);
    if (t > 0 && t < 5) {
        switch (t)
        {
        case 1: {
            int* a = (int*)malloc(sizeof(int));
            s = 4;
            printf("\n想入队的【整型数据】：\n");
            checkinput(a);
            EnAQueue(Q, a, s);
            break;
        }
        case 2: {
            char* a = (char*)malloc(sizeof(char));
            s = 1;
            printf("\n想入队的【字符型数据】：\n");
            scanf("%c", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 3: {
            double* a = (double*)malloc(sizeof(double));
            s = 8;
            printf("\n想入队的【浮点型数据】：\n");
            scanf("%lf", a);
            getchar();
            EnAQueue(Q, a, s);
            break;
        }
        case 4: {
            char* a = (char*)malloc(20 * sizeof(char));
            s = 20;
            printf("\n想入队的【字符串型数据】（最大长度为20哦！）：\n");
            gets(a);
            EnAQueue(Q, a, s);
            break;
        }
        }
    }
    else
    {
        printf("\n应输入在[1,4]之间的整数！\n");
        CheckType(Q);
    }
    return;
}

#include"AQueue.h"
#include<stdio.h>
#include<stdlib.h>
int main() {
	int num = 0;
	AQueue* Q = (AQueue*)malloc(sizeof(AQueue));
	Q->length=0;
	Q->data[0] = NULL;
	while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|         循环队列基本操作         |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1---建立队列                |\n");
		printf("\t\t\t|      2---销毁队列                |\n");
		printf("\t\t\t|      3---判断满队列              |\n");
		printf("\t\t\t|      4---判断空队列              |\n");
		printf("\t\t\t|      5---获得队头元素            |\n");
		printf("\t\t\t|      6---获得队列长度            |\n");
		printf("\t\t\t|      7---入队                    |\n");
		printf("\t\t\t|      8---出队                    |\n");
		printf("\t\t\t|      9---清空队列                |\n");
		printf("\t\t\t|      10---遍历打印队列           |\n");
		printf("\t\t\t|      11---退出                   |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|                 前端-Sheldonlee  |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\n请选择操作:\n");
		checkinput(&num);
		if (num >= 1 && num <= 11) {
			switch (num) {
			case 1: {
				if (Q->data[0] != NULL) {
					printf("\n已存在一个队列，请先销毁此链表！\n");
				}
				else {
					InitAQueue(Q);
				}
				break;
			}
			case 2: {
				DestoryAQueue(Q);
				break;
			}
			case 3: {
				IsFullAQueue(Q);
				break;
			}
			case 4: {
				IsEmptyAQueue(Q);
				break;
			}
			case 5: {
				GetHeadAQueue(Q);
				break;
			}
			case 6: {
				LengthAQueue(Q);
				break;
			}
			case 7: {
				if (Q->data[0] == NULL) {
					printf("\n请先输入【1】创建链队列\n");
				}
				else if (Q->length == MAXQUEUE - 1)
				{
					printf("队列满了！不能再入队了！\n");
				}
				else {
					CheckType(Q);
				}
				break;
			}
			case 8: {
				DeAQueue(Q);
				break;
			}
			case 9: {
				ClearAQueue(Q);
				break;
			}
			case 10: {
				TraverseAQueue(Q);
				break;
			}
			case 11:
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t尚有很多不足之处，望多多指教!\n\n\n\n\n\n");
				exit(0);
				break;
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
