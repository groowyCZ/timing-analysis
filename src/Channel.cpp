#include "Channel.h"

Channel::Channel(const string &fileName, double minimalNoteSpacing, double volumeThreshold, bool usePercents = false)
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

		if (noteIndices.empty()) {
			spacing = minimalNoteSpacing + timing;
		} else {
			spacing = i*timing - noteIndices.back();
		}

		if (difference >= volumeThreshold && spacing >= minimalNoteSpacing) {
			noteIndices.push_back(i * timing);
		}
	}

	return noteIndices;
}
