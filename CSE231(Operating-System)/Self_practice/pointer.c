    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>


    typedef struct Student{

    char name[50];
    int roll;



    }std;

    typedef struct Node Node;
    struct Node {
    int data;
    Node *nextptr;
    };


    int main()
    {
    unsigned int x = 3251;
    char *cp = &x;
    unsigned char c1 = *cp++, c2 = *cp;

    printf("%d\n",c1);
    printf("%d\n",c2);
    return 0;
    }