#ifndef ISBN_H
#define ISBN_H

class isbn
{
public:
	isbn();
	isbn(char* isbn);

	bool isValid();
	bool setIsbn(char *isbn);
	char* getIsbn();

private:
	bool makeIsbn13();
	char *isbnNumber;
};

#endif // ISBN_H
