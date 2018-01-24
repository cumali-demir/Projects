#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct recordData
{
    int id;
    char firstName[15];
    char lastName[15];
    double phoneNum;
    char adress[50];
};

typedef struct recordData Data;
Data *dataArray[100];
int numberOfPerson=0;
int numberOfLines = 0;
int recursive=0;



int controllingInput(char *input)   //controlling inputs from user
{
    
    int counter=0;
    int i=0;
    
    while(input[i]!='\0')   //if input not null, go to other index
    {
        if(isdigit(input[i]))
        {
            counter++;//count number of n umber
            i++;//going other index
        }
        
        else
            i++;
    }
    
    if(input[0] == '-' || input[0] == '+')   //controlling negative numbers. or +positive number(e.g +5)
    {
        if(counter==strlen(input)-1)   //if number of number equals strlen- this means that in put is negative number
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
        if(counter==strlen(input))   //if number of number equals strlen this menas thar input is positive number
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int searchInList(Data *search[],int currDataId)
{
    if(numberOfPerson == 0)
    {
        return -1;
    }
    
    else
    {
        int i;
        
        for(i=0; i<numberOfPerson; i++)
        {
            
            if(search[i]->id == currDataId)
            {
                
                return i;
            }
            
        }
        return -1;
    }
    
    
}

void printOneRecord(Data *search[],int index)
{
    printf("%d\t %s\t %s\t %lf\t %s\n",search[index]->id,search[index]->firstName,search[index]->lastName,search[index]->phoneNum,search[index]->adress);
}

void updateRecord(Data *dataArray[],int index)
{
    char S_subChosen[50];
    
    printf("1-)Update Phone Number\n");
    printf("2-)Update Adress\n");
    
    scanf("%s", S_subChosen);
    
    if(controllingInput(S_subChosen))
    {
        int subchosen = atoi(S_subChosen);
        char updateText[50];
        
        if(subchosen == 1)
        {
            
            printf("Enter the phone number\n");
            scanf("%s",updateText);
            if(controllingInput(updateText))
            {
                dataArray[index]->phoneNum = atof(updateText);
            }
            else
            {
                printf("wrong input\n");
            }
            
        }
        
        if(subchosen == 2)
        {
            printf("Enter the adress\n");
            scanf("%s",dataArray[index]->adress);
            
        }
        
        
    }
    else
    {
        printf("wrong input\n");
    }
}

void deleteRecord(Data *Array[],int index)
{
    int i;
    if(numberOfPerson == 0)
    {
        printf("there is no record\n");
    }
    else
    {
        for(i=index; i<numberOfPerson; i++)
        {
            Array[i] = Array[i+1];
        }
        Array[numberOfPerson]=NULL;
        numberOfPerson--;
    }
}

void writeTxt(Data *Array[])
{
    
    
    FILE *dosya_yaz;
    
    dosya_yaz = fopen("cumali.txt","w");
    
    
    
    int i;
    for(i = 0; i<numberOfPerson; i++)
    {
        fprintf(dosya_yaz,"%d\t%s\t%s\t%Lf\t%s\n",Array[i]->id,Array[i]->firstName,Array[i]->lastName,Array[i]->phoneNum,Array[i]->adress);
        
    }
    
    
    
    fclose(dosya_yaz);
}

void readTxt(Data *Array[])
{
    
    FILE *file;  /* dosya gostericisi */
    file = fopen("cumali.txt", "r");
    Data *tempT = (Data*)malloc(sizeof(Data)) ;


    
    
    
    while(!feof(file))   //dosyadan oku
    {
        
        fscanf(file,"%d\t%s\t%s\t%Lf\t%s    ",&tempT->id,tempT->firstName,tempT->lastName,&tempT->phoneNum,tempT->adress);
        Array[numberOfPerson] =tempT;
        numberOfPerson++;
        numberOfLines++;

    }
    fclose(file);
    
}




int isFirstUse()
{
    FILE *file;  /* dosya gˆstericisi */
    file = fopen("cumali.txt", "r");
    if(file==NULL)
        return 1;
    else
        return 0;
}
void orderByLastName(Data *Array[])
{
    
    Data *tempRec = (Data*)malloc(sizeof(Data));
    int i;
    int j;
    
    for (i = 1; i < numberOfPerson; i++)
    {
        for (j = 1; j < numberOfPerson; j++)
        {
            if (strcmp( Array[j-1]->lastName , Array[j]->lastName ) > 0)
            {
                tempRec= Array[j-1];
                Array[j-1] = Array[j];
                Array[j] = tempRec;
            }
        }
    }
    
    
}
int main()
{
    if(isFirstUse()==0)
    {
        printf("previous record has been taken\n");
        readTxt(dataArray);
    }
    do
    {
        
        printf("1 - List all records\n");
        printf("2 - Update a record\n");
        printf("3 - Create a new record\n");
        printf("4 - Delete a record\n");
        printf("5 - Exit\n");
        char Schoosen[50];
        
        scanf("%s" , Schoosen);//assign input to charChosen
        
        if(controllingInput(Schoosen))
        {
            int choosen = atoi(Schoosen);
            if(choosen == 1)
            {
              
                  if(numberOfPerson==0)
                  {
                      printf("there is no records\n");
                  }
                  else
                  {
                      int i;
                      printf("NO\tFIRST NAME\tLAST NAME\tPHONE NUMBER\tADRESS\n");
                      printf("===========================================================================================================\n");
                      for(i=0; i<numberOfPerson; i++)
                      {
                          orderByLastName(dataArray);
                          printOneRecord(dataArray,i);
                      }
                  }
            }
            
            if(choosen == 2)
            {
                char S_updatingInput[20];
                printf("Please enter the record number of the person you want to update.\n");
                scanf("%s", S_updatingInput);
                if(controllingInput(S_updatingInput))
                {
                    int updatingId = atof(S_updatingInput);
                    int index =searchInList(dataArray,updatingId);
                    if(index == -1 )
                    {
                        printf("there no record this id\n");
                    }
                    else
                    {
                        printOneRecord(dataArray,index);
                        updateRecord(dataArray,index);
                        printOneRecord(dataArray,index);
                        
                    }
                    
                }
                else
                {
                    printf("wrong Input\n");
                }
                
            }
            
            if(choosen == 3)
            {
                Data *temp = (Data*)malloc(sizeof(Data)) ;
                char S_idControl[20];
                do
                {
                    printf("Enter the record number to create a new record\n");
                    
                  
                    scanf("%s",S_idControl);

                    if(controllingInput(S_idControl))
                    {
                        temp->id = atoi(S_idControl);
                        break;
                    }
                    else
                    {
                        printf("please number\n");
                    }
                }while(1);
                
                
                
                if(searchInList(dataArray,temp->id) == -1)
                {
                    printf("Enter the first name\n");
                    scanf("%s",temp->firstName);
                    
                    printf("Enter the last name\n");
                    scanf("%s",temp->lastName);
                    
                    do
                    {
                        printf("Enter the phone number\n");
                        char numberControl[20];
                        scanf("%s",numberControl);
                        if(controllingInput(numberControl))
                        {
                            temp->phoneNum = (double)atoi(numberControl);
                            break;
                        }
                        else
                        {
                            printf("number please!!\n");
                        }
                    }
                    while(1);
                    
                    printf("Enter the adress\n");
                    scanf("%s",temp->adress);
                    dataArray[numberOfPerson] = temp;
                    numberOfPerson++;
                }
                else
                {
                    int index =searchInList(dataArray,temp->id);
                    char S_updatingInput[20];
                    
                    printf("This record is exist.\n");
                    printOneRecord(dataArray,index);
                    printf("1-)Update\n2-)Delete\n3-)Nothing(biger than 3' going to upper menu)\n");
                    scanf("%s",S_updatingInput);
                    
                    if(controllingInput(S_updatingInput))
                    {
                        int updatingInput = atof(S_updatingInput);
                        
                        if(updatingInput == 1)
                        {
                            updateRecord(dataArray,index);
                        }
                        if(updatingInput == 2)
                        {
                            printOneRecord(dataArray,index);
                            deleteRecord(dataArray,index);
                            printf("deleted!\n");
                        }
                        if(updatingInput >= 3)
                        {
                            
                        }
                        
                    }
                    else
                    {
                        printf("wrong input!\n");
                    }
                    
                    
                }
            }
            
            if(choosen == 4)
            {
                char S_deleteInput[20];
                printf("Enter the record number to delete : ");
                scanf("%s",S_deleteInput);
                if(controllingInput(S_deleteInput))
                {
                    int deleteId = atoi(S_deleteInput);
                    int index = searchInList(dataArray,deleteId);
                    if(index==-1)
                    {
                        printf("there no record this id\n");
                    }
                    else
                    {
                        printOneRecord(dataArray,index);
                        deleteRecord(dataArray,index);
                        printf("deleted!\n");
                    }
                    
                    
                }
                else
                {
                    printf("wrong Input\n");
                }
            }
            if(choosen == 5)
            {
                printf("bye\n");
                writeTxt(dataArray);
                
                return 0;
            }
            
        }
        
        else
        {
            printf("Wrong input\n");
        }
        
        
    }
    while(1);
    
    
    return 0;
}




