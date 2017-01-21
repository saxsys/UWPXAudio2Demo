#include "pch.h"
#include "AudioComponent.h"

using namespace WindowsRuntimeComponent;
using namespace Platform;

AudioComponent::AudioComponent()
{
	XAudio2Create(&xaudio_engine);
	xaudio_engine->CreateMasteringVoice(&xaudio_master);

	ZeroMemory(&xaudio_buffer, sizeof(xaudio_buffer));
	xaudio_buffer.AudioBytes = BUFFERSIZE;

	WAVEFORMATEX waveformat;
	waveformat.nChannels = 1;
	waveformat.nSamplesPerSec = SAMPLERATE;
	waveformat.wBitsPerSample = 8;
	waveformat.nAvgBytesPerSec = SAMPLERATE;
	waveformat.wFormatTag = WAVE_FORMAT_PCM;
	waveformat.nBlockAlign = 1;
	waveformat.cbSize = 0;

	xaudio_engine->CreateSourceVoice(&xaudio_source, &waveformat, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL);
	xaudio_source->Start();

	sounddata = new BYTE[BUFFERSIZE];
	for (int i = 0; i < BUFFERSIZE; i++)
	{
		double v = sin(2 * PI * i * (440.0 / SAMPLERATE));
		sounddata[i] = (BYTE)(v * 128) + 128;
	}

	xaudio_buffer.pAudioData = sounddata;
}

void AudioComponent::PlayTone()
{
	xaudio_source->SubmitSourceBuffer(&xaudio_buffer);
}

AudioComponent::~AudioComponent()
{
	xaudio_engine->Release();
	delete sounddata;
}