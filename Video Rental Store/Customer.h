//Customer.h

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <vector>

#include "Person.h"
#include "Movie.h"

using namespace std;


class Customer : public Person
{
private:
	//vector of movies rented
	vector<Movie> moviesRented;
	int movies;
public:
	//Default constructor
	Customer::Customer() : Person() { movies = 0; }

	// Constructor using only phone number
	Customer::Customer(string inCustomerPhoneNum, string inCustomerName = "")
		: Person(inCustomerPhoneNum, inCustomerName) {
		movies = 0;
	}

	//Constructor that takes uses base class information
	Customer::Customer(Person inPerson)
		: Person(inPerson.getPhoneNum(), inPerson.getName()) {
		movies = 0;
	};


	// Inherited print info method
	virtual void printInfo();

	//Takes a movie from the store
	void rentMovie(Movie);

	//Returns a movie to the store
	Movie returnMovie(Movie);

	//Checks to see if this customer has a movie by title
	bool hasMovie(string);

	//Check to see if customer has no rented movies
	bool isEmpty();

	//Outputs movies rented by customer
	void displayMovies();

	//Overloaded bool equality operator 
	bool operator == (Customer in);

	//Overloaded assignment equal operator
	void operator=(Customer in);


};


//Makes use of the base class
//Prints movies(if any)
void Customer::printInfo() {
	Person::printInfo();
	if (!moviesRented.empty())
	{
		for (unsigned int i = 0; i < moviesRented.size(); i++)
		{
			cout << moviesRented[i] << endl;
		}
	}
	else
		cout << "No movies currently rented by user\n";
}

//Takes a movie from the store
void Customer::rentMovie(Movie theMovie)
{
	moviesRented.push_back(theMovie);
	movies++;
}

//Returns a movie to the store
Movie Customer::returnMovie(Movie theMovie)
{
	bool removed = false;
	for (unsigned int i = 0; i < moviesRented.size(); i++)
	{
		if (moviesRented[i].title == theMovie.title)
		{
			theMovie = moviesRented[i];
			moviesRented.erase(moviesRented.begin() + i);
			removed = true;
		}
	}
	if (!removed)
	{
		cout << "You don't have that movie\n";
	}
	else
		movies--;

	return theMovie;
}

//Checks to see if this customer has a movie by title
bool Customer::hasMovie(string movieTitle)
{
	for (unsigned int i = 0; i < moviesRented.size(); i++)
	{
		if (moviesRented[i].title == movieTitle)
		{
			return true;
		}
	}
	return false;
}

//Check to see if customer has no rented movies
bool Customer::isEmpty()
{
	if (moviesRented.empty())
		return true;
	return false;
}

//Outputs movies rented by customer
void Customer::displayMovies()
{
	if (!moviesRented.empty())
	{
		for (unsigned int i = 0; i < moviesRented.size(); i++)
		{
			cout << moviesRented[i] << endl;
		}
	}
}

//Overloaded bool equality operator 
bool Customer::operator==(Customer in)
{
	if (getPhoneNum() == in.getPhoneNum())
		return true;
	return false;
}

//Overloaded assignment equal operator
void Customer::operator=(Customer in)
{
	setPhoneNum(in.getPhoneNum());
	setName(in.getName());
	movies = in.movies;
	for (unsigned int i = 0; i < moviesRented.size(); i++)
	{
		moviesRented[i] = in.moviesRented[i];
	}
}



#endif