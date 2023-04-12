#include<iostream>
#include<queue>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
using namespace std;

typedef struct BiTNode* Position;
typedef struct BiTNode* SearchTree;

Position Find(int x, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
 
//���ݽṹ
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}*BiTree;

BiTree InitTree(int x, SearchTree T);//����ڵ㣨���������������
BiTree Delete(int x, SearchTree T);//ɾ���ڵ�

//�������������������������
BiTree InitTree(int x, SearchTree T) {
    int i = 0;
    if (T == NULL) {
        T = (BiTree)malloc(sizeof(struct BiTNode));
        if (T == NULL)
            return 0;
        else {
            T->data = x;
            T->rchild = NULL;//���ҽڵ㣬����ڵ�
            T->lchild = NULL;
        }
    }
    else if (x < T->data) {
        T->lchild = InitTree(x, T->lchild);
    }
    else if (x > T->data) {
        T->rchild = InitTree(x, T->rchild);
    }
    else
        printf("%d�����Ѿ��������ˣ������ٴβ���\n", x);
    return T;
}

 
//�ݹ��������
void PreOrder(BiTree T)
{

    if(T){
        cout<<T->data<<" ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
 
 
//�ݹ��������
void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        cout<<T->data<<" ";
        InOrder(T->rchild);
    }
}
 
 
//�ݹ�������
void SubOrder(BiTree T){
    if(T){
        SubOrder(T->lchild);
        SubOrder(T->rchild);
        cout<<T->data<<" ";
    }
}
 
 
//�������
void LayerOrder(BiTNode* root) { 
	queue<BiTNode*> q; //�����������ǵ�ַ �ǵõ���ͷ�ļ�<quene>
	q.push(root);  //�����ڵ����
	while (!q.empty())  //�˳�����Ϊ����Ϊ��
	{
		BiTNode* now = q.front(); //ȡ������Ԫ��
		cout << now->data <<" ";
		q.pop();        //��������Ԫ��
		if (now->lchild != NULL) q.push(now->lchild);//�������ǿ���ѹ�����
		if (now->rchild != NULL) q.push(now->rchild);//�������ǿ���ѹ�����
	}
} 
 

//���ƶ�����
bool Copy(BiTree T, BiTree &NewT){
    if(T == NULL){
        NewT = NULL;
        return false;
    } else{
        NewT = new BiTNode;
        NewT->data = T->data;
        Copy(T->lchild, NewT->lchild);
        Copy(T->rchild,NewT->rchild);
    }
    return true;
}

 
//������������
int Depth(BiTree T){
    if(T == NULL)
			return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        if(m>n)
            return (m+1);
        else
            return (n+1);
    }
}

 
//����������
int NodeCount(BiTree T){
    if(T == NULL)
     	return 0;
    else
        return (NodeCount(T->lchild) + NodeCount(T->rchild) + 1);
}
 
 
 
//����Ҷ�ӽڵ���
int LeafCount(BiTree T){
    if(T == NULL)
        return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return 1;
    else
        return (LeafCount(T->lchild) + LeafCount(T->rchild));
}

 
//����ָ��Ԫ��
Position Find(int x, SearchTree T) {
    if (T == NULL)
   		return 0;
    if (x < T->data)
        return Find(x, T->lchild);
    else if (x > T->data)
        return Find(x, T->rchild);
    else
        return T;
}


//������Сֵ
Position FindMin(SearchTree T) {
    if (T == NULL){
	printf("���δ�������޷����в���"); 
        return 0;}
    else if (T->lchild == NULL)
        return T;
    else
        return FindMin(T->lchild);
}


//�������ֵ
Position FindMax(SearchTree T) {
    if (T == NULL){
    printf("���δ�������޷����в���"); 
        return 0;}
    else if (T->rchild == NULL)
        return T;
    else
        return FindMax(T->rchild);
} 
 
 
//ɾ�����
BiTree Delete(int x, SearchTree T) {
    Position temp;
    if (T == NULL){
    printf("���δ�������޷����в���"); 
        return 0;}
    else if (x < T->data)
        T->lchild = Delete(x, T->lchild);
    else if (x > T->data)
        T->rchild = Delete(x, T->rchild);
    else if (T->lchild && T->rchild) {
        temp = FindMin(T->rchild);
        T->data = temp->data;
        T->rchild = Delete(T->data, T->rchild);
    }
    else {
        temp = T;
        if (T->lchild == NULL)
            T = T->rchild;
        else if (T->rchild == NULL)
            T = T->lchild;
        free(temp);
    }
    return T;
}
 
 
//�ǵݹ�������� 
void preOrderNRec(BiTree root ,int num){
	BiTree stack[num], node;
	int k = -1;
 
	if (root == NULL){
		printf("�����ǿյ�!\n");
		return;
	}
	else{
		k++;
		// ����һ��ջ
		stack[k] = root; // �����ڵ���ջ
		while (k > -1){
			//��ջ
			node = stack[k--];
			printf("%d ", node->data);
 
			// �Ȱ��������Ž�ȥ��ջ���Ƚ�ȥ���������������������ȳ�
			if (node->rchild != NULL){
				stack[++k] = node->rchild;
			}
			if (node->lchild != NULL){
				stack[++k] = node->lchild;
			}
 
		}
 
	}
} 
 

// �ǵݹ��������
void inOrderNRec(BiTree root,int num){
	BiTree stack[num], node;
	int top = 0;
	// �ж����Ƿ�Ϊ��
	if (root == NULL){
		printf("���ǿյ�!\n");
		return;
	}
	node = root;
 
	while (node != NULL || top > 0){
 
		// �����е��������ڵ���ջ
		while (node != NULL){
			stack[++top] = node;
			node = node->lchild;
		}
		//  ����ҽڵ�Ϊ�յĻ���ִ���������
		node = stack[top--];
		printf("%d ", node->data);
 
		// ɨ���ҽڵ�
		node = node->rchild;
	}
}
 
 
//�ǵݹ������� 
void backOrderNRecSimple(BiTree root,int num){
	BiTree stack[num], node;
	int top = 0;
	int count = 0;
	int array[num]; // ʹ��һ���������������ݣ������������ķ�ת
 
	if (root == NULL){
		printf("���ǿյ�!\n");
		return;
	}
	else{
		top++;
		// ����һ��ջ
		stack[top] = root; // �����ڵ���ջ
		while (top > 0){
			//��ջ
			node = stack[top--];
			array[count++] = node->data; // ���䱣����һ�����鵱��
 
			// �Ȱ��������Ž�ȥ��ջ���Ƚ�ȥ���������������������ȳ�
			if (node->lchild != NULL){
				stack[++top] = node->lchild;  // ��ջ
			}
			if (node->rchild != NULL){
				stack[++top] = node->rchild;
			}
 
		}
 
	}
	// ��ת���飬���
	for (int i = count-1; i >= 0; i--){
		printf("%d ", array[i]);
	}
}

 
 
//������������ģ��
int intdetect()
{
	int pw;//����������������������
	//��һ�������ж�����������Ƿ�Ϸ���������Ľ�����һ������
	while(!(scanf("%d", &pw) && getchar() == '\n'))
	{
		while(getchar() != '\n');//��ջ�����
		printf("���������������������һ�飡\n");//��ܰ����һ��
	}
	printf("���������ֵתΪ�ַ�Ϊ��%c\n", (char)pw);
	return 0;
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
 
 
 
 
 
 
 
 
 
 
 
//��������� 
int main() {
	
	
    BiTree T,NewT;
    T = NULL;
	
    int num, x, y,num_insert;
    BiTree find, min, max;
   
    while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG�����ܡ�������������      |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----��������������         |\n");
		printf("\t\t\t|      2----�ݹ��������           |\n");
		printf("\t\t\t|      3----�ݹ��������           |\n");
		printf("\t\t\t|      4----�ݹ�������           |\n");
		printf("\t\t\t|      5----�������               |\n");
		printf("\t\t\t|      6----���ƶ�����             |\n");
		printf("\t\t\t|      7----�����������           |\n");
		printf("\t\t\t|      8----�����������           |\n");
		printf("\t\t\t|      9----Ҷ�ӽ����             |\n");
		printf("\t\t\t|      10---����ָ��Ԫ��           |\n");
		printf("\t\t\t|      11---�������Ԫ��           |\n");
		printf("\t\t\t|      12---������СԪ��           |\n");
		printf("\t\t\t|      13---������               |\n");
		printf("\t\t\t|      14---ɾ�����               |\n");
		printf("\t\t\t|      15---�ǵݹ��������         |\n");
		printf("\t\t\t|      16---�ǵݹ��������         |\n");
		printf("\t\t\t|      17---�ǵݹ�������         |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      18---�˳�                   |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp������׿Ȼ��|\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("Ŀǰ����״̬��");		
		InOrder(T);
		cout<<endl;	
		printf("\n��ѡ�����:\n");
		checkinput(&num);
		if (num >= 1 && num <= 18) {
			switch (num) {
			
		
		case 1: {
			//����һ����������������
    	printf("������ƻ���ӵĽ�������");
   		while(!(scanf("%d", &num) && num > 0 && getchar() == '\n'))
		{
			while(getchar() != '\n');//��ջ�����
			printf("������ֻ����������ร�\n");//��ܰ����һ��
		}
		//��ʼ����Ԫ��	   
  	    int a[num];    
  		for (int i = 0; i < num; i++) {
	    printf("�������%d��������",i+1);
		while(!(scanf("%d", &a[i]) && getchar() == '\n'))
		{
			while(getchar() != '\n');//��ջ�����
			printf("���������ֻ��������ร�\n");//��ܰ����һ��
		}
	 	T = InitTree(a[i], T);	
   		}
    	break;
		}
		
		
		case 2: {
		//���ܶ����ݹ�������� 
		cout<<"�ݹ��������:";
    	PreOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 3: {
		//���������ݹ��������
		cout<<"�ݹ��������:";
    	InOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 4: {
		//�����ģ��ݹ�������
		cout<<"�ݹ�������:";
    	SubOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 5: {
		//�����壺�������
		cout<<"�������:";
    	LayerOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 6: {
		//�����������ƶ�����
	 	cout<<"���ƶ�����(���ܲ���):";
    	if(Copy(T,NewT)) cout<<" ִ�гɹ�"<<endl;	
		break;
		}
			
			
		case 7: {					
		//�����ߣ������������	
		cout<<"��������ȣ�"<<Depth(T)<<endl;
		break;
		}
			
			
		case 8: {				
		//���ܰˣ������������ 
		cout<<"ʵ�ʽ������"<<NodeCount(T)<<endl;
		break;
		}
			
			
		case 9: {
		//���ܾţ�Ҷ�ӽ���� 
	 	cout<<"Ҷ�ӽ������"<<LeafCount(T)<<endl;
		break;
		}
			
			
		case 10: {
		//����ʮ������ָ��Ԫ�� 
		printf("������������ҵ�Ԫ�أ�");
  	  	scanf("%d", &x);
   	 	find = Find(x, T);
  	  	if(find)
		printf("���ҳɹ�����Ԫ�ش��ڣ�%d\n", find->data);
		else
    	printf("�����ڸ�Ԫ�أ�����ʧ��!\n");
		break;
		}
			
			
		case 11: {			
		//����ʮһ���������Ԫ��
    	max = FindMax(T);
    	printf("���Ԫ��:%d\n", max->data);
		break;
		}
			
			
		case 12: {
		//����ʮ����������СԪ�� 
	 	min = FindMin(T);
    	 printf("��СԪ��:%d\n", min->data);
		break;
		}
			
			
		case 13: {
		//����ʮ���������� 
		printf("������ƻ���ӵĽ�������");
    	while(!(scanf("%d", &num_insert) && num_insert > 0 && getchar() == '\n'))
		{
			while(getchar() != '\n');//��ջ�����
			printf("������ֻ����������ร�\n");//��ܰ����һ��
		}
		//��ʼ����Ҫ�����Ԫ��	   
    	int b[num_insert];    
    	for (int i = 0; i < num_insert; i++) {
			printf("�������%d��������",i+1);
			while(!(scanf("%d", &b[i]) && getchar() == '\n'))
		{
			while(getchar() != '\n');//��ջ�����
			printf("���������ֻ��������ร�\n");//��ܰ����һ��
		}
		 T = InitTree(b[i], T);	
   		}    
		break;
		}
		
		
		case 14: {
		//����ʮ�ģ�ɾ�����
		printf("����������ɾ����Ԫ�أ�");
    	scanf("%d", &y);
    	T = Delete(y, T);
		break;
		}
		
		
		case 15:{
		//����ʮ�壺�ǵݹ�������� 
		cout<<"�ǵݹ��������:";
    	preOrderNRec(T,NodeCount(T)); 
    	cout<<endl;
		break;
		}
		
		
		case 16:{
		//����ʮ�����ǵݹ�������� 
		cout<<"�ǵݹ��������:";
   		inOrderNRec(T,NodeCount(T)); 
    	cout<<endl;
		break;
		}
		
			
		case 17:{
		//����ʮ�ߣ��ǵݹ������� 
		cout<<"�ǵݹ�������:";
    	backOrderNRecSimple(T,NodeCount(T)); 
    	cout<<endl;	
		break;
		} 

			
		case 18:{	
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

