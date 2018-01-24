//
//  main.c
//  HW3
//
//  Created by MyMacbookPro on 06/05/2017.
//  Copyright © 2017 MyMacbookPro. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
struct node
{
   int id;
   char name[50];
   char author[50];
   struct node *next;
};


struct node *root = NULL;
struct node *lastNode;
int numberOfBook;

int controllingInput(char *input)//controlling inputs from user
{

   int counter=0;
   int i=0;

   while(input[i]!='\0')//if input not null, go to other index
   {
      if(isdigit(input[i]))
      {
         counter++;//count number of n umber
         i++;//going other index
      }

      else
         i++;
   }

   if(input[0] == '-' || input[0] == '+')//controlling negative numbers. or +positive number(e.g +5)
   {
      if(counter==
            strlen(input)-1)//if number of number equals strlen- this means that in put is negative number
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }

   else
   {
      if(counter==strlen(input))//if number of number equals strlen this menas thar input is positive number
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }
}
void swapNode(struct node * node1, struct node * node2)//swap node usýng sort methods
{
   struct node *temp = (struct node*)malloc(sizeof(struct node));


   temp->id = node1->id;
   strcpy(temp->name,node1->name);
   strcpy(temp->author,node1->author);

   node1->id = node2->id;
   strcpy(node1->name,node2->name);
   strcpy(node1->author,node2->author);

   node2->id = temp->id;
   strcpy(node2->name,temp->name);
   strcpy(node2->author,temp->author);
   temp=NULL;

}
void listAllBook()//listýng all book
{

   struct node *listNode;
   listNode = root;
   if(root == NULL)
   {
      printf("there is no book!\n");
   }
   else
   {
      while(listNode!=NULL)
      {
         printf("ID: %d\tNAME: %s\t AUTHOR: %s\n",listNode->id,listNode->name,listNode->author);
         listNode = listNode->next;
      }
   }
}

void listOneBook(struct node *currNode)
{
   printf("ID: %d\tNAME: %s\t AUTHOR: %s\n",currNode->id,currNode->name,currNode->author);

}




void goLastNode()//detemrine last node 
{

   lastNode = root;
   while(lastNode->next!=NULL)
   {
      lastNode = lastNode->next;
   }
}

struct node * searchinList(int id)//search data in link list and return founded node
{
   struct node * searchPtr;
   searchPtr = root;
   while (searchPtr != NULL)
   {
      if(searchPtr-> id == id)
      {
         return searchPtr;
      }
      searchPtr = searchPtr->next;
   }
   return NULL;

}

void createNewBook()//create new record
{



   char S_id[20];
   int id;


   char S_name[20];
   char S_author[20];
   do
   {
      printf("Please enter book id: ");//controlling number or not in do whýle loop
      scanf("%s", S_id);
      if(controllingInput(S_id))
      {
         id = atoi(S_id);
         break;
      }
      else
         printf("please enter number!!\n");
   }
   while(1);

   if(searchinList(id) == NULL )
   {
      struct node *temp = (struct node*)malloc(sizeof(struct node));
      struct node * prevNode;
      struct node * nextNode;



      printf("please enter book name: ");
      scanf("%s",S_name);
      printf("please enter author: ");
      scanf("%s",S_author);
      temp->id = id;
      strcpy(temp->name,S_name);
      strcpy(temp->author,S_author);


      if(root == NULL)//insert first node
      {

         root = temp;

         root->next = NULL;

         numberOfBook++;

         goLastNode();
      }
       //printf("a");
      else if(root->next == NULL)//insert second record 
      {
         if(temp->id > root->id)
         {
            printf("%d", temp->id);
            root->next = temp;
            temp->next = NULL;
         }
         else
         {
            temp->next = root;
            root = temp;
         }
         goLastNode();
      }
 //printf("z");
      else if(temp->id < root->id)//insert head
      {
         temp->next = root;
         root = temp;
         goLastNode();

      }

 //printf("x");

      else if(temp->id > lastNode->id)//insert to second node
      {
         lastNode->next = temp;
         temp->next = NULL;
         numberOfBook++;
         goLastNode();
      }
      //
	  // printf("c");
	  else// insert btween first and last
      {
         prevNode = root;
         nextNode = prevNode->next;
         while(temp->id > nextNode->id)
         {
            nextNode = nextNode->next;
            prevNode = prevNode->next;
         }

         temp->next = nextNode;
         prevNode->next = temp;
         goLastNode();
      }
   }

   else
   {
      printf("this book is here!\n");
      listOneBook(searchinList(id));
   }
}

void updateBook()
{

   struct node * temp = (struct node *)malloc(sizeof(struct node));


   char S_id[20];
   int id;


   char S_name[20];
   char S_author[20];
   do
   {
      printf("Please enter book id: ");
      scanf("%s", S_id);
      if(controllingInput(S_id))
      {
         id = atoi(S_id);
         break;
      }
      else
         printf("please enter number!!\n");
   }
   while(1);

   if(searchinList(id) != NULL )
   {
      printf("please enter book name: ");
      scanf("%s",S_name);
      printf("please enter author: ");
      scanf("%s",S_author);
      temp = searchinList(id);
      strcpy(temp->name,S_name);
      strcpy(temp->author, S_author);
   }

   else
   {
      printf("there is no book that has this id!\n");
   }

}
void deleteBook()
{


   char S_id[20];
   int id;


   do
   {
      printf("Please enter book id: ");
      scanf("%s", S_id);
      if(controllingInput(S_id))
      {
         id = atoi(S_id);
         break;
      }
      else
         printf("please enter number!!\n");
   }
   while(1);

   struct node * deleteBook;
   deleteBook = searchinList(id);
   if(deleteBook == NULL)
   {
      printf("there is no book has this id!!\n");
   }
   else
   {

      struct node * previousDelete = root;
      if(deleteBook->id == root->id)
      {
         root = root->next;
         free(deleteBook);
         numberOfBook--;
         goLastNode();
      }
      else
      {
         while (previousDelete->next != deleteBook)
         {
            previousDelete = previousDelete->next;
         }
         previousDelete->next = deleteBook->next;
         free(deleteBook);
         numberOfBook--;
         goLastNode();
      }

      printf("succesfully deleted");

   }


}



void sortBookName()
{
   struct  node *new1 , *count;
   new1 = root;
   while(new1->next != NULL)
   {
      count = new1->next;
      while( count != NULL )
      {
         if(strcmp(new1->name , count->name)>0)//bubble sort algorithm
         {
            swapNode(new1,count);
         }
         count = count->next;
      }

      new1 = new1->next;

   }
   listAllBook();

}
void sortBookAuthorName()//buble sort algortihm
{
   struct  node *new1 , *count;
   new1 = root;
   for( ; new1->next != NULL; new1 = new1->next)
   {
      for(count = new1->next; count != NULL; count = count->next)
      {
         if(strcmp(new1->author , count->author)>0)
         {
            swapNode(new1,count);
         }
      }
   }
   listAllBook();

}
void sortID()//bubblesortt algorithm
{
   struct  node *new1 , *count;
   new1 = root;
   for( ; new1->next != NULL; new1 = new1->next)
   {
      for(count = new1->next; count != NULL; count = count->next)
      {
         if(new1->id > count->id)
         {
            swapNode(new1,count);
         }
      }
   }

}
void writeTxt()//write txt records
{
   FILE *dosya_yaz;

   dosya_yaz = fopen("denemesss.txt","w");

   struct node *listNode;

   sortID();
   listNode = root;
   while(listNode!=NULL)
   {
      fprintf(dosya_yaz,"%d\t%s\t%s\n",listNode->id,listNode->name,listNode->author);
      listNode = listNode->next;
   }


}
void readTxt()//read record from txt
{

   FILE *file;  /* dosya gostericisi */
   file = fopen("denemesss.txt", "r");
   struct node *tempT;
   struct node *iter;

   fseek(file, 0, SEEK_END);
   int len = ftell(file);
   rewind(file);
   if(len == 0 || file == NULL)
   {
		
   }
   else
   {

		
		root = (struct node*)malloc(sizeof(struct node)) ;

         fscanf(file,"%d\t%s\t%s\n",&root->id,root->name,root->author);
         numberOfBook++;
      		
      		root->next = NULL;

            iter = root;

         
       
       
      while(!feof(file))   //dosyadan oku
      {
         tempT = (struct node*)malloc(sizeof(struct node)) ;

         fscanf(file,"%d\t%s\t%s\n",&tempT->id,tempT->name,tempT->author);
         numberOfBook++;
     
       

            iter->next = tempT;
            iter = iter->next;
            iter->next = NULL;
         
         tempT = NULL;
      }


      fclose(file);
	goLastNode();
   }
   
}
int firstMenu()//first menu
{
   char S_input[10];
   int input;

   printf("IBRARY PROGRAM\n");
   printf("1 - List all books\n");
   printf("2 - Update book\n");
   printf("3 - Create a new book\n");
   printf("4 - Delete a book\n");
   printf("5 - Sort all books according to id\n");
   printf("6 - Sort all books according to book name\n");
   printf("7 - Sort all books according to author name\n");
   printf("8 - Exit\n");
   do
   {

      printf("Enter your choice :");

      scanf("%s", S_input);
      if(controllingInput(S_input))
      {
         input  = atoi(S_input);
         return input;
      }
      else
      {
         printf("wrong input please try again\n");
      }

   }
   while(1);





}
int main(int argc, const char * argv[])
{
   readTxt();

   while(1)
   {
      int input=0;

      input =firstMenu();

      if(input> 8 )
         printf("please enter 1-8");
      if(input == 1)
         listAllBook();
      if(input == 2)
         updateBook();
      if(input == 3)
         createNewBook();
      if(input == 4)
         deleteBook();
      if(input == 5)
      {
         sortID();
         listAllBook();
      }
      if(input == 6)
         sortBookName();
      if(input == 7)
         sortBookAuthorName();
      if(input == 8)
      {
         writeTxt();
         return 0;
      }

   }
   return 0;

}

