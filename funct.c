#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "structs.h"
#include <string.h>
#include <locale.h>

//FUNÇÕES ALUNOS.

Student* get_students()
{
    FILE *alunosFilePtr;
    Student* arrayAlunos = NULL;
    Student* lastStudent = NULL;
    char currentName[100], currentMatricula[10];
    float currentNota;

    if ((alunosFilePtr = fopen("studentsData.dat", "r")) == NULL)
    {
        printf("Não foi possível acessar os dados dos alunos!\n");
    }
    else
    {
        while (fscanf(alunosFilePtr, "%s %s %f", currentName, currentMatricula, &currentNota) == 3)
        {
            Student* newStudent = (Student*)malloc(sizeof(Student));
            newStudent->nextStudent = NULL;

            strcpy(newStudent->name, currentName);
            strcpy(newStudent->matricula, currentMatricula);

            newStudent->nota = currentNota;

            if (arrayAlunos == NULL)
            {
                arrayAlunos = newStudent;
                lastStudent = newStudent;
            }
            else
            {
                lastStudent->nextStudent = newStudent;
                lastStudent = newStudent;
            }
        }
        fclose(alunosFilePtr);
    }

    return arrayAlunos;
}


void update_Students(Student *studentsArray)
{
    FILE *alunosfilePtr;
    Student* currentStudent = studentsArray;

    if ((alunosfilePtr = fopen("studentsData.dat", "w")) == NULL)
    {
        printf("Não foi possivel acessar os dados dos alunos!\n");
    }
    else
    {
        while (currentStudent != NULL) 
        {
            fprintf(alunosfilePtr,"%s %s %.2f\n", currentStudent->name, currentStudent->matricula, currentStudent->nota);
            currentStudent = currentStudent->nextStudent;
        }
        fclose(alunosfilePtr);
    }
    
}

Student* addAluno(char novoName[], char newMat[], float novaNota, Student* arrayAlunos)
{
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->nextStudent = NULL;

    strcpy(newStudent->name, novoName);
    strcpy(newStudent->matricula, newMat);
    newStudent->nota = novaNota;
    
    if(arrayAlunos == NULL)
    {
        arrayAlunos = newStudent;
    }
    
    else
    {
        Student *currentStudent = arrayAlunos;
        while(currentStudent != NULL)
        {
            if(currentStudent->nextStudent == NULL)
                {
                    currentStudent -> nextStudent = newStudent;
                    update_Students(arrayAlunos);
                    return arrayAlunos;
                }
                
            currentStudent = currentStudent->nextStudent;
        }
    }    
    update_Students(arrayAlunos);
    return arrayAlunos;
}




//FUNÇÕES DE PROFESSORES

Teacher* get_Teachers()
{
    FILE *teacherFilePtr;
    Teacher *arrayTeacher = NULL;
    Teacher *lastTeacher = NULL;
    char currentCpf[12], currentName[100], currentPassword[50];

    if ((teacherFilePtr = fopen("teachers.dat", "r")) == NULL)
    {
        printf("Não foi possível acessar o Banco de Professores!\n");
    }
    else
    {
        while (fscanf(teacherFilePtr, "%s %s %s", currentName, currentCpf, currentPassword) == 3)
        {
            Teacher *newTeacher = (Teacher*)malloc(sizeof(Teacher));
            newTeacher->nextTeacher = NULL;

            strcpy(newTeacher->name, currentName);
            strcpy(newTeacher->cpf, currentCpf);
            strcpy(newTeacher->password, currentPassword);

            if (arrayTeacher == NULL)
            {
                arrayTeacher = newTeacher;
                lastTeacher = newTeacher;
            }
            else
            {
                lastTeacher->nextTeacher = newTeacher;
                lastTeacher = newTeacher;
            }
        }
        fclose(teacherFilePtr);
    }
    return arrayTeacher;
}

void update_Teachers(Teacher *teachesArray)
{
    FILE *teacherFilePtr;
    Teacher* currentTeacher = teachesArray;

    if ((teacherFilePtr = fopen("teachers.dat", "w")) == NULL)
    {
        printf("Não foi possivel acessar os dados dos professores!\n");
    }
    else
    {
        while (currentTeacher != NULL) 
        {
            fprintf(teacherFilePtr,"%s %s %s\n", currentTeacher->name, currentTeacher->cpf, currentTeacher->password);
            currentTeacher = currentTeacher->nextTeacher;
        }
        fclose(teacherFilePtr);
    }
    
}

bool checkCPF(Teacher *arrayTeachers, char cpf[])
{
    char currentCpf[12];
    Teacher* currentTeacher = arrayTeachers;

    while (currentTeacher != NULL) 
    {
        strcpy(currentCpf, currentTeacher->cpf);
        if(strcmp(currentCpf,cpf)==0)
                return true;
        else
            currentTeacher = currentTeacher->nextTeacher;
    }

    return false;
}

Teacher* addTeacher(char name[], char cpf[], char password[], Teacher *arrayTeachers)
{
    if (checkCPF(arrayTeachers, cpf) == true)
    {
        printf("RELATORIO DE ERRO:\n");
        printf("    # Esse professor já está cadastrado no sistema.\n    FAÇA O LOGIN!\n");
        
        return arrayTeachers; 
    }
    else
    {   
        printf("ENTROU NO ELSE\n");
        Teacher *newTeacher = (Teacher*)malloc(sizeof(Teacher));
        newTeacher->nextTeacher = NULL;
        printf("CRIOU O 'NEWTEACHER'\n");

        strcpy(newTeacher->name, name);
        strcpy(newTeacher->cpf, cpf);
        strcpy(newTeacher->password, password);
        printf("ADICIONOU VALORES A ELE\n");


        if (arrayTeachers == NULL)
        {
           arrayTeachers = newTeacher;
        }
        else
        {
            Teacher *currentTeacher = arrayTeachers;
            while (currentTeacher != NULL)
            {
                printf("AINDA NÃO É O ULTIMO\n");
                if(currentTeacher->nextTeacher == NULL)
                {
                    currentTeacher -> nextTeacher = newTeacher;
                    update_Teachers(arrayTeachers);
                    return arrayTeachers;
                }
                
                currentTeacher = currentTeacher->nextTeacher;
            }
 
        }  
    }

}

bool loginTeacher(char cpf[], char password[])
{
    FILE *teacherPtr;
    char currentCpf[12], currentName[100], currentPassword[50];
    if ((teacherPtr = fopen("teachers.dat", "r")) == NULL)
    {
        printf("Não foi possivel acessar o Banco de Professores!");
    }
    else
    {
        while (!feof(teacherPtr))
        {
            fscanf(teacherPtr, "%s %s %s\n", currentName, currentCpf, currentPassword);
            if (strcmp(cpf, currentCpf) == 0 && strcmp(password, currentPassword) == 0)
            {
                fclose(teacherPtr);
                return true;
            }
            else if (strcmp(cpf, currentCpf) == 0 && strcmp(password, currentPassword) != 0)
            {
                return false;
            }
            else if (strcmp(cpf, currentCpf) != 0 && strcmp(password, currentPassword) == 0)
            {
                return NULL;
            }
        }
        fclose(teacherPtr);
    }
}

bool validatePassword(char password[])
{
    int has_digit = 0, has_upper = 0, has_lower = 0, has_space = 0;
    for (int i = 0; i < strlen(password); i++)
    {
        if (isdigit(password[i]))
        {
            has_digit++;
        }
        else if (isupper(password[i]))
        {
            has_upper++;
        }
        else if (islower(password[i]))
        {
            has_lower++;
        }
        else if (isspace(password[i]))
        {
            has_space++;
        }
    }
    if (strlen(password) < 8)
    {
        printf("Senha Inválida!\nTamanho mínimo da senha: 8\n");
        return false;
    }
    else if (has_digit == 0)
    {
        printf("Senha Inválida!\nA senha não possui digitos\n");
        return false;
    }
    else if (has_upper == 0)
    {
        printf("Senha Inválida!\nA senha não possui caracteres maiusculos\n");
        return false;
    }
    else if (has_lower == 0)
    {
        printf("Senha Inválida!\nA senha não possui caracteres minusculos\n");
        return false;
    }
    else if (has_space != 0)
    {
        printf("Senha Inválida!\nA senha não pode possuir espaços\n");
        return false;
    }
    else
        printf("Senha válida\n");
    return true;
}

bool validateCpf(char cpf[])
{
    setlocale(LC_ALL, "");
    int notDigit = 0;
    for (int i = 0; i < 11; i++)
    {
        if (!isdigit(cpf[i]))
        {
            notDigit++;
        }
    }
    if (strlen(cpf) != 11)
    {
        printf("DIGITE UM CPF VÁLIDO, COM 11 DIGITOS!");
        return false;
    }
    else if (notDigit != 0)
    {
        printf("DIGITE UM CPF VÁLIDO, APENAS NÚMEROS!");
        return false;
    }
    return true;
}