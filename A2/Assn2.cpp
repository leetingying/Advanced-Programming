#include "otherfunc.h"

int main() {
    string choice;
    bool flag = true;
    int option = 0;
    //StudentID and Student_name variable
	string student_id = "8551741";
	string student_name = "Lee Ting Ying";

    //list of options in the display menu
	string mainmenulist[] = {
        "Input sensor data",
        "Compute area (for all records)",
        "Print shapes report",
        "Sort shape data",
        "Exit Program"
    };

    while(flag)
    {
        cout << endl;
        cout << "Student ID : " << student_id << endl;
        cout << "Student Name : " << student_name << endl;
        cout << "---------------------------------" << endl;
        cout << "Welcome to Assn2 program!" << endl;

        const int mainmenuSize = sizeof(mainmenulist) / sizeof(mainmenulist[0]);

        //Printing display of the menu
        for (int i = 0; i < mainmenuSize; i++) {
            cout << i + 1 << ") " << mainmenulist[i] << endl;
        }
		cout << endl;
		
		cout << "Please enter your choice :" ;
		//get the user input choice
		getline(cin, choice);
		cout << endl;
		
		//ensures that the choice is not empty, only single digit input and only numbers from 1-5 is allowed
		if (!choice.empty() && choice.length() == 1 && isdigit(choice[0])) {
			//convert char digit to int
			option = choice[0] - '0';
			if (option < 1 || option > 5) {
				cout <<"Invalid input. Please enter a digit between 1 and 5." << endl;
				continue;
			}
		} else {
			cout << "Invalid input. Please enter a single digit only." << endl;;
			continue;
		}

        switch (option) {
            case 1:
            {
            	//Calls function to input sensor data
               	cout << "[" << mainmenulist[option - 1] << "]" << endl;
               	o1();
                break;
			}
			
            case 2:
            {
            	// calls function to compute area of all records
            	o2();
                break;
			}
			
            case 3:
            {
            	// calls function to print shapes report
                o3();
                break;
			}

            case 4:
            {
            	//calls function to sort shape data
                o4();
                break;
			}
            
            case 5:
            {
                cout << "Exiting the program." << endl;
                //exit the main loop to end program
                flag = false;
                break;
			}
			
            default:
            {
                cout << "Please key in a valid option." << endl;
                break;
			}
        }
    }
    //After exiting loop, free all dynamically allocated shape and clear vector shapeArr
    deleteAllShapes();
    
    return 0;
}

