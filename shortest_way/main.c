
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#define MAX 15
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}


int search_time(int r,int source,int destination,int routes[r][3])
{int i;
    for( i=0; i<r; i++)
    {
        if(routes[i][0]==source)
        {
            if(routes[i][1]==destination)
                return routes[i][2];
        }
    }
}

// the dijkstra algorithm code .................................................................
void dijkstra(int r,int inputArray[r][r],int n,int source,int destination,int m, int routes[r][3])
{

    int cost[r][r],path[r],pred[r];
    int visited[r],count,minpath,succ,i,j;

    for(i=0; i<n; i++) //create the cost matrix
        for(j=0; j<n; j++)
            if(inputArray[i][j]==0)
                cost[i][j]=9999; //infinity
            else
                cost[i][j]=inputArray[i][j];

    for(i=0; i<n; i++)
    {
        path[i]=cost[source][i];
        pred[i]=source;
        visited[i]=0;
    }

    path[source]=0;
    visited[source]=1;
    count=1;

    while(count<n-1)
    {
        minpath=9999; //infinity
        for(i=0; i<n; i++)
            if(path[i]<minpath&&!visited[i])
            {
                minpath=path[i];
                succ=i;
            }

        //check if there is a a better path
        visited[succ]=1;
        for(i=0; i<n; i++)
            if(!visited[i])
                if(minpath+cost[succ][i]<path[i])
                {
                    path[i]=minpath+cost[succ][i];
                    pred[i]=succ;
                }
        count++;
    }

    //print cost , time and path of each node

    j=destination;
    int counter=-1;
    printf("\nthe route with minimum cost is: ");
    struct Stack* s = createStack(r); //to save the visited routes
    push(s,destination+1);
    do
    {
        j=pred[j];
        push(s,j+1);
        counter++;
    }
    while(j!=source);
    int time=0;
    while(!isEmpty(s))
    {
        int sou;
        int des;
        if(time==0)
        {
            sou= pop(s);
            printf("%d->",sou);
            des= pop(s);
            printf("%d->",des);
        }
        else
        {
            sou=des;
            des=pop(s);
            if (des==destination+1)
                printf("%d",des);
            else
                printf("%d->",des);
        }
        time=time+search_time(r,sou,des,routes);
    }
    printf("\ntotal time =%d",time+counter);
    counter=counter*m;
    printf("\ntotal cost =%d$\n",path[destination]+counter+time*m);


}
//controller of the user interface........................
void Q3()
{
    int m,start_city,c,r,end_city,source,destination,cost,i,j ;
    printf("please enter amount M:");
    scanf("%d",&m);
    printf("please enter number of cities:");
    scanf("%d",&c);
    printf("please enter number of routes:");
    scanf("%d",&r);
    int inputArray[r][r];
    int routes[r][3];
    for( i=0; i<c; i++)
        for( j=0; j<c; j++)
            inputArray[i][j]=0;
    printf("please enter source , destination,time and cost for each route:\n");
    for( i=0; i<r; i++)
    {
        scanf("%d",&source);
        scanf("%d",&destination);
        scanf("%d",&routes[i][2]);
        scanf("%d",&cost);
        routes[i][0]=source;
        routes[i][1]=destination;
        inputArray[source-1][destination-1]=cost;
    }
    printf("\nplease enter source city:");
    scanf("%d",&start_city);
    printf("please enter destination city:");
    scanf("%d",&end_city);
    dijkstra(r,inputArray,c,start_city-1,end_city-1,m,routes);
}
int main()
{
    printf("Hello world!\n");
    Q3();
    return 0;
}
