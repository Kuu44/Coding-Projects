/********
 *
 * Sujit Maharjan
 *
 * lab 1
 * Store and retrieve the name of the students and obtained marks in c programming in 1st semester using structure.
 * 
 ********/


#include <stdio.h>
// header file for console input output

// basic data structure;
struct student
{
  char name[20];
  int marks;
};
/**********
 *
 * Stores new student name and marks in file
 *
 * \param filename
 *********/
int store(char* filename)
{
  // opening file in appending mode
  FILE* fp = fopen(filename,"a+");
  // checking if the file is available
  if (fp == NULL)
    {
      fprintf(stderr,"could not open the file");
      return -1;
    }
  // decalaring struct variable
  struct student student;
  // temp variable
  char ans;
  do
    {
      // asking user for student infromation
      printf("Enter the name of the student");
      scanf(" %s",student.name);
      printf("Enter the marks obtained by student in computer science");
      scanf(" %d",&student.marks);
      // writing the student to the file
      fprintf(fp,"%s %d",student.name,student.marks);
      printf("Press y to continue\n");
      // asking if user want to continue updating the record
      scanf(" %c",&ans);
    }
  while( ans == 'y');
  fclose(fp);
  return 0;
}
/********
 *
 * retrives the student record from the file
 * 
 * \params filename
 ********/
int retrive(char* filename)
{
  // temprorary struct
  struct student student;
  // opening the file in read mode
  FILE* fp = fopen(filename, "r");
  // checking if file was sucessfully opened
  if ( fp == NULL)
    {
      fprintf(stderr,"Could not open the file");
      return -1;
    }
  // getting the each input and printing them out
  while( 1 )
    {
      fscanf(fp,"%s %d",student.name,&student.marks);
      printf("Student Name %s\n",student.name);
      printf("Student Marks %d\n",student.marks);
      printf("\n");
      if (feof(fp))
	break;
    }
  return 0;
}
int main()
{
  // getting user option
  char filename[50];
  printf("Enter the filename");
  scanf(" %s",filename);
  printf("What do you want to do:\n");
  printf("1. Store data\n");
  printf("2. Retrive data\n");
  int choice;
  scanf(" %d",&choice);
  switch(choice)
    {
    case 1:
       store(filename);
	break;
    case 2:
       retrive(filename);
	break;
    default:
      return -3;
    }
  return 0;
}

