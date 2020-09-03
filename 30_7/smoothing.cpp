#include<iostream>
#include<stdlib.h>
#include<ctime>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand((unsigned) time(0));
    int array[100];
    for(int i=0;i<100;i++)
    {
        array[i]=(rand() % 100) + 1;
//        cout<<i<<": "<<array[i]<<endl;
    }
    sort(array,array+100);
    for(int i=0;i<100;i++)
    {
        cout<<i+1<<": "<<array[i]<<"\t";
    }
//Mean------------------------------------------
    float mean = 0;
    float sum = 0;
    for(int i=0;i<100;i++)
    {
        sum += array[i];
    }
    mean = sum/100;
//Median----------------------------------------
    int n1 = array[50];
    int n2 = array[51];
    float median = (n1+n2)/2;
//mode------------------------------------------
    int maxi = array[99] + 1;
    int count[maxi];
//      cout<<"max="<<maxi;
    for (int i = 0; i < maxi; i++)
        count[i] = 0;
    for (int i = 0; i < 100; i++)
        count[array[i]]++;
    int mode = 0;
    int k = count[0];
    for (int i = 0; i < maxi; i++)
    {
        if (count[i] > k)
        {
            k = count[i];
            mode = i;
        }
    }
//range-----------------------------------------
    maxi = array[99];
    int mini = array[0];
    int range = maxi - mini;
//S.Deviation-------------------------------------
    float SD = 0.0;
    for(int i = 0; i < 100; ++i)
        SD += pow(array[i] - mean, 2);
    float variance = SD;
    SD = sqrt(SD/100);
//-------------------------

    cout<<"\n\nmean= "<<mean<<endl;
    cout<<"median= "<<median<<endl;
    cout<<"mode= "<<mode<<endl;
    cout<<"variance= "<<variance<<endl;
    cout<<"SD= "<<SD;
    return 0;
}
