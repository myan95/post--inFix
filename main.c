#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define TYPE float
#include <strings.h>
#define STACKSIZE 100
typedef struct /*implementation of a struct for symbol table*/
{ char symbol; /*for variables*/
float result; /*for data*/
}data;
data arr[100];/*array of struct*/
int k=0;
typedef struct /*implementation of stack*/
{
    int top;
    TYPE items[STACKSIZE]; /*top */
} Stack; /*array of items of type float */
void initialize(Stack *s) /*initialize function of stack */
{
    s->top=0;
}
void push(Stack *s,TYPE value) /*push function add to top increment top by array of struct */
{
    s->items[s->top++]=value;
}
TYPE pop(Stack *s) /*pop function decrement and then pops value */
{
    return s->items[--s->top];
}
int isfull(Stack *s) /*check if stack reached full size if top equal full size */
{
    return s->top<STACKSIZE?0:1 ;
}
int isempty(Stack *s) /*check if stack empty if top equal zero */
{
    return s->top==0?1:0;
}

int isoperator(char c)
{
    switch(c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '^':
        return 1;
    default:
        return 0;

    }

}

int returning( Stack *s)  /*pops the last value at top and then returns it to stack */
{
    int x=pop(s);
    push(s,x);
    return x;
}
int priority(char c) /*checks operators and numbers */
{
    if (c>='0' && c<= '9') return 0;  /*if no return 0 */
    switch (c)
    {
    case '+' :
    case '-' :
        return 1;
    case '*' :
    case '/' :
    case '%':
        return 2;
    case '(' :
        return 9;
    case ')':
        return -1;
    case '^':
        return 3;
    default :
        return 0; /*as return value increase priority of operator increases */
    }
}
void print_postfix(char*str,char *out) /*printf postfix takes two strings input infix and output postfix as we use it in eval fun*/
{  arr[k].symbol=str[0];
    char ch;
    int index=0;
    Stack stack, *s=&stack;
    initialize(s);
    str+=2;
    while (ch=*str++) /*while as long as there is a value in string */
    {
        int pr=priority(ch);
        if (!pr) out[index++]=ch; /*if number put in out string */
        else if (ch==')')
        {
            while(!isempty(s) && returning(s)!='(') out[index++]=pop(s);
            pop(s);
        }
     else if(ch=='.') /*if dot put it in the string for float calulation */
     {
         out[index++]=ch;
     }
        else /* if operator */
          {
            while(!isempty(s) && priority(returning(s))>=pr && returning(s)!='(') /*as long as not empty and pri of return f >= pri of looped value and return not equal open bracket*/
            {

                    char x=pop(s);
                if (x!='(')
                    out[index++]=x;



            }

            out[index++]=' ';
            push(s,ch);
        }
    }
    while(!isempty(s)) out[index++]=pop(s);/*put remaining elements in string out */
    out[index]=0;

    printf("%s", out);/* print post fix */
    printf("\n");
}
void error() /*prints error and exit main */
{
    printf("ERROR !!");
    exit(-1);
}

float eval (char *str) /*evaulate float value of infix */
{
    char num[20];
    Stack s;
    float sum=0;
    initialize(&s); /*declare and ini stack */
    int i;
    int j=0;
    int f=0;
    for (i=0 ; i<strlen (str); i++) /*loop length of stack */
    {
        if (str[i]==' ')continue; /*if string have space continue */

        if (str[i]<='9' && str[i]>='0')  /*if number put it in array num */
        {
            num[j++]=str[i++];

            while(str[i]!=' ' && !isoperator(str[i]) ) /*for two digit case */
                num[j++]=str[i++];

            num[j]='\0';/* put black sladh zero in end of string */
             /*change from string to float and push in stack */
            float x=atof(num);
            push(&s,x);
            j=0; /*so we can use array again to push athoer values */
            i--;
        }
        else if (priority(str[i])==0)
        {
        { for (f=0;f<=(k+1);f++)
{
        if( str[i]==arr[f].symbol)
        {
        push(&s,arr[f].result);

        }

}

        }
        }
        else /* if operator */
        {
            float a,b;
            if (isempty(&s))error();
            else
                a=pop(&s);

            if (isempty(&s))error();
            else b=pop(&s);


            switch (str[i])
            {

            case '+':
                push(&s,a+b);
                break;
            case '-':
                push(&s,b-a);
                break;
            case '*':
                push(&s,a*b);
                break;
            case '/':
                push(&s,b/a);
                break;
            case '%': /*fmod function returning float */
                push(&s,fmod(b,a));
                break;
            case '^': /*power function returning float */
                push(&s,powf(b,a));
                break;
            default :
                error();
            }
        }
    }
     float z = pop(&s);
     arr[k++].result=z;
    return (z);
}


int main()
{   system("color 48");
    char str[100];
    Stack s;
    initialize(&s);
    int n,i;
    char out[100];
    printf("enter number of exprsessions ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
    printf("Enter the infix expression as variable = \n");
    scanf("%s",str);
    print_postfix(str,out);
    printf("%f \n",eval(out));
    }

    return 0;
}
