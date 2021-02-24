#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Property of ze Dank Bros Co.
This basically creates a struct filled with that data, you can easily read the data.
Note, I didn't use strings, so check for null when using the char*.
*/

struct JR
{
	int index;
	int year;
	char first_name[50];    // Each person has a name.
	char middle_name[50];   // Not everyone has a middle name, check for null.
	char middle_name2[50];  //Same as middle_name, check for null.
	char last_name[50];     //Everyone has this so yeah.
	char address[50];
	int roll;
	char gender[10];
	int rank;
};

int count_spaces(char* word)
{
	int spaces = 0, i = 0;
	while(word[i] != '\0')
	{
		if(word[i] == ' ') spaces++;
		i++;
	}
	return spaces;
}

int main()
{
	char line[128];
	JR* jr = (JR*)malloc(7000 * sizeof(JR));
	int counter = 0;
	FILE* file = fopen("entrance.cpp","r");
	if(file == 0)
	{
		printf("You got cucked, can't open it\n");
	}
	else
	{
		int counter = 0;
		while(fgets(line, 128, file) != 0)
		{
			switch(count_spaces(line))
			{
				case 8:
				sscanf(line, "%d %d - %d %s %s %s %s %d",&jr[counter].index, &jr[counter].year, &jr[counter].roll, jr[counter].first_name, jr[counter].last_name, jr[counter].gender, jr[counter].address, &jr[counter].rank);
				break;
				
				case 9:
				sscanf(line, "%d %d - %d %s %s %s %s %s %d",&jr[counter].index, &jr[counter].year, &jr[counter].roll, jr[counter].first_name, jr[counter].middle_name, jr[counter].last_name, jr[counter].gender, jr[counter].address, &jr[counter].rank);
				break;
				
				case 10:
				sscanf(line, "%d %d - %d %s %s %s %s %s %s %d",&jr[counter].index, &jr[counter].year, &jr[counter].roll, jr[counter].first_name, jr[counter].middle_name, jr[counter].middle_name2,jr[counter].last_name, jr[counter].gender, jr[counter].address, &jr[counter].rank);
				break;
				
				default:
				printf("yo, this wasn't covered, shit\n");
				printf("%s",line);
				break;
			}
			counter++;
			//Access the jr[index] struct to get each junior's data.
			//  for(int i = 0; i < counter; i++)
			//     jr[counter].name;
		}
	}
	return 0;
}