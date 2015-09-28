#include <iostream>
#include "readwave.h"
#include "trainingdata.h"
#include "kmeandata.h"
#include <fstream>
#include  <direct.h>
#include "kmeanprocess.h"
using namespace std;

#define filenumber (5)
#define kmeantime (12)
string filenames[10] = {"zero\\", "one\\", "two\\", "three\\" ,"four\\" ,"five\\" ,"six\\" 
						,"seven\\" ,"eight\\" ,"nine\\"};

int main()
{
	for (int num_file = 0; num_file < 10; num_file++)
	{
		trainingdata data[filenumber];
		kmeandata kmean[5];
		kmeanprocess KP;

		// 读取所有的模板文件
		for (int i = 0; i < filenumber; i++)
		{
			char   buffer[100];   
			_getcwd(buffer, 100);   
			ifstream inputfile;
			string filename = buffer;
			filename = filename + "\\template\\";
			filename = filename + filenames[num_file];
			char t = i+1+48;
			filename = filename + t;
			char k = num_file + 48;
			filename = filename + "\\digit_number_" + k + ".txt";
			trainingdata datatem = trainingdata(filename);
			data[i] = datatem;
		}

		// 初始化segmental kMean 算法
		// 对所有模板平均分为5个segment, 并加入到每一个state中,计算每一个segment的平均值
		for(int i = 0; i < 5; i++)
		{
			int current_state = 0;
			int each_frame;
			each_frame = data[i].frame_count / 5;
			for (int j = 0; j < data[i].frame_count; j++)
			{
				kmean[current_state].push_segment(data[i].dctdata[j]);
				if((j+1) % (each_frame) == 0 && current_state < 4)
					current_state++;
			}
		}
		// 正式K-mean
		int time = kmeantime;
		while (time--) // 当设定一个迭代次数或者检测是否收敛
		{
			vector<double> test[filenumber];

			for(int i = 0; i < filenumber; i++)
			{
				test[i] = KP.construc_covmatrix(kmean, data[i]);
				//KP.transi_probile(kmean);
			}

			for(int cl = 0; cl < 5; cl++) // 清空segment内数据，重新分配
				kmean[cl].clear();
			for(int i = 0; i < filenumber; i++)
			{
				vector<int> seg_index;
				seg_index = KP.dtwprocess(test[i]);


				for (int sta = 0; sta < 5; sta++)
				{
					for (int j = seg_index[sta]; j < seg_index[sta+1]; j++)
					{
						kmean[sta].push_segment(data[i].dctdata[j]);
					}
				}

			}

		}

		//for(int i = 0; i < 10; i++)
		//{
		//	char   buffer[100];   
		//	_getcwd(buffer, 100);   
		//	ifstream inputfile;
		//	string filename = buffer;
		//	filename = filename + "\\kemanresult\\";
		//	filename = filename + filenames[i];
		//	char t = filenum+1+48;
		//	filename = filename + t;
		//	filename = filename + ".txt";
		//}

		for (int filenum = 0; filenum < filenumber; filenum++)
		{
			char   buffer[100];   
			_getcwd(buffer, 100);   
			ifstream inputfile;
			string filename = buffer;
			filename = filename + "\\kemanresult\\" + filenames[num_file];
			char t = filenum+1+48;
			filename = filename + t;
			filename = filename + ".txt";
			ofstream outputfile;
			outputfile.open(filename);
			outputfile.clear();
			outputfile.close();
			ofstream outputfile2;
			outputfile2.open(filename,ios::app);
			for(int i=0;i< 39;i++)
				outputfile2 << kmean[0].segment_mean[i] << endl;
			outputfile2.close();
		}
	}

	//// test 计算准确率
	for (int i = 0; i < 50; i++)
	{
		char   buffer[100];   
		_getcwd(buffer, 100);   
		ifstream inputfile;
		string filename = buffer;
		filename = filename + "\\zero\\";
		char t = i+1+48;
		filename = filename + t;
		filename = filename + "\\delta.txt";
		trainingdata datatem = trainingdata(filename);


	}

	system("pause");
	return 0;
}