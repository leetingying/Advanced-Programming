#include "otherfunc.h"

//global dynamic array vector storing pointers to ShapeTwoD objects
vector <ShapeTwoD *> shapeArr;

//function to convert entire string to lowercase; used for user inputs
string toLowerCase(string input)
{
	transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

//function to convert entire string to lower then capitalize first letter
//used for display purpose
string toLowerAndCapitalize(string input) {
    // Convert whole string to lowercase
    for (char& ch : input) {
        ch = tolower(ch);
    }

    // Capitalize first character if it's a letter
    if (!input.empty() && isalpha(input[0])) {
        input[0] = toupper(input[0]);
    }

    return input;
}

//function to get shape name and special type from user inputs
//creates an object of shape type dynamically and store in shapeArr
void o1()
{
	//variables to store user input
	string shape_name;
    string shape_type;
    string input;
    bool contain_warp;
    bool shapeCheck = true;
    
    //Get valid shape name from user (square, rectangle, circle, cross) 
    do
    {
    	cout << "Please enter name of shape : ";
		getline(cin, input);
		shape_name = toLowerCase(input);
		
		if (shape_name == "square" || shape_name == "rectangle" || shape_name == "circle" || shape_name == "cross")
		{
			shapeCheck = false;
		}
		else
		{
			cout << "Invalid Shape Name. Please enter Square / Rectangle / Circle / Cross" << endl;
		}
    }
    while (shapeCheck == true);
    
    shapeCheck = true;
    
    //Get special type of shapes from user
    do
    {
    	cout << "Please enter Special type (WS/NS) : ";
		getline(cin, input);
		shape_type = toLowerCase(input);
		if (shape_type == "ws" || shape_type == "ns")
		{
			shapeCheck = false;
		}
		else
		{
			cout << "Invalid Special Type. Please enter WS (Warp-Space) or NS (Normal-Space)" << endl;
		}
    }
    while (shapeCheck == true);
    
    //convert the special type string to bool accordingly
    if (shape_type == "ws")
    {
    	contain_warp = true;
    }
    else
    {
    	contain_warp = false;
    }
    
    //Create the correct shape object and add to shapeArr
    if(shape_name == "square")
    {
     	ShapeTwoD* shape= new Square(toLowerAndCapitalize(shape_name), contain_warp);
    	shapeArr.push_back(shape);
    	cout << "Record successfully stored. Going back to main menu....."  << endl;
    }
    else if(shape_name == "rectangle")
    {
     	ShapeTwoD* shape= new Rectangle(toLowerAndCapitalize(shape_name), contain_warp);
    	shapeArr.push_back(shape);
    	cout << "Record successfully stored. Going back to main menu....."  << endl;
    }
    else if (shape_name == "circle")
    {
    	ShapeTwoD* shape = new Circle(toLowerAndCapitalize(shape_name), contain_warp);
    	shapeArr.push_back(shape);
    	cout << "Record successfully stored. Going back to main menu....."  << endl;
    }
    else if (shape_name == "cross")
    {
    	ShapeTwoD* shape = new Cross(toLowerAndCapitalize(shape_name), contain_warp);
    	shapeArr.push_back(shape);
    	cout << "Record successfully stored. Going back to main menu....."  << endl;
    }
    
}

//function to compute area for all shapes in shapeArr
void o2()
{
	//check if there is any shapes in the array
	if (shapeArr.size() ==0)
	{
		cout << "No data input. Please choose option 1 to input data." << endl;
		return;
	}
	else
	{
		for (size_t i = 0; i < shapeArr.size(); i++) 
		{
			//polymorphically computes area for each shape object
			shapeArr[i]->computeArea();
		}
		//confirms that the area are computed 
		cout << "Computation completed! (" << shapeArr.size() << " records were updated )" << endl;
	}
}

//function to display all shape objs in shapeArr
void o3()
{
	// check if shapeArr is empty
	if (shapeArr.size() == 0)
	{
		cout << "No data input. Please choose option 1 to input data." << endl;
		return;
	}
	else
	{
		cout << "Total no. of records available : " << shapeArr.size() << endl;
		cout << endl;
		for (size_t i = 0; i < shapeArr.size(); i++) {
			//Assign record number
			shapeArr[i] -> setShapeNum(i);
			//print details of each shape
			cout << shapeArr[i]->toString() << endl;
			cout << endl;
		}
	}
}

//function for sort options and sorting of shapes
void o4()
{
	string input;
	string optchoice[] = 
	{
		"a",
		"b",
		"c",
	};
	string sortOptions[] =
	{
		"Sort by area (ascending)",
		"Sort by area (descending)",
		"Sort by special type and area"
	};
	
	int optSize = sizeof(optchoice) / sizeof(optchoice[0]);
	cout << endl;
	if (shapeArr.size() == 0)
	{
		cout << "No data input. Please choose option 1 to input data." << endl;
		return;
	}
	else
	{
		for (int i = 0; i < optSize; i++)
		{
			cout << "\t" << optchoice[i] << ")\t" << sortOptions[i] << endl;
		}
		cout << endl;
		cout << "Please select sort option ('q' to go main menu) : " << endl;
		getline(cin, input);

		char option = tolower(input[0]);
		if (input.length() != 1 || (option != 'a' && option != 'b' && option != 'c' && option != 'q')) 
		{
			cout << "Invalid input. Please choose a, b, c or q!" << endl;
			return;
		}

		switch (option)
		{
		case 'a':
			//sort ascending by area
		    sort(shapeArr.begin(), shapeArr.end(), [](ShapeTwoD* a, ShapeTwoD* b)
		    {
		        return a->getArea() < b->getArea();
		    });
		    cout << "\n Sort by area (smallest to largest) ..." << endl;
		    break;

		case 'b':
			// sort descending by area
		    sort(shapeArr.begin(), shapeArr.end(), [](ShapeTwoD* a, ShapeTwoD* b)
		    {
		        return a->getArea() > b->getArea();
		    });
		    cout << "\n Sort by area (largest to smallest) ..." << endl;
		    break;

		case 'c':
			//sort by special type (WS first) then area descending
		    sort(shapeArr.begin(), shapeArr.end(), [](ShapeTwoD* a, ShapeTwoD* b)
		    {
		        if (a->getContainsWarpSpace() != b->getContainsWarpSpace())
		            return a->getContainsWarpSpace(); // true first

		        return a->getArea() > b->getArea(); // Descending area within each group
		    });
		    cout << "\n Sort by special type and area (largest to smallest) ..." << endl;
		    break;

		case 'q':
			//quit back to display menu
		    cout << "\nYou have chosen q to return to main menu ..." << endl;
		    return;

		default:
		    cout << "Invalid input choice. Please only choose a, b, c or q!" << endl;
		    return;
		}
		// After sorting, print all records
		cout << endl;
		for(size_t i = 0; i < shapeArr.size(); i++)
		{
			cout << shapeArr[i]->toString() << endl;
		}
	}
}

//function to free dynamically allocated memory for all shape objects
//clear to remove all pointers from vector
void deleteAllShapes()
{
	for (auto shape : shapeArr)
	{
		//free memory for each shape created with new
		delete shape;
	}
	shapeArr.clear();
}




