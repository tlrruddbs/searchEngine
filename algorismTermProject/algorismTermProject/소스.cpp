#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;
template <typename Iterator> void quickSort(Iterator start, Iterator end) {
	int size = (end - start);
	if (size <= 0)
		return;

	int pivotIndex = randomNumber(0, size);
	typename std::iterator_traits<Iterator>::value_type pivot = *(start + pivotIndex);

	if (pivotIndex != 0)
		std::swap(*(start + pivotIndex), *start);

	int i = 1;
	for (int j = 1; j < size; j++) {
		if (*(start + j) < pivot) {
			std::swap(*(start + j), *(start + i));
			i++;
		}
	}

	std::swap(*start, *(start + i - 1));

	quickSort(start, start + i - 1);
	quickSort(start + i, end);
}
int randomNumber(int start, int end) {
	srand(time(NULL));

	return rand() % end + start;
}

int main() {
	// word_map �����
	map <string, vector<string>> word_map;
	int startNum;
	string findWord1;
	int findWord2;


	cout << "* ���ݺ��� ��������Ʈ â�� �����մϴ�.\n\n";
	cout << "* ���� : 21211758����ȣ, 21211779 �����" << endl;
	cout << "\n";
	cout << "* �� ���α׷��� document.txt�� ���� map���� HashTable�� ����ϴ�.\n";
	cout << "* ���ϴ� ���ڿ� ���� �� �࿡ �ִ��� ã���ϴ�.\n";
	cout << "* ���� �ܾ���� ���տ� ���� � �࿡ �ִ��� ����� �˾� �� �� �ֽ��ϴ�." << endl;
	cout << "* ������ ���� Ȥ�� �� ������ �����ϴ� ���� ���� ���� �Ÿ��� ����� ���� �࿡ ���� ���� ������ �ű�ϴ�." << endl;
	cout << endl;
	cout << "******************************************************************" << endl;
	cout << "1. document.txt�� �̿��Ͽ� HashTable������ map.txt�� �����ϱ�" << endl;
	cout << "2. HashTable �ҷ�����" << endl;
	cout << "3. ���ϴ� �� ���� document.txt���� ã�� \n";
	cout << "4. ���ϴ� ���� ���� document.txt���� ã�� \n";
	cout << "0. ȭ���� �����մϴ�." << endl;
	cout << "******************************************************************" << endl;

	do {
		cout << "\n\n ";
		cout << " ���ϴ� ����� ���ڸ� �Է��ϼ��� : ";
		cin >> startNum;
		cout << endl;
		if (cin.fail()) {
			cout << "   ���ڸ� �Է��ؾ� �մϴ�." << endl; // ���� �޽��� ���
			cin.clear(); // ������Ʈ���� �ʱ�ȭ
			cin.ignore(256, '\n'); // �Է¹��۸� ���
			startNum = 6;
		}
		if (startNum == 1) {
			word_map.clear();
			cout << "  HashTable�� ����ϴ�." << endl;
			// define the size of character array

			ifstream fin("document.txt");

			if (!fin.is_open()) {
				perror("   ������ ������ �ʽ��ϴ�.");
				return EXIT_FAILURE;
			}


			cout << "   ������ �����ϴ�!!!!!" << endl;

			char c;
			string k = {};
			double docnum = 1.0;
			double count = 0.0;
			do {
				c = fin.get();
				if (c == ' ' || c == '\n' || c == '\0') {
					if (c == '\n') {
						count = 0;
						cout << docnum << " �� �� ���� �� �Դϴ�." << endl;
						docnum++;
					}
					else if (c == ' ') {
						count++;
					}
					string key = k;
					string value = to_string(docnum + count / 1000);
					word_map[key].push_back(value);
					k = {};
				}
				else {
					k = k + c;
				}
			} while (!fin.eof());


			ofstream newFile("map.txt");
			map<string, vector<string>>::iterator in;
			for (in = word_map.begin(); in != word_map.end(); in++) {
				double docnum;
				int end = (in->second).size();
				newFile << (in->first) << "=";
				for (int j = 0; j < end; j++) {
					newFile << (in->second[j]) << " ";
				}
				newFile << "\n";
			}

			cout << "  HashTable�� ��������ϴ�." << endl;
			cout << "  HashTable�� map.txt�� ����˴ϴ�." << endl;
			cout << "  ó������ ���ư��ϴ�.\n" << "******************************************************************" << endl;
			
		}

		if (startNum == 2) {
			word_map.clear();
			cout << "  HashTable�� �ҷ��ɴϴ�." << endl;

			pair< string, vector<string>> x;

			ifstream mapfile("map.txt");
			if (!mapfile.is_open()) {
				cout << "   ����� HashTable�� �����ϴ�.\n";
			}
			else {
				word_map.clear();
				string mapword = {};
				char mapc;
				int num;
				vector<string> v_str;
				vector<int> v_int;
				do {
					mapc = mapfile.get();
					int row = 1;
					if (mapc == '=') {
						x.first = mapword;
						mapword = {};
					}
					else if (mapc == ' ') {
						v_str.push_back(mapword);
						mapword = {};
					}
					else if (mapc == '\n') {

						mapword = {};
						x.second = v_str;
						word_map.insert(x);
						v_str = {};
						mapc = {};

					}
					else {
						mapword = mapword + mapc;

					}


				} while (!mapfile.eof());
			}

			cout << "  ó������ ���ư��ϴ�.\n" << "******************************************************************" << endl;
			
		}

		if (startNum == 3) {
			cout << "  ã���� �ϴ� ���ڸ� �Է��ϼ��� : ";
			cin >> findWord1;
			map<string, vector<string>> ::iterator iter;
			iter = word_map.find(findWord1);
			int end;
			if (word_map.empty()) {
				cout << "   ����� word_map�� �����ϴ�. ���� Hash Table�� ���弼��" << endl;
			}
			else if (iter == word_map.end()) {

				cout << "   ã�����ϴ°���� �����ϴ�." << endl;

			}
			else {
				
				end = (iter->second).size();
				for (int j = 0; j < end; j++) {
					cout << floor(stod(word_map.find(findWord1)->second[j])) 
						<< "�� <- "
						<< (stod(word_map.find(findWord1)->second[j])- floor(stod(word_map.find(findWord1)->second[j])))*1000+1
						<< "��°   ";
					//   a = word_map.find(wantKey)->second[j];

				}

				cout << endl;

			}


			cout << endl;
			cout << "  ó������ ���ư��ϴ�.\n" << "******************************************************************" << endl;
		}


		if (startNum == 4) {
			cout << "  ã���� �ϴ� ���ڰ� ��Դϱ�? : ";
			cin >> findWord2;
			if (word_map.empty()) {
				cout << "   ����� word_map�� �����ϴ�. ���� Hash Table�� ���弼��" << endl;
				cout << "  ó������ ���ư��ϴ�.\n" << "******************************************************************" << endl;
				startNum = 100;
			}
			else {
				vector <double> vdouble = {};
				vector <int > vint = {};
				int end1;
				int wordnum=0;
				for (int i = 0; i < findWord2; i++) {
					cout << endl;
					cout << i+1 << " ��° ���� �� �Է��ϼ���. : ";
					cin >> findWord1;
					cout << endl;
					map<string, vector<string>> ::iterator iter1 = word_map.find(findWord1);
					if (iter1 == word_map.end()) {
						cout << "ã���� �ϴ� �ܾ��� ����� �����ϴ�." << endl;
						i = i - 1;
					}
					else {

						wordnum=wordnum+1;
						end1 = (iter1->second).size();
						for (int j = 0; j < end1; j++) {
							double k = stod(word_map.find(findWord1)->second[j]);
							vdouble.push_back(k);
							int q = stoi(word_map.find(findWord1)->second[j]);
							vint.push_back(q);
							cout << floor(k) << "�� ";
						}
						cout << endl;
						
					}
					
				}


				clock_t tbegin, tend;

				tbegin = clock();

				quickSort(vdouble.begin(), vdouble.end());
				quickSort(vint.begin(), vint.end());
				cout << wordnum << "���� ���ڿ� ���ؼ� ������ ã���ϴ�.\n" << endl;
				
				vector<double> compare;
				map<int, int>rowcount;
				pair<int, int> x;
				int maxsize = 1;
				for (int i = 0; i < vint.size(); i++) {
					map<int, int>::iterator it = rowcount.find(vint[i]); // v[*iter]���� ã�µ� ã���� ���� �ݺ����� it���� �����Ѵٴ� ���̴�.
					if (it != rowcount.end()) { //rowcount���� v[*iter]�� �ش��ϴ� ���� ã�Ҵٴ� ��
						int b = rowcount[vint[i]]; // ������ v[*iter]���� b�� �޾ƿͼ�
						rowcount[vint[i]] = b + 1; // +1�� ���ְڴٴ� ���̴�.
						maxsize = maxsize < rowcount[vint[i]] ? rowcount[vint[i]] : maxsize;
					}
					else {
						x.first = vint[i];
						x.second = 1;
						rowcount.insert(x);
					}
				}
				map <int, vector<int>> maximumcount;
				map <double, vector<int>> findscore;
				pair<int, vector<int>> scorePair;
				vector<int> scoreline;
				for (map<int, int>::iterator rit = rowcount.begin(); rit != rowcount.end(); rit++)
				{
					//cout << "    ";
					//std::cout << (rit)->first << "���� " << (rit)->second << "�� �ֽ��ϴ�.";
					//cout << endl;
					double k = (rit)->first;
					double n = (rit)->second;
					double score = 0;
					double standard = 0;
					for (int j = vdouble.size() - 1; j >= 0; j--)
					{
						if (floor(vdouble[j]) == k) {
							standard = pow((vdouble[j] - floor(vdouble[j])) * 1000, 2);
							score = standard + score;
				
						}
					}
					
					score = n * 1000 + (1000 - round(sqrt(score) / sqrt(n)))*k/1000;
					findscore[score].push_back((rit)->first);
					maximumcount[(rit)->second].push_back((rit)->first);
					
					
				}
				vector<double> vscore;
				vector<int> vrow;
				for (map<double, vector<int>>::iterator fit = findscore.begin(); fit != findscore.end(); fit++)
				{
					
					for (int j = 0; j < findscore[fit->first].size(); j++){
						//cout << "    ";
						//cout << (fit -> second)[j]<< "����" << (fit->first) << "���Դϴ�." << endl;
						vscore.push_back(fit->first);
						vrow.push_back((fit->second)[j]);
					}
					
				}

				cout << endl;
				int k = 1;
				for (int i = vrow.size()-1; i >= vrow.size() - 10; i--) {
					cout << "    " << k << "���� " << vrow[i] << "���� "<< vscore[i]<< "���Դϴ�." << endl;
					k++;
				}

				cout << endl;
				for (map<int, vector<int>>::iterator mit = maximumcount.begin(); mit != maximumcount.end(); mit++)
				{
					cout << "    ";
					std::cout << (mit)->first << "���� ���� �� : ";
					for (int i = 0; i < maximumcount[(mit)->first].size(); i++) {
						cout << ((mit)->second)[i] << "�� ";
					}
					cout << endl;
				}

				tend = clock();
				cout << endl;
		
				cout << "    ";
				cout << "�Է� �ܾ����� �� �࿡ ���Ե� �ִ� �ܾ� ���� : " << maxsize << "�� �̴�."<< endl;
				cout << endl;
				cout << "    �ܾ� ������ ������ �� ���� �ð��� : " << (double)(tend - tbegin) / CLOCKS_PER_SEC<<"���̴�."<<endl;
				

				


				cout << "  ó������ ���ư��ϴ�.\n" << "******************************************************************" << endl;
				
			}
		}
	} while (startNum != 0);
}


