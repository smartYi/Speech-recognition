//完成所有功能，能存储录音，但是未写自动生成background，未使用老师的classify判定方法
#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <conio.h>
#include <time.h>
#include <iostream>
using namespace std;

#include <math.h>
#include <memory.h>
#include <assert.h>
#include <string.h>
#include "readwave.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (16000)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (100)
#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
#define WRITE_TO_FILE   (1)

/* Select sample format. */
#if 0
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int forgetfactor = 1;      //forgetting factor,遗忘因子
float adjustment = 0.05;   //
float level = 0.03;
float threshold = 0.016;
float background = 450.0;
bool classifyFrame(float audioframe){
	//SAMPLE current = audioframe;
	bool isSpeech = false;
	/*level = ((level * forgetfactor) + current) / (forgetfactor+ 1);
	if (current < background)
		background = current;
    else
	    background += (current -background) * adjustment;
    if (level < background) level = background;
    if (level -background > threshold) isSpeech= true;*/
	if(audioframe>background)isSpeech = true;
    return isSpeech;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/


//++++++++++++++++++++++++++++++增加++++++++++++++++++++++++++++++++++++++++++++++++++
bool alreadyspeech = false;
time_t lastspeechtime;     //the last time on speech,最后在说话的时间
time_t pausespeechtime;    //the time that the speaker pause the speech,暂停说话的时间
time_t startrecord;        //the time begin to record,开始录音时间
double totalrecordtime;    //total times that the record last,录音的总时长
time_t startplay;          //the time begin to play,开始播音时间
time_t timeonplay;               //the time when it is on play,正在播音的当前时间
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


static int recordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	SAMPLE averagepower=0.0;
	float audiopower=0.0;
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if( inputBuffer == NULL )
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    }
    else
    {
        for( i=0; i<framesToCalc; i++ )
        {
            //++++++++++++++++++++++++++++增加+++++++++++++++++++++++++++++++++
			if(*rptr<0) audiopower -= *rptr;
			else audiopower += *rptr;
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			*wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;

	//++++++++++++++++++++++++++++++++增加++++++++++++++++++++++++++++++++++++++++
	averagepower = audiopower / framesToCalc;cout<<averagepower<<endl;
	bool onspeech = false;
	onspeech = classifyFrame(averagepower);
	if(onspeech){
		printf("average=1\n");
	}
	else{
		printf("average=0\n");
	}
	if(onspeech){              //当前在说话
		alreadyspeech = true;
		lastspeechtime = time(NULL);           //It is on speech at this time,表明当前时间仍在说话
	}
	if(!onspeech&&alreadyspeech&&finished==paContinue){    //当前未说话且之前已说过话并且录音正在进行
		pausespeechtime = time(NULL);
		if(difftime(pausespeechtime,lastspeechtime)>2)     //if there are two seconds people don't speech,超过两秒未说话
		{
			finished = paComplete;
			totalrecordtime = difftime(pausespeechtime,startrecord);
			printf("finished record!\n结束录音时间(stop recording time):%s\n",ctime(&pausespeechtime));
			printf("经过的时间:%f\n",totalrecordtime);
		}
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    return finished;
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int playCallback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *userData )
{
    paTestData *data = (paTestData*)userData;
    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    SAMPLE *wptr = (SAMPLE*)outputBuffer;
    unsigned int i;
    int finished;
    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) inputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        /* final buffer... */
        for( i=0; i<framesLeft; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
        for( ; i<framesPerBuffer; i++ )
        {
            *wptr++ = 0;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
        }
        data->frameIndex += framesLeft;
        finished = paComplete;
    }
    else
    {
        for( i=0; i<framesPerBuffer; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
        data->frameIndex += framesPerBuffer;
        finished = paContinue;
    }

	//++++++++++++++++++++++++++++++++++增加+++++++++++++++++++++++++++++++++++++++++++++++++++
	timeonplay = time(NULL);
	if(difftime(timeonplay,startplay)>=totalrecordtime){
		finished = paComplete;
		printf("finished playing!\n结束播音时间(stop playing time)：%s\n",ctime(&timeonplay));
	}
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    return finished;
}//+++++++++++++++++++++++++++++++++++++++++++++++增加++++++++++++++++++++++++++++++++++++++++++++++++++++++
//填充声波开头 
void FillWaveHeader(void *buffer, int raw_wave_len, int sampleRate)
{
	WavFileHead  wavHead;

	strcpy(wavHead.RIFF, "RIFF");
	strcpy(wavHead.WAVEfmt_, "WAVEfmt ");
	wavHead.FileLength = raw_wave_len + 36;
	wavHead.noUse = 16;
	wavHead.FormatCategory = 1;
	wavHead.NChannels = 1;
	wavHead.SampleRate = sampleRate;
	wavHead.SampleBytes = sampleRate*2;
	wavHead.BytesPerSample = 2;
	wavHead.NBitsPersample = 16;
	strcpy(wavHead.data, "data");
	wavHead.RawDataFileLength = raw_wave_len;

	memcpy(buffer, &wavHead, sizeof(WavFileHead));
}

//写声波 
void WriteWave(char *wavFile, short *waveData, int numSamples, int sampleRate)
{
	FILE	*wavFp;
	WavFileHead		wavHead;
	long	numWrite;

	wavFp = fopen(wavFile, "wb");
	if (!wavFp)	
	{
		printf("\nERROR:can't open %s!\n", wavFile);
		exit(0);
	}

	FillWaveHeader(&wavHead, numSamples*sizeof(short), sampleRate);
	fwrite(&wavHead, sizeof(WavFileHead), 1, wavFp);
	numWrite = fwrite(waveData, sizeof(short), numSamples, wavFp);
	assert(numWrite == numSamples);
	fclose(wavFp);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*******************************************************************/
int main(void)
{
    PaStreamParameters  inputParameters,
                        outputParameters;
    PaStream*           stream;
    PaError             err = paNoError;
    paTestData          data;
    int                 i;
    int                 totalFrames;
    int                 numSamples;
    int                 numBytes;
    SAMPLE              max, val;
    double              average;

    printf("patest_record.c\n"); fflush(stdout);

	//++++++++++++++++++++++++++++++++++++++++++++++++++
	printf("Please press any key to begin record！\n");
	while(!kbhit());
	//++++++++++++++++++++++++++++++++++++++++++++++++++

    data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    data.frameIndex = 0;
    numSamples = totalFrames * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    data.recordedSamples = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
    if( data.recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        goto done;
    }
    for( i=0; i<numSamples; i++ ) data.recordedSamples[i] = 0;

    err = Pa_Initialize();
    if( err != paNoError ) goto done;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        goto done;
    }
    inputParameters.channelCount = 1;                    /* stereo input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

	//++++++++++++++++++增加++++++++++++++++++++++++++++
	startrecord = time(NULL);
	printf("开始录音时间(begin recording time):%s\n",ctime(&startrecord));
	//++++++++++++++++++++++++++++++++++++++++++++++++++

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              recordCallback,
              &data );
    if( err != paNoError ) goto done;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto done;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

    while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
    {
        Pa_Sleep(1000);
        printf("index = %d\n", data.frameIndex ); fflush(stdout);
    }
    if( err < 0 ) goto done;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto done;

    /* Measure maximum peak amplitude. */
    max = 0;
    average = 0.0;
    for( i=0; i<numSamples; i++ )
    {
        val = data.recordedSamples[i];
        if( val < 0 ) val = -val; /* ABS */
        if( val > max )
        {
            max = val;
        }
        average += val;
    }

    average = average / (double)numSamples;

    printf("sample max amplitude = "PRINTF_S_FORMAT"\n", max );
    printf("sample average = %lf\n", average );

    /* Write recorded data to a file. */
#if WRITE_TO_FILE
    {
        /*FILE  *fid;
        fid = fopen("recorded.raw", "wb");
        if( fid == NULL )
        {
            printf("Could not open file.");
        }
        else
        {
            fwrite( data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid );
            fclose( fid );
            printf("Wrote data to 'recorded.raw'\n");
        }*/
		FILE  *fid;
        fid = fopen("project1_recorded.wav","wb");
		if( fid == NULL )
        {
            printf("Could not open file.");
        }
        else{
			WriteWave("project1_recorded.wav",data.recordedSamples,data.frameIndex , SAMPLE_RATE);
		}
    }
#endif

    /* Playback recorded data.  -------------------------------------------- */
    data.frameIndex = 0;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto done;
    }
    outputParameters.channelCount = 1;                     /* stereo output */
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    printf("\n=== Now playing back. ===\n"); fflush(stdout);

	//++++++++++++++++++增加++++++++++++++++++++++++++++
	startplay = time(NULL);
	printf("开始播音时间(begin playing time):%s\n",ctime(&startplay));
	//++++++++++++++++++++++++++++++++++++++++++++++++++

    err = Pa_OpenStream(
              &stream,
              NULL, /* no input */
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              playCallback,
              &data );
    if( err != paNoError ) goto done;

    if( stream )
    {
        err = Pa_StartStream( stream );
        if( err != paNoError ) goto done;
        
        printf("Waiting for playback to finish.\n"); fflush(stdout);

        while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
        if( err < 0 ) goto done;
        
        err = Pa_CloseStream( stream );
        if( err != paNoError ) goto done;
        
        printf("Done.\n"); fflush(stdout);
		system ("pause");
    }

done:
    Pa_Terminate();
    if( data.recordedSamples )       /* Sure it is NULL or valid. */
        free( data.recordedSamples );
    if( err != paNoError )
    {
        fprintf( stderr, "An error occured while using the portaudio stream\n" );
        fprintf( stderr, "Error number: %d\n", err );
        fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
        err = 1;          /* Always return 0 or 1, but no other return codes. */
    }
    return err;
}