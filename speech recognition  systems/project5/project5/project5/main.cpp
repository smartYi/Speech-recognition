#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>


const int SIZE = 26;
const int Treesize = 26822;
const int loop_back_cost = 1;

using namespace std;

int  letters = 0;
int Trelly1[Treesize][20];//problem1
int Trelly2[Treesize][615];//problem2 
char Tree_letter[Treesize];
int transition[Treesize];
int if_leaf[Treesize];
int location[Treesize];


//构建lextree 数据结构

typedef struct Trie
{
	Trie *next[SIZE];    //一律只考虑小写字母
	int flag;            //判断是否是词尾,1为词尾
	char element;        //当前结点的字母
	int level;           //标记当前结点层数
	int  count;         //记录单词是字典vector中的第几个单词
	int distance[25];   //记录每个结点的历史距离
	int exit_next;     //记录该节点之后是否还有分支
	Trie *initial;      //用来储存每个单词结束时的根节点
}Trie;

Trie root;  //构建字典树的根节点


int CreatLextree(string str,int number){
	
	int level_adder = 0;  //用来标记当前结点层数,每当更新存储单词，层数重新开始
	int len = str.length();
	Trie *p = &root, *q;
	for(int i=0;i<len;i++)
	{
		str[i] = tolower(str[i]);//只考虑小写字母
		int id = str[i] - 'a';
		if(id>25||id<0)  //如果不是字母，则不放入字典树中
			continue;
		if(p->next[id] == NULL)
		{
			letters++;
			p->exit_next =1;
			q = (Trie *)malloc(sizeof(root));
			q->initial = &root;                   //如果是一个单词结尾，标记一个回到根节点的指针
			for(int i=0;i<25;i++)
				q->distance[i] = 100;
			q->level = ++level_adder;
			q->element = str[i];
			for(int i=0;i<SIZE;i++)
				q->next[i] = NULL;
			q->exit_next =0;
			p->next[id] = q;
			p = p->next[id];
			if((i==len-1)||(i==len-2&&str[i+1]=='\'')){    //判断是否是词尾
				q->flag =1;
				q->count = number;
			}
			else
				q->flag=0;
		}
		else{
			p = p->next[id];
			level_adder++;  //往下移动结点，相应的层数加1
		}//if
	}// for
	return level_adder;
}

//字典矩阵的计算方法
vector<string> get_fixed(vector<string> input,char tree_trelly[],int transport[],vector<string> dict){

	vector<string> return_string;

	for(int i=0;i<input.size();i++){
		
		string temp = input.at(i);
		temp = '*' + temp;
		int len = temp.size();
		Trelly1[0][0] = 0;
		//第一行单独赋值
		for(int j=1;j<len;j++)
			Trelly1[0][j] = Trelly1[0][j-1]+1;
		//第一列单独赋值
		for(int j=1;j<Treesize;j++)
			Trelly1[j][0] = Trelly1[transport[j]][0]+1;
			

		for(int i=1;i<Treesize;i++)
			for(int j=1;j<len;j++){
				int cost1,cost2,cost3;
				cost1 = Trelly1[i][j-1]+1;
				cost2 = Trelly1[transport[i]][j]+1;
				if(tree_trelly[i]==temp[j])
					cost3 = Trelly1[transport[i]][j-1];
				else
					cost3 =Trelly1[transport[i]][j-1]+1;
				Trelly1[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
			}
			
			//找出最匹配单词,problem1
			int mini = 1000;
			int index =0;
			int site=0;
			for(int i=0;i<Treesize;i++)
				if(if_leaf[i]==1&&Trelly1[i][len-1]<=mini){
					index = i;
					mini = Trelly1[i][len-1];
				}
				site = location[index];
				return_string.push_back(dict.at(site));

	}
	return return_string;
}


//做分词处理 case2,case3
vector<string> get_segementation0(vector<char> pre_segment,char tree_trelly[],int transport[],vector<string> dict){

	vector<string> right_segement_words;
	vector<int> state;
	Trelly2[0][0] = 0;
	Trelly2[0][1] = 1;


	//第一列赋值
		for(int i=1;i<Treesize;i++)
			Trelly2[i][0] = Trelly2[transport[i]][0]+1;
		state.push_back(0);

		//第二列赋值
		for(int i=1;i<Treesize;i++){
			int cost1,cost2,cost3;
			cost1 = Trelly2[i][0] + 1;
			cost2 = Trelly2[transport[i]][1] +1;
			if(tree_trelly[i]==pre_segment.at(1))
				cost3 = Trelly2[transport[i]][0];
			else
				cost3 = Trelly2[transport[i]][0] + 1;
			Trelly2[i][1] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
		}

		state.push_back(0);

		int state_index = -1;
		for(int j=2;j<pre_segment.size();j++){
			//先找出前一列所有叶子节点的最小值
				int minimum = 1000;
				for(int k=1;k<Treesize;k++){
					if(if_leaf[k]==1&&Trelly2[k][j-1]<minimum){
						minimum = Trelly2[k][j-1];
					state_index = k;
					}
				}
			     int site = location[state_index];
				   state.push_back(site);
				   Trelly2[0][j] = minimum + loop_back_cost;

				for(int i=1;i<Treesize;i++){
					int cost1,cost2,cost3;
					if(transport[i]==0){
						if(tree_trelly[i] == pre_segment.at(j))
						cost1 = Trelly2[transport[i]][j];
						else
							cost1 = Trelly2[transport[i]][j]+1;
			           cost2 = Trelly2[i][j-1]  + 1;
					  Trelly2[i][j] = cost1<cost2?cost1:cost2;
					}
					else{
					 cost1 = Trelly2[transport[i]][j] +1;
			         cost2 = Trelly2[i][j-1]  + 1;
			     if(tree_trelly[i] == pre_segment.at(j))
				     cost3 = Trelly2[transport[i]][j-1];
			     else 
				     cost3 = Trelly2[transport[i]][j-1]+1;
				 Trelly2[i][j] = cost1<cost2?(cost1<cost3?cost1:cost3):(cost2<cost3?cost2:cost3);
				}
				}
		}
		/*for(int i=0;i<state.size();i++)
			cout<<dict.at(state.at(i))<<" "; 
		system("pause");*/
		//现在开始回溯
		
		int minimum =1000;
		string temp = "";
		int index=0;
		for(int i=1;i<Treesize;i++)
			if(if_leaf[i] == 1&&Trelly2[i][pre_segment.size()-1]<=minimum){
				minimum = Trelly2[i][pre_segment.size()-1];
				index = i;
			}
			/*int j=pre_segment.size()-1;
			while(j>0){
				int site = location[index];
				temp  = dict.at(site);
				right_segement_words.push_back(temp);
				j = j - temp.size();
				temp="";
				int mini =1000;
				for(int i=1;i<Treesize;i++)
			if(if_leaf[i] == 1&&Trelly2[i][j]<mini){
				mini = Trelly2[i][j];
				index = i;
			}
			}*/

	//		//通过C++来制作表格
	//cout<<left;
	//cout<<setw(6)<<" ";
	//for(int i=0;i<pre_segment.size();i++)
	//	cout<<setw(6)<<pre_segment.at(i);
	//    cout<<endl;
	//	for(int i=0;i<25;i++){
	//		cout<<setw(6)<<tree_trelly[i];
	//		for(int j=0;j<pre_segment.size();j++){
	//        cout<<setw(6)<<Trelly2[i][j];
	//	}
	//	cout<<endl;
	//}
	//	
			int j=pre_segment.size()-1;
			while(j>0){
				if(index ==0){
					int mini = 1000;
					right_segement_words.push_back(temp);
					temp = "";
					for(int m=1;m<Treesize;m++){
						if(if_leaf[m]==1&&Trelly2[m][j-1]<mini){
							mini = Trelly2[m][j-1];
							index = m;
						}
					}
					j = j-1;
				}
				
				else{
					temp = tree_trelly[index] + temp;
					if(transport[index]==0){
						index = transport[index];
					}
					else{
				if(Trelly2[index][j-1] == Trelly2[index][j]-1)
					j = j-1;
				else if(Trelly2[transport[index]][j] == Trelly2[index][j]-1)
					index = transport[index];
				else 
				{
					index = transport[index];
					j = j-1;
				}
			}
				}
			}
	right_segement_words.push_back(temp);
	return right_segement_words;
}//get_segementation0
int main(){
	vector <string>  templs_vector;  //用来存储字典单词
    vector <string>  inputs_vector;  //用来存储比较文本单词
	vector <string>  fixed_words;    //用来存储识别后的单词
	vector<char>   unsegement0_vector;//用来储存正确文本未分割单词的字母
	vector<char>   unsegement_vector;//用来储存错误文本未分割单词的字母
	vector<string> segemented0_words;//用来储存正确文本分词后的单词
	vector<string> segemented_words;//用来储存错误文本分词后的单词
	vector<string> right_words;//用来正确文本的单词
	int max_level = -1;                   //找出最长单词的层数
	int temp_max_level = 0;
	int choice = -1;

	//读取字典单词到vector里面
   ifstream templread("dict_1.txt");
   string maintempl;
    while(templread>>maintempl)
	templs_vector.push_back(maintempl);
	

	//读取文本单词到vector里面
   ifstream txtread("typos.txt");
   string txt;
    while(txtread>>txt)
	inputs_vector.push_back(txt);

	//读取正确未分割文本unsegemented0.txt
	ifstream unsegment0("unsegmented0.txt");
	if(!unsegment0){
		cout<<"Can not open a file!";
		exit(1);}
	char unsegement0_letter;
	while(unsegment0>>unsegement0_letter)
		unsegement0_vector.push_back(unsegement0_letter);
	unsegement0_vector.insert(unsegement0_vector.begin(),'*');

	

	

	//读取错误未分割文本unsegemented.txt
	ifstream unsegment("unsegmented.txt");
	if(!unsegment){
		cout<<"Can not open a file!";
		exit(1);}
	char unsegement_letter;
	while(unsegment>>unsegement_letter)
		unsegement_vector.push_back(unsegement_letter);
	unsegement_vector.insert(unsegement_vector.begin(),'*');

	

	//读取分割文本segemented.txt
	ifstream segment("segmented.txt");
	if(!segment){
		cout<<"Can not open a file!";
		exit(1);}
	string segment_word;
	while(segment>>segment_word)
		right_words.push_back(segment_word);

	//读取我的文本my_dict.txt
	vector<string> my_vector;
	ifstream segment2("my_dict.txt");
	if(!segment2){
		cout<<"Can not open a file!";
		exit(1);}
	string segment_word2;
	while(segment2>>segment_word2)
		my_vector.push_back(segment_word2);

	/*cout<<my_vector.size();
	system("pause");*/


	//将根节点的26个子节点初始化NULL
	for(int i=0;i<SIZE;i++)
		root.next[i] = NULL;
	root.element = '*';       //所有单词前面都加上*
	root.level = 0;//根结点的层数为0
	//构建字典树
	for(int i=0;i<templs_vector.size();i++){
		temp_max_level = CreatLextree(templs_vector.at(i),i);
		if(temp_max_level>max_level)
			max_level = temp_max_level;
	}
	

	//构建字典树矩阵

	    int m=0,n=0;
		int current=0;
		vector<Trie> Queue;
		Queue.push_back(root);
		Tree_letter[0] = root.element;
		transition[0] = 0;
		/*cout<<p->element;
		system("pause");*/

		while(current!=Queue.size()){
		for(int i=0;i<SIZE;i++){
			if(Queue.at(current).next[i]!=NULL){
				Tree_letter[++m] = Queue.at(current).next[i]->element;
				Queue.push_back(*Queue.at(current).next[i]);
				transition[++n] = current;//每一个子节点都是后面那些结点的父亲,因此数组里面的每个数值都是标记在字母组里面的父亲位置
			}
		}
		if(Queue.at(current).flag==1){
			if_leaf[current] = 1;
			location[current]= Queue.at(current).count;}
		else{
			if_leaf[current] = 0;
			location[current]= -1;
		}

		current++;
		}
		
		for(int i=0;i<Treesize;i++)
			for(int j=0;j<20;j++)
				Trelly1[i][j] = 1000;
		/*vector<char> contemp;
		vector<string> example;
		char char1;
		for(int i=0;i<9;i++){
		cin>>char1;
		contemp.push_back(char1);}
		contemp.insert(contemp.begin(),'*');
		example = get_segementation0(contemp,Tree_letter,transition,my_vector);
		for(int i=example.size()-1;i>=0;i--)
			cout<<example.at(i)<<" ";
		system("pause");*/


		//开始进行project处理
	do{
		cout<<"Push 1 to run a spellcheck on typos.txt: "<<endl;
		cout<<"Push 2 to run a segementation on unsegemented0.txt: "<<endl;
		cout<<"Push 3 to run a segementation on unsegemented.txt: "<<endl;
		cout<<"Push 0 to exit this programme:"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		switch (choice){
		case 0: break;
		case 1:{
	//进行DP计算距离
			fixed_words = get_fixed(inputs_vector,Tree_letter,transition,templs_vector);
		for(int i=0;i<fixed_words.size();i++)
			cout<<fixed_words.at(i)<<" ";
		cout<<fixed_words.size();
		system("pause");
		break;}

		case 2:{
			segemented0_words = get_segementation0(unsegement0_vector,Tree_letter,transition,templs_vector);
			cout<<segemented0_words.size()<<endl;
			for(int i=segemented0_words.size()-1;i>=0;i--)
				cout<<segemented0_words.at(i)<<" ";
			cout<<endl;
			break;
			   }
		case 3:{
			segemented_words = get_segementation0(unsegement_vector,Tree_letter,transition,templs_vector);
			segemented_words = get_fixed(segemented_words,Tree_letter,transition,templs_vector);
			cout<<segemented_words.size()<<endl;
			for(int i=segemented_words.size()-1;i>=0;i--)
				cout<<segemented_words.at(i)<<" ";
			cout<<endl;
			break;
			   }

		default: break;
		}//switch
	}while(choice!=0);

	return 0;
}
