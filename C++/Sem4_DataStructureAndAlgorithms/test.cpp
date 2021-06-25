#include<stdio.h>
int main() {
    int range, start, last, i, j, k, total_expense = 0;
    int total[10];
    printf("Enter the starting year: ");
    scanf("%d", &start);
    printf("Enter the final year: ");
    scanf("%d", &last);
    range = last - start + 1;
    char month[12][50] = { "January","february","Sum","Average" };//"march","april","may","june","july","august","september","october","november","december"};
    int  expense[100][12] = { 0 };
    int count, ave = 0, sum = 0;
    count = start;
    for (i = 0; i < range; i++)
    {
        printf("Enter expenditure of  %d: \n", count);

        count++;

        for (k = 0; k < 2; k++)
        {
            printf("%s  : ", month[k]);
            scanf("%d", &expense[i][k]);

        }

    }
    for (int i = 0; i < range; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            total[i] += expense[i][j];
        }
        total_expense = total_expense + total[i];
    }
    printf("Expenses:\nYear|| ");
    for (k = 0; k < 4; k++)
    {
        printf(" %s  :  ", month[k]);
    }
    printf("\n");
    for (i = 0; i < range; i++) {
        printf("%d\t", start);
        start++;
        for (k = 0; k < 2; k++) {
            printf("%d\t        ", expense[i][k]);

        }
        sum = total[i];
        ave = total[i] / 12;
        printf("%d      %d", sum, ave);
        printf("\n");
    }
    printf("\n");
    printf("Total expenditure in %d years: %d\n Average:", range, total_expense, total_expense / range);
    return 0;
}