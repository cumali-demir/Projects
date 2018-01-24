//include libraries
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>



//define macros and constants,colors
#define MAX_LINE 128 // 128 chars per line
#define BUFSIZE 128
#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_APPEND)
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAG     "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m"
 pid_t BackID;
//declare or initialize variables
char pathArray[100][100];// for environment
char commandLineInput[MAX_LINE];
char bookmarkArray[200][128];
int counterOfPathArray = 0;
int countOfBookmarkArray=0;
int numberOfArgs;
int isExit=0;

void setup(char inputBuffer[], char *args[], int *background)
{
    int length,     /* # of characters in the command line */
            i,      /* loop index for accessing inputBuffer array */
            start,  /* index where beginning of next command parameter is */
            ct=0;   /* index of where to place the next parameter into args[] */
    /* read what the user enters on the command line */
    length = (int) read(STDIN_FILENO, inputBuffer, MAX_LINE);
    strcpy(commandLineInput,inputBuffer); /* copy input line to a char array */
    /* 0 is the system predefined file descriptor for stdin (standard input),
       which is the user's screen in this case. inputBuffer by itself is the
       same as &inputBuffer[0], i.e. the starting address of where to store
       the command that is read, and length holds the number of characters
       read in. inputBuffer is not a null terminated C-string. */
    start = -1;
    if (length == 0){
        exit(0);
    }

    /* ^d was entered, end of user command stream
     the signal interrupted the read system call
     if the process is in the read() system call, read returns -1
      However, if this occurs, errno is set to EINTR. We can check this  value
      and disregard the -1 value */
    if ( (length < 0) && (errno != EINTR) ) {
        perror("Error reading the command!");
        exit(-1);           /* terminate with error code of -1 */
    }
    for (i=0;i<length;i++){ /* examine every character in the inputBuffer */
        switch (inputBuffer[i]){
            case ' ':
            case '\t' :               /* argument separators */
                if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
                    ct++;
                }
                inputBuffer[i] = '\0'; /* add a null char; make a C string */
                start = -1;
                break;
            case '\n':                 /* should be the final char examined */
                if (start != -1){
                    args[ct] = &inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
                break;
            default :             /* some other character */
                if (start == -1) {
                    start = i;
                }
                if (inputBuffer[i] == '&' && strcmp(args[0],"bookmark") != 0){
                    *background  = 1;
                    inputBuffer[i-1] = '\0';
                    //backgroundProcess++;
                }
        }   /* end of switch */
    }   /* end of for */
    args[ct] = NULL;    /* just in case the input line was > 80 */
    numberOfArgs=ct;
    if(ct>32){
        perror("Maximum Argument Error: ");
    }

   /*for (i = 0; i <= ct; i++) //to print arguments
        printf("args %d = %s\n",i,args[i]);*/

} /* end of setup routine */

void create_path_array()
{
    char * pathList;
    pathList = getenv ("PATH");
    char separator[2] = ":";
    char *token;
    token = strtok(pathList, separator);
    int i=0;
    while( token != NULL )
    {
        strcpy( pathArray[i], token );
        token = strtok(NULL, separator);
        i++;
        counterOfPathArray++;
    }
}

void  executeRedirectCommand(char *argRedirect[])
{
    char fullPath[222];
    strcpy(fullPath,argRedirect[0]);
    argRedirect[0] = ".\\";
    execv(fullPath,argRedirect);
}

int create_process(char *args[])
{
    char fullPath[222];
    int i;

    for(i=0;i<counterOfPathArray;i++)
    {
        strcpy(fullPath,pathArray[i]);
        strcat(fullPath,"/");
        strcat(fullPath,args[0]);

        if( execv(fullPath,args) == -1 ){

        }

    }
    printf(RED"No valid path.\n"RESET);
    kill(getpid(),SIGTERM);
}

void bookmark_process(char *args[])
{
    if(strcmp(args[1],"-i") == 0 ){//invoke
        if(args[2] != NULL ){
            if(atoi(args[2]) < countOfBookmarkArray){
                int index = atoi(args[2]);
                char *NewArgs[120];
                char *temp = malloc(500);
                strcpy(temp, bookmarkArray[index]);
                char *s = temp;
                while(*s != NULL){
                    if(*s == '\"'){
                        if(*(s+1) == NULL ){
                            *s = '\0';
                        }else{
                            temp = temp + 1;
                        }
                    }
                    s++;
                }
                char *p;
                int j = 0;
                p = strtok(temp," ");
                while(p!=NULL){
                    printf ("%s\n",p);
                    NewArgs[j] = p;
                    p = strtok (NULL, " ");
                    j++;
                }
                NewArgs[j] = '\0';
                create_process(NewArgs);
            }else{
                printf(RED"Exception bound overflow.\n"RESET);
            }
        }else{
            printf(RED"Missing Arguments\n"RESET);
        }
    }else if(strcmp(args[1],"-d") == 0){//delete
        if(args[2] != NULL && args[3] == NULL){
            if(atoi(args[2])>=0){
                if( atoi(args[2]) < countOfBookmarkArray ){
                    int i;
                    for(i=0;i<countOfBookmarkArray;i++){
                        if( i>=atoi(args[2]) ){
                            strcpy(bookmarkArray[i],bookmarkArray[i+1]);
                        }
                    }
                    countOfBookmarkArray--;
                   /* for(i = 0; i<countOfBookmarkArray;i++){
                        printf("%d %s\n",i,bookmarkArray[i]);
                    }*/
                }else{
                    printf(RED"Bookmark array error.\n"RESET);
                }
            }else{
                printf(RED"Please enter index after argument.\n"RESET);
            }
        }else{
            printf(RED"Delete Case Error\n"RESET);
        }
    }else if(strcmp(args[1],"-l") == 0){//list
        int i;
        for(i = 0; i<countOfBookmarkArray;i++){
            printf("%d %s\n",i,bookmarkArray[i]);
        }
    }else{ //insert case
        strcpy(bookmarkArray[countOfBookmarkArray],args[1]);
        int i;
        for(i = 2; i < numberOfArgs; i++){
            strcat(bookmarkArray[countOfBookmarkArray]," ");
            strcat(bookmarkArray[countOfBookmarkArray] , args[i]);
        }
        countOfBookmarkArray++;
    }
}

void codesearch_process( char *args[])
{
    char grep[5][100]= {0,0,0,0,0};
    char* Buffer = malloc(BUFSIZE);
    char buf[BUFSIZE];
    int length=0;
    strcpy(grep[0],"/bin/grep");
    strcpy(grep[1],"-nw");//number of lines and just given string
    strcpy(grep[2],"--include=*.c --include=*.h --include=*.C --include=*.H"); // limit file types
    strcpy(grep[3],"");
    if(args[0]!=NULL && args[1]!=NULL) { //check first two indexes
        if(strcmp("-r", args[1]) == 0) { //with subdirectories
            strcat(grep[1],"r");
            strcat(grep[3],args[2]);
            strcat(grep[3]," ");
            strcpy(grep[4],"./");
            int forInt=0;
            for(forInt=0;forInt<5;forInt++){ //create command
                length += snprintf(Buffer+length, BUFSIZE-length, strcat(grep[forInt]," "));
            }
            FILE *fp;
            if ((fp = popen(Buffer, "r")) == NULL) {
                printf(RED"Error opening pipe!\n"RESET);
            }
            while (fgets(buf, BUFSIZE, fp) != NULL) {
                printf(MAG"%s"RESET, buf);
            }
            if(pclose(fp)) {
                printf(RED"Command not found or exited with error status\n"RESET);
            }
        }else{ // just in the current directory
            strcpy(grep[4],"./*");
            strcat(grep[3],args[1]);
            strcat(grep[3],"");
            int forIntB=0;
            for(forIntB=0;forIntB<5;forIntB++){
                length += snprintf(Buffer+length, 128-length, strcat(grep[forIntB]," "));
            }

            FILE *fp;
            if ((fp = popen(Buffer, "r")) == NULL) {
                printf(RED"Error opening pipe!\n"RESET);
            }
            while (fgets(buf, BUFSIZE, fp) != NULL) {
                printf("-");
                printf(MAG"%s"RESET, buf);
            }
            if(pclose(fp)) {
                printf(RED"\n*Command not found or exited with error status.*\n"RESET);
            }
        }
    }else{
        printf(RED"Missing Arguments.\n"RESET);
    }
}

void print_process(char *args[])
{
    extern char **environ;
    char * env_variable;
    if(args[1]==NULL ){
        for (char **env = environ; *env; ++env){
            printf(WHITE"%s\n"RESET, *env);
        }
    }else if(args[1]!=NULL) {
        env_variable=getenv(args[1]);
        if (env_variable!=NULL) {
            printf(MAG"%s = %s\n"RESET, args[1],env_variable);
        }else{
            printf(RED"No variables in this environment called %s.\n"RESET,args[1]);
        }
    }
}

void set_process(char *args[])
{
    int i = 0, j = 0, k = 0, count = 0;
    char mainInput[MAX_LINE];
    strcpy(mainInput, commandLineInput);
    while (args[count] != NULL) {
        count++;
    }
    if (count == 4) { //full whitespace option
        if (args[3] != NULL) {
            i = setenv(args[1], args[3], 1);
            if (i == 0) {
                printf(CYAN"Result: %s variable is set to %s value.\n"RESET, args[1], args[3]);
            } else if (i == -1) {
                printf(RED"Result: %s could not be set to %s.There may be some memory leaks.\n"RESET, args[1], args[3]);
            }
        } else {
            j = setenv(args[1], args[2], 1);
            if (j == 0) {
                printf(CYAN"Result: %s variable is set to %s value.\n"RESET, args[1], args[2]);
            } else if (j == -1) {
                printf(RED"Result: %s could not be set to %s.There may be some memory leaks.\n"RESET, args[1], args[2]);
            }
        }
    } else {

        if (commandLineInput != NULL) {
            char argv[5][100];
            char *string=NULL;
            char *token=NULL;
            char *tofree=NULL;
            int index = 0;
            char *line = strdup(commandLineInput);
            char *first_part = strtok(line, " ");
            char *sec_part = strtok(NULL, "\n");
            strcpy(argv[0],first_part);
            string = strdup(sec_part);
            index=0;
            if (string != NULL) {
                tofree = string;
                while ((token = strsep(&string, "=")) != NULL)
                {
                    strcpy(argv[index], token);
                    index++;
                }
                free(tofree);
            }
            k = setenv(argv[0], argv[1], 1);
            if (k == 0) {
                printf(CYAN"%s variable is set to %s value.\n"RESET, argv[0], argv[1]);
            } else if (k == -1) {
                printf(RED"%s could not be set to %s.There may be some memory leaks.\n"RESET, argv[0], argv[1]);
            }
        } else {
            printf("text");
        }

    }
}

void help_process(char *args[])
{
    printf(CYAN"Help Command!\nSample Usage of Shell\n");
    printf("-gedit\n-gedit &\n-bookmark \"ls -lh\"\n-bookmark -l\n-bookmark -i 0\n");
    printf("-bookmark -d 0\n-codesearch -r \"foo\"\n-codesearch \"foo\"\n");
    printf("set TEST_VAR=test_value\nset TEST_VAR = test_value\n");
    printf(""RESET);
}

void redirectOne(char *argRedirect[],char *fileName)
{
    int fd = open(fileName, CREATE_FLAGS, CREATE_MODE);
    if (fd == -1){
        perror("Failed to open my.file");
    }
    if (dup2(fd, STDOUT_FILENO) == -1){
        perror("Failed to redirect standard output");
    }
    if (close(fd) == -1){
        perror("Failed to close the file");
    }
    printf(GREEN"Output will be seen in my.file\n"RESET);
    char *s = *argRedirect;
    if(*s == '/'){
        executeRedirectCommand(argRedirect);
    }else{
        create_process(argRedirect);
    }
}

void error_proc(char *argRedirect[],char *fileName)
{
    int fd;


    fd = open(fileName, CREATE_FLAGS, CREATE_MODE);
    if (fd == -1){
        perror(RED"Failed to open my.file"RESET);
    }
    if (dup2(fd, STDERR_FILENO) == -1){
        perror(RED"Failed to redirect standard output"RESET);
    }
    if (close(fd) == -1){

        perror(RED"Failed to close the file"RESET);
    }
    printf(GREEN"Output will be seen in my.file\n"RESET);
    char *s = *argRedirect;
    if(*s == '/'){
        executeRedirectCommand(argRedirect);
    }else{
        create_process(argRedirect);
    }
}

void redirectTwo(char *argRedirect[],char *fileName)// > metodu
{
    int fd;
    fd = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd == -1){
        perror(RED"Failed to open file.out"RESET);
    }
    if (dup2(fd, STDOUT_FILENO) == -1){
        perror(RED"Failed to redirect standard output"RESET);
    }
    if (close(fd) == -1){
        perror(RED"Failed to close the file"RESET);
    }
    char *s = *argRedirect;
    if(*s == '/'){
        executeRedirectCommand(argRedirect);
    }else{
        create_process(argRedirect);
    }
}

void fileIO1(char * args[], char* inputFile, char* outputFile)
{

    int fileDescriptor; // between 0 and 19, describing the output or input file
    fileDescriptor = open(inputFile, O_RDONLY, 0600);
    dup2(fileDescriptor, STDIN_FILENO);
    close(fileDescriptor);
    fileDescriptor = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    dup2(fileDescriptor, STDOUT_FILENO);
    close(fileDescriptor);
    char *s = *args;
    if(*s == '/')
    {
        executeRedirectCommand(args);
    }
    else
    {
        create_process(args);
    }
}

void fileIO2(char * args[], char* inputFile)
{
    int fileDescriptor;
    fileDescriptor = open(inputFile, O_RDONLY, 0600);
    dup2(fileDescriptor, STDIN_FILENO);
    close(fileDescriptor);
    char *s = *args;
    if(*s == '/'){
        executeRedirectCommand(args);
    }else{
        create_process(args);
    }
}

int main(void)
{
    //declarations
    char bookmark[] = "bookmark";
    char codesearch[] = "codesearch";
    char print[] = "print";
    char set[] = "set";
    char help[] = "help";
    char exit_text[] = "exit";


    create_path_array(); // gets environment paths
    while (1) {
        char inputBuffer[MAX_LINE]; /*buffer to hold command entered */
        char *args[MAX_LINE / 2 + 1]; /*command line arguments */
        char *args_fileIO[256];
        int background=0; /* equals 1 if a command is followed by '&' */
        int j = 0;
        pid_t childPid;
        int ioBit = 0;

        printf(GREEN"\nmyshell: "RESET);
        fflush(stdout);
        /*setup() calls exit() when Control-D is entered */
        setup(inputBuffer, args, &background);
        childPid = fork();
		if( childPid<0) 
		{
            perror(RED"\nError in fork.\n"RESET);
        }
		if (childPid == 0)
		{
			while ( args[j] != NULL)
			{
                if ( (strcmp(args[j],">") == 0) || (strcmp(args[j],"<") == 0) || (strcmp(args[j],">>") == 0) || (strcmp(args[j],"2>") == 0)){
                    ioBit = 1;
                    break;
                }
                args_fileIO[j] = args[j];
                if (strcmp(args[j],"&") == 0){
                    background = 1;
                    args[j] = NULL;
                }
                j++;
            } //end of while
            args_fileIO[j] = NULL;

			if (strcmp(bookmark, args[0]) == 0) 
			{ //bookmark
                    		bookmark_process(args);
			} 
			else if (strcmp(codesearch, args[0]) == 0) 
			{//codesearch
                		codesearch_process(args);
			} 
			else if (strcmp(print, args[0]) == 0) 
			{// print <varname>
                		print_process(args);
			} 
			else if (strcmp(set, args[0]) == 0) 
			{// set varname = somevalue –
                		set_process(args);
			} 

			else if (strcmp(help, args[0]) == 0) 
			{// help
                		help_process(args);
			} 
		

			else if (strcmp(exit_text, args[0]) == 0) 
			{
				printf(WHITE"Logging out...\n"RESET);
				exit(0);


            }



			else if(ioBit == 1)
			{
                int i = 0;
                while(args[i] != NULL){
                    if(strcmp(args[i],"<") == 0){
                        if(args[i+1] != NULL){
                            if(args[i+2] != NULL){
                                if(strcmp(args[i+2],">") == 0 && args[i+3] != NULL){
                                    if(args[i+4] != NULL){
                                        printf(RED"read/write case error.\n"RESET);
                                        break;
                                    }else{
                                        printf(GREEN"read/write case works\n"RESET);
                                        fileIO1(args_fileIO, args[i + 1], args[i + 3]);
                                        break;
                                    }
                                }else{
                                    printf(RED"read/write case error.\n"RESET);
                                    break;
                                }
                            }else{
                                fileIO2(args_fileIO,args[i+1]);
                                break;
                            }
                        }else{
                            printf(RED"read case error\n"RESET);
                            break;
                        }
                    }else if(strcmp(args[i],">") == 0){
                        if(args[i+1] != NULL && args[i+2] == NULL){
                            redirectTwo(args_fileIO,args[i+1]);
                            break;
                        }else{
                            printf(RED"write case error\n"RESET);
                        }
                    }else if(strcmp(args[i],">>") == 0){
                        if(args[i+1] != NULL && args[i+2] == NULL){
                            redirectOne(args_fileIO,args[i+1]);
                            break;
                        }else{
                            printf(RED">> case error"RESET);
                            break;
                        }
                    }else if(strcmp(args[i],"2>") == 0){
                        if(args[i+1] != NULL && args[i+2] == NULL){
                            error_proc(args_fileIO,args[i+1]);
                        }else{
                            printf(RED"2> case error"RESET);
                            break;
                        }
                    }
                    i++;
                }   //end of while loop
			} 
			else 
			{ //execute
                char *s = *args;
                if(*s == '/'){
                    executeRedirectCommand(args);
                }else{
                    create_process(args);
                }
            }
		} // end if childPid == 0
		else//parent process scope
		{
				
			if (background == 0)
			{
				waitpid(childPid,NULL,0);
				if(strcmp(args[0],"exit") == 0)
				{	
					int status;
					pid_t result = waitpid(BackID, &status, WNOHANG);
					if (result == 0) 
					{
						printf(YELLOW"There are background processes..\n"RESET);
					  // Child still alive
					}
					else 
					{
					  // Child exited
						printf(GREEN"Goodbye...\n"RESET);    
						kill(getpid(),SIGTERM);
                				 	
					}	
				}
			}
			else
			{
				BackID = childPid;
				printf(MAG"\nProcess created with PID: %d\n"RESET,childPid);
				printf(BLUE"Parent id is = %d\n"RESET,getpid());
			}
		}
	
    } // end of while loop
} //end of main method
