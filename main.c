#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// Function for checking whether it's a keyword or not !

int isKeyword(char buffer[]){

    // Samy Code of manipulating the keywords or adding some of them below .. ( PYTHON )

        /*  " WRITE YOUR CODE HERE / MODIFY THE ONE BELOW */


    // Reserved Keywords in C Language

    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};

    int i,flag = 0;   // the return value which would let us know if it's a reserved keyword or not

    // Checking if the word is a keyword or not using STRCMP BuiltIn Function

    for(i = 0; i < 32; ++i){
        if(strcmp(keywords[i], buffer) == 0){
            flag = 1;
            break;
        }
    }

    return flag;
}

// remove end of line
void remove_end_of_line(char line[])
{
    int i=0;
    while(1)
    {
        if (line[i]!='\n')
            i++;
        else
            break;
    }
    line[i]='\0';
}

// check for extension we accept .hapd only
void extention(char path[])
{
    int i = 0 ;
    char check[5];
    while(1)
    {
        if (path[i]=='.')
        {
            check[0]=path[i+1];
            check[1]=path[i+2];
            check[2]=path[i+3];
            check[3]=path[i+4];
            check[4]='\0';
            if(strcmp(check,"hapd")!=0)
            {
                printf("error in your file extension, your file extension is %s ,please make sure to make it .hapd",check);
                exit(0);
            }
            else
                break;
        }
        i++;
    }
}

/* added for operators (Salim) */
///////////////////////////////
int isOp(char c){
    char operators[] = "+-*/%=><!";
    int i=0;
    for(i = 0; i < 9; i++){ // 6 to be replaced with size of operators array
        if(c == operators[i])
            return 1;
    }
    return -1;
}
///////////////////////////////

int main(){

    // Scope of Variables wanted ( VARIABLES MUST BE MEANINGFUL )
        /* " WRITE YOUR VARIABLES HERE " */

        //removed operators from here, it's now in the isOp func (Salim)
        char ch, buffer[15],special[]="[]{},.()\":'?", op[2];
        int first =0, second=0; // to catch the operators(Salim)
        FILE *fp;            // File Pointer to open the file needed..
        int i,bufferCnt = 0;   // Buffer Counter for concatenating chars and cutting them

    // Nassar Code of reading the path of the file and checking it's extension

        /*  " WRITE YOUR CODE HERE && MODIFY THE ONE BELOW "  */
        // Enter PATH of file which want to compile

        char PATH[100];
        printf("Enter Full Path to your file\n");
        fgets(PATH,100,stdin);
        remove_end_of_line(PATH); // remove \n from input file
        extention(PATH);

        fp = fopen(PATH,"r");    // open the file test1 on the folder of the code path

        // checking whether the file opened or there's a problem

        if(fp == NULL){
            printf("error while opening the file\n");
            exit(0);
        }
        int x = 2;


    while((ch = fgetc(fp)) != EOF){         // While the file does not reach its end

         // Salim Code of handling Operators and handling identifiers before and after Ex: 1+2+3=5;
            /*  " WRITE YOUR CODE HERE "  */
    	first = isOp(ch);
        if(first == 1){
            op[0] = ch;
            char ch2 = fgetc(fp);
            second = isOp(ch2);
            if(second == 1){
                if((ch2 == '=' && (ch == '+' || ch == '-')) || (ch2 == '+' && ch == '+') || (ch2 == '-' && ch == '-')){
                    op[1] = ch2;
                    printf("%c%c is the double operator\n", op[0], op[1]); // here we have the double operators     
                }
                else{
                    printf("There is no such operator as: %c%c\n", op[0], ch2);
                    op[0] = 'E';
                }
            }
            else{
                op[1] = '\0';
                ch = ch2;
                printf("%c is the single operator\n", op[0]); // here we have the double operator
            }
        }

        // Youssef Code of handling Assigning value after equality
            /*  " WRITE YOUR CODE HERE "  */


        // Essam Code of handling Special Characters
            for(i = 0; i < 13; ++i){
               if(ch == special[i]){
                   if (bufferCnt !=0){
                       buffer[bufferCnt] = '\0';
                       bufferCnt = 0;
                       if(isKeyword(buffer) == 1)
                           printf("%s is keyword\n", buffer);
                       else
                           printf("%s is indentifier\n", buffer);
                   }
               printf("%c is special character\n", ch);
               }
           }

        // Checking whether the character is an alphabet or a number

           if(isalnum(ch)){
               buffer[bufferCnt++] = ch;
           }

        // Ammar Code of handling Spaces
            /*  " WRITE YOUR CODE HERE "  */

        // Checking the Spaces

           else if((ch == ' ' || ch == '\n') && (bufferCnt != 0)){
                   buffer[bufferCnt] = '\0';
                   bufferCnt = 0;

                   if(isKeyword(buffer) == 1)
                       printf("%s is keyword\n", buffer);
                   else
                       printf("%s is indentifier\n", buffer);
           }

    }

        // Checking keywords

            if(isKeyword(buffer) == 1)
                printf("%s is keyword\n", buffer);
            else
                printf("%s is indentifier\n", buffer);

        fclose(fp); // close the file

    return 0;
}
