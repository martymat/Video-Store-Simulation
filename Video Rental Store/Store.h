//Store.h

#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Customer.h"
#include "Person.h"
#include "Movie.h"

using namespace std;

class Store {
private:
	//Vector of customers
	vector <Customer> Customers;

	//Vector of movies
	vector <Movie> Movies;

	int rentedH;
	int rentedF;
	int rentedC;
public:
	//Constructor
	Store(string);

	//Rent a movie to a person
	void rent(Person, string);

	//Return a movie to the store
	void returnMov(Person, string);

	//Print all Movies that aren't in the store
	void printOutMovies();

	//Prompt users for input
	int prompt();

	//Print all Movies the store has.
	void printInMovies();

	//Display which movie is most popular
	void popularCategory();

	//Welcomes the user
	void welcome();

	//Say goodbye to user
	void goodBye();

	//Rent by phone number
	void phoneRent(string);

	//Return by phone number
	void phoneReturn(string);

	//Display if the user enters a phone number that real
	void phoneError();

};
#endif

//Constructor
Store::Store(string fileName)
{
	//Opening file
	fstream file;
	file.open(fileName);
	//Check to see if the file is open or not
	//It will end the code if the file is not found
	if (!file.is_open())
	{
		cout << "Error: File not found \nNow terminating program\n";
		exit(1);
	}

	string title, id, category;

	int tempCat = 0;

	//While program has not yet reached the end of the file
	while (!file.eof())
	{
		//Read in movie data from text file
		getline(file, title, ':');
		getline(file, id, ':');
		getline(file, category);

		//The following loop will assign a number based on category
		if (category == "feature")
			tempCat = 1;
		else if (category == "comedy")
			tempCat = 2;
		else if (category == "horror")
			tempCat = 3;
		else
		{
			cout << "Error assigning category to " << title << endl; exit(1);
		}

		//Fill in movie vector
		Movie temp(title, id, tempCat);
		Movies.push_back(temp);
	}

	file.close();
}

//Rent a movie to a person
void Store::rent(Person renter, string wantedMovie)
{
	//This makes sure there are Movies
	int movieIndex = 0;
	int customerIndex = 0;
	if (Movies.size() != 0)
	{
		Customer renterCust(renter);
		Movie test;
		test.title = wantedMovie;
		bool movieFound = false;
		//This checks to see if the movie exists in the store
		for (unsigned int i = 0; i < Movies.size(); i++)
		{
			if (Movies[i].title == wantedMovie)
			{
				movieIndex = i;
				movieFound = true;
			}
		}

		if (movieFound == true)
		{
			bool found = false;
			int i = 1;
			bool over = false;
			for (unsigned int i = 0; i < Customers.size(); i++)
			{
				if (renterCust == Customers[i])
				{
					customerIndex = i;
					found = true;
				}
			}
			if (found)
			{
				if (Movies[movieIndex].category == 1)
					rentedF++;
				else if (Movies[movieIndex].category == 2)
					rentedC++;
				else if (Movies[movieIndex].category == 3)
					rentedH++;

				Customers[customerIndex].rentMovie(Movies[movieIndex]);
				Movies.erase(Movies.begin() + movieIndex);

			}
			else
			{
				if (Movies[movieIndex].category == 1)
					rentedF++;
				else if (Movies[movieIndex].category == 2)
					rentedC++;
				else if (Movies[movieIndex].category == 3)
					rentedH++;

				renterCust.rentMovie(Movies[movieIndex]);
				Customers.push_back(renterCust);
				Movies.erase(Movies.begin() + movieIndex);



			}
		}
		else if (movieFound == false)
		{
			cout << "Movie not found\n";
		}
	}

}

//Return a movie to the store
void Store::returnMov(Person inPerson, string inTitle)
{
	int index = 0;
	bool found = false;
	Movie returned;
	returned.title = inTitle;
	for (unsigned int i = 0; i < Customers.size(); i++)
	{
		if (Customers[i].getPhoneNum() == inPerson.getPhoneNum())
		{
			index = i;
			found = true;
			break;
		}
	}
	if (found)
	{
		returned = Customers[index].returnMovie(returned);
		Movies.push_back(returned);
	}
}

//Print all Movies that aren't in the store
void Store::printOutMovies()
{
	for (unsigned int i = 0; i < Customers.size(); i++)
	{
		Customers[i].printInfo();
	}
}
//This will be used to prompt users for their input 
int Store::prompt()
{
	bool done = false;
	int input = -1;
	while (!done)
	{

		cout << "\tPlease choose a command\n";
		cout << "1: View all Movies available in store\n2: View all Movies not available in store, and who currently has them\n";
		cout << "3: Rent a movie (ten digit phone number required)\n4: Return a movie (ten digit phone number required)\n";
		cout << "5: Check which movie category is the most popular\n6: Exit the store\n";
		cin >> input;
		if (input > 6 || input < 1)
		{
			cout << "ERROR: Please enter a real option\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
		if (input == 3 || input == 4)
		{
			cout << "Please enter your phone number\n";
			done = true;
			return input;
		}
		else
			return input;

	}
	return input;
}

//Print all Movies the store has.
void Store::printInMovies()
{
	if (Movies.empty())
	{
		cout << "Sorry, we are fresh out of Movies!\n";
	}
	else
	{
		for (unsigned int i = 0; i < Movies.size(); i++)
		{
			cout << Movies[i] << endl;
		}
	}
}

//Display which movie is most popular
void Store::popularCategory()
{
	cout << "The most popular categroy is ";
	if (rentedF >= rentedC)
	{
		if (rentedF >= rentedH)
		{
			cout << "feature\n";
		}
		else
		{
			cout << "horror\n";
		}
	}

	else
	{
		if (rentedC >= rentedH)
		{
			cout << "comedy\n";
		}
		else
		{
			cout << "horror\n";
		}
	}
}

//Welcomes the user
void Store::welcome()
{
	cout << "\t\t\tWelcome to the Video Rental Store!\n";
}

//Say goodbye to user
void Store::goodBye()
{
	cout << "Goodbye, have a great day!\n";
}

//Rent by phone number
void Store::phoneRent(string phoneNum)
{
	bool numFound = false;
	bool movieFound = false;
	int index = 0;
	string movieName;
	int movieIndex = 0;
	for (unsigned int i = 0; i < Customers.size(); i++)
	{
		if (Customers[i].getPhoneNum() == phoneNum)
		{
			numFound = true;
			index = i;
		}
	}
	cin.ignore();
	if (!numFound)
	{
		cout << "I see you are new, let me register you\nWhat is your name?\n";
		string personName;

		getline(cin, personName);
		Customer you(phoneNum, personName);
		Customers.push_back(you);
		for (unsigned int k = 0; k < Customers.size(); k++)
		{
			if (Customers[k].getPhoneNum() == phoneNum)
			{
				index = k;
			}
		}
	}
	cout << "We currently have:\n";
	printInMovies();
	cout << "What movie would you like to rent today?\n";

	getline(cin, movieName);
	for (unsigned int i = 0; i < Movies.size(); i++)
	{
		if (Movies[i].title == movieName)
		{
			movieIndex = i;
			movieFound = true;
		}
	}
	if (movieFound)
	{
		if (Movies[movieIndex].category == 1)
			rentedF++;
		else if (Movies[movieIndex].category == 2)
			rentedC++;
		else if (Movies[movieIndex].category == 3)
			rentedH++;

		Customers[index].rentMovie(Movies[movieIndex]);
		Movies.erase(Movies.begin() + movieIndex);
		cout << "Ah, " << movieName << " great choice!\n";
	}
	else
		cout << "We do not currently have that movie\n";
}

//Return by phone number
void Store::phoneReturn(string phoneNum)
{
	bool numFound = false;
	string movieName;
	int index = 0;
	int indexMovie;
	Movie returning;
	for (unsigned int i = 0; i < Customers.size(); i++)
	{
		if (Customers[i].getPhoneNum() == phoneNum)
		{
			numFound = true;
			index = i;
		}
	}
	if (!numFound)
	{
		cout << "You aren't in our database\n";
		return;
	}
	if (!Customers[index].isEmpty())
	{
		cout << "What movie would you like to return today?\nYou currently have: \n";
		Customers[index].displayMovies();
		cin.ignore();
		getline(cin, movieName);
		returning.title = movieName;
		if (Customers[index].hasMovie(movieName))
		{
			returning = Customers[index].returnMovie(returning);
			Movies.push_back(returning);
			cout << movieName << " has been returned, thank you!\n";
		}
		else
			cout << "You do not have that movie\n";
	}
	else
		cout << "You aren't renting any Movies at the moment\n";
}

//Display if the user enters a phone number that real
void Store::phoneError()
{
	cout << "ERROR: Phone number not 10 digits\n";
}