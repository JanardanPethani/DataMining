#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include<bits/stdc++.h>
#include <algorithm>
#include <math.h>
using namespace std;

int power(float num)
{
    int cou=0;
    while(num>1){
        num /= 10;
        cou++;
    }
    return cou;
}


int main(){
    string road,air,temp,line;
    vector<float> roadT;
	vector<float> airT;
    vector<float> roadTM;
	vector<float> airTM;
    vector<float> roadTZ;
	vector<float> airTZ;
    vector<float> roadTD;
	vector<float> airTD;

	int i,powOften_road,powOften_air = 0;
	float roadTmax,roadTmin,airTmax,airTmin,roadSD,airSD = 0;

	ifstream coeff("weather.csv");

//save data in vector formate
	if (coeff.is_open()) //if the file is open
	{
		//ignore first line
		string line;
		getline(coeff, line);

		while (!coeff.eof())
		{
			getline(coeff, temp, ',');getline(coeff, temp, ',');
			getline(coeff, temp, ',');getline(coeff, temp, ',');
			getline(coeff, temp, ',');getline(coeff, temp, ',');
			getline(coeff, road, ',');
			roadT.push_back(stof(road));
			getline(coeff, air, '\n');
			airT.push_back(stof(air));

			i += 1;
		}
		coeff.close();
		cout << "Number of lines: " << i-1 << endl;
	}
	else{
        cout << "Unable to open file"<<endl;
	}

//Min-Max normalization
    roadTmax = *max_element(roadT.begin(), roadT.end());
    roadTmin = *min_element(roadT.begin(), roadT.end());
    for (auto& data : roadT) {
            roadTM.push_back(((data - roadTmin)/(roadTmax-roadTmin))*(1-0)*(1));
    }

    airTmax = *max_element(airT.begin(), airT.end());
    airTmin = *min_element(airT.begin(), airT.end());
    for (auto& data : airT) {
            airTM.push_back(((data- airTmin)/(airTmax-airTmin))*(1-0)*(1));
    }

//decimal
    if (abs(roadTmax)>abs(roadTmin)){
            powOften_road = power(abs(roadTmax));
    }
    else{
            powOften_road = power(abs(roadTmin));
    }

    if (abs(airTmax)>abs(airTmin)){
            powOften_air = power(abs(airTmax));
    }
    else{
            powOften_air = power(abs(airTmin));
    }

    for (auto& data : roadT) {
            roadTD.push_back(data/pow(10,powOften_road));
    }
    for (auto& data : airT) {
            airTD.push_back(data/pow(10,powOften_air));
    }

//Z-score
    float roadAvg = accumulate( roadT.begin(), roadT.end(), 0.0)/roadT.size();
    float airAvg = accumulate( airT.begin(), airT.end(), 0.0)/airT.size();

    for(int i = 0; i < roadT.size(); ++i)
    {
         roadSD+= pow(roadT[i] - roadAvg, 2);
         airSD+= pow(airT[i] - airAvg, 2);
    }
    roadSD/=roadT.size();
    airSD/=airT.size();

    for(int i=0;i<roadT.size();i++)
    {
        roadTZ.push_back((roadT[i]-roadAvg)/sqrt(roadSD));
        airTZ.push_back((airT[i]-airAvg)/sqrt(airSD));
    }


//give output to file
    ifstream inFile;
    inFile.open("weather.csv");
    ofstream outfile;
    outfile.open("Output.csv");
    getline(inFile,line);
    line=line+",RoadTempMin-max,AirTempMin-Max,RoadTempZ,AirTempZ,RoadTempDec,AirTempDec\n";
    outfile<<line;
    int k=0;
    while(getline(inFile,line))
    {
        line=line+","+to_string(roadTM[k])+","+to_string(airTM[k])+","+to_string(roadTZ[k])+","+to_string(airTZ[k])+","+to_string(roadTD[k])+","+to_string(airTD[k])+"\n";
        k++;
        outfile<<line;
    }
    return 0;




}


