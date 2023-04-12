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
 
//数据结构
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}*BiTree;

BiTree InitTree(int x, SearchTree T);//插入节点（创建二叉查找树）
BiTree Delete(int x, SearchTree T);//删除节点

//构造二叉查找树树（插入操作）
BiTree InitTree(int x, SearchTree T) {
    int i = 0;
    if (T == NULL) {
        T = (BiTree)malloc(sizeof(struct BiTNode));
        if (T == NULL)
            return 0;
        else {
            T->data = x;
            T->rchild = NULL;//先右节点，在左节点
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
        printf("%d——已经在树中了，不会再次插入\n", x);
    return T;
}

 
//递归先序遍历
void PreOrder(BiTree T)
{

    if(T){
        cout<<T->data<<" ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
 
 
//递归中序遍历
void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        cout<<T->data<<" ";
        InOrder(T->rchild);
    }
}
 
 
//递归后序遍历
void SubOrder(BiTree T){
    if(T){
        SubOrder(T->lchild);
        SubOrder(T->rchild);
        cout<<T->data<<" ";
    }
}
 
 
//层序遍历
void LayerOrder(BiTNode* root) { 
	queue<BiTNode*> q; //队列里面存的是地址 记得导入头文件<quene>
	q.push(root);  //将根节点入队
	while (!q.empty())  //退出条件为队列为空
	{
		BiTNode* now = q.front(); //取出队首元素
		cout << now->data <<" ";
		q.pop();        //弹出队首元素
		if (now->lchild != NULL) q.push(now->lchild);//左子树非空则压入队列
		if (now->rchild != NULL) q.push(now->rchild);//右子树非空则压入队列
	}
} 
 

//复制二叉树
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

 
//计算二叉树深度
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

 
//计算结点总数
int NodeCount(BiTree T){
    if(T == NULL)
     	return 0;
    else
        return (NodeCount(T->lchild) + NodeCount(T->rchild) + 1);
}
 
 
 
//计算叶子节点数
int LeafCount(BiTree T){
    if(T == NULL)
        return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return 1;
    else
        return (LeafCount(T->lchild) + LeafCount(T->rchild));
}

 
//查找指定元素
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


//查找最小值
Position FindMin(SearchTree T) {
    if (T == NULL){
	printf("结点未创建，无法进行操作"); 
        return 0;}
    else if (T->lchild == NULL)
        return T;
    else
        return FindMin(T->lchild);
}


//查找最大值
Position FindMax(SearchTree T) {
    if (T == NULL){
    printf("结点未创建，无法进行操作"); 
        return 0;}
    else if (T->rchild == NULL)
        return T;
    else
        return FindMax(T->rchild);
} 
 
 
//删除结点
BiTree Delete(int x, SearchTree T) {
    Position temp;
    if (T == NULL){
    printf("结点未创建，无法进行操作"); 
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
 
 
//非递归先序遍历 
void preOrderNRec(BiTree root ,int num){
	BiTree stack[num], node;
	int k = -1;
 
	if (root == NULL){
		printf("树还是空的!\n");
		return;
	}
	else{
		k++;
		// 仿照一个栈
		stack[k] = root; // 将根节点入栈
		while (k > -1){
			//出栈
			node = stack[k--];
			printf("%d ", node->data);
 
			// 先把右子树放进去，栈是先进去后出，所以下面的左子树先出
			if (node->rchild != NULL){
				stack[++k] = node->rchild;
			}
			if (node->lchild != NULL){
				stack[++k] = node->lchild;
			}
 
		}
 
	}
} 
 

// 非递归中序遍历
void inOrderNRec(BiTree root,int num){
	BiTree stack[num], node;
	int top = 0;
	// 判断树是否为空
	if (root == NULL){
		printf("树是空的!\n");
		return;
	}
	node = root;
 
	while (node != NULL || top > 0){
 
		// 将所有的左子树节点入栈
		while (node != NULL){
			stack[++top] = node;
			node = node->lchild;
		}
		//  如果右节点为空的话，执行下列语句
		node = stack[top--];
		printf("%d ", node->data);
 
		// 扫描右节点
		node = node->rchild;
	}
}
 
 
//非递归后序遍历 
void backOrderNRecSimple(BiTree root,int num){
	BiTree stack[num], node;
	int top = 0;
	int count = 0;
	int array[num]; // 使用一个数组来保存数据，方便最后数组的反转
 
	if (root == NULL){
		printf("树是空的!\n");
		return;
	}
	else{
		top++;
		// 仿照一个栈
		stack[top] = root; // 将根节点入栈
		while (top > 0){
			//出栈
			node = stack[top--];
			array[count++] = node->data; // 将其保存在一个数组当中
 
			// 先把右子树放进去，栈是先进去后出，所以下面的左子树先出
			if (node->lchild != NULL){
				stack[++top] = node->lchild;  // 入栈
			}
			if (node->rchild != NULL){
				stack[++top] = node->rchild;
			}
 
		}
 
	}
	// 反转数组，输出
	for (int i = count-1; i >= 0; i--){
		printf("%d ", array[i]);
	}
}

 
 
//限制整数输入模块
int intdetect()
{
	int pw;//这个变量是用来接受输入的
	//这一步就是判断输入的数据是否合法，且输入的仅仅是一个整数
	while(!(scanf("%d", &pw) && getchar() == '\n'))
	{
		while(getchar() != '\n');//清空缓存区
		printf("你输入的数据有误，请再输一遍！\n");//温馨提醒一下
	}
	printf("你输入的数值转为字符为：%c\n", (char)pw);
	return 0;
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
 
 
 
 
 
 
 
 
 
 
 
//主函数入口 
int main() {
	
	
    BiTree T,NewT;
    T = NULL;
	
    int num, x, y,num_insert;
    BiTree find, min, max;
   
    while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG第四周——二叉排序树      |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----创建二叉排序树         |\n");
		printf("\t\t\t|      2----递归先序遍历           |\n");
		printf("\t\t\t|      3----递归中序遍历           |\n");
		printf("\t\t\t|      4----递归后序遍历           |\n");
		printf("\t\t\t|      5----层序遍历               |\n");
		printf("\t\t\t|      6----复制二叉树             |\n");
		printf("\t\t\t|      7----二叉树的深度           |\n");
		printf("\t\t\t|      8----二叉树结点数           |\n");
		printf("\t\t\t|      9----叶子结点数             |\n");
		printf("\t\t\t|      10---查找指定元素           |\n");
		printf("\t\t\t|      11---查找最大元素           |\n");
		printf("\t\t\t|      12---查找最小元素           |\n");
		printf("\t\t\t|      13---插入结点               |\n");
		printf("\t\t\t|      14---删除结点               |\n");
		printf("\t\t\t|      15---非递归先序遍历         |\n");
		printf("\t\t\t|      16---非递归中序遍历         |\n");
		printf("\t\t\t|      17---非递归后序遍历         |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      18---退出                   |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|    QG-STUDIO Bootcamp——蒋卓然造|\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("目前数据状态：");		
		InOrder(T);
		cout<<endl;	
		printf("\n请选择操作:\n");
		checkinput(&num);
		if (num >= 1 && num <= 18) {
			switch (num) {
			
		
		case 1: {
			//功能一、创建二叉排序树
    	printf("请输入计划添加的结点个数：");
   		while(!(scanf("%d", &num) && num > 0 && getchar() == '\n'))
		{
			while(getchar() != '\n');//清空缓存区
			printf("结点个数只能是正整数喔！\n");//温馨提醒一下
		}
		//开始创建元素	   
  	    int a[num];    
  		for (int i = 0; i < num; i++) {
	    printf("请输入第%d个整数：",i+1);
		while(!(scanf("%d", &a[i]) && getchar() == '\n'))
		{
			while(getchar() != '\n');//清空缓存区
			printf("储存的数据只能是整数喔！\n");//温馨提醒一下
		}
	 	T = InitTree(a[i], T);	
   		}
    	break;
		}
		
		
		case 2: {
		//功能二：递归先序遍历 
		cout<<"递归先序遍历:";
    	PreOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 3: {
		//功能三：递归中序遍历
		cout<<"递归中序遍历:";
    	InOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 4: {
		//功能四：递归后序遍历
		cout<<"递归后序遍历:";
    	SubOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 5: {
		//功能五：层序遍历
		cout<<"层序遍历:";
    	LayerOrder(T);
    	cout<<endl;
		break;
		}
			
			
		case 6: {
		//功能六：复制二叉树
	 	cout<<"复制二叉树(功能测试):";
    	if(Copy(T,NewT)) cout<<" 执行成功"<<endl;	
		break;
		}
			
			
		case 7: {					
		//功能七：二叉树的深度	
		cout<<"二叉树深度："<<Depth(T)<<endl;
		break;
		}
			
			
		case 8: {				
		//功能八：二叉树结点数 
		cout<<"实际结点数："<<NodeCount(T)<<endl;
		break;
		}
			
			
		case 9: {
		//功能九：叶子结点数 
	 	cout<<"叶子结点数："<<LeafCount(T)<<endl;
		break;
		}
			
			
		case 10: {
		//功能十：查找指定元素 
		printf("请输入你想查找的元素：");
  	  	scanf("%d", &x);
   	 	find = Find(x, T);
  	  	if(find)
		printf("查找成功，该元素存在：%d\n", find->data);
		else
    	printf("不存在该元素，查找失败!\n");
		break;
		}
			
			
		case 11: {			
		//功能十一：查找最大元素
    	max = FindMax(T);
    	printf("最大元素:%d\n", max->data);
		break;
		}
			
			
		case 12: {
		//功能十二：查找最小元素 
	 	min = FindMin(T);
    	 printf("最小元素:%d\n", min->data);
		break;
		}
			
			
		case 13: {
		//功能十三：插入结点 
		printf("请输入计划添加的结点个数：");
    	while(!(scanf("%d", &num_insert) && num_insert > 0 && getchar() == '\n'))
		{
			while(getchar() != '\n');//清空缓存区
			printf("结点个数只能是正整数喔！\n");//温馨提醒一下
		}
		//开始创建要插入的元素	   
    	int b[num_insert];    
    	for (int i = 0; i < num_insert; i++) {
			printf("请输入第%d个整数：",i+1);
			while(!(scanf("%d", &b[i]) && getchar() == '\n'))
		{
			while(getchar() != '\n');//清空缓存区
			printf("储存的数据只能是整数喔！\n");//温馨提醒一下
		}
		 T = InitTree(b[i], T);	
   		}    
		break;
		}
		
		
		case 14: {
		//功能十四：删除结点
		printf("请输入你想删除的元素：");
    	scanf("%d", &y);
    	T = Delete(y, T);
		break;
		}
		
		
		case 15:{
		//功能十五：非递归先序遍历 
		cout<<"非递归先序遍历:";
    	preOrderNRec(T,NodeCount(T)); 
    	cout<<endl;
		break;
		}
		
		
		case 16:{
		//功能十六：非递归中序遍历 
		cout<<"非递归中序遍历:";
   		inOrderNRec(T,NodeCount(T)); 
    	cout<<endl;
		break;
		}
		
			
		case 17:{
		//功能十七：非递归后序遍历 
		cout<<"非递归后序遍历:";
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
			printf("\n请输入正确的数字。\n");    //错误提醒
		}
		system("PAUSE");
	}
	return 0;
} 

