#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class PublicationType{ BOOK, MAGAZINE };

class Publication
{
private:
	string title;
	string author;
	int pub_year;
public:
	Publication (string title, string author, int pub_y) : title{title}, author{author}, pub_year{pub_y} {};

	string get_title() {return title;}
	string get_author() {return author;}
	int get_publication_year() {return pub_year;}

	virtual void display_info() = 0; /* { cout << "Title:" << title << "\n" << "Author: " << author << "\n" << "Publication year: " << pub_year << endl; } */
	virtual PublicationType get_type() = 0;

	virtual ~Publication() {};
};

class Book : public Publication
{
private:
	string isnb;
public:
	Book (string title, string author, int pub_y, string isnb) : Publication(title, author, pub_y), isnb{isnb} {}; 

	void display_info() override {
		cout << "Title:" << this->get_title() << "\n" << "Author: " << this->get_author() << "\n" << "Publication year: " << this->get_publication_year() << "\n" << "ISNB: " << isnb << endl;
	}

	PublicationType get_type() override { return PublicationType::BOOK; }

	~Book() override {};
};

class Magazine : public Publication
{
private:
	int issue_number;
public:
	Magazine(string title, string author, int pub_y, int iss_n) : Publication(title, author, pub_y), issue_number{iss_n} {};

	void display_info() override {
		cout << "Title:" << this->get_title() << "\n" << "Author: " << this->get_author() << "\n" << "Publication year: " << this->get_publication_year() << "\n" << "Issue number: " << issue_number << endl;
	}

	PublicationType get_type() override { return PublicationType::MAGAZINE; }
	
	~Magazine() override {};
};

int main()
{
	vector<Publication *> ptrPub = {
	    new Magazine("Nikelodeon", "Ninja Turtles", 2012, 25467),
	    new Book("Leo", "War and Peace", 2009, "0140447938"),
	    new Magazine("MediaCo.", "New Stars", 2012, 4)
	}; //(2, nullptr);
//ptrPub[0] = new Magazine("Nikelodeon", "Ninja Turtles", 2012, 25467);
//ptrPub[1] = new Book("Leo", "War and Peace", 2009, "0140447938");
//ptrPub[2] = new Magazine("MediaCo.", "New Stars", 2012, 4);
	//using enum PublicationType; // only in c++ v20+

	for (int i = 0; i < 3; i++) {
		if (ptrPub[i]->get_type() == PublicationType::BOOK) {
			ptrPub[i]->display_info(); }
	}
};

