#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct names
{
    int serial;
    char name[30];
};

int main(void)
{
    /*generate  the serial*/
    names name_and_serial[62]={};
    for(int i=0;i<62;i++)
    {
        name_and_serial[i].serial=i;
    }

    /*read the namesheet and input the names*/
    FILE *nameset=fopen("names.txt","r");
    if(nameset==nullptr)
    {
        cout << "something error!";
        return 1;
    }
    for(int i=0;i<62;i++)
    {
        fscanf(nameset,"%s",name_and_serial[i].name);
    }

    /*generate random number*/
    srand(time(NULL));
    int rand_num=rand() % 61 + 0;

    /*output the name which is extracted*/
    cout << name_and_serial[rand_num].name;

    return 0;
}