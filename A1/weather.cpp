#ifndef WEATHER_CPP
#define WEATHER_CPP
#include "weather.h"
#include "otherfunc.h"
#include "city.h"
#include "cloud.h"
#include "pressure.h"

//Purpose of function: to generate and display a summary for the weather reports of each city and the probability of rain per city
//arrLength: Number of cities(cityA[]), totalCity: total number of unique cities (max cityID), totalLength: Number of cloud/pressure data points
void weatherReport(int arrLength, int totalCity, int totalLength)
{
	//Initialize vectors
	//Each city will have count of valid surrounding data points(perimeter), sum of cloud cover and pressure and city name for display purposes
	vector<int> cityCount(totalCity,0);
	vector<double> totalCloud(totalCity,0);
	vector<double> totalPressure(totalCity,0);
	vector<string> cityNames(totalCity);
	
	cout << "Weather Forecast Summary Report" << endl;
	cout << "-------------------------------" << endl;
	
	//loop through the cities and gather surrounding perimeter
	for (int i = 0; i< arrLength; i++)
	{
		for (int j = 0; j < totalLength; j++)
		{
			//check for any data point within 1 unit in any direction of the city's (x,y)
			if (abs(cityA[i].x - cloudA[j].x) <= 1 && abs(cityA[i].y- cloudA[j].y) <= 1)
			{
				//if surrounding data point is found
				int cityIndex = cityA[i].cityID - 1;
				
				//sum of cloud cover of the city including the surrounding perimeter
				totalCloud[cityIndex] += cloudA[j].cloudcover;
				//sum of pressure of the city including the surrounding perimeter
				totalPressure[cityIndex] += pressureA[j].pressure;
				//count of perimeter
				cityCount[cityIndex]++;
				//cityName for display purposes
				cityNames[cityIndex] = cityA[i].cityName;
			}
		}
	}
	
	//fix the doubles to 2 decimal point
	cout << fixed << setprecision(2);
	
	//iterate in reverse by starting with the highest cityId city
	for (int i = (totalCity-1); i >= 0 ; i--)
	{
		//if the city does not have any surrounding perimeter counted, skip
		if(cityCount[i] == 0)
		{
			continue;
		}
		
		//struct WeatherReport
		WeatherReport r;
		r.cityID = i+1;
		r.cityName = cityNames[i];
		//Average cloud cover counted by dividing sum from the number of grids the city has including the perimeter
		r.AvgCC = totalCloud[i] / cityCount[i];
		//Average pressure counted by dividing sum from the number of grids the city has including the perimeter
		r.AvgP = totalPressure[i] / cityCount[i];
		//get the symbols for the average after conversion
		r.cloudSym = sortSymbol(r.AvgCC);
		r.pressureSym = sortSymbol(r.AvgP);
		
		//Display in terminal
		cout << endl;
		cout << "City Name	; " << r.cityName << endl;
		cout << "City ID	: " << r.cityID <<endl;
		cout << "Ave. Cloud Cover	(ACC)	: " << r.AvgCC << " (" << r.cloudSym << ")" <<endl;
		cout << "Ave. Pressure		(AP)	: " << r.AvgP << " (" << r.pressureSym << ")" << endl;
		
		//generate rain probability based on the symbols of the average
		sortRainprob(r.cloudSym, r.pressureSym);
		cout << endl;
		
		
	}
}

//Purpose of function: based on the symbols for the average cloud cover and pressure, display the percentage of probability of rain and the ASCII graphics accordingly
void sortRainprob(string cloud, string pressure)
{
	if (cloud == "H")
	{
		if (pressure == "H")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 30.00" << endl;
			cout << "~~~" << endl;
			cout << "~~~~" << endl;
		}
		else if (pressure == "M")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 60.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "   \\\\" << endl;
		}
		else
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 90.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "\\\\\\\\\\"  << endl;
		}
	}
	else if (cloud == "M")
	{
		if (pressure == "H")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 20.00" << endl;
			cout << "~~" << endl;
			cout << "~~~" << endl;
		}
		else if (pressure == "M")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 50.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "    \\" << endl;
		}
		else
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 80.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << " \\\\\\\\" << endl;
		}
	}
	else
	{
		if (pressure == "H")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 10.00" << endl;
			cout << "~" << endl;
			cout << "~~" << endl;
		}
		else if (pressure == "M")
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 40.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
		}
		else
		{
			cout << endl;
			cout << "Probability of Rain (%)	: 70.00" << endl;
			cout << "~~~~" << endl;
			cout << "~~~~~" << endl;
			cout << "  \\\\\\" << endl;
		}
	}
}

#endif
