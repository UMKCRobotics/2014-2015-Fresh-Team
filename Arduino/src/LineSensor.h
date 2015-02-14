#ifndef LINESENSOR_H
#define LINESENSOR_H

const int readingThreshold = 800; 	// Dummy reading theshold
const int timingThreshold = 1000; 	// Microseconds between when one line
									// sensor can see a line and the next

class LineSensor
{
private:
	bool seesLine;
	long timeWhenDetected;
	int lastReading;
	int linesPassed;
public:
	LineSensor();

	void update(float reading);
	bool lineDetected(long compareTime);
	void resetLinesPassed();
	
	long getTimeDetected();
	int getLastReading();
	int getLinesPassed();
	// We can possibly add in a function to differentiate between
	// a big line and a small line (actual line and gap in the
	// table)
};

#endif
