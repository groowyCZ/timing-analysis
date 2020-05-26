#include "headers/Channel.h"
#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <string>
#include <getopt.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;
using std::exception;
using std::ofstream;
using std::vector;


void writeSamples(Channel channel) {
	double timing = channel.getTiming();
	vector<double> samples = channel.getSamples()[0];

	ofstream file;
	file.open("samples.csv");

	if (file.is_open()) {
		for (int i = 0; i < (int)samples.size(); i++) {
			file << (double)i*timing << "," << samples[i]  << endl;
		}

		file.close();
	} else {
		cout << "Couldn't open file \"samples.csv\"" << endl;
	}
}

void writeNoteIndices(Channel channel) {
	double timing = channel.getTiming();
	vector<double> samples = channel.getSamples()[0];
	vector<double> noteIndices = channel.getNoteIndices();

	ofstream file;
	file.open("note_indices.csv");

	if (file.is_open()) {
		for (int i = 0; i < (int)noteIndices.size(); i++) {
			file << noteIndices[i] << "," << samples[(int)(noteIndices[i]/timing)] << endl;
		}

		file.close();
	} else {
		cout << "Couldn't open file \"mote_indices.csv\"" << endl;
	}
}

void displayUsage() {
	cout << "Options:" << endl;
	cout << "\t-f, --file <path to wave file>" << endl;
	cout << "\t-m, --min-note-spacing <minimal distance between notes in seconds>" << endl;
	cout << "\t-v, --volume-threshold <volume threshold for note detection>" << endl;
	cout << "\t-p, --use-percents" << endl;
	cout << "\t-h, --help" << endl;
}

static const char *optString = "f:m:v:ph";
static const struct option longOpts[] = {
	{"file", required_argument, NULL, 'f'},
	{"min-note-spacing", required_argument, NULL, 'm'},
	{"volume-threshold", required_argument, NULL, 'v'},
	{"use-percents", no_argument, NULL, 'p'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

template<typename T>
struct arg_t {
	T value;
	bool setted = false;
};

int main(int argc, char *argv[])
{
	if (argc > 1) {
		int opt;
		int optionIndex = 0;

		arg_t<string> filename;
		arg_t<double> minimalNoteSpacing;
		arg_t<double> volumeThreshold;
		bool usePercents = false;

		while ((opt = getopt_long(argc, argv, optString, longOpts, &optionIndex)) != -1) {
			switch (opt) {
				case 'f':
					filename.value = optarg;
					filename.setted = true;
					break;
				case 'm':
					minimalNoteSpacing.value = atof(optarg);
					minimalNoteSpacing.setted = true;
					break;
				case 'v':
					volumeThreshold.value = atof(optarg);
					volumeThreshold.setted = true;
					break;
				case 'p':
					usePercents = true;
					break;
				case 'h':
					displayUsage();
					return 0;
			}
		}

		// checks

		if (!filename.setted) {
			cout << "You must specify filename. (option -f, --file)" << endl;
			return 1;
		}

		if (!minimalNoteSpacing.setted) {
			cout << "You must specify minimal spacing between notes in seconds. (option -m, --min-note-spacing)" << endl;
			return 1;
		}

		if (!volumeThreshold.setted) {
			cout << "You must specify volume threshold for note detection. (option -v, -volume-threshold)" << endl;
			return 1;
		}

		try {
			Channel channel(filename.value, minimalNoteSpacing.value, volumeThreshold.value, usePercents);
			writeSamples(channel);
			writeNoteIndices(channel);
		} catch (exception& ex) {
			cout << ex.what() << endl;
			return 1;
		}
	} else {
		displayUsage();
		return 1;
	}

	return 0;
}
