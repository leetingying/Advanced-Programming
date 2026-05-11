#include "otherfunc.h"
#include "city.h"
#include "cloud.h"
#include "pressure.h"
#include "weather.h"

using namespace std;

//global variables to store configuration values read from the config file
string gridXrange, gridYrange, cityfile, cloudfile, pressurefile;

int main()
{
	//flag to track if the data is loaded
	bool isDataLoaded = false;
	string config;
	string choice;
	int option = 0;
	string errormsg;
	int xMax = 0;
	int yMax = 0;
	
	//StudentID and Student_name variable
	string student_id = "8551741";
	string student_name = "Lee Ting Ying";
	
	//list of options in the display menu
	string mainmenulist[] = {"Read in and process a configuration file" ,
								 "Display city map",
								 "Display cloud coverage map (cloudiness index)",
								 "Display cloud coverage map (LMH symbols)",
								 "Display atmospheric pressure map (pressure index)",
								 "Display atmospheric pressure map (LMH symbols)",
								 "Show weather forecast summary report",
								 "Quit"
							};
	
	do
	{
		cout << endl;
		cout << "Student ID : " << student_id <<endl;
		cout << "Student Name : " << student_name << endl;
		cout << "---------------------------------" << endl;
		cout << "Welcome to Weather Information Processing System!" << endl;
		int mainmenuSize = sizeof(mainmenulist) / sizeof(mainmenulist[0]);
		
		//Printing display of the menu
		for (int i = 0; i < mainmenuSize; i++)
		{
			cout << i+1 << ")	" << mainmenulist[i] << endl;
		}
		cout << endl;
		
		if(!errormsg.empty())
		{
			cout << errormsg << endl;
			errormsg.clear();
		}
		
		cout << "Please enter your choice :" ;
		//get the user input choice
		getline(cin, choice);
		cout << endl;
		
		//ensures that the choice is not empty, only single digit input and only numbers from 1-8 is allowed
		if (!choice.empty() && choice.length() == 1 && isdigit(choice[0])) {
			
			option = choice[0] - '0';
			if (option < 1 || option > 8) {
				errormsg = "Invalid input. Please enter a digit between 1 and 8.";
				continue;
			}
		} else {
			errormsg = "Invalid input. Please enter a single digit only.";
			continue;
		}
		
		//if user tries to choose 2-7 without laoding config, they will be blocked
		if(option >= 2 && option <= 7 && !isDataLoaded)
			{
				cout << "Please load data first using the first option" << endl;
				Freeze();
				continue;
			}
			
		
		switch (option)
		{
			case 1: 
			{
				cout << "[" << mainmenulist[option - 1] << "]" << endl;
				cout << "Please enter a config filename : ";
				//get the user input file
				getline(cin, config);
				cout << endl;

				if (config.empty()) {
					cout << "Empty config file input" << endl;
					Freeze();
					break;
				}

				string line;
				int linecount = 0;
				// clean the lines in the file one at a time by removing any leading and trailing white spaces, tabs,and newlines, remove any empty lines at the end and write the cleaned lines back into the file
				cleanFile(config);  

				ifstream configData(config);

				if (configData.is_open()) {
					while (getline(configData, line)) {
						line = trim(line);
						if (line.empty() || line.substr(0, 2) == "//") {
						    continue;
						}

						size_t fline = line.find('=');
						if (fline != string::npos) {
						    string key = trim(line.substr(0, fline));
						    string value = trim(line.substr(fline + 1));
							
							//Parsing of data from files to global variabkes
						    if (key == "GridX_IdxRange") {
						        gridXrange = value;
						    } else if (key == "GridY_IdxRange") {
						        gridYrange = value;
						    } else {
						        cerr << "Warning: Unknown config key: " << key << endl;
						    }
						} else if (line.find(".txt") != string::npos) {
						    switch (linecount) {
						        case 0: cityfile = line; break;
						        case 1: cloudfile = line; break;
						        case 2: pressurefile = line; break;
						        default:
						            cerr << "Warning: Extra file ignored in config: " << line << endl;
						            break;
						    }
						    linecount++;
						}
					}
					configData.close();

					// Get max X and Y for city coordinates
					string citylastline = readLastNonEmpty(cityfile);
					//First split the line by "-" 
					//will get [0] = [x, y], [1] = cityID, [2] = cityName
					vector<string> lastlinesplit = tokenizeString(citylastline, "-");
					if (lastlinesplit.empty()) {
						cerr << "Error: last line of city file is empty or invalid" << endl;
						break;
					}
					//to check if the size of the split, if it is less than 3, there is input missing
					if (lastlinesplit.size() < 3) {
						cerr << "Invalid line format: " << line << endl;
						continue;
					}
					
					//Second split by ","
					//will get [0] = [x and [1] = y]
					vector<string> coordsplit = tokenizeString(lastlinesplit[0], ",");
					//if this split is less than 2, the format is wron
					if (coordsplit.size() != 2) {
						cerr << "Error: Invalid city coordinate format: " << lastlinesplit[0] << endl;
						break;
					}

					// Clean brackets
					if (!coordsplit[0].empty() && coordsplit[0][0] == '[')
						coordsplit[0].erase(coordsplit[0].begin());

					if (!coordsplit[1].empty() && coordsplit[1].back() == ']')
						coordsplit[1].pop_back();

					// Grid parsing
					vector<string> xValues = tokenizeString(gridXrange, "-");
					vector<string> yValues = tokenizeString(gridYrange, "-");

					if (xValues.size() < 2 || yValues.size() < 2) {
						cerr << "Invalid grid range format in config." << endl;
						break;
					}

					try {
						int cityX = stoi(coordsplit[0]);
						int cityY = stoi(coordsplit[1]);
						int gridXMax = stoi(xValues[1]);
						int gridYMax = stoi(yValues[1]);
						
						//comparing if the city x and y value is bigger than the grid max x and y value
						if (cityX > gridXMax && cityY > gridYMax) {
						    errormsg = "Grid X and Y are out of range for your cities! Re-adjust your ranges in: " + config;
						    break;
						} 
						//if x is bigger, output error
						else if (cityX > gridXMax) {
						    errormsg = "Grid X: " + xValues[1] + " is out of range for your cities! Re-adjust your X range in: " + config;
						    break;
						} 
						//if y is bigger, output error
						else if (cityY > gridYMax) {
						    errormsg = "Grid Y: " + yValues[1] + " is out of range for your cities! Re-adjust your Y range in: " + config;
						    break;
						}

						// Store the x and y which will be used to display all the grid maps(+1 because 0-indexed)
						xMax = gridXMax + 1;
						yMax = gridYMax + 1;

						// Call data population functions
						populateCity(cityfile, xMax, yMax);
						populateCloud(cloudfile, xMax, yMax);
						populatePressure(pressurefile, xMax, yMax);

						//Display on terminal if everything is smooth
						cout << "Reading in GridX_IdxRange : " << gridXrange << " ... done!" << endl;
						cout << "Reading in GridY_IdxRange : " << gridYrange << " ... done!" << endl;
						cout << endl;
						
						cout << "Storing data from input file :" << endl;
						cout << cityfile << " ... done!" << endl;
						cout << cloudfile << " ... done!" << endl;
						cout << pressurefile << " ... done!" << endl;
						cout << endl;

						cout << "All records successfully stored. Going back to main menu ..." << endl << endl;
						isDataLoaded = true;
						break;

					} catch (const exception& e) {
						cerr << "Error: " << e.what() << endl;
						break;
					}

				} else {
					cerr << "Error: Unable to open config file: " << config << endl;
					Freeze();
					break;
				}
			}
			
			case 2:
			{
				//check to ensure that the data is loaded in smoothly from the config
				if(cityfile.empty())
				{
					cout << "city text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					displaycitymap(xMax, yMax);
					Freeze();
					break;
				}
			}
			
			case 3:
			{
				//check if the file is loaded in smoothly from the config
				if(cloudfile.empty())
				{
					cout << "cloud text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					displayCloudByIndex(xMax, yMax);
					Freeze();
					break;
				}
			}
			
			case 4:
			{
				//check if the file is loaded in smoothly from the config
				if(cloudfile.empty())
				{
					cout << "cloud text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					displayCloudBySym(xMax, yMax);
					Freeze();
					break;
				}
			}
			
			case 5:
			{
				//check if the file is loaded in smoothly from the config
				if(pressurefile.empty())
				{
					cout << "pressure text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					displayPressureByIndex(xMax, yMax);
					Freeze();
					break;
				}
			}		
			
			case 6:
			{
				//check if the file is loaded in smoothly from the config
				if(pressurefile.empty())
				{
					cout << "pressure text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					displayPressureBySym(xMax, yMax);
					Freeze();
					break;
				}
			}
			
			case 7:
			{
				//check if the file is loaded in smoothly from the config
				if(cloudfile.empty())
				{
					cout << "cloud text file is missing from config file" << endl;
					Freeze();
					break;
				}
				//check if the file is loaded in smoothly from the config
				else if(pressurefile.empty())
				{
					cout << "pressure text file is missing from config file" << endl;
					Freeze();
					break;
				}
				else
				{
					cout << "[" << mainmenulist[option - 1] << "]" << endl;
					int arrayLength = 0;
					int totalCity = 0;
					//read the cityfile
					string line;
					ifstream cityData(cityfile);
					
					if (cityData.is_open())
					{
						while(getline(cityData, line))
						{
							vector<string> split = tokenizeString(line, "-");
							
							if (split.size() < 2)
							{
								continue;
							}
							
							int cityID = stoi(trim(split[1]));
							//check if the cityID for the line is higher or the already stored highest cityID
							if (cityID > totalCity)
							{
								totalCity = cityID;
							}
							
							//total number of lines from the cityfiles
							arrayLength++;
						}
						cityData.close();
						
						//grid calculation
						int mapLength = xMax * yMax;
						
						weatherReport(arrayLength, totalCity, mapLength);
						Freeze();
						break;
					}
					else
					{
						cout << "Error: cannot open city file" << endl;
						Freeze();
						break;
					}
					Freeze();
					break;
				}
			}
			
			case 8:
			{
				cout << "You have chosen to quit the program..." << endl;
				break;
			}
			default:
				errormsg = "Unknown option selected.";
				break;	
		}
	}		
	while(option!=8);	
	deleteCityMem(xMax, yMax);
	deleteCloudMem(xMax, yMax);
	deletePressureMem(xMax,yMax);
	cout << "Quitting..." << endl;
	cout << endl;
	return 0;
}
		




