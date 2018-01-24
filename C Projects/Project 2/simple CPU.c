#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

struct node* MAKE_bin_HEAP();
int bin_LINK(struct node*,struct node*);
struct node* bin_HEAP_UNION(struct node*,struct node*);
struct node* bin_HEAP_INSERT(struct node*,struct node*);
struct node* bin_HEAP_MERGE(struct node*,struct node*);
struct node* bin_HEAP_EXTRACT_MIN(struct node*);
int REVERT_LIST(struct node*);
int DISPLAY(struct node*);
struct node* FIND_NODE(struct node*,int);
int bin_HEAP_DECREASE_KEY(struct node*,int,int);
int bin_HEAP_DELETE(struct node*,int);


int id1[10];
int e1[10];
int tArr1[10];
int tChange1[10];
int eNew1[10];
int numberOfLines=0;
int quanta=1;
int maxTArrival = 0;
float maxE =-1;
int q =1;
int time=0;


struct node
{
	int n;
	int e;
	int tChange;
	int eNew;
	int eMax;
	int tArr;
	int tArrFirst;
	int degree;
	int waitingTime;
	float priorty;
	struct node* parent;
	struct node* child;
	struct node* sibling;
};

struct node * H=NULL;
struct node *Hr=NULL;

struct node* MAKE_bin_HEAP()
{
	struct node* np;
	np=NULL;
	return np;
}
int bin_LINK(struct node* y,struct node* z)
{
	y->parent=z;
	y->sibling=z->child;
	z->child=y;
	z->degree=z->degree+1;
}
struct node* CREATE_NODE(int id1, int e1,int tArr1,int tChange1,int eNew1)
{
	struct node* p;//new node;
	p=(struct node*)malloc(sizeof(struct node));
	p->tArr = tArr1;
	p->tArrFirst = tArr1;
	p->n=id1;
	p->eMax=e1;
	p->tChange=tChange1;
	p->eNew = eNew1;
	p->e=e1;
	p->priorty = e1;
	p->waitingTime=0;
	return p;
}
struct node* bin_HEAP_UNION(struct node* H1,struct node* H2)
{
	struct node* prev_x;
	struct node* next_x;
	struct node* x;
	struct   node* H=MAKE_bin_HEAP();
	H=bin_HEAP_MERGE(H1,H2);
	if(H==NULL)
		return H;
	prev_x=NULL;
	x=H;
	next_x=x->sibling;
	while(next_x!=NULL)
	{
		if((x->degree!=next_x->degree)||((next_x->sibling!=NULL)&&(next_x->sibling)->degree==x->degree))
		{
			prev_x=x;
			x=next_x;
		}
		else
		{
			if(x->n<=next_x->n)
			{
				x->sibling=next_x->sibling;
				bin_LINK(next_x,x);
			}
			else
			{
				if(prev_x==NULL)
					H=next_x;
				else
					prev_x->sibling=next_x;
				bin_LINK(x,next_x);
				x=next_x;
			}
		}
		next_x=x->sibling;
	}
	return H;
}
struct node* bin_HEAP_INSERT(struct node* H,struct node* x)
{
	struct node* H1=MAKE_bin_HEAP();
	x->parent=NULL;
	x->child=NULL;
	x->sibling=NULL;
	x->degree=0;
	H1=x;
	H=bin_HEAP_UNION(H,H1);
	return H;
}
struct  node* bin_HEAP_MERGE(struct node* H1,struct node* H2)
{
	struct node* H=MAKE_bin_HEAP();
	struct  node* y;
	struct  node* z;
	struct  node* a;
	struct node* b;
	y=H1;
	z=H2;
	if(y!=NULL)
	{
		if(z!=NULL&&y->degree<=z->degree)
			H=y;
		else if(z!=NULL&&y->degree>z->degree)
			/* need some modifications here;the first and the else conditions can be merged together!!!! */
			H=z;
		else
			H=y;
	}
	else
		H=z;
	while(y!=NULL&&z!=NULL)
	{
		if(y->degree<z->degree)
		{
			y=y->sibling;
		}
		else if(y->degree==z->degree)
		{
			a=y->sibling;
			y->sibling=z;
			y=a;
		}
		else
		{
			b=z->sibling;
			z->sibling=y;
			z=b;
		}
	}
	return H;
}
int DISPLAY(struct node* H)
{
	struct node* p;
	if(H==NULL)
	{
		printf("\nHEAP EMPTY");
		return 0;
	}
	printf("\nTHE ROOT NODES ARE:-\n");
	p=H;
	while(p!=NULL)
	{
		printf("%d",p->n);
		if(p->sibling!=NULL)
			printf("-->");
		p=p->sibling;
	}
	printf("\n");
}
struct  node* bin_HEAP_EXTRACT_MIN(struct node* H1)
{
	int min;
	struct node* t=NULL;
	struct   node* x=H1;
	struct node *Hr;
	struct node* p;
	Hr=NULL;
	if(x==NULL)
	{
		printf("\nNOTHING TO EXTRACT");
		return x;
	}
//    int min=x->n;
	p=x;
	while(p->sibling!=NULL)
	{
		if((p->sibling)->n<min)
		{
			min=(p->sibling)->n;
			t=p;
			x=p->sibling;
		}
		p=p->sibling;
	}
	if(t==NULL&&x->sibling==NULL)
		H1=NULL;
	else if(t==NULL)
		H1=x->sibling;
	else if(t->sibling==NULL)
		t=NULL;
	else
		t->sibling=x->sibling;
	if(x->child!=NULL)
	{
		REVERT_LIST(x->child);
		(x->child)->sibling=NULL;
	}
	H=bin_HEAP_UNION(H1,Hr);
	return x;
}
int REVERT_LIST(struct node* y)
{
	if(y->sibling!=NULL)
	{
		REVERT_LIST(y->sibling);
		(y->sibling)->sibling=y;
	}
	else
	{
		Hr=y;
	}
}
struct  node* FIND_NODE(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->n==k)
	{
		p=x;
		return p;
	}
	if(x->child!=NULL&&p==NULL)
	{
		p=FIND_NODE(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		p=FIND_NODE(x->sibling,k);
	}
	return p;
}
int BOOLEAN_FIND_NODE(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->n==k)
	{
		p=x;
		return 1;
	}
	if(x->child!=NULL&&p==NULL)
	{
		BOOLEAN_FIND_NODE(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		BOOLEAN_FIND_NODE(x->sibling,k);
	}
	return 0;
}
struct  node* FIND_NODE_WITH_ID(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->n==k)
	{
		p=x;
		return p;
	}
	if(x->child!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_ID(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_ID(x->sibling,k);
	}
	return p;
}
struct  node* FIND_NODE_WITH_TARRFIRST(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->tArrFirst==k)
	{
		p=x;
		return p;
	}
	if(x->child!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_TARRFIRST(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_TARRFIRST(x->sibling,k);
	}
	return p;
}
struct  node* FIND_NODE_WITH_TARR(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->tArr==k)
	{
		p=x;
		return p;
	}
	if(x->child!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_TARR(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_TARR(x->sibling,k);
	}
	return p;
}
struct  node* FIND_NODE_WITH_PRIORTY(struct node* H,int k)
{
	struct node* x=H;
	struct  node* p=NULL;
	if(x->priorty==k)
	{
		p=x;
		return p;
	}
	if(x->child!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_PRIORTY(x->child,k);
	}

	if(x->sibling!=NULL&&p==NULL)
	{
		p=FIND_NODE_WITH_PRIORTY(x->sibling,k);
	}
	return p;
}
int bin_HEAP_DECREASE_KEY(struct node* H,int i,int k)
{
	int temp;
	struct     node* p;
	struct node* y;
	struct node* z;
	p=FIND_NODE(H,i);
	if(p==NULL)
	{
		printf("\nINVALID CHOICE OF KEY TO BE REDUCED");
		return 0;
	}
	if(k>p->n)
	{
		printf("\nSORY!THE NEW KEY IS GREATER THAN CURRENT ONE");
		return 0;
	}
	p->n=k;
	y=p;
	z=p->parent;
	while(z!=NULL&&y->n<z->n)
	{
		temp=y->n;
		y->n=z->n;
		z->n=temp;
		y=z;
		z=z->parent;
	}
	printf("\nKEY REDUCED SUCCESSFULLY!");
}
int bin_HEAP_DELETE(struct node* H,int k)
{
	struct  node* np;
	if(H==NULL)
	{
		printf("\nHEAP EMPTY");
		return 0;
	}

	bin_HEAP_DECREASE_KEY(H,k,-1000);
	np=bin_HEAP_EXTRACT_MIN(H);
	if(np!=NULL)
		printf("\nNODE DELETED SUCCESSFULLY");
}






float calculatingPriority(struct node *a)   //priorty hesapla
{
	float x;
	float y;
	float z;
	float t;
	float w;

	if(a->e == a->eMax)
	{
		return a->e;
	}
	else
	{
		x = (2 * a->e);
		y=(3 * maxE);
		z = x/y;
		t = -pow( z ,3 );
		w = 1/(  exp(   t  )   );
		return a->e*w;
	}

}

void GetProcessesFromFile()
{



	FILE *file;  /* dosya göstericisi */
	file = fopen("oku.txt", "r");



	while(!feof(file))   //dosyadan oku
	{

		fscanf(file,"%d %d %d %d %d", &id1[numberOfLines],&e1[numberOfLines], &tArr1[numberOfLines], &tChange1[numberOfLines],&eNew1[numberOfLines]);

		numberOfLines++;
	}
	fclose(file);
}

struct node * assignVariablesHeap()
{
	int a;
	for(a=0; a<numberOfLines; a++)   //struct array e atama yap
	{
	//	struct node* p;
		struct node* np;
		np=CREATE_NODE(id1[a],e1[a],tArr1[a],tChange1[a],eNew1[a]);
		np->priorty = calculatingPriority(np);
		H=bin_HEAP_INSERT(H,np);
	}
	return H;
}

int findMaxTArr()
{
	int a;

	for(a=0; a<numberOfLines; a++)   //maximum tArr bul
	{
		if(tArr1[a] > maxTArrival)
			maxTArrival=tArr1[a];
	}
}

int findMaxE()
{
	int a;

	for(a=0; a<numberOfLines; a++)   //maximum tArr bul
	{
		if(e1[a] > maxE)
			maxE=e1[a];
	}
	return maxE;
}

struct node * GetWillSendingProcess(int timer)
{
	struct node * currNode =NULL;
	struct node * willSendigNodeToProcess=NULL;
	float minPriorty = 11111;
	float minTarrFirst=11111;
	int counterSamePriority= 0;
	while(1)
	{
		currNode = FIND_NODE_WITH_TARR(H,timer);
		if(currNode!=NULL)
		{
			if(currNode->priorty < minPriorty)
			{
				willSendigNodeToProcess=currNode;
				if(willSendigNodeToProcess->tArrFirst<minTarrFirst)
				{
					minTarrFirst = willSendigNodeToProcess->tArrFirst;
				}
			}
			currNode->tArr=-1;

			if(currNode->priorty == minPriorty)
			{
				if(currNode->tArrFirst < willSendigNodeToProcess->tArrFirst)
				{
					willSendigNodeToProcess = currNode;
				}
			}
			minPriorty = currNode->priorty;

		}

		else
		{
			while(1)
			{

				currNode = FIND_NODE_WITH_TARR(H,-1);
				if(currNode != NULL )
				{
					if(currNode == willSendigNodeToProcess)
					{
						currNode->tArr = timer;
					}
					else
					{
						currNode->tArr = timer+1;
						currNode->waitingTime++;
					}
				}


				if(currNode==NULL)
				{
					break;
				}
			}
			break;
		}

	}

	return willSendigNodeToProcess;
}
void correctTchange(int time)
{
	int controllingTChange=123456789;//default value
	int eNewTchange;
	int changingID;
	struct node *changeTime;
	int i;

	for(i=0; i<numberOfLines; i++)
	{
		if(time==tChange1[i])
		{
			controllingTChange = tChange1[i];
			eNewTchange = eNew1[i];
			changingID = id1[i];
			changeTime = FIND_NODE_WITH_ID(H,changingID);
			changeTime ->e = eNewTchange;

		}
	}
}
void nodeProcess(int metotTime,struct node *willSendigNodeToProcess)
{
	willSendigNodeToProcess=GetWillSendingProcess(metotTime);


	if(willSendigNodeToProcess!=NULL)
	{
		printf("  ID: %d e: %d tARR: %d  tArrFirst: %d  Priorty: %f\n" ,
		       willSendigNodeToProcess->n,willSendigNodeToProcess->e,willSendigNodeToProcess->tArr,willSendigNodeToProcess->tArrFirst, willSendigNodeToProcess->priorty);

		if(willSendigNodeToProcess->e >=q)
		{
				willSendigNodeToProcess->tArr +=q;

			willSendigNodeToProcess->e -=q;

			time+=q;
		}
		else
		{
		
				willSendigNodeToProcess->tArr++;
			willSendigNodeToProcess->e -=1;
			time++;
		}
		if(willSendigNodeToProcess->e <= 0 )
		{
			willSendigNodeToProcess->tArr = -7;
		}
		else
		{
			willSendigNodeToProcess->priorty = calculatingPriority(willSendigNodeToProcess);
		}

	}
	else
	{
		nodeProcess(metotTime+1,willSendigNodeToProcess);
	}

}



int main()
{
	struct node * willSendigNodeToProcess=NULL;
	struct node * waitingTime=NULL;
	struct node * preWillSendigNodeToProcess=NULL;


	for(q=1 ; q<9; q++)
	{
		GetProcessesFromFile();
		H = assignVariablesHeap();
		maxTArrival= findMaxTArr();
		maxE = findMaxE();
		struct node * whileTest=NULL;
//		whileTest = GetWillSendingProcess(time);
		printf("q: %d\n",q);
		while(GetWillSendingProcess(time)!=NULL)

		{
			correctTchange(time);

			willSendigNodeToProcess=GetWillSendingProcess(time);
			int timeModify;
			timeModify = time;
			printf("\ntime %d",time);

			nodeProcess(time,willSendigNodeToProcess);
			int i = 0;

			struct node * modifyTArr = NULL;
			while(i!=7)
			{
				if(timeModify < tArr1[i] & tArr1[i]<time)
				{
					modifyTArr = FIND_NODE_WITH_TARR(H,tArr1[i]);
					modifyTArr->tArr = time;
				}
				i++;
			}
			i = 0;


		}

		int y;
		float  sumOfWT=0;

		for(y=1; y<=numberOfLines; y++)
		{
			struct node * writeWaitingTime = FIND_NODE(H,y);
			sumOfWT += writeWaitingTime->waitingTime;
			printf("waiting time P%d: %d \n",writeWaitingTime->n,writeWaitingTime->waitingTime);

		}
		printf("-----------------\n ");
		printf("awt: %f", sumOfWT/numberOfLines);

		time=0;
		H = NULL;
		maxTArrival=0;
		maxE=0;
		numberOfLines=0;

	}

	return 0;

}

