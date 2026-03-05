#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
using namespace std;

int how_many_stu=0;
struct names
{
    int serial;
    char name[30];
};


int dataset_preprocess(names *name_and_serial)
{
    /*generate  the serial*/
    for(int i=0;i<how_many_stu;i++)
    {
        (name_and_serial+i)->serial=i;
    }

    /*read the namesheet and input the names*/
    FILE *nameset=fopen("names.txt","r");
    if(nameset==nullptr)
    {
        cout << "File open error!";
        return 1;
    }
    for(int i=0;i<how_many_stu;i++)
    {
        if(fscanf(nameset,"%s",(name_and_serial+i)->name)==EOF)
        {
            cout << "The number of student is error,please check and reinput:";
            return 1;
        }
    }

    return 0;
}

int check_dupli_item(int *logs,int rand_num,int i)
{
    int flag=0;
    for(int j=0;j<i;j++)
    {
        if(rand_num==*(logs+j))
        {
            flag=1;
            break;
        }
    }

    return flag;
}

int main(void)
{
    /*solve the garbled text,tell the sys that use utf-8 to process all of the things*/
    SetConsoleOutputCP(CP_UTF8);

    {   /*welcome infos*/
        cout <<endl;
        cout << "==============================================================================" <<endl;
        cout << "*                                 Welcome!                                   *" <<endl;
        cout << "*                         This is a name extractor.                          *" <<endl;
        cout << "*                         By: ElonFreeman(zhanghao)                          *" <<endl;
        cout << "*               My_Github_home_page:https://github.com/ElonFreeman           *" <<endl;
        cout << "*                               version:v1.0                                 *" <<endl;
        cout << "*    Project adress:https://github.com/ElonFreeman/random_name_extractor     *" <<endl;
        cout << "==============================================================================" <<endl;
        cout <<endl;
    }

    cout << "How many students in your class:";
    cin >> how_many_stu;
    names name_and_serial[how_many_stu]={};
    int status=0;
    status=dataset_preprocess(name_and_serial);
    while(status==1)
    {
        cin >> how_many_stu;
        name_and_serial[how_many_stu]={};
        status=dataset_preprocess(name_and_serial);
    }
    

    /*user options*/
    int num_of_name=0;
    cout << "How many people do you want to extract:";
    cin >> num_of_name,cout << endl;
    while(!(num_of_name>0&&num_of_name<(how_many_stu+1)))
    {
        cout << "Illeagally input!" << endl << "Please reinput:";
        cin >> num_of_name,cout << endl;
    }

    int logs[num_of_name]={};  //antiduplicate logs
    srand(time(NULL));  //intalize the seed for random num
    for(int i=0;i<num_of_name;i++)
    {
        /*generate the random number*/
        int rand_num=rand()%(how_many_stu-1)+0;

        /*check the duplicate items*/
        int flag=check_dupli_item(logs,rand_num,i);
        if(flag==1)
        {
            i--;
            continue;
        }
        logs[i]=rand_num;

        /*output the name which is extracted*/
        cout << name_and_serial[rand_num].name << endl;
    }

    {
        /*anticrash machanism*/
        while(getchar() != '\n'){};
        printf("\nPress any key to kill the terminal...");
        getchar();
    }

    return 0;
}