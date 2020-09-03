#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <cstring>
#include <string>
using namespace std;

int main()
{
    ifstream ifs;
    string line;
    ifs.open("road-weather-information-stations_Final.csv");
    getline(ifs,line);
    cout<<line<<"\n";
    int i =0;
    float surf[8000],air[8000];
    while(i<8000){
        getline(ifs,line);
        int n = line.length();
        char str[n+1];

        strcpy(str, line.c_str());

        char *token = strtok(str, ",");
        int j=0;
        while (token != NULL)
        {
            token = strtok(NULL, ",");
            if(j == 5){
                surf[i] = atof(token);
            }
            if(j == 6){
                air[i] = atof(token);
            }
            j++;
        }
        i++;
    }
    ifs.close();

    //Min-Max Normalization
    float maxRoad,maxAir,minRoad,minAir;
    maxRoad = surf[0];
    minRoad =  surf[0];
    maxAir,minAir = air[0];
    for(int i=1;i<8000;i++){
        if(surf[i]>maxRoad)
            maxRoad = surf[i];
        if(air[i]>maxAir)
            maxAir = air[i];
        if(surf[i]<minRoad)
            minRoad = surf[i];
        if(air[i]<minAir)
            minAir = air[i];
    }

    float mmsurf[8000],mmair[8000];
    float sums,suma =0;
    for(int i=0;i<8000;i++){
        sums+= surf[i];
        suma+= air[i];
        mmsurf[i] = (surf[i]-minRoad)/(maxRoad-minRoad);
        mmair[i] = (air[i]-minRoad)/(maxAir-minAir);
    }

    //Z-score Normalization
    float means = sums/8000;
    float meana = suma/8000;
    sums = 0;suma = 0;
    for(int i=0;i<8000;i++){
        sums+= (surf[i]-means)*(surf[i]-means);
        suma+= (air[i]-meana)*(air[i]-meana);
    }
    float sds = sqrt(sums/8000),sda = sqrt(suma/8000);
    float zsurf[8000],zair[8000];
    for(int i=0;i<8000;i++){
        zsurf[i]= (surf[i]-means)/sds;
        zair[i]= (air[i]-meana)/sda;
    }

    //Decimal scaling Normalization
    int temp1 = log10(maxRoad)+1;
    int temp2 = log10(maxAir)+1;
    int a[100];
    float dssurf[8000],dsair[8000];

    for(int i=0;i<8000;i++){
        dssurf[i]= surf[i]/pow(10,temp1);
        dsair[i]= air[i]/pow(10,temp2);
    }

    ofstream ofs;
    ofs.open("output.csv",ios::out);
    ofs<<"MinMaxNormalization,, Z-ScoreNormalization,, DecimalScalingNormalization\n";
    ofs<<"RoadSurfaceTemperature, AirTemperature, RoadSurfaceTemperature, AirTemperature, RoadSurfaceTemperature, AirTemperature\n";

    for(int i=0;i<8000;i++){
        ofs<<mmsurf[i]<<","<<mmair[i]<<","<<zsurf[i]<<","<<zair[i]<<","<<dssurf[i]<<","<<dsair[i]<<"\n";
    }
    cout<<"File created"<<endl;
    ofs.close();
}
