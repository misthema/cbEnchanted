#include "cbchannel.h"
#include "debug.h"
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

CBChannel::CBChannel(): bufferCount(3), sampleCount(4000), flow(NULL), instance(NULL)
{

}

CBChannel::~CBChannel() {
	if (playtype == soundType) {
		al_destroy_sample_instance(instance);
	}
	else {
		al_destroy_audio_stream(flow);
	}
}
void CBChannel::playSound(CBSound &sound,  float volume, float pan, int32_t freq) {

	instance = al_create_sample_instance(sound.getSample());
	al_attach_sample_instance_to_mixer(instance, mixer);
	playtype = soundType;

	if (volume==100.0) {
		al_set_sample_instance_gain(instance,  sound.getGain());
	}
	else {
		float newGain = float(volume) / 100.0;
		al_set_sample_instance_gain(instance, newGain);
	}

	if (pan==0.0) {
		al_set_sample_instance_pan(instance, sound.getBalance());
	}
	else {
		float newPan = float(pan) / 100.0;
		al_set_sample_instance_pan(instance, newPan);
	}


	if (freq>0.0f) {
		float newFreq = freq / float(sound.getFreq());
		al_set_sample_instance_speed(instance, newFreq);
	}
	else {
		al_set_sample_instance_speed(instance, sound.getFreqScale());
	}


	if (sound.isLooping())
		al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);

	al_play_sample_instance(instance);
}

void CBChannel::playSound(string str,  float volume, float pan, int32_t freq) {

	flow = al_load_audio_stream(str.c_str(), bufferCount, sampleCount);
	al_attach_audio_stream_to_mixer(flow, mixer);
	playtype = streamType;

	float streamGain = al_get_audio_stream_gain(flow);
	uint32_t frequency = al_get_audio_stream_frequency(flow);

	if (volume==100.0) {
		al_set_audio_stream_gain(flow, streamGain);
	}
	else {
		al_set_audio_stream_gain(flow, volume / 100.0 * streamGain);
	}

	if (pan != 0){
		al_set_audio_stream_pan(flow, 0.0);
	}
	else {
		al_set_audio_stream_pan(flow, pan / 100.0);
	}

	if (freq != frequency) {
		float speed = float(freq) / float(frequency);
		al_set_audio_stream_speed(flow, speed);
	}
	else {
		al_set_audio_stream_speed(flow, 1.0);
	}
	al_set_audio_stream_playing(flow, true);
}

bool CBChannel::isPlaying() {
	switch (playtype) {
		case soundType:
			return al_get_sample_instance_playing(instance);
		break;
		case streamType:
			return al_get_audio_stream_playing(flow);
		break;
	}
}

void CBChannel::freeChannel() {
	if (instance != NULL) {
		//al_detach_sample_instance(instance);
		al_destroy_sample_instance(instance);
	}
	if (flow != NULL) {
		//al_detach_audio_stream(flow);
		al_destroy_audio_stream(flow);
	}
	INFO("Vapautettu'd");
}

void CBChannel::stopSound() {
	switch (playtype) {
		case soundType:
			al_set_sample_instance_playing(instance, false);
		break;
		case streamType:
			al_set_audio_stream_playing(flow, false);
		break;
	}
}
