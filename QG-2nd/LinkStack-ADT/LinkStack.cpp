#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

//û�������Լ�д��ͷ�ļ��������� 

// LinkStack.

StackNode *bottom = NULL;
 // ��ʼ��ջ
Status initLStack(LinkStack *s)
{
	s->count = 0;
	s->top = (StackNode*)malloc(sizeof(StackNode));
	s->top->data = 1234567890;
	s->top->next = NULL;
	bottom = s->top;
	printf("Successfully initialize the stack.\n");
	return SUCCESS;
}
//�ж��Ƿ�Ϊ��ջ 
Status isEmptyLStack(LinkStack *s)
{
	if (s->count == 0)
    {
        printf("It is empty.\n");
		return SUCCESS;
	}
    printf("Not empty.\n");
    return ERROR;
}
// �õ�ջ��Ԫ�� 
Status getTopLStack(LinkStack *s, ElemType *e)
{
    if(s->top == NULL)
    {
        printf("There is no stack.\n");
        return ERROR;
    }
    *e = s->top->data;
    printf("The top element is %d.\n", *e);
	return SUCCESS;
}
//���ջ 
Status clearLStack(LinkStack *s)
{
	StackNode* p = NULL;
	s->count = 0;
	s->top = bottom;
	p = bottom = bottom->next;
	while (p)
	{
		p = bottom->next;
		free(bottom);
		bottom = p;
	}
	printf("Successfully clear the stack.\n");
	return SUCCESS;
}
//����ջ 
Status destroyLStack(LinkStack *s)
{
	StackNode* p = NULL;
	s->count = 0;
	s->top = NULL;
	while (p)
	{
		p = bottom->next;
		free(bottom);
		bottom = p;
	}
	printf("Successfully destroy the stack.\n");
	return SUCCESS;
}
//���ջ�ĳ��� 
Status LStackLength(LinkStack *s, int *length)
{
    if(s->top == NULL)
    {
        printf("There is no stack.\n");
        return ERROR;
    }
	*length = s->count;
	printf("The length of the stack is %d.\n", *length);
	return SUCCESS;
}
//��ջ 
Status pushLStack(LinkStack *s, ElemType data)
{
	StackNode * p = (StackNode*)malloc(sizeof(StackNode));
	p->data = data;
	p->next = NULL;
	s->top->next = p;
	s->top = p;
	s->count++;
	printf("Successfully push %d to the stack.\n", data);
	return SUCCESS;
}
//��ջ 
Status popLStack(LinkStack *s, ElemType *data)
{
	StackNode * p = bottom;
	if (s->count == 0)
    {
		printf("The stack is empty.\n");
		return ERROR;
	}
	else
	{
		*data = s->top->data;
		for (; p; p = p->next) {
			if (p->next == s->top) {
				free(p->next);
				p->next = NULL;
				s->top = p;
				s->count--;
				break;
			}
		}
		printf("Successfully pop %d out the stack.\n", *data);
		return SUCCESS;
	}
}

// ʵʱ��ӡ��ջ
Status printStack(LinkStack * s)
{
	StackNode * p = NULL;
	if (s->top == NULL) {
		printf("There is no stack now.\n");
		return ERROR;
	}
	else if (s->count == 0)
    {
		return ERROR;
	}
	for (p = bottom->next; p; p = p->next)
    {
		printf("|%d", p->data);
	}
	printf("\n");
	return SUCCESS;
}

// �����������
int InputNumber()
{
	int num = 0; // �洢ת���������.
	int status = 0; // ���״̬
	char str[100]; // �����ַ���
	do
	{
		scanf("%s", str);
		status = SUCCESS;
		for (int i = 0; str[i] != '\0'; i++)
		{
			// ���Υ�����ַ���
			if (i == 0)
            {
				if (str[i] == '-' || str[i] == '+')
					continue;
			}
			else
			{
				if (str[i] < '0' || str[i] > '9')
				{
					status = ERROR;
				}
			}
		}
		if (status == ERROR) {
			printf("Illegally input, please input again:");
		}
		else
		{
			int i = 0;
			// �ַ���ת��Ϊ����
			for (i = 0, num = 0; str[i] != '\0'; i++)
			{
				if (i == 0)
                {
					if (str[i] == '-' || str[i] == '+')
					{
						continue;
					}
					else
					{
						num *= 10;
						num += (str[i] - 48);
					}
				}
				else
				{
					num *= 10;
					num += (str[i] - 48);
				}
			}
			if (str[0] == '-')
            {
				num = -num;
			}
			// �������������Ƿ�Խ��
			if (i >= 10)
			{
				printf("Overflow, please input again:");
				status = ERROR;
			}
		}
	} while (status == ERROR);
	return num;
}


int main()
{
    int flag = 0; // ��ջ
    LinkStack *head = (LinkStack*)malloc(sizeof(StackNode));
    head->count = 0;
    head->top = NULL;
    while(1)
    {
        system("cls");
        printf("Welcome to Jiang Zhuoran's ADT\n");
        printf("This is the homework for QG-Studio\n");
        printf("-----------------\n");
        printf(">>> 1.Initialize \n");
        printf(">>> 2.Push       \n");
        printf(">>> 3.Pop        \n");
        printf(">>> 4.Clear      \n");
        printf(">>> 5.Destroy    \n");
        printf(">>> 6.Length     \n");
        printf(">>> 7.isEmpty    \n");
        printf(">>> 8.getTop     \n");
        printf(">>> 9.Exit       \n");
        printf("-----------------\n");
        printStack(head);
        printf("-----------------\n");
        printf("Input a choice you want:");
        switch(InputNumber())
        {
            case 1:
                initLStack(head);
                flag = 1;
                break;
            case 2:
                if(flag == 1)
                {
                    printf("Input the data to be push:");
                    pushLStack(head, InputNumber());
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 3:
                if(flag == 1)
                {
                    ElemType *e = (ElemType*)malloc(sizeof(ElemType));
                    popLStack(head, e);
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 4:
                if(flag == 1)
                {
                    clearLStack(head);
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 5:
                if(flag == 1)
                {
                    destroyLStack(head);
                    flag = 0;
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 6:
                {
                    int *length = (int*)malloc(sizeof(int));
                    LStackLength(head, length);
                }
                break;
            case 7:
                if(flag == 1)
                {
                    isEmptyLStack(head);
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 8:
                if(flag == 1)
                {
                    ElemType *e = (ElemType*)malloc(sizeof(ElemType));
                    getTopLStack(head, e);
                }
                else
                {
                    printf("Now there is no stack.\n");
                }
                break;
            case 9:
                printf("\nByeBye~");
                exit(0);
                break;
            default:
                printf("No such option.\n");
        }
        system("pause");
    }
    return 0;
}

