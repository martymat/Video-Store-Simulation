//Driver.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Customer.h"
#include "Person.h"
#include "Store.h"
#include "Movie.h"

using namespace std;

void main()
{
	//Store object sending name of text file containing movie data for program
	Store video("Movies Data.txt");	

	//The following lines of code are just other people renting movies before the user arrives
	Person defaultOne("9171234567", "Jon Smith");  
	Person defaultTwo("6469871234", "Hans David");
	Person defaultThree("7183336424", "Arthur Blanc");
	video.rent(defaultOne, "Star Wars");
	video.rent(defaultTwo, "The Avengers");
	video.rent(defaultThree, "Deadpool");
	video.rent(defaultOne, "Saw");

	video.welcome();
	bool done = false;
	string userQuestion;

	//While loop simulating user's experience at store
	//Contains 6 options
	//Goes until they say they are done
	while (!done)
	{
		int input = video.prompt();
		if (input == 1)
		{
			video.printInMovies();
		}
		else if (input == 2)
		{
			video.printOutMovies();
		}
		else if (input == 3)
		{
			cin >> userQuestion;
			if (userQuestion.length() == 10)
			{
				video.phoneRent(userQuestion);
			}
			else
				video.phoneError();
		}
		else if (input == 4)
		{
			cin >> userQuestion;
			if (userQuestion.length() == 10)
			{
				video.phoneReturn(userQuestion);
			}
			else
				video.phoneError();
		}
		else if (input == 5)
		{
			video.popularCategory();
		}
		else if (input == 6)
		{
			done = true;
		}
	}

	video.goodBye();
}