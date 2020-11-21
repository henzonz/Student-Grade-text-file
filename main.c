//
//  main.c
//  Assignment_1_476
//
//  Created by Henzon Zambrano on 2/6/20.
//  Copyright © 2020 Henzon Zambrano. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define amountOfStudents 7

typedef struct Students{
    char nameOfStudents[20];
    int studentNumber;
    float subjectAGrades, subjectBGrades;
}Student;

int readFile(Student[], char*, FILE*);
void obtainDiploma(Student[],FILE*);
void ascendingOrderSubjA(Student[],FILE*);
void calculateAvgDev(Student[], FILE*);



int main() {
    FILE *out;
    out = fopen("/Users/henzonzambrano/Desktop/ENGR_476_lab/lab1output.txt", "w");
    //saving data into output file
    char filePath[100];
    
    //user input
    printf("Please enter input filename: ");
    scanf("%s", filePath);
    fprintf(out,"Please enter input filename: %s\n", filePath);
    
    Student student[amountOfStudents];
    readFile(student, filePath, out);
    
    char command;
    
    while(1){
        printf("Please enter a command (enter h for help):");
        fprintf(out, "Please enter a command (enter h for help):");
        scanf("%s", &command);
        fprintf(out,"%s", &command);
        switch(command){
            case 'h':
                printf("a/1 to obtain all the students that got diploma\nb/2 to arrange subject A in ascending order\n c/3 to calculate the average and standard deviation\nd/4 to save all the above results in an output file\ne to exit\n");
                fprintf(out, "a/1 to obtain all the students that got diploma\nb/2 to arrange subject A in ascending order\n c/3 to calculate the average and standard deviation\nd/4 to save all the above results in an output file\ne to exit\n");
                break;
            case '1':
            case 'a':
                obtainDiploma(student, out);
                break;
            case '2':
            case 'b':
                ascendingOrderSubjA(student,out);
                break;
            case '3':
            case 'c':
                printf("Average/Deviation of Subjects A and B:\n");
                fprintf(out, "Average/Deviation of Subjects A and B:\n");
                calculateAvgDev(student,out);
                break;
            case '4':
            case 'd':
                fflush(out);
                break;
            case 'e':
                return 0;
            default:
                printf("Wrong command!\n");
                fprintf(out, "Wrong command!\n");
                break;
        }
        
    }
    return 0;
    
}
//function for opening and reading file
int readFile(Student studentInfo[], char* fileName, FILE *outputFile){
    FILE* file;
    char c[30];
    int counter = 0;
    //open file
    file = fopen(fileName, "r");
    //skips first line (Student name, student no., etc.)
    fscanf(file, "%s %s %s %s %s %s %s %s", c, c, c, c, c, c, c, c);
    printf("%s:\n\n", fileName);
    fprintf(outputFile, "%s:\n\n", fileName);
    //header
    printf("STUDENT NAME\tSTUDENT NO.\t\tSUBJECT A\tSUBJECT B\n");
    fprintf(outputFile, "STUDENT NAME\tSTUDENT NO.\t\tSUBJECT A\tSUBJECT B\n");
    //students' info.
    while(fscanf(file,"%s %d %f %f\n",
                 &studentInfo[counter].nameOfStudents,
                 &studentInfo[counter].studentNumber,
                 &studentInfo[counter].subjectAGrades,
                 &studentInfo[counter].subjectBGrades) != EOF){
        printf("%-12s\t%d\t\t\t\t%0.1f\t\t%0.1f\n",
               studentInfo[counter].nameOfStudents, studentInfo[counter].studentNumber, studentInfo[counter].subjectAGrades, studentInfo[counter].subjectBGrades);
        fprintf(outputFile, "%-12s\t%d\t\t\t\t%0.1f\t\t%0.1f\n",
                studentInfo[counter].nameOfStudents, studentInfo[counter].studentNumber, studentInfo[counter].subjectAGrades, studentInfo[counter].subjectBGrades);
        counter++;
    }
    fclose(file);
    printf("\n");
    fprintf(outputFile, "\n");
    return 1;
}
//function for obtaining diploma
void obtainDiploma(Student student[], FILE *outputFile){
    printf("All the students that obtained diploma:\n");
    fprintf(outputFile, "All the students that obtained diploma:\n");
    printf("STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    fprintf(outputFile, "STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    for(int i = 0; i < amountOfStudents; i++){
        if(student[i].subjectAGrades >= 50 && student[i].subjectBGrades >= 50){
            printf("%-12s\t%0.1f\t\t%0.1f\n", student[i].nameOfStudents, student[i].subjectAGrades, student[i].subjectBGrades);
            fprintf(outputFile, "%-12s\t\t\t\t%0.1f\t\t%0.1f\n", student[i].nameOfStudents, student[i].subjectAGrades, student[i].subjectBGrades);
        }
    }
    printf("\n");
    fprintf(outputFile, "\n");
}

void ascendingOrderSubjA(Student student[], FILE *outputFile){
    //need temp array
    Student temp[amountOfStudents];
    
    
    printf("Subject A in ascending order\n");
    fprintf(outputFile, "Subject A in ascending order\n");
    printf("STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    fprintf(outputFile, "STUDENT NAME\tSUBJECT A\tSUBJECT B\n");
    
    //copy array of original student array
    for (int i = 0; i < amountOfStudents; i++){
        temp[i] = student[i];
    }
    
    for(int i = 0; i < amountOfStudents; i++){
        for(int j = i + 1; j < amountOfStudents; j++){
            if(temp[i].subjectAGrades > temp[j].subjectAGrades){
                Student ascendingOrderSubjA = temp[i];
                temp[i] = temp[j];
                temp[j] = ascendingOrderSubjA;
            }
        }
    }
    for(int i = 0; i < amountOfStudents; i++){
        printf("%-12s\t%0.1f\t\t%0.1f\n", temp[i].nameOfStudents, temp[i].subjectAGrades, temp[i].subjectBGrades);
        fprintf(outputFile, "%-12s\t\t\t\t%0.1f\t\t%0.1f\n", temp[i].nameOfStudents, temp[i].subjectAGrades, temp[i].subjectBGrades);
    }
    printf("\n");
    fprintf(outputFile, "\n");
}

void calculateAvgDev(Student student[], FILE *outputFile){
    float avgA = 0, avgB = 0, devA = 0, devB = 0;
    //avg.
    for(int i = 0; i < amountOfStudents; i++){
        avgA += student[i].subjectAGrades;
        avgB += student[i].subjectBGrades;
    }
    avgA = avgA / amountOfStudents;
    avgB = avgB / amountOfStudents;
    
    printf("Average of subject A: %0.1f\nAverage of subject B: %0.1f\n", avgA, avgB);
    fprintf(outputFile, "Average of subject A: %0.1f\nAverage of subject B: %0.1f\n", avgA, avgB);
    
    //dev.
    for(int i = 0; i< amountOfStudents; i++){
        devA += pow(student[i].subjectAGrades - avgA, 2);
        devB += pow(student[i].subjectBGrades - avgB, 2);
    }
    devA = sqrtf(devA/amountOfStudents);
    devB = sqrtf(devB/amountOfStudents);
    
    printf("Standard deviation of Subject A: %0.1f\nStandard deviation of Subject B: %0.1f\n\n", devA, devB);
    fprintf(outputFile, "Standard deviation of Subject A: %0.1f\nStandard deviation of Subject B: %0.1f\n\n", devA, devB);
}

// /Users/henzonzambrano/Desktop/ENGR_476_lab/lab1.txt
