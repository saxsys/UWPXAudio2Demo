#pragma once
#include <xaudio2.h>

#define PI 3.14159265358979323846f
#define SAMPLERATE 44100  
#define BUFFERSIZE 22500

namespace WindowsRuntimeComponent
{
	public ref class AudioComponent sealed
	{
	public:
		AudioComponent();
		virtual ~AudioComponent();

		void PlayTone();

	private:
		BYTE* sounddata;

		IXAudio2* xaudio_engine;

		XAUDIO2_BUFFER xaudio_buffer;
		IXAudio2SourceVoice* xaudio_source;
		IXAudio2MasteringVoice* xaudio_master;
	};
}
