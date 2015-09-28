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


//����lextree ���ݽṹ

typedef struct Trie
{
	Trie *next[SIZE];    //һ��ֻ����Сд��ĸ
	int flag;            //�ж��Ƿ��Ǵ�β,1Ϊ��β
	char element;        //��ǰ������ĸ
	int level;           //��ǵ�ǰ������
	int  count;         //��¼�������ֵ�vector�еĵڼ�������
	int distance[25];   //��¼ÿ��������ʷ����
	int exit_next;     //��¼�ýڵ�֮���Ƿ��з�֧
	Trie *initial;      //��������ÿ�����ʽ���ʱ�ĸ��ڵ�
}Trie;

Trie root;  //�����ֵ����ĸ��ڵ�


int CreatLextree(string str,int number){
	
	int level_adder = 0;  //������ǵ�ǰ������,ÿ�����´洢���ʣ��������¿�ʼ
	int len = str.length();
	Trie *p = &root, *q;
	for(int i=0;i<len;i++)
	{
		str[i] = tolower(str[i]);//ֻ����Сд��ĸ
		int id = str[i] - 'a';
		if(id>25||id<0)  //���������ĸ���򲻷����ֵ�����
			continue;
		if(p->next[id] == NULL)
		{
			letters++;
			p->exit_next =1;
			q = (Trie *)malloc(sizeof(root));
			q->initial = &root;                   //�����һ�����ʽ�β�����һ���ص����ڵ��ָ��
			for(int i=0;i<25;i++)
				q->distance[i] = 100;
			q->level = ++level_adder;
			q->element = str[i];
			for(int i=0;i<SIZE;i++)
				q->next[i] = NULL;
			q->exit_next =0;
			p->next[id] = q;
			p = p->next[id];
			if((i==len-1)||(i==len-2&&str[i+1]=='\'')){    //�ж��Ƿ��Ǵ�β
				q->flag =1;
				q->count = number;
			}
			else
				q->flag=0;
		}
		else{
			p = p->next[id];
			level_adder++;  //�����ƶ���㣬��Ӧ�Ĳ�����1
		}//if
	}// for
	return level_adder;
}

//�ֵ����ļ��㷽��
vector<string> get_fixed(vector<string> input,char tree_trelly[],int transport[],vector<string> dict){

	vector<string> return_string;

	for(int i=0;i<input.size();i++){
		
		string temp = input.at(i);
		temp = '*' + temp;
		int len = temp.size();
		Trelly1[0][0] = 0;
		//��һ�е�����ֵ
		for(int j=1;j<len;j++)
			Trelly1[0][j] = Trelly1[0][j-1]+1;
		//��һ�е�����ֵ
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
			
			//�ҳ���ƥ�䵥��,problem1
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


//���ִʴ��� case2,case3
vector<string> get_segementation0(vector<char> pre_segment,char tree_trelly[],int transport[],vector<string> dict){

	vector<string> right_segement_words;
	vector<int> state;
	Trelly2[0][0] = 0;
	Trelly2[0][1] = 1;


	//��һ�и�ֵ
		for(int i=1;i<Treesize;i++)
			Trelly2[i][0] = Trelly2[transport[i]][0]+1;
		state.push_back(0);

		//�ڶ��и�ֵ
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
			//���ҳ�ǰһ������Ҷ�ӽڵ����Сֵ
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
		//���ڿ�ʼ����
		
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

	//		//ͨ��C++���������
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
	vector <string>  templs_vector;  //�����洢�ֵ䵥��
    vector <string>  inputs_vector;  //�����洢�Ƚ��ı�����
	vector <string>  fixed_words;    //�����洢ʶ���ĵ���
	vector<char>   unsegement0_vector;//����������ȷ�ı�δ�ָ�ʵ���ĸ
	vector<char>   unsegement_vector;//������������ı�δ�ָ�ʵ���ĸ
	vector<string> segemented0_words;//����������ȷ�ı��ִʺ�ĵ���
	vector<string> segemented_words;//������������ı��ִʺ�ĵ���
	vector<string> right_words;//������ȷ�ı��ĵ���
	int max_level = -1;                   //�ҳ�����ʵĲ���
	int temp_max_level = 0;
	int choice = -1;

	//��ȡ�ֵ䵥�ʵ�vector����
   ifstream templread("dict_1.txt");
   string maintempl;
    while(templread>>maintempl)
	templs_vector.push_back(maintempl);
	

	//��ȡ�ı����ʵ�vector����
   ifstream txtread("typos.txt");
   string txt;
    while(txtread>>txt)
	inputs_vector.push_back(txt);

	//��ȡ��ȷδ�ָ��ı�unsegemented0.txt
	ifstream unsegment0("unsegmented0.txt");
	if(!unsegment0){
		cout<<"Can not open a file!";
		exit(1);}
	char unsegement0_letter;
	while(unsegment0>>unsegement0_letter)
		unsegement0_vector.push_back(unsegement0_letter);
	unsegement0_vector.insert(unsegement0_vector.begin(),'*');

	

	

	//��ȡ����δ�ָ��ı�unsegemented.txt
	ifstream unsegment("unsegmented.txt");
	if(!unsegment){
		cout<<"Can not open a file!";
		exit(1);}
	char unsegement_letter;
	while(unsegment>>unsegement_letter)
		unsegement_vector.push_back(unsegement_letter);
	unsegement_vector.insert(unsegement_vector.begin(),'*');

	

	//��ȡ�ָ��ı�segemented.txt
	ifstream segment("segmented.txt");
	if(!segment){
		cout<<"Can not open a file!";
		exit(1);}
	string segment_word;
	while(segment>>segment_word)
		right_words.push_back(segment_word);

	//��ȡ�ҵ��ı�my_dict.txt
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


	//�����ڵ��26���ӽڵ��ʼ��NULL
	for(int i=0;i<SIZE;i++)
		root.next[i] = NULL;
	root.element = '*';       //���е���ǰ�涼����*
	root.level = 0;//�����Ĳ���Ϊ0
	//�����ֵ���
	for(int i=0;i<templs_vector.size();i++){
		temp_max_level = CreatLextree(templs_vector.at(i),i);
		if(temp_max_level>max_level)
			max_level = temp_max_level;
	}
	

	//�����ֵ�������

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
				transition[++n] = current;//ÿһ���ӽڵ㶼�Ǻ�����Щ���ĸ���,������������ÿ����ֵ���Ǳ������ĸ������ĸ���λ��
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


		//��ʼ����project����
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
	//����DP�������
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
