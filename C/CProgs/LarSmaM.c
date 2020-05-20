#include<stdio.h>
int large(int [][10],int,int);
int small(int [][10],int,int);
void main()
{
    int m,n,i,j,min;
    printf("Enter the number of rows of the 2d Array.");
    scanf("%d",&m);
    printf("Enter the number of columns of the 2d Array.");
    scanf("%d",&n);
    int arr[m][n];
    printf("Enter the elements:\n");
    for(i=0;i<m-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            printf("Enter element: %d x %d ",i+1,j+1);
            scanf("%d",&arr[i][j]);
        }
    }
   /*min=arr[0][0];
     for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(min<arr[i][j])
            {
                min=arr[i][j];
               // printf("hi.");
            }
        }
        }
   printf("The Largest number is %d.",min);
    min=arr[0][0];
     for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(min>arr[i][j])
            {
                min=arr[i][j];
               // printf("hi.");
            }
        }
        }

   printf("The Smallest number is %d.",min);
   //printf("L=%d\tS=%d",large(arr,m,n),small(arr,m,n));
}*/
int z=small(arr,m,n);
int y=large(arr,m,n);
printf("The smallest element is: %d\n",z);
printf("The largest element is %d\n",y);
}
int large(int arr[][10],int m,int n)
{
    int i,j,l=arr[0][0];
     for(i=0;i<m-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if((arr[i][j])>l)
                l=arr[i][j];
        }
    }
        return l;
}

int small(int arr[][10],int m,int n)
{
    int i,j,s=arr[0][0];
     for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
           // printf("%d",arr[i][j]);
            if(arr[i][j]<s)
                s=arr[i][j];
        }
        }
        return s;
}
