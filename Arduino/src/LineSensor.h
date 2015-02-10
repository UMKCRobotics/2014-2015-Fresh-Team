#ifndef LINESENSOR_H
#define LINESENSOR_H

const int readingThreshold = 1000; 	// Dummy reading theshold
const int timingThreshold = 200; 	// Milliseconds between when one line
									// sensor can see a line and the next

class LineSensor
{
private:
	bool seesLine;
	long timeWhenDetected;
public:
	LineSensor();

	void update(float reading);
	bool lineDetected(long copareTime);
	long getTimeDetected();
	// We can possibly add in a function to differentiate between
	// a big line and a small line (actual line and gap in the
	// table)
};

#endif