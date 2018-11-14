#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function for checking whether it's a keyword or not !
static FILE *source_fp, *dest_fp;

int isKeyword(char buffer[])
{

    // Samy Code of manipulating the keywords or adding some of them below .. ( PYTHON )

    char keywords[33][10] = {"False", "class", "finally", "is", "return", "None", "continue",
                             "for", "lambda", "try", "and", "del", "global", "not", "with",
                             "True", "def", "from", "nonlocal", "while", "as", "elif",
                             "if", "or", "yield", "assert", "else", "import",
                             "pass", "break", "except", "in", "raise"};

    int i, flag = 0; // the return value which would let us know if it's a reserved keyword or not

    // Checking if the word is a keyword or not using STRCMP BuiltIn Function

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

// remove end of line
void remove_end_of_line(char line[])
{
    int i = 0;
    while (1)
    {
        if (line[i] != '\n')
            i++;
        else
            break;
    }
    line[i] = '\0';
}

// check for extension we accept .hapd only
void extention(char path[])
{
    int i = 0;
    char check[5];
    while (1)
    {
        if (path[i] == '.')
        {
            check[0] = path[i + 1];
            check[1] = path[i + 2];
            check[2] = path[i + 3];
            check[3] = path[i + 4];
            check[4] = '\0';
            if (strcmp(check, "hapd") != 0)
            {
                printf("error in your file extension, your file extension is %s ,please make sure to make it .hapd\n", check);
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
int isOp(char c)
{
    char operators[] = "+-*/%=><!";
    int i = 0;
    for (i = 0; i < 9; i++)
    { // 6 to be replaced with size of operators array
        if (c == operators[i])
            return 1;
    }
    return -1;
}
///////////////////////////////

char* return_path(){
    // Nassar Code of reading the path of the file and checking it's extension
    
    /*  " WRITE YOUR CODE HERE && MODIFY THE ONE BELOW "  */

    FILE *fp;
    // Enter PATH of file which want to compile
    char PATH[100];
    printf("Enter Full PAth to your file\n");
    fgets(PATH, 100, stdin);
    remove_end_of_line(PATH); // remove \n from input file
    extention(PATH);
    

    return PATH;
}

void init_io(FILE **fp, FILE *std, const char mode[], const char fn[]) {
    if (fn[0] == '\0')
        *fp = std;
    else if(fn[0] == '-' && fn[1] == 'p'){
        //from a certain given path
        fn = return_path();                  // File Pointer to open the file needed..
        if ((*fp = fopen(fn, mode)) == NULL)
            printf("Failed to open file");
    }

    else{
        //from argv (in the same folder)
        extention(fn);
        if ((*fp = fopen(fn, mode)) == NULL)
            printf("Failed to open file");
    }
}

void checkOperators (char *ch){
    
    char op[2];
    int first = 0, second = 0; // to catch the operators(Salim)
    first = isOp(*ch);
        if (first == 1)   //first char is operator
        {
            op[0] = *ch;
            char ch2 = fgetc(source_fp);
            second = isOp(ch2);
            if (second == 1)
            {
                if ((ch2 == '=' && (*ch == '+' || *ch == '-' || *ch == '<' || *ch == '>')) || (ch2 == '=' && *ch == '=') || (ch2 == '+' && *ch == '+') || (ch2 == '-' && *ch == '-'))
                {
                    op[1] = ch2;
                    printf("%c%c is the double operator\n", op[0], op[1]); // here we have the double operators
                }
                else
                {
                    printf("There is no such operator as: %c%c\n", op[0], ch2);
                    op[0] = 'E';
                }
            }
            else
            {
                op[1] = '\0';
                *ch = ch2;
                printf("%c is the single operator\n", op[0]); // here we have the double operator
            }
        }

}


void openBuffer(int *bufferCnt,char buffer[]){
    buffer[*bufferCnt] = '\0';
    *bufferCnt = 0;
}

void checkKwdOrIdnt(char buffer){
    if (isKeyword(buffer) == 1)
        printf("%s is keyword\n", buffer);
    else
        printf("%s is indentifier\n", buffer);
}

void checkSpecial(char *ch, int *bufferCnt, char buffer){
    int i;
    char special[] = "[]{},.()\"\;:'?";
    for (i = 0; i < 13; ++i)
    {
        if (ch == special[i])
        {
            if (*bufferCnt != 0)
            {
                openBuffer(&bufferCnt, buffer);
                checkKwdOrIdnt(buffer);

            }
            printf("%c is special character\n", ch);
        }
    }
}

void buildBuffer(char *ch, int *bufferCnt, char buffer){
    if (isalnum(*ch))
    {
        buffer[*++bufferCnt] = *ch;
    }
}

void check_all(){
    char ch;
    char  buffer[15]; 
    int i, bufferCnt = 0;      // Buffer Counter for concatenating chars and cutting them
    while ((ch = fgetc(source_fp)) != EOF)
    { // While the file does not reach its end

        // Salim Code of handling Operators and handling identifiers before and after Ex: 1+2+3=5;
        checkOperators(&ch);
        // Youssef Code of handling Assigning value after equality
        
        // Essam Code of handling Special Characters
        checkSpecial(&ch, &bufferCnt, buffer);        

        // Checking whether the character is an alphabet or a number
        buildBuffer(&ch, &bufferCnt, buffer);

        if ((ch == ' ' || ch == '\n') && (bufferCnt != 0))
        {
            openBuffer(&bufferCnt, buffer );
            checkKwdOrIdnt(buffer);
        }
        
    }

}



int main(int argc, char *argv[])
{

    // Scope of Variables wanted ( VARIABLES MUST BE MEANINGFUL )
    /* " WRITE YOUR VARIABLES HERE " */


    // get data from stdin or path or from argv
    init_io(&source_fp, stdin,  "r",  argc > 1 ? argv[1] : "");
    
    check_all();
    // Checking keywords

    // if (isKeyword(buffer) == 1)
    //     printf("%s is keyword\n", buffer);
    // else
    //     printf("%s is indentifier\n", buffer);

    fclose(source_fp); // close the file

    return 0;
}
