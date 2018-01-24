#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>


struct bin_tree
{
	int key1;
	int key2;
	struct bin_tree *right;
	struct bin_tree *left;
	int depth;
};

typedef struct bin_tree trees;

int data1[100];
int data2[100];
int globalDepth = 0;
int nodeDepth = 0;
int isExit=0;
trees *willDeletingNode = NULL;
trees *previousDeletingNode = NULL;
int counterNode=0;
trees *twoDTree;
trees *temp;

void insert(trees *tree, int data1,int data2)
{

	if(tree==NULL)
	{
		temp =(trees *)malloc(sizeof(trees));
		temp->key1 = data1;
		temp->key2 = data2;
		temp->left = NULL;
		temp->right = NULL;
		temp->depth = 0;
		twoDTree=temp;
		return;

	}
		if(tree->key1 >= data1 & tree->depth % 2 == 0)
		{
			if(tree->left == NULL)
			{
				trees *temp = (trees *)malloc(sizeof(trees));
				temp->key1 = data1,
				temp->key2 = data2;
				temp->left = NULL;
				temp->right = NULL;
				temp->depth = (tree->depth) + 1;
				tree->left = temp;
				return;
			}

			else
			{
				insert(tree->left,data1,data2);
			}
		}

		if(tree->key1 < data1 & tree->depth % 2 == 0)
		{
			if(tree->right == NULL)
			{
				trees *temp = (trees *)malloc(sizeof(trees));
				temp->key1 = data1;
				temp->key2 =data2;
				temp->left = NULL;
				temp->right = NULL;
				temp->depth = (tree->depth) + 1;
				tree->right = temp;
				return;
			}

			else
			{
				insert(tree->right,data1,data2);
			}
		}

		if(tree->key2 >= data2 & tree->depth % 2 == 1)
		{
			if(tree->left == NULL)
			{
				trees *temp = (trees *)malloc(sizeof(trees));
				temp->key1 = data1,
				temp->key2 = data2;
				temp->left = NULL;
				temp->right = NULL;
				temp->depth = (tree->depth) + 1;
				tree->left = temp;
				return;
			}

			else
			{
				insert(tree->left,data1,data2);
			}
		}

		if(tree->key2 < data2 & tree->depth % 2 == 1)
		{
			if(tree->right == NULL)
			{
				trees *temp = (trees *)malloc(sizeof(trees));
				temp->key1 = data1;
				temp->key2 =data2;
				temp->left = NULL;
				temp->right = NULL;
				temp->depth = (tree->depth) + 1;
				tree->right = temp;
				return;
			}

			else
			{
				insert(tree->right,data1,data2);
			}
		}
}

void print_preorder(trees *tree)//printng preorder
{
    if (tree)
    {
    	printf("%d,%d\n",tree->key1,tree->key2);
        print_preorder(tree->left);
        print_preorder(tree->right);
    }

}
void Copy(trees *tree,int arr1[],int arr2[])//copying delete node and under that nodes into arrays
{

	if(tree)
	{
		arr1[counterNode] = tree->key1;
		arr2[counterNode] = tree->key2;

		counterNode++;
		Copy(tree->left,arr1,arr2);
		Copy(tree->right,arr1,arr2);

	}
	
}
int controllingInput(char *input)//controlling inputs from user
{
	int counter=0;
	int i=0;

	while(input[i]!='\0')
	{
		if(isdigit(input[i]))
		{
			counter++;
			i++;
		}

		else
			i++;
	}

		if(counter==strlen(input))
		{
			return 1;
		}
		else
		{
			return 0;
		}
}
int searchInTree(trees *tree,int key1,int key2)//searching will deleting node in tree
{

	if(tree)
	{

		if(tree->depth%2 == 0 & tree->key1 > key1)
			{
				return searchInTree(tree->left,key1,key2);
			}
		else if(tree->depth%2 == 0 & tree->key1 < key1)
			{
				return searchInTree(tree->right,key1,key2);
			}
		else if(tree->depth%2 == 1 & tree->key2 > key2)
			{
				return searchInTree(tree->left,key1,key2);
			}
		else if(tree->depth%2 == 1 & tree->key2 < key2)
			{
				return searchInTree(tree->right,key1,key2);

			}
		else if(tree->key1 == key1 & tree->key2 == key2)
			{
				willDeletingNode = tree;
				return 1;
			}
        else
        	return 0;
	}

}

void searchInTreePreDelete(trees *tree,int key1,int key2)//searching previous deleting node in tree becasuse assignment to Null to willDeletingNode
{

	if(tree!=NULL)
	{
		if(tree->key1 == key1 & tree->key2 == key2)
			{
				return;
			}
		previousDeletingNode=tree;

		if( tree->depth%2 == 0 & tree->key1 > key1)//SOL
			{
			searchInTreePreDelete(tree->left,key1,key2);
			}

		else if(tree->depth%2 == 0 & tree->key1 < key1)//SAG
			{
			searchInTreePreDelete(tree->right,key1,key2);

			}
		else if(tree->depth%2 == 1 & tree->key2 > key2)//SOL
			{
			searchInTreePreDelete(tree->left,key1,key2);

			}
		else if(tree->depth%2 == 1 & tree->key2 < key2)//SAG
			{
			searchInTreePreDelete(tree->right,key1,key2);
			}


	}

}


int main()
{




	FILE *file;  /* dosya göstericisi */
file = fopen("input.txt", "r");

	int numberOfNodes=0;

	int k;


	while(!feof(file))
	{
  		fscanf(file,"%d,%d",&data1[numberOfNodes], &data2[numberOfNodes]);
  		numberOfNodes++;
	}
	fclose(file);



	for(k=0;k<numberOfNodes;k++)
	{
		insert(twoDTree,data1[k],data2[k]);//isertion from the txt file
	}


		char IKey1[1000];
		char IKey2[1000];
		int InputKey1;
		int InputKey2;
	int a;
	do
	{

		printf("\n\tplease select one:\n");
		printf("\t1: Enter a new input in tree ENTER 1\n");
		printf("\t2: Deleting an entry from the tree ENTER 2\n");
		printf("\t3: PRÝNT TREE 3\n");
		printf("\t4: FOR EXIT PRESS 4\n");

		char charChosen[50];
		scanf("%s",charChosen);

		if(controllingInput(charChosen))
		{
			int chosen = atoi(charChosen);

			if(chosen == 1)
			{
				do
				{
				printf("please enter key1\n");//contolling input
				scanf("%s",IKey1);
				}while(controllingInput(IKey1) == 0);//if inputs are not integer again input

				do
				{
				printf("please enter key2\n");
				scanf("%s",IKey2);
				}while(controllingInput(IKey2) == 0);//if inputs are not integer again input

				InputKey1 = atoi(IKey1);
				InputKey2 = atoi(IKey2);
				insert(twoDTree,InputKey1,InputKey2);
			}

			 if(chosen == 2)
			{
				do
				{
				printf("please enter delete key1\n");//contolling input
				scanf("%s",IKey1);
				}while(controllingInput(IKey1) == 0);//if inputs are not integer again input

				do
				{
				printf("please enter delete key2\n");
				scanf("%s",IKey2);
				}while(controllingInput(IKey2) == 0);//if inputs are not integer again input

				InputKey1 = atoi(IKey1);
				InputKey2 = atoi(IKey2);
				int arr1[100];
				int arr2[100];

					if(searchInTree(twoDTree,InputKey1,InputKey2) == 1 )
					{
						printf("Values found\n");
						Copy(willDeletingNode, arr1 , arr2);
						int j;

						searchInTreePreDelete(twoDTree,InputKey1,InputKey2);
						if(previousDeletingNode == NULL)//if willDeletingNode is root.
						{
							twoDTree = NULL;
		
							for(j=1;j<counterNode;j++)
							{
								insert(twoDTree,arr1[j],arr2[j]);
							}
							int a;
							for(a=0;a<100;a++)
							{
								arr1[a]=0;
								arr2[a]=0;
							}
							counterNode=0;
							previousDeletingNode=NULL;
							print_preorder(twoDTree);
						}

						else//willDeletingNode is not root
						{
							if(previousDeletingNode->left!=NULL)
							{
								if(  (previousDeletingNode->left->key1 == willDeletingNode->key1) & 
													(previousDeletingNode->left->key2 == willDeletingNode->key2) )//if willDeletingNode is previousDeletingNode->left
									previousDeletingNode->left=NULL;
							}
							if(previousDeletingNode->right!=NULL)
							{
								if( (previousDeletingNode->right->key1 == willDeletingNode->key1) 
								& (previousDeletingNode->right->key2 == willDeletingNode->key2) )//if willDeletingNode is previousDeletingNode->right
									previousDeletingNode->right=NULL;
							}

											for(j=1;j<counterNode;j++)//insertion nodes under the willDeletingNode
											{
												insert(twoDTree,arr1[j],arr2[j]);
											}
											int b;
											for(b=0;b<100;b++)
											{
												arr1[b]=0;
												arr2[b]=0;
											}
											counterNode=0;
											previousDeletingNode=NULL;
						}
					}


				else if(searchInTree(twoDTree,InputKey1,InputKey2) == 0)
				{
					printf("Values doesn't in tree ");
				}
			}

			if(chosen == 3)
			{
				print_preorder(twoDTree);
			}
				if(chosen == 4)
			{
				printf("BYE BYE.. See You Later :)");
				return 0;
			}
			if(chosen >= 5)
			{
				printf("Wrong chosen. please press 1 , 2 or 3\n");
			}
		}
		else
			printf("Please Enter Number.Don't Character\n");
	}while(isExit!=1);

	return 0;
}

