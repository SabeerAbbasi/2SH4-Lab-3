#include <stdio.h>
#include <stdlib.h>
#include "Questions.h"



student **create_class_list(char *filename, int *sizePtr){
	
		student **class_list;
		FILE *file;
		file = fopen(filename, "r");

		//finds the number of students in the list
		fscanf(file, "%d", sizePtr);

		//creating an array that will hold the array of students
		class_list = (student **)calloc(*sizePtr, sizeof(student *));

		for (int i = 0; i < *sizePtr; i++)
		{
			//creates an array for a student and inputs their student id, first name and last name
			class_list[i] = (student *)calloc(1, sizeof(student));
			fscanf(file, "%d %s %s", &class_list[i]->student_id, class_list[i]->first_name, class_list[i]->last_name);
		}

		fclose(file);

	/* finally return the created class list*/
	return class_list;
}


int find(int idNo, student **list, int size){

		//Iterates through the list of students to find unique student ID, and returns the position of said student
		for (int x = 0; x < size; x++)
		{
			if (list[x]->student_id == idNo)
				return x;
		}

		//if no student is found then returns -1
	return -1;
}

void input_grades(char *filename, student **list, int size)
{

		//declaring file and opening it for reading
		FILE *grades;
		grades = fopen(filename, "r");

		int ID_num, location;

		//reads through file until end is reached
		while (fscanf(grades, "%d", &ID_num) != EOF){
			//finding position of student using their ID with find()
			location = find(ID_num, list, size);
			//assigns students their project one and two grade
			fscanf(grades, "%d %d", &list[location]->project1_grade, &list[location]->project2_grade);
		}

		fclose(grades);

}

void compute_final_course_grades(student **list, int size)
{

		//computes final course mark by averaging project 1 and 2 grades then adding it to their array
		for (int i = 0; i < size; i++){
			list[i]->final_grade = (list[i]->project1_grade + list[i]->project2_grade) / 2.0;
		}
}

void output_final_course_grades(char *filename, student **list, int size)
{
	
		//declaring file and opening it for writing
		FILE *output;
		output = fopen(filename, "w");

		//total number of students
		fprintf(output, "%d \n", size);

		//prints out the student ID and final grade on a line for each student
		for (int i = 0; i < size; i++)
		{
			fprintf(output, "%d %.2f \n", list[i]->student_id, list[i]->final_grade);
		}

		fclose(output);
}


void withdraw(int idNo, student **list, int* sizePtr)
{
		//initializing variables
		int x;
	    int counter = 0;

	    //checking if student id is in list
	    for (x = 0; x < *sizePtr; x++)
	    {
	        if (list[x]->student_id == idNo)
	        {
	        	//if student id is found then counter is assigned the value of 1
	            counter=1;
	            break;
	        }
	    }

	    if (counter)
	    {
	    	//frees position x
	        free(list[x]);
	        //shifts all students 1 position to the left
	        for (x = x + 1; x < *sizePtr; x++)
	        {
	            list[x - 1] = list[x];
	        }
	        //decreases class size by 1
	        (*sizePtr) = (*sizePtr) - 1;
	    }
	    else
	    {
	    	//prints an error message if student id is not found
	        printf("Specified student ID : %d was not found in the list\n", idNo);
	    }

}

void destroy_list(student **list, int *sizePtr)
{

		//clearing all students info
		for (int i = 0; i < *sizePtr; i++)
			free(list[i]);

		//clearing class
		free(list);

		//sets class size to 0
		*sizePtr = 0;
}

int mainfunc()
{
	//main function utilizing all functions
    int size;

    student **student_list;

    student_list = create_class_list("students.txt", &size);

    find(3000, student_list, 6);

    input_grades("grades.txt", student_list, size);

    compute_final_course_grades(student_list, size);

    output_final_course_grades("final.txt", student_list, size);

    //uses withdraw three times, twice for successful withdrawals and once for a unsuccessful withdrawal
    withdraw(2000, student_list, &size);
    withdraw(6547, student_list, &size);
    withdraw(7000, student_list, &size);

    destroy_list(student_list, &size);
    return 0;
}
