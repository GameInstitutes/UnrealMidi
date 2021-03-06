// Copyright 2011 Alex Leffelman
// Updated 2016 Scott Bishel

#pragma once

#include "../MidiEvent.h"

#include <sstream>
using namespace std;

/**
 * abstract class for meta events
 */
class MIDI_API MetaEvent : public MidiEvent
{
protected:
	VariableLengthInt * mLength;

	MetaEvent(long tick, long delta, int type, VariableLengthInt * length);
	virtual ~MetaEvent();

	virtual int getEventSize() = 0;
public:
	virtual void writeToFile(FMemoryWriter & output, bool writeType);

protected:
	virtual void writeToFile(FMemoryWriter & output);

public:
	static MetaEvent * parseMetaEvent(long tick, long delta, FBufferReader & input);

protected:
	class MetaEventData
	{
	public:
		int type;
		VariableLengthInt* length;
		char* data;

		MetaEventData(FBufferReader& input) : type(0), length(NULL), data(NULL)
		{
			input.Serialize(&type, 1);
			length = new VariableLengthInt(input);
			data = new char[length->getValue()];
			if (length->getValue() > 0)
			{
				input.Serialize(&data, length->getValue());
			}
		}
	};

public:
	static const int SEQUENCE_NUMBER = 0;
	static const int TEXT_EVENT = 1;
	static const int COPYRIGHT_NOTICE = 2;
	static const int TRACK_NAME = 3;
	static const int INSTRUMENT_NAME = 4;
	static const int LYRICS = 5;
	static const int MARKER = 6;
	static const int CUE_POINT = 7;
	static const int MIDI_CHANNEL_PREFIX = 0x20;
	static const int END_OF_TRACK = 0x2F;
	static const int TEMPO = 0x51;
	static const int SMPTE_OFFSET = 0x54;
	static const int TIME_SIGNATURE = 0x58;
	static const int KEY_SIGNATURE = 0x59;
	static const int SEQUENCER_SPECIFIC = 0x7F;
};
