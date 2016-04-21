//Movie.h

#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

using namespace std;

//Struct for controlling movie data
struct Movie {
public:
	//Default constructor
	Movie() : category(0),
		title(" "), identification(" ") {}

	//Constructor initializer
	Movie(string theTitle, string theID, int theCategory)
		: title(theTitle), identification(theID), category(theCategory) {}

	//Copy constructor
	Movie(const Movie &inMovie) : category(inMovie.category),
		title(inMovie.title), identification(inMovie.identification) {}

	int category;
	string identification;
	string title;

	//Overloaded operator for comparing movie objects
	bool operator ==(Movie in)
	{
		if (title == in.title)
			return true;
		return false;
	}

	//Overloaded operator outputting movie objects
	friend ostream& operator<<(ostream& out, const Movie& mv)
	{
		string temp;
		if (mv.category == 1)
			temp = "feature";
		else if (mv.category == 2)
			temp = "comedy";
		else if (mv.category == 3)
			temp = "horror";
		out << "Title: " << mv.title << " ID: " << mv.identification << " Category: " << temp;
		return out;
	}
};

#endif