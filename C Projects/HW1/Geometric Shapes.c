#include<stdio.h>




void drawLine(int a , int b)
{

	int i;
	int j;
	for(i = 10; i>-11; i--)//print y axis
	{

		for(j = -10; j<11; j++)//print x asis
		{

			if(i == a*j + b  )
				printf("*");
			else 
			if(j==0)
				printf("|");//y axsis


			else if(i==0)
				printf("-");//x axsis





			else
				printf(" ");
		}
		printf("\n");

	}
}

void drawParabola(int a , int b ,int c)
{

	int i;
	int j;

	for(i = 10; i>-11; i--)
	{

		for(j = -10; j<11; j++)
		{
			if(i == a*j*j + b*j + c )
			{
				printf("*");
			}
			else if(j==0)
				printf("|");


			else if(i==0)
				printf("-");

			else
				printf(" ");
		}
		printf("\n");

	}
}

void drawCircle(int a , int b ,int r)
{

	int i;
	int j;

	for(i = 10; i>-11; i--)
	{

		for(j = -10; j<11; j++)
		{
			if(r*r == (j-a)*(j-a) + (i-b)*(i-b) )
			{
				printf("*");
			}
			else if(j==0)
				printf("|");


			else if(i==0)
				printf("-");

			else
				printf(" ");
		}
		printf("\n");

	}
}

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
		if(counter==strlen(input)-1)//if number of number equals strlen- this means that in put is negative number
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


int main()
{
		char a[50];//coffiecent a in char
		int iA;//coeficinet b in char

		char b[50];
		int iB;

		char c[50];
		int iC;

		char r[50];
		int iR;

	do
	{

		printf("\nWhich shape would you like to draw?\n1. Line\n2. Parabola\n3. Circle\n4. Exit\n");
		char charChosen[50];//getting input via pointer
		scanf("%s" , charChosen);//assign input to charChosen
		int chosen;
		chosen = atoi(charChosen);//casting char pointer to integer
		if(controllingInput(charChosen))//control input
		{

			if(chosen == 1)//draw line
			{
				do
				{
					printf("Line formula is y = ax + b. . Please enter coefficient a:\n");
					scanf("%s",a);
					if(controllingInput(a)==1 )// a is number break loop
					{
						break;
					}
					else
					{
						printf("\n\n---> a should be number  <----\n\n");// not number give this output
					}
				}
				while(1);

				do
				{
					printf("Line formula is y = ax + b.  Please enter coefficient b:\n");
					scanf("%s",b);
					if(controllingInput(b) ==1 )//b is number break loop
					{
						break;
					}

					else
					{
						printf("\n\n---> b shold be number  <----\n\n");//not number give this output
					}

				}
				while(1);



				iA = atoi(a);//convert char a to int iA
				iB = atoi(b);//convert char a to int iA

				drawLine(iA,iB);//caal function drawLine

			}


			if(chosen == 2)
			{
				do
				{
					printf("Parabola formula is y = ax^2 + bx + c\nPlease enter coefficients  a:\n");
					scanf("%s",a);
					if(controllingInput(a))
					{
						break;
					}
					else
					{
						printf("\n\n\n ----> a should number <---- \n\n\n");
					}
				}
				while(1);

				do
				{
					printf("Parabola formula is y = ax^2 + bx + c\nPlease enter coefficients  b:\n");
					scanf("%s",b);
					if(controllingInput(b))
					{
						break;
					}
					else
					{
						printf("\n\n\n ----> b should number <---- \n\n\n");
					}
				}
				while(1);

				do
				{
					printf("Parabola formula is y = ax^2 + bx + c\nPlease enter coefficients  c:\n");
					scanf("%s",c);
					if(controllingInput(c))
					{
						break;
					}
					else
					{
						printf("\n\n\n ----> c should number <---- \n\n\n");
					}
				}
				while(1);

				iA = atoi(a);
				iB = atoi(b);
				iC = atoi(c);
				drawParabola(iA,iB,iC);

			}

			if(chosen == 3)
			{
				do
				{
					printf("Circle formula is (x-a)^2 + (y-b)^2 = r^2\nPlease enter center's coordinates a\n");
					scanf("%s",a);
					if(controllingInput(a))
					{
						break;
					}
					else
					{
						printf("\n\n\n ----> a must be number <---- \n\n\n");
					}
				}
				while(1);

				do
				{
					printf("Circle formula is (x-a)^2 + (y-b)^2 = r^2\nPlease enter center's coordinates b\n");
					scanf("%s",b);

					if(controllingInput(b))
					{
						break;
					}
					else
					{
						printf("\n\n\n ----> b must be number <---- \n\n\n");
					}
				}
				while(1);


				do
				{
					printf("Circle formula is (x-a)^2 + (y-b)^2 = r^2\nPlease enter center's radius r\n");
					scanf("%s",r);
					if(controllingInput(r))
					{
						if(atoi(r) > 0)// controlling r greater than 0
						{
							break;
						}
						else
						{
							printf("\n\n\n ----> r must be greater than 0! <----\n\n\n");
						}
					}
					else
					{
						printf("\n\n\n ----> r must be number! <----\n\n\n");
					}
				}
				while(1);

				iA = atoi(a);
				iB = atoi(b);
				iR = atoi(r);
				drawCircle(iA,iB,iR);
			}

			if(chosen == 4)
			{
				printf("bye");
				return 0;
			}

			if(chosen>5)
				printf("pres 1 or 2 or 3 or 4 ");
		}
		else
		{
			printf("Please enter number that 1 2 3 4");
		}
	}
	while(1);

}













