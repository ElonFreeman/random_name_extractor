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
        cout << "file open error!";
        return 1;
    }
    for(int i=0;i<62;i++)
    {
        fscanf(nameset,"%s",name_and_serial[i].name);
    }


    /*main*/
    int num_of_name=0;
    cout << "How many people do you want to extract?" << endl;
    cin >> num_of_name;
    while(!(num_of_name>0&&num_of_name<63))
    {
        cout << "Illeagally input!" << endl << "Please reinput:";
        cin >> num_of_name;
    }

    int logs[num_of_name]={};
    srand(time(NULL));  //intalize the seed for random num
    for(int i=0;i<num_of_name;i++)
    {
        int flag=0;
        /*generate random number*/
        int rand_num=rand() % 61 + 0;
        for(int j=0;j<i;j++)
        {
            if(rand_num==logs[j])
            {
                i--;
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            continue;
        }

        logs[i]=rand_num;
        /*output the name which is extracted*/
        cout << name_and_serial[rand_num].name << endl;
    }

    while(getchar() != '\n'){};  //放闪退机制
    printf("\nPress any key to kill the terminal...");
    getchar();

    return 0;
}