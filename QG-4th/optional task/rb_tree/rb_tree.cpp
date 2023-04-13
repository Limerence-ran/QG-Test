#include <iostream>
#include <assert.h>
#include<stdlib.h>
using namespace std;

typedef enum
{
    RED = 0,
    BLACK
} Color;

//������������
template <typename Type>
struct RBTNode
{
    Color color;     //��ɫ
    Type key;        //�ؼ���
    RBTNode *left;   //����
    RBTNode *right;  //�Һ���
    RBTNode *parent; //�����
};

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
template <typename Type>
class RBTree
{
public:
    //���캯��
    RBTree()
    {
        Nil = BuyNode();
        root = Nil;
        Nil->color = BLACK;
    }
    //��������
    ~RBTree()
    {
        destroy(root); //���ٴ����ķ�Nil���
        delete Nil;    //���ɾ��Nil���
        Nil = NULL;
    }

    //�������
    void InOrder() { InOrder(root); }

    //����
    //1.BST��ʽ����
    //2.����ƽ��
    bool Insert(const Type &value)
    {
        RBTNode<Type> *pr = Nil; //pr������ס���ڵ�
        RBTNode<Type> *s = root; //�������sָ���
        while (s != Nil)
        {
            if (value == s->key)
            {
                return false;
            }
            pr = s; //ÿ�μ�סs�ĸ��ڵ�
            if (value < s->key)
            {
                s = s->left;
            }
            else
            {
                s = s->right;
            }
        }
        //ѭ����s==Nil
        s = BuyNode(value); //������
        if (pr == Nil)      //������ڵ�pr�Ǹ��ڵ㣬��һ��rootָ��Nil������pr==Nil
        {
            root = s;
            root->parent = pr;
        }
        else //������ڵ㲻�Ǹ��ڵ�
        {
            if (value < pr->key)
            {
                pr->left = s;
            }
            else
            {
                pr->right = s;
            }
            s->parent = pr; //�����½��s�ĸ��ڵ�
        }
        //����ƽ��
        Insert_Fixup(s);
        return true;
    }

    //ɾ��key���(�Ȳ��ң��ٵ����ڲ�ɾ��)
    void Remove(Type key)
    {
        RBTNode<Type> *t;
        if ((t = Search(root, key)) != Nil)
        {
            Remove(t);
        }
        else
        {
            cout << "Key is not exist." << endl;
        }
    }

    //���������ӡ�����ϸ�Ľ����ɫ
    void InOrderPrint() { InOrderPrint(root); }

protected:
    //�������㣬��������ɫ��ʼ��Ϊ��ɫ����ʼ�����Ĺؼ��֣������ĳ�ʼ��Ϊ��
    RBTNode<Type> *BuyNode(const Type &x = Type())
    {
        RBTNode<Type> *s = new RBTNode<Type>();
        assert(s != NULL);
        s->color = RED;
        s->left = s->right = s->parent = Nil;
        s->key = x;
        return s;
    }

    //�������
    void InOrder(RBTNode<Type> *root)
    {
        if (root != Nil)
        {
            InOrder(root->left);
            cout << root->key << " ";
            InOrder(root->right);
        }
    }

    /* ��ת����z�����ת
     *       zp                 zp
     *       /                  /
     *     z                   y
     *    / \      ===>       / \
     *   lz  y               z   ry
     *      / \             / \
     *     ly  ry          lz  ly  
     */
    void LeftRotate(RBTNode<Type> *z)
    {
        RBTNode<Type> *y = z->right; //��yָ��Ҫת����z���
        z->right = y->left;
        if (y->left != Nil) //y��ָ�������㲻Ϊ��
        {
            y->left->parent = z;
        }
        y->parent = z->parent;
        if (root == z) //z���Ǹ��ڵ�
        {
            root = y;
        }
        else if (z == z->parent->left) //z������
        {
            z->parent->left = y;
        }
        else //z���ҽ��
        {
            z->parent->right = y;
        }
        y->left = z;
        z->parent = y;
    }

    /* ��ת����z��������ת
    *         zp               zp
    *        /                 /
    *       z                 y
    *      / \    ===>       / \
    *     y   rz           ly   z   
    *    / \                   / \
    *   ly  ry                ry  rz
    */
    void RightRotate(RBTNode<Type> *z)
    {
        RBTNode<Type> *y = z->left;
        z->left = y->right;
        if (y->right != Nil)
        {
            y->right->parent = z;
        }
        y->parent = z->parent;
        if (root == z) //���z�Ǹ����
        {
            root = y;
        }
        else if (z == z->parent->left) //z������
        {
            z->parent->left = y;
        }
        else //z���ҽ��
        {
            z->parent->right = y;
        }
        y->right = z;
        z->parent = y;
    }

    //�����ĵ�������
    void Insert_Fixup(RBTNode<Type> *s)
    {
        RBTNode<Type> *uncle;           //���㣨�������ֵܽ�㣩
        while (s->parent->color == RED) //���ڵ����ɫҲΪ��ɫ
        {
            if (s->parent == s->parent->parent->left) //���ڵ�������
            {
                uncle = s->parent->parent->right;

                if (uncle->color == RED) //����Ϊ��ɫ
                {
                    //���ڵ�����㶼��Ϊ��ɫ
                    s->parent->color = BLACK;
                    uncle->color = BLACK;
                    //�游����Ϊ��ɫ
                    s->parent->parent->color = RED;
                    //��sָ��ָ���游��㣬��һ��ѭ�������ж��游�ĸ��ڵ��Ƿ�Ϊ��ɫ
                    s = s->parent->parent;
                }
                else //û�����㣬������Ϊ��ɫ(�������ѭ��ת�����������Ϊ��)
                {
                    if (s == s->parent->right) //��������Ľ�����ҽ��
                    {
                        s = s->parent; //�Ƚ�sָ��s�ĸ����
                        LeftRotate(s); //����ת
                    }
                    //��������Ľ��������,��s�ĸ��ڵ��Ϊ��ɫ�����游�Ľ���Ϊ��ɫ����s���游�����ת
                    s->parent->color = BLACK;
                    s->parent->parent->color = RED;
                    RightRotate(s->parent->parent);
                }
            }
            else
            {
                if (s->parent == s->parent->parent->right) //���ڵ����ҽ��
                {
                    uncle = s->parent->parent->left;
                    if (uncle->color == RED) //����Ϊ��ɫ
                    {
                        //���ڵ�����㶼��Ϊ��ɫ
                        s->parent->color = BLACK;
                        uncle->color = BLACK;
                        //�游����Ϊ��ɫ
                        s->parent->parent->color = RED;
                        //��sָ��ָ���游��㣬��һ��ѭ�������ж��游�ĸ��ڵ��Ƿ�Ϊ��ɫ
                        s = s->parent->parent;
                    }
                    else //û�����㣬������Ϊ��ɫ(�������ѭ��ת�����������Ϊ��)
                    {
                        if (s == s->parent->left) //��������Ľ��������
                        {
                            s = s->parent;  //�Ƚ�sָ��s�ĸ����
                            RightRotate(s); //����ת
                        }
                        //��������Ľ�����ҽ��,��s�ĸ��ڵ��Ϊ��ɫ�����游�Ľ���Ϊ��ɫ����s���游�����ת
                        s->parent->color = BLACK;
                        s->parent->parent->color = RED;
                        LeftRotate(s->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK; //���ʼ�ս����ڵ���Ϊ��ɫ
    }

    //����key���
    RBTNode<Type> *Search(RBTNode<Type> *root, Type key) const
    {
        if (root == Nil) //rootΪ�գ���key�͸���key��ͬ
        {
            return Nil;
        }

        if (root->key == key)
        {
            return root;
        }
        if (key < root->key)
        {
            return Search(root->left, key);
        }
        else
        {
            return Search(root->right, key);
        }
    }

    /* ��u���ӽڵ�ָ��u��ָ��ı�ָ��v����v�ĸ��ڵ�ָ��ı�Ϊָ��u�ĸ��ڵ�
     *      up
     *        \
     *         u
     *        / \
     *      ul   ur
     *     / \
     *    v  ulr
     *     \
     *     rv
     */
    void Transplant(RBTNode<Type> *u, RBTNode<Type> *v)
    {
        if (u->parent == Nil) //u�ĸ��ڵ�Ϊ��
        {
            root = v; //ֱ�����rootΪv
        }
        else if (u == u->parent->left) //u���ڵ㲻Ϊ�գ���u��������
        {
            u->parent->left = v;
        }
        else //u��������
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    /* �ҵ�������(��С)
     *      xp
     *        \
     *         x
     *        / \
     *      xl   xr
     *     / \
     *   xll  xlr
     */
    RBTNode<Type> *Minimum(RBTNode<Type> *x)
    {
        if (x->left == Nil)
        {
            return x;
        }
        return Minimum(x->left);
    }

    //ɾ����������z
    void Remove(RBTNode<Type> *z)
    {
        RBTNode<Type> *x = Nil;
        RBTNode<Type> *y = z;    //y��ס��������z���
        Color ycolor = y->color; //
        if (z->left == Nil)      //zֻ���Һ���
        {
            x = z->right;
            Transplant(z, z->right);
        }
        else if (z->right == Nil) //zֻ���Һ���
        {
            x = z->left;
            Transplant(z, z->left);
        }
        else //�����Ӻ��Һ���
        {
            y = Minimum(z->right); //y��z�������ĵ���������
            ycolor = y->color;
            x = y->right;
            if (y->parent == z) //z�����ӽ��û����ڵ��ΪNil
            {
                x->parent = y;
            }
            else //z�����ӽ������ڵ��ΪNil
            {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            Transplant(z, y);
            //�ı�ָ��
            y->left = z->left;
            z->left->parent = y;
            y->color = z->color;
        }
        if (ycolor == BLACK)
        {
            Remove_Fixup(x);
        }
    }

    //�����ɾ������
    void Remove_Fixup(RBTNode<Type> *x)
    {
        while (x != root && x->color == BLACK) //�����x��Ϊ������������ɫ���Ǻ�ɫ
        {
            if (x == x->parent->left) //x��������
            {
                RBTNode<Type> *w = x->parent->right; //w��x���ֽ��

                if (w->color == RED) //���1
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) //���2
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK) //���3
                    {
                        w->color = RED;
                        w->left->color = BLACK;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    //���4
                    w->color = w->parent->color;
                    w->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root; //����ѭ��
                }
            }
            else //x��������
            {
                RBTNode<Type> *w = x->parent->left;
                if (w->color == RED) //���1
                {
                    w->parent->color = RED;
                    w->color = BLACK;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->right->color == BLACK) //���2
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK) //���3
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    //���4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->parent);
                    x = root; //����ѭ��
                }
            }
        }
        x->color = BLACK;
    }

    //���ٺ����
    void destroy(RBTNode<Type> *&root)
    {
        if (root == Nil)
        {
            return;
        }
        if (root->left != Nil)
        {
            destroy(root->left);
        }
        if (root->right != Nil)
        {
            destroy(root->right);
        }
        delete root;
        root = NULL;
    }

    //���������ӡ�����ϸ�Ľ����ɫ
    void InOrderPrint(RBTNode<Type> *node)
    {
        if (node == Nil)
        {
            return;
        }
        if (node->left != NULL)
        {
            InOrderPrint(node->left);
        }
        cout << node->key << "(" << ((node->color == BLACK) ? "BLACK" : "RED") << ")"
             << " ";
        if (node->right != Nil)
        {
            InOrderPrint(node->right);
        }
    }




private:
    RBTNode<Type> *root; //��ָ��
    RBTNode<Type> *Nil;  //�ⲿ��㣬��ʾ�ս�㣬��ɫ��
};










int main(int argc, char *argv[])
{
RBTree<int> rb;     
int num,num_check;
		
while (1) {
		system("cls");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      QG�����ܡ��������          |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      1----����Ԫ��               |\n");
		printf("\t\t\t|      2----�������               |\n");
		printf("\t\t\t|      3----�����������ɫ��       |\n");
		printf("\t\t\t|      4----ɾ�����               |\n");
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|���Ͻ�Ϊpublic��չʾ���ܣ�      |\n");
		printf("\t\t\t|        ���๦�����Դ��protected |\n");						
		printf("\t\t\t|----------------------------------|\n");
		printf("\t\t\t|      5----�˳�                   |\n");
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
	
	//��ʼ����Ԫ��	   
    int arr[num];    
  	for (int i = 0; i < num; i++) {
	printf("�������%d��������",i+1);
	while(!(scanf("%d", &arr[i]) && getchar() == '\n'))
	{
		while(getchar() != '\n');//��ջ�����
		printf("���������ֻ��������ร�\n");//��ܰ����һ��
	}
	rb.Insert(arr[i]); 
}
    	break;
		}
		
			
		case 2: {
	rb.InOrder(); 
    cout << endl;
		break;
		}
			
			
	
			
		case 3: {
	rb.InOrderPrint();
    cout << endl;
	break;
}
			
		case 4: {
			int z;
		printf("����������ɾ����Ԫ�أ�");
  	  	scanf("%d", &z);
  	  	rb.Remove(z); 
		printf("ִ�����!�ѱ�֤��Ԫ�ز�����");
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



