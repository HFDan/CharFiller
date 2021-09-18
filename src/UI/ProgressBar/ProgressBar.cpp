#include <iostream>
#include "ProgressBar.h"

ProgressBar::ProgressBar(double MinAmount, double MaxAmount) {
	MinValue = MinAmount;
	MaxValue = MaxAmount;

	std::cout << "Working: " << BorderChar[0] << EmptyChar;

	Tick();
}

ProgressBar::~ProgressBar(){  }

void ProgressBar::Tick() {
	while (true) {
		UpdatePercentage();
	}
}

void ProgressBar::UpdatePercentage() {

}
