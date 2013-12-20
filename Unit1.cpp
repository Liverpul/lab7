//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define SIGN "Vou"

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
    if(argc!=3)                             //Проверка наличия параметров
    {
        printf("%s","Error, enter name of file in parametrs") ;
        getch();
        return 0;
    }

    FILE *f=fopen(argv[1],"rt");            //Открытие файла для чтения
    if(!f)                                  //Проверка сущестования файла
    {
        printf("Error!") ;
        return 0;
    }

    char *p = strtok(argv[1],".");         //Разбиваем имя файла до точки
    strcat(argv[1], ".idx");               //Склеивает имя файла, переделывая разрешение
    FILE *fk=fopen(argv[1],"wt");          //Открываем файл для записи
    if(!fk)                                //Проверка существования файла
    {
        printf("Error!") ;
        return 0;
    }

    int i=0;
    char str[256];
    int seek=0;
    fwrite(SIGN,sizeof(char),4,fk);             //Запись сигнатуры

    for(;;)					 					//Запись в бинарный файл
    {
        seek=ftell(f);                           //В переменной seek присваивается значение текущего указателя в f
        if (fgets(str,256,f) == NULL) break;
        i++;                                     
        fwrite(&seek,sizeof(int),1,fk);			//Записываем кол-во байт в бинарный файл
    }
    fclose(fk);

    char str1[256];
    int x=atoi(argv[2]);                         //Конвертируем строку в число
    if (x>i)                                    //Проверка существования строки
    {
        printf("Error! String don't exist");
        getch();            return 0;
    }

    char b[4];
    fk=fopen(argv[1],"rt");
    fread (b, sizeof(char), 4, fk);
    fseek(fk,4,SEEK_SET);
    if (strcmp(b,SIGN)!=0)                       //Проверка сигнатуры файла
    {
        printf("%s","That`11 isn't my file") ;
        getch();
        return 0;
    }

    int a;
    fseek(fk,(x-1)*4,SEEK_CUR);
    fread(&a, sizeof(int), 1, fk);             //Считывает данные

    fseek(f,a,SEEK_SET);                       //Устанавливает указатель на а элементов от начала файла
    fgets(str1,256,f);                         //Считываем строку
    printf("%s",str1);                         //Выводим строку
    getch();
    fclose(f);
    fclose(fk);                                //Закрываем файлы
}
//---------------------------------------------------------------------------
