#ifndef AQUEUE_H_INCLUDED
#define AQUEUE_H_INCLUDED
#define MAXQUEUE 5

//循环队列结构

typedef struct Aqueue
{
    void *data[MAXQUEUE];
    int front;
    int rear;
    int length;
    int type[MAXQUEUE];
} AQueue;

typedef enum
{
    FALSE=0, 
    TRUE=1
} Status;

void InitAQueue(AQueue *Q);

void DestoryAQueue(AQueue *Q);

Status IsFullAQueue(const AQueue *Q);

Status IsEmptyAQueue(const AQueue *Q);

Status GetHeadAQueue(AQueue *Q);		

void LengthAQueue(AQueue *Q);	

Status EnAQueue(AQueue *Q, void *data,int s);	

Status DeAQueue(AQueue *Q);		

void ClearAQueue(AQueue *Q);	

Status TraverseAQueue(const AQueue *Q);	

void checkinput(int* r);

void CheckType(AQueue* Q);

#endif
