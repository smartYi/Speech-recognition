#include <iostream>
#include "readwave.h"
#include "trainingdata.h"
#include "kmeandata.h"
#include <fstream>
#include  <direct.h>
#include <map>
#include "kmeanprocess.h"
using namespace std;

#define filenumber (9)
#define kmeantime (12)
string filenames[11] = {"zero\\", "one\\", "two\\", "three\\" ,"four\\" ,"five\\" ,"six\\" 
,"seven\\" ,"eight\\" ,"nine\\", "ten\\"};

string meanfilename[11] = {"mean0.txt", "mean1.txt", "mean2.txt", "mean3.txt", "mean4.txt", "mean5.txt",
"mean6.txt", "mean7.txt", "mean8.txt", "mean9.txt", "mean10.txt"};

string covfilename[11] = {"cov0.txt","cov1.txt","cov2.txt","cov3.txt","cov4.txt","cov5.txt",
"cov6.txt","cov7.txt","cov8.txt","cov9.txt","cov10.txt"};

int main()
{
	map<string, vector<kmeandata>> hmm_model;
	for (int num_file = 0; num_file < 11; num_file++)
	{
		vector<kmeandata> temp_kmean; 
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
			filename = filename + "\\zhengyu\\template\\";
			filename = filename + filenames[num_file];
			char t = i+1+48;
			filename = filename + t;
			char k = num_file + 48;
			if(num_file == 10)
				filename = filename + "\\digit_number_" + "10" + ".txt";
			else
				filename = filename + "\\digit_number_" + k + ".txt";
			trainingdata datatem = trainingdata(filename);
			data[i] = datatem;
		}

		// 初始化segmental kMean 算法
		// 对所有模板平均分为5个segment, 并加入到每一个state中,计算每一个segment的平均值
		for(int i = 0; i < filenumber; i++)
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

		
		for (int i = 0; i < 5; i++)
		{
			temp_kmean.push_back(kmean[i]);
		}
		hmm_model[filenames[num_file]] = temp_kmean;

		// 记录下当前数字的mean和cov

		string filename = meanfilename[num_file];
		ofstream midsamplevalue3;
		midsamplevalue3.open(filename);
		midsamplevalue3.clear();
		midsamplevalue3.close();
		ofstream midsamplevalue21;
		midsamplevalue21.open(filename,ios::app);
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 39; j++)
			{
				midsamplevalue21 << kmean[i].segment_mean[j] << endl;
			}
		}
		midsamplevalue21.close();

		string covfile = covfilename[num_file];
		ofstream shuchu;
		shuchu.open(covfile);
		shuchu.clear();
		shuchu.close();
		ofstream newshuchu;
		newshuchu.open(covfile, ios::app);

		for (int i = 0; i < 5; i++)
		{
			framedata tem = kmean[i].get_cov();
			for (int j = 0; j < 39; j++)
			{
				newshuchu << tem.data[j] << endl;
			}
		}
	}


	int num_current = 0;
	// test 计算准确率
 
	for (int num_file = 0; num_file < 11; num_file++)
	{
		for (int test_num = 1; test_num <= 5; test_num++)
		{
			char   buffer[100];   
			_getcwd(buffer, 100);   
			ifstream inputfile;
			string filename = buffer;
			filename = filename + "\\zhengyu\\" + filenames[num_file];
			char t = test_num + 48;
			filename = filename + t + "\\input_record.txt";
			trainingdata current_data = trainingdata(filename);

			double last_result = 10000000.0;
			int last_recon = 0;
			for (int kean_file = 0; kean_file < 11; kean_file++)
			{
				double sum = 0.0;
				kmeanprocess KP;
				kmeandata kmean[5];
				for (int i = 0; i < 5; i++)
					kmean[i] = hmm_model[filenames[kean_file]][i];
				vector<double> node_cost = KP.construc_covmatrix(kmean, current_data);
				sum = KP.dtw(node_cost);
				if(sum < last_result)
				{
					last_recon = kean_file;
					last_result = sum;
				}
			}

			cout << "The test number is " 
				<< num_file << ", the reconizing number is " << last_recon << endl; 

			if(last_recon == num_file)
				num_current++;
		}
	}

	cout << num_current << endl;
	system("pause");
	return 0;
}