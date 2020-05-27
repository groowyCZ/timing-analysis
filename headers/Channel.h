#ifndef _Channel_h
#define _Channel_h

#include "AudioFile.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;
using std::max_element;
using std::abs;
using std::invalid_argument;

class Channel
{
public:
	/* Constructor */
	Channel(const string &fileName, double minimalNoteSpacing, double volumeThreshold, bool usePercents);

	/* Returns vector<vector<double>> representing volume samples for each audio channel */
	vector<vector<double>> getSamples() const;

	/* Returns duration of sample */
	double getTiming() const;

	/* Returns volume threshold */
	double getVolumeThreshold() const;

	/* Returns vector<double> representing time of beginning of each note */
	vector<double> getNoteIndices() const;

private:
	AudioFile<double> audio;
	double timing;
	double volumeThreshold;
	double minimalNoteSpacing;
};

#endif /* _Channel_h */