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
	Channel(string fileName, double minimalNoteSpacing, double volumeThreshold, bool usePercents);

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


Channel::Channel(string fileName, double minimalNoteSpacing, double volumeThreshold, bool usePercents = false)
{
	bool loaded = audio.load(fileName);

	if (!loaded) {
		throw invalid_argument("File \"" + fileName + "\" couldn't be loaded");
	}

	this->minimalNoteSpacing = minimalNoteSpacing;
	timing = 1.0f / (double)audio.getSampleRate();

	if (usePercents) {
		this->volumeThreshold = (volumeThreshold / 100) * (double)*max_element(audio.samples[0].begin(), audio.samples[0].end());
	} else {
		this->volumeThreshold = volumeThreshold;
	}
}

vector<vector<double>> Channel::getSamples() const
{
	return audio.samples;
}

double Channel::getTiming() const
{
	return timing;
}

double Channel::getVolumeThreshold() const
{
	return volumeThreshold;
}

vector<double> Channel::getNoteIndices() const
{
	vector<double> noteIndices;
	double difference;
	double spacing;

	for (int i = 1; i < audio.getNumSamplesPerChannel(); i++) {
		difference = abs(audio.samples[0][i - 1] - audio.samples[0][i]);

		if (noteIndices.size() > 0) {
			spacing = i*timing - noteIndices.back();
		} else {
			spacing = minimalNoteSpacing + timing;
		}

		if (difference >= volumeThreshold && spacing >= minimalNoteSpacing) {
			noteIndices.push_back(i * timing);
		}
	}

	return noteIndices;
}

#endif /* _Channel_h */