#include <stdio.h>
#include "functions.h"

bool checkCPF(char name[], char cpf[], char password[])
{
    FILE *managersPtr;
    char currentCpf[12], currentName[strlen(name)], currentPassword[strlen(password)];    
    if ((managersPtr = fopen("gerentes.txt", "r"))==NULL)
    {
        printf("Não foi possivel acessar o Banco de gerentes!");
    }
    else
    {     
        while((fscanf(managersPtr,"%s|%s|%s",currentName,currentCpf,currentPassword))==3)
        {
            if(strcmp(cpf,currentCpf) == 0)
                {
                fclose(managersPtr);                
                return 0;
                }
        }
    }
    fclose(managersPtr);
    return 1;
}

void addGerente(char name[], char cpf[], char password[])
{
    FILE *managersPtr;
    if ((managersPtr = fopen("gerentes.txt", "a"))==NULL)
    {
        printf("Não foi possivel acessar o Banco de gerentes!");
    }
    else
    {   
        if (checkCPF(cpf) == false)
            printf("Esse Gerente já está cadastrado no sistema");
        else
        fprintf(managersPtr,"%s|%s|%s\n",name,cpf,password);
    }
    fclose(managersPtr);
}