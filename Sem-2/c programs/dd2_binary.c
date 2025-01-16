#include<stdio.h>
#include<Stdlib.h>
#include<string.h>
void ConvertToBinary(char T[])
{
    int N;
   
    int a[30],i;
    N=atoi(T);
    i=-1;
    while(N!=0)
    {
        a[++i]=N%2;
        N=N/2;
    }
    for(;i>=0;i--)
    {
        printf("%d",a[i]);
    }
}
int main()
{
    char S[100],R[100];
    int i,j,k;
    printf("Enter the dotted decimal number:");
    gets(S);
    printf("Binary equivalent is :");
    for(i=0,k=0;S[i]!='\0';i++)
    {
        if (S[i] =='.')
            {
                R[k]='\0';
               ConvertToBinary(R);
                k=0;
                printf(".");
                strcpy(R,"");
            }
            else
            {
            R[k]=S[i];
            k++;
            }
    }
    R[k]='\0';
    ConvertToBinary(R);
    return 0;
}