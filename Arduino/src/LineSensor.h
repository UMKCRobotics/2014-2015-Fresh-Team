#ifndef LINESENSOR_H
#define LINESENSOR_H

const int readingTheshold = 1000; // Dummy reading theshold

class LineSensor
{
private:
	bool seesLine;
public:
	LineSensor();

	void update(float reading);
	bool seesLine();
	// We can possibly add in a function to differentiate between
	// a big line and a small line (actual line and gap in the
	// table)
};

#endif