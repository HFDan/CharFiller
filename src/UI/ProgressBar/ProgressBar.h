#pragma once

class ProgressBar {

protected:

	double CurrentPercentage = 0;
	double CurrentValue;
	double MaxPercentage = 100;
	double MaxValue = 100;
	double MinPercentage = 0;
	double MinValue = 0;
	const char FillChar = '#';
	const char EmptyChar = ' ';
	const char BorderChar[2] = { '[' , ']' };

public:

	// Constructor and Destructor
	ProgressBar(double MinAmount, double MaxAmount);
	~ProgressBar();

	virtual void Tick();

	void UpdatePercentage();

};