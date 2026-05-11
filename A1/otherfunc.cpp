#ifndef OTHERFUNC_CPP
#define OTHERFUNC_CPP
#include "otherfunc.h"

//Purpose of function: split a string into parts based on a delimiter
vector<string> tokenizeString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);

	return (result);
}

//Purpose of function: Removes leading and trailing spaces, tabs, newlines from a string
string trim (string str)
{
	const char* whitespace = " \t\r\n";
    auto first = str.find_first_not_of(whitespace);
    auto end = str.find_last_not_of(whitespace);
    return (first == string::npos || end == string::npos) ? "" : str.substr(first, end - first + 1);
}

//Purpose of function: read all line from a file, trim each line, remove empty lines from the end and write the cleaned lines back into the file
void cleanFile(string filename)
{
	ifstream inputFile (filename);
	vector<string> lines;
	string line;
	
	if(inputFile.is_open())
	{
		while(getline(inputFile,line))
		{
			line = trim(line);
			lines.push_back(line);
		}
		inputFile.close();
	}
	else
	{
		cerr << "Failed to open the file for reading"<< endl;
		return;
	}
	
	while(!lines.empty() && lines.back().empty())
	{
		lines.pop_back();
	}
	
	ofstream outputFile(filename, ios::trunc);
	if (outputFile.is_open())
	{
		for(size_t i = 0; i <lines.size(); i++)
		{
			outputFile << lines[i];
			if (i<lines.size() - 1)
			{
				outputFile << endl;
			}
		}
		outputFile.close();
	}
	else
	{
		cerr << "Failed to open the " << filename << " file for writing" << endl; 
	}
}

//Purpose of function: Read the last non-empty line of a file, even if there are blank lines at the end
string readLastNonEmpty(string filename)
{
	ifstream file(filename, ios::in);
	if (!file.is_open())
	{
		throw runtime_error("Could not open file");
	}
	
	file.seekg(0, ios::end);
	
	auto fileSize = file.tellg();
	if(fileSize ==0)
	{
		return "";
	}
	
	long long pos = static_cast <long long>(fileSize)-1;
	string lastLine;
	while (pos>=0)
	{
		file.seekg(pos);
		char ch;
		file.get(ch);
		
		if (ch == '\n' && pos != static_cast<long long>(fileSize)-1)
		{
			if(getline(file, lastLine))
			{
				lastLine = trim(lastLine);
				if(!lastLine.empty())
				{
					return lastLine;
				} 
			}
			pos--;
			continue;
		}
		pos--;
	}
	
	file.clear();
	file.seekg(0);
	 if (getline(file, lastLine))
    {
        lastLine = trim(lastLine);
    }
    else
    {
        lastLine = "";
    }
	return lastLine;
}

//Purpose of function: Converting numbers between 0 and 99 to index of 0-9, each representing a range of 10
int sortIndex(int sN)
{
	if(sN < 0 || sN>=100)
	{
		cout << "invalid number found: " << sN << endl;
		return -1;
	}
	else if(sN< 10)
	{
		return 0;
	}
	else if(sN < 20)
	{
		return 1;
	}
	else if(sN < 30)
	{
		return 2;
	}
	else if(sN < 40)
	{
		return 3;
	}
	else if(sN < 50)
	{
		return 4;
	}
	else if(sN < 60)
	{
		return 5;
	}
	else if(sN < 70)
	{
		return 6;
	}
	else if(sN < 80)
	{
		return 7;
	}
	else if(sN < 90)
	{
		return 8;
	}
	else if(sN < 100)
	{
		return 9;
	}
	else
	{
		return 9;
	}
}

//Purpose of function: converts the value into symbols
string sortSymbol(int sN)
{
	if(sN < 35)
	{
		return "L";
	}
	else if(sN< 65)
	{
		return "M";
	}
	else if(sN < 100)
	{
		return "H";
	}
	else
	{
		cout << "Invalid number found";
		return("");
	}
}

//Purpose of function: pauses the program until the user presses enter
void Freeze() {
	cout << endl;
	string chh = "1";
	cout << "Press <enter> to go back to main menu ..." << endl;
	cin.ignore();
	do {
		getline(cin, chh);
	} while(chh.length() != 0);
}



#endif
