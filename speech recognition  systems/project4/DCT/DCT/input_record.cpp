#include"stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include "readwave.h"
#include<ctime>
#include <vector>
#include <math.h>
#include<algorithm>
#include <fstream>
#include <ostream>
#include<conio.h>
using namespace std;

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (16000)
#define FRAMES_PER_BUFFER (400)
#define NUM_SECONDS     (100)
#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/
/** Set to 1 if you want to capture the recording to a file. */
#define WRITE_TO_FILE   (0)

#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#define PI     (3.1415926)
#define filterNum (40)
#define coffi1   (sqrt(1/(float)filterNum)) 
#define coffi2   (sqrt(2/(float)filterNum)) 




//////////////////////////////
double hamming(int m,int n)
{
       return (0.54-0.46*cos(2 * m * 3.1415926 / n ));
}
    
// hz to mel formulation
double hztomel(double hz)
{
	double mel = 2595 * log10(1.0 + (hz / 700));
	return mel;
}//构造函数，必须表明函数的返回值数据类型，然后在函数内部返回该值（数据类型必须一致）

double meltohz(double mel)
{
	double hz = 700 * (pow(10.0, mel / 2595) - 1);
	return hz;
}

//定义FFT
typedef struct 
{
	double real;
	double image;
}complex;

complex* fft(short* data, int length)
{
	// zero padding
	int z = 1;
	while (pow(2.0, z) < length)
	{
		z++;
	}
	int paddingLength = pow(2.0,z);
	// real 2 complex
	complex *TD = new complex[paddingLength];

	int i = 0;

	for (i = 0; i < paddingLength; i++)
	{
		TD[i].real = 0;
		TD[i].image = 0;
	}

	for (i = 0; i < length; i++)
	{
		TD[i].real = data[i];
		TD[i].image = 0;
	}

	int x, nv2, j, k, le, l, le1, ip, nm1;
	complex t, u, w;  //复数
	int ntemp = paddingLength;
	for(x = 0; paddingLength>1; x++)
		paddingLength /= 2;

	paddingLength = ntemp;

	nv2 = paddingLength/2;
	nm1 = paddingLength-1;

	j=1;

	for(i=1; i<=nm1; i++)
	{
		if(i<j)  //i是前一个点，j是后一个点
		{
			t.real = TD[i-1].real;
			t.image = TD[i-1].image;
			TD[i-1].real = TD[j-1].real; 
			TD[i-1].image = TD[j-1].image;
			TD[j-1].real = t.real;
			TD[j-1].image = t.image;  //后一个点被前一个点代替
		}
		k = nv2;
		while(k < j)
		{
			j -= k;
			k /= 2;
		}
		j += k;
	}

	le = 1;
	for(l = 1; l <= x; l++)
	{
		le *= 2;
		le1 = le / 2;
		u.real = 1.0f;
		u.image = 0.0f;
		w.real = (float)cos(PI/le1);
		w.image = (float)-sin(PI/le1);
		for(j=1; j <= le1; j++)
		{
			for(i=j; i <= paddingLength; i += le)
			{
				ip = i+le1;
				t.real = TD[ip-1].real*u.real-TD[ip-1].image*u.image;
				t.image = TD[ip-1].real*u.image+TD[ip-1].image*u.real;
				TD[ip-1].real = TD[i-1].real-t.real;
				TD[ip-1].image = TD[i-1].image-t.image;
				TD[i-1].real = t.real+TD[i-1].real;
				TD[i-1].image = t.image+TD[i-1].image;
			}
			t.real = u.real*w.real-u.image*w.image;
			t.image = u.image*w.real+u.real*w.image;
			u.real = t.real;
			u.image = t.image;
		}
	}

	return TD;
}


time_t startime, endtime,diftime, begintime, totalendtime;
time_t enginestar = time(NULL);

typedef enum StopResult
{
	noVoice = 0,
	haveVoice = 1,
	stopVoice = 2
}
recordLable;

recordLable test = noVoice;

int classifyFrame(SAMPLE voicevalue);


typedef struct
{
	int          frameIndex;  /* Index into sample array. */
	int          maxFrameIndex;
	SAMPLE      *recordedSamples;////SAMPLE是什么类型？不明白
	SAMPLE      *preemphaisesanples;
}
paTestData;////统一定义一个结构体paTestData,里面有四个参量，这个结构体在之后可以有不同名字，但是都包含这四个参量

paTestData procesed;///将paTestData这个结构体命名为procesed，因此procesed也包含如上四个参量，后面的data,smothdata都是这样的定义方法。

/************************************************************************/
/* initial function                                                     */
/************************************************************************/
/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int recordCallback( const void *inputBuffer, void *outputBuffer,
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData )
{
	paTestData *data = (paTestData*)userData;
	const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
	SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	SAMPLE *pro = &procesed.recordedSamples[procesed.frameIndex * NUM_CHANNELS];
	long framesToCalc;
	long i;
	int finished;
	unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
	SAMPLE amvalue;
	double ave;
	long double val;
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
			*pro++ = SAMPLE_SILENCE;
			*wptr++ = SAMPLE_SILENCE;  /* left */
			if( NUM_CHANNELS == 2 ) *pro++ = *wptr++ = SAMPLE_SILENCE;  /* right */
		}
	}
	else
	{   while(!_kbhit());
		amvalue = 0.0;
		ave = 0.0;
		val = 0.0;
		for( i=0; i<framesToCalc; i++ )
		{
			amvalue = *rptr;
			val += amvalue * amvalue;
			*pro++ = *rptr + 1;
			*wptr++ = *rptr++;  /* left */

			if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */

			if(amvalue < 0)
				amvalue = -amvalue;
			ave += amvalue;
		}
	}
	{
		ofstream valwrite;
		if (data->frameIndex == 0)
		{
			valwrite.open("val1.txt");
			val = 10 * log10(val);
			valwrite << val << endl;
		}

		valwrite.open("val1.txt",ios::app);
		val = 10 * log10(val);
		valwrite << val << endl;
	}
	ave = ave / framesToCalc;
	int isos = 0;
	isos = classifyFrame(val);
	printf("ave = %d\n", isos);
	
	{
		ofstream isspeechfile;
		isspeechfile.open("isspeech.txt", ios::app);
		isspeechfile << isos << endl;
		isspeechfile.close();
	}
	
	if(isos == 1)
	{
		test = haveVoice;
		time_t now_time;
		now_time = time(NULL);
		startime = now_time;
		procesed.frameIndex += framesToCalc;

	}
	if(isos == 0 && test == haveVoice)
	{

		time_t now_time;
		now_time = time(NULL);
		time_t diff = difftime(now_time, startime);

		if(diff > 3)
		{
			finished = paComplete;
			diftime = difftime(time(NULL), startime);
		}
	}

	data->frameIndex += framesToCalc;
	return finished;
}

  

/************************************************************************/
/*classifyFrame                                                         */
/************************************************************************/

float forgetfactor = 1.0;
float level = 73.0;
float adjustment = 0.05;
float threshold = 30;
SAMPLE background = 670.0;

int classifyFrame(SAMPLE voicevalue)
{
	int isspeech = 0;
	if (voicevalue > 80)
		isspeech = 1;
	return isspeech;
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

		finished = paContinue;
	}
	data->frameIndex += framesPerBuffer;
	if(*rptr == NULL)
		finished = paComplete;
	return finished;
	
}


/*******************************************************************/
void input_record()
{
	PaStreamParameters  inputParameters,
		                outputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;
	paTestData			smothdata;
	int                 i;
	int                 totalFrames;
	int					filedatatofalFrames;
	int                 numSamples;
	int					filenumSamples;
	int                 numBytes;
	int					filenumBytes;
	SAMPLE              max, val;
	double              average;
	vector<double>		strenth;
	vector<SAMPLE>		preempl;
	vector<int>			isspeech;
	vector<double>    windowed_raw_data;
	vector<short>      windowedsamplevalue;
	vector<double>     finalfftpower;
	vector<double>     melpower;
	vector<double>    dctsum;
	

	printf("patest_record.c\n"); fflush(stdout);
	procesed.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
	procesed.frameIndex = 0;
	smothdata.frameIndex = 0;
	smothdata.maxFrameIndex = NUM_SECONDS * SAMPLE_RATE;
	data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
	data.frameIndex = 0;
	numSamples = totalFrames * NUM_CHANNELS;
	numBytes = numSamples * sizeof(SAMPLE);
	data.recordedSamples = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
	smothdata.preemphaisesanples = (SAMPLE *) malloc( numBytes ); /* From now on, preemphaisesanples is initialised. */
	procesed.recordedSamples = (SAMPLE *) malloc( numBytes );//什么情况下必须先分配内存？
	smothdata.recordedSamples = (SAMPLE *) malloc( numBytes );
	
	if( data.recordedSamples == NULL )
	{
		printf("Could not allocate record array.\n");
		goto done;
	}
	for( i=0; i<numSamples; i++ ) 
	{
		procesed.recordedSamples[i] = 0;
		data.recordedSamples[i] = 0;
	}

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

	begintime = time(NULL);
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

	{
		ofstream isspeechfile;
		isspeechfile.open("isspeech.txt");
		isspeechfile.clear();
		isspeechfile.close();
	}
	printf("\n=== Now recording!! Please speak into the microphone. ===\n");
	fflush(stdout);

	while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
	{
		//Pa_Sleep(1000);
		//printf("index = %d\n", data.frameIndex ); fflush(stdout);
		//printf("%f", data.recordedSamples);
	}
	if( err < 0 ) goto done;

	err = Pa_CloseStream( stream );
	if( err != paNoError ) goto done;

	/* Get the isspeech array *///什么意思，看不懂
	{
		ifstream inputfile;
		inputfile.open("isspeech.txt");
		while(! inputfile.eof())
		{
			int temnumber;
			inputfile >> temnumber;
			isspeech.push_back(temnumber);
		}
	}



	int zerocount = 0;
	for (int i = 0; i < isspeech.size(); i++)
	{
		if (isspeech[i] == 0)
		{
			zerocount++;
		}
		if (isspeech[i] == 1)
		{
			if (zerocount < 6)
			{
				for(int j = 1; j <= zerocount; j++)
					isspeech[i - j] = 1;
			}			
			zerocount = 0;
		}
	}


	for (int i = 0; i < isspeech.size(); i++)
	{
		int mark = 0;
		if (mark == 0 && isspeech[i] == 1)
		{
			for(int j = 1; j <= 10; j++)
			{
				if (i-j >= 0)
				{
					isspeech[i - j] = 1;
				}
			}
			mark = 1;
		}
		if (mark == 1 && isspeech[i] == 0)
		{
			mark = 0;
			for(int j = 1; j <= 10; j++)
			{
				if(i + j < isspeech.size())
					isspeech[i++] = 1;
			}
		}
	}
	



	// extend the boundary of speech segment

	
	

	/* Smooth the value */
	SAMPLE *smo = &smothdata.recordedSamples[smothdata.frameIndex];
	max = 0;
	average = 0.0;
	int strenthindex = 0;

	for (int i = 0; i < isspeech.size(); i++)
	{
		if (isspeech[i] == 1)
		{
			for (int j = 0; j < 400; j++)
			{
				*smo++ = data.recordedSamples[(i * 400) + j];
			}
			smothdata.frameIndex += 400;
		}
	}

	SAMPLE *dataread;
	

	WriteWave( "input_record.wav", smothdata.recordedSamples ,smothdata.frameIndex, SAMPLE_RATE);
	{
		int dataread_numSample, dataread_RATE;
		dataread = ReadWavFile("input_record.wav", &dataread_numSample, &dataread_RATE);

		printf("%d", dataread_numSample);
		int valueindex = smothdata.frameIndex;
	}

	/////////////
	
	
	/* Write recorded data to a file. */
#if WRITE_TO_FILE
	{
		FILE  *fid;
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
		}
	}
#endif
	//进行预加重//
//········································//
	smothdata.preemphaisesanples[0] = smothdata.recordedSamples[0];
	for(int i=1;i<smothdata.frameIndex;i++)
		smothdata.preemphaisesanples[i] = smothdata.recordedSamples[i] - 0.95*smothdata.recordedSamples[i-1];

	///////////////////////
	

	//进行窗口化处理//
	//···········································//
	int wlen = 400;
	int  inc = 160;
	int fn = (smothdata.frameIndex - wlen + inc)/inc;
   

	for(int n=0;n<fn;n++){
		for(int m=0;m<wlen;m++)
			windowed_raw_data.push_back( smothdata.preemphaisesanples[m + inc*n]*hamming(m,wlen));
	}
	//////将窗口化vector转为数组//

	double* prezero = new double(fn*wlen);
	prezero = windowed_raw_data.data();
	//进行zero padding//
//····················································//
	 int padlen =512;
	 int  totallen = padlen * fn;
	

	for(int n=0;n<fn;n++)
		for(int m=0,i=0;m<wlen;){
			windowedsamplevalue.push_back(prezero[m+n*400]);
			m++;i++;
			if(m == wlen){
				for(;i<padlen;i++)
					windowedsamplevalue.push_back(0);
			}
		}

	
	//将加窗vector转为数组//
	//·································//
		short* prefftvalue = new short[totallen] ;
		prefftvalue = windowedsamplevalue.data();
		
	//········做FFT变换····················//
		short tocalufft[512];
		complex * tem;
		for(int i=0;i<fn;i++){
			for(int j=0;j<512;j++)
			tocalufft[j] = prefftvalue[j+i*512];
		tem =  fft(tocalufft,512);
		for(int n=0;n<512;n++)
			finalfftpower.push_back((tem[n].image * tem[n].image + tem[n].real * tem[n].real));
		
		}
		
	
//·················································//
	//将FFT能量vector转为数组//
	//·································//
		double* premel = new double[totallen] ;
		premel = finalfftpower.data();////finalfftpower.data()返回的是一个指针，这个指针指向data的首地址，然后将这个地址赋值给
		//new 返回的premel数组（也是一个指针），就可以通过调用premel数组来调用finalfftpower中的数据了，，如果要删除动态数组premel，可以通过调用
		//delete[]premel来进行。动态数组的使用可能会造成问题，最好是在使用完动态数组后对其进行delete操作。
		

	
		/////mel滤波器////////////////////////////////////////
		double maxmel = hztomel(SAMPLE_RATE / 2);
		double sideWidth = maxmel / (filterNum + 1);
		int filterBankPrm[filterNum][3] = {0}; // mel matrix
		
		for(int i = 0; i < filterNum; i++)
		{
			filterBankPrm[i][0] = int((meltohz(i * sideWidth) / SAMPLE_RATE * 512)) + 1;
			filterBankPrm[i][1] = int((meltohz((i+1) * sideWidth) / SAMPLE_RATE * 512)) + 1;
			filterBankPrm[i][2] = int((meltohz((i+2) * sideWidth) / SAMPLE_RATE * 512)) + 1;
		}
            filterBankPrm[filterNum-1][2] = 512/2;


		
		
		for(int win=0;win<fn;win++){

		double melenergy  [filterNum] = {0.0};
	
		for(int index = 0;index<filterNum;index++){
			for(int count=0;count<256;count++)
			{
				if(((count+1)>=filterBankPrm[index][0])&&((count+1)<filterBankPrm[index][1]))
					melenergy[index] +=( ((count+1)-filterBankPrm[index][0])/(float)(filterBankPrm[index][1]-filterBankPrm[index][0])*(premel[count+win*512]));
				
			  if((count+1>=filterBankPrm[index][1])&&((count+1)<filterBankPrm[index][2]))
				
			        melenergy[index] +=(((filterBankPrm[index][2]-(count+1))/(float) (filterBankPrm[index][2]-filterBankPrm[index][1]))* (premel[count+win*512]));
			 
			}
			melpower.push_back(melenergy[index]);
			
		
		}
		}


		//将mel能量vector转为数组//
	//·································//
		double* prelogmel = new double[fn*filterNum] ;
		prelogmel =melpower.data();

	

		
		// DCT transfromation

		
	for(int win=0;win<fn;win++){
    float temp[13] = {0.0};
     	for(int i = 0; i < 13; i++)
	{
		   for(int j = 0; j < filterNum; j++){
			   if(prelogmel[j+filterNum*win] == 0)
				   temp[i] +=prelogmel[j+40*win];
			   else
			temp[i] +=(log(prelogmel[j+filterNum*win]) * cos( ( (PI * i) / (2 * filterNum) ) * ((2 * j) + 1)));
		  
		   }
		   if(i==0){
			   temp[i] = temp[i]*coffi1;
		   dctsum.push_back(temp[i]);
		   }
		   else{
			   temp[i] = temp[i]*coffi2;
		   dctsum.push_back(temp[i]);
		   }
		}
	}
	
	
		//将DCT转为数组//
		//······························/
		double* dct = new double[fn*13];
		dct = dctsum.data();
		
	
	////////////////////////////////////////////
	
////////////mean归一化///////////////
		double sumpower[13] = {0.0};
		double averagesum[13] = {0.0};
		for(int i =0;i<13;i++)
		    for(int index = 0;index<fn;index++)
				sumpower[i] +=dct[i+index*13];
		for(int i=0;i<13;i++)
			averagesum[i] = sumpower[i]/(double)fn;///求得归一化向量//

	for(int index=0;index<fn;index++)
		for(int i=0;i<13;i++){
			if(dct[i+index*13]!=0)
				dct[i+index*13] = dct[i+index*13] - averagesum[i];
		}

		////////////////方差归一化////////////////////////////
		double sumpower2[13] = {0.0};
		double averagesum2[13] = {0.0};
		for(int i =0;i<13;i++)
		    for(int index = 0;index<fn;index++)
				sumpower2[i] +=dct[i+index*13]*dct[i+index*13];
		for(int i=0;i<13;i++)
			averagesum2[i] = sqrt(sumpower2[i]/(double)fn);///求得归一化向量//

	for(int index=0;index<fn;index++)
		for(int i=0;i<13;i++){
			
				dct[i+index*13] = dct[i+index*13] / averagesum2[i];
		}
	////////////////////////////////////
	//////将13组DCT系数转化为39组特征/////zhengyu
	//////////////////////////////////

		// 先把每一个部分的增量求出 zhengyu
		double *first_dct = new double[(fn-2)*13];
		double *second_dct = new double[(fn-4)*13];
		for(int index = 0; index < fn-2; index++)
		{
			for (int i = 0; i < 13; i++)
			{
				first_dct[i + index * 13] = dct[i+(index+2)*13] - dct[i+index*13];
			}
		}	
		for(int index = 0; index < fn - 4; index++)
		{
			for (int i = 0; i < 13; i++)
			{
				second_dct[i + index * 13] = first_dct[i+(index+2)*13] - first_dct[i+index*13];
			}
		}
		
		double *feature_c = new double[(fn-4) * 39];
		int count = 0;
		// 将每一帧的39组合并 zhengyu
		for (int index = 2; index < fn-2; index++)
		{
			int index_mark = 0;
			for(int j = 0; j < 13; j++)
			{
				feature_c[j + count * 39] = dct[j + index * 13];
				feature_c[(j+13) + count * 39] = first_dct[j + (index-1)*13];
				feature_c[(j+26) + count * 39] = second_dct[j + (index-2)*13];
			}
		}

		
	////////////////////////////////////////////
	
	//////////归一化后的数据///////
		
		{
		ofstream midsamplevalue3;
		midsamplevalue3.open("input_record.txt");
		midsamplevalue3.clear();
		midsamplevalue3.close();
		ofstream midsamplevalue21;
		midsamplevalue21.open("input_record.txt",ios::app);
		for(int i=0;i<fn*13;i++){
			if(i!= 0 && i%13 == 0)
				midsamplevalue21<<endl;
			midsamplevalue21<<dct[i]<<" ";
		}
	
	midsamplevalue21.close();
	}

  
	///* Playback recorded data.  -------------------------------------------- */
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

	//printf("\n=== Now playing back. ===\n"); fflush(stdout);
	//err = Pa_OpenStream(
	//	&stream,
	//	NULL, /* no input */
	//	&outputParameters,
	//	SAMPLE_RATE,
	//	FRAMES_PER_BUFFER,
	//	paClipOff,      /* we won't output out of range samples so don't bother clipping them */
	//	playCallback,
	//	&data );
	//if( err != paNoError ) goto done;

	//if( stream )
	//{
	//	err = Pa_StartStream( stream );
	//	if( err != paNoError ) goto done;

	//	printf("Waiting for playback to finish.\n"); fflush(stdout);

	//	while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
	//	if( err < 0 ) goto done;

	//	
	//	err = Pa_CloseStream( stream );
	//	if( err != paNoError ) goto done;

	//	printf("Done.\n"); fflush(stdout);
	//}


	////// play the proceed audio data
	//Pa_Sleep(1000);
	//procesed.frameIndex = 0;
	//printf("\n=== Now playing back. ===\n"); fflush(stdout);
	//err = Pa_OpenStream(
	//	&stream,
	//	NULL, /* no input */
	//	&outputParameters,
	//	SAMPLE_RATE,
	//	FRAMES_PER_BUFFER,
	//	paClipOff,      /* we won't output out of range samples so don't bother clipping them */
	//	playCallback,
	//	&procesed );
	//if( err != paNoError ) goto done;

	//if( stream )
	//{
	//	err = Pa_StartStream( stream );
	//	if( err != paNoError ) goto done;

	//	printf("Waiting for playback to finish.\n"); fflush(stdout);

	//	while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
	//	if( err < 0 ) goto done;


	//	err = Pa_CloseStream( stream );
	//	if( err != paNoError ) goto done;

	//	printf("Done.\n"); fflush(stdout);
	//}

	system("pause");

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

	
}

