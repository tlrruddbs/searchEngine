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
	// word_map 만들기
	map <string, vector<string>> word_map;
	int startNum;
	string findWord1;
	int findWord2;


	cout << "* 지금부터 텀프로젝트 창을 시작합니다.\n\n";
	cout << "* 조원 : 21211758박인호, 21211779 윤경식" << endl;
	cout << "\n";
	cout << "* 이 프로그램은 document.txt를 통해 map으로 HashTable을 만듭니다.\n";
	cout << "* 원하는 글자에 대해 몇 행에 있는지 찾습니다.\n";
	cout << "* 여러 단어들의 조합에 대해 어떤 행에 있는지 결과를 알아 볼 수 있습니다." << endl;
	cout << "* 조합의 전부 혹은 몇 가지를 포함하는 행의 글자 사이 거리가 가까울 수록 행에 대한 낮은 점수로 매깁니다." << endl;
	cout << endl;
	cout << "******************************************************************" << endl;
	cout << "1. document.txt를 이용하여 HashTable만들기고 map.txt로 저장하기" << endl;
	cout << "2. HashTable 불러오기" << endl;
	cout << "3. 원하는 한 글자 document.txt에서 찾기 \n";
	cout << "4. 원하는 갯수 글자 document.txt에서 찾기 \n";
	cout << "0. 화면을 종료합니다." << endl;
	cout << "******************************************************************" << endl;

	do {
		cout << "\n\n ";
		cout << " 원하는 기능의 숫자를 입력하세요 : ";
		cin >> startNum;
		cout << endl;
		if (cin.fail()) {
			cout << "   숫자를 입력해야 합니다." << endl; // 에러 메시지 출력
			cin.clear(); // 오류스트림을 초기화
			cin.ignore(256, '\n'); // 입력버퍼를 비움
			startNum = 6;
		}
		if (startNum == 1) {
			word_map.clear();
			cout << "  HashTable을 만듭니다." << endl;
			// define the size of character array

			ifstream fin("document.txt");

			if (!fin.is_open()) {
				perror("   파일이 열리지 않습니다.");
				return EXIT_FAILURE;
			}


			cout << "   파일이 열립니다!!!!!" << endl;

			char c;
			string k = {};
			double docnum = 1.0;
			double count = 0.0;
			do {
				c = fin.get();
				if (c == ' ' || c == '\n' || c == '\0') {
					if (c == '\n') {
						count = 0;
						cout << docnum << " 줄 이 진행 중 입니다." << endl;
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

			cout << "  HashTable을 만들었습니다." << endl;
			cout << "  HashTable이 map.txt로 저장됩니다." << endl;
			cout << "  처음으로 돌아갑니다.\n" << "******************************************************************" << endl;
			
		}

		if (startNum == 2) {
			word_map.clear();
			cout << "  HashTable을 불러옵니다." << endl;

			pair< string, vector<string>> x;

			ifstream mapfile("map.txt");
			if (!mapfile.is_open()) {
				cout << "   저장된 HashTable이 없습니다.\n";
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

			cout << "  처음으로 돌아갑니다.\n" << "******************************************************************" << endl;
			
		}

		if (startNum == 3) {
			cout << "  찾고자 하는 글자를 입력하세요 : ";
			cin >> findWord1;
			map<string, vector<string>> ::iterator iter;
			iter = word_map.find(findWord1);
			int end;
			if (word_map.empty()) {
				cout << "   저장된 word_map이 없습니다. 먼저 Hash Table을 만드세요" << endl;
			}
			else if (iter == word_map.end()) {

				cout << "   찾고자하는결과가 없습니다." << endl;

			}
			else {
				
				end = (iter->second).size();
				for (int j = 0; j < end; j++) {
					cout << floor(stod(word_map.find(findWord1)->second[j])) 
						<< "행 <- "
						<< (stod(word_map.find(findWord1)->second[j])- floor(stod(word_map.find(findWord1)->second[j])))*1000+1
						<< "번째   ";
					//   a = word_map.find(wantKey)->second[j];

				}

				cout << endl;

			}


			cout << endl;
			cout << "  처음으로 돌아갑니다.\n" << "******************************************************************" << endl;
		}


		if (startNum == 4) {
			cout << "  찾고자 하는 글자가 몇개입니까? : ";
			cin >> findWord2;
			if (word_map.empty()) {
				cout << "   저장된 word_map이 없습니다. 먼저 Hash Table을 만드세요" << endl;
				cout << "  처음으로 돌아갑니다.\n" << "******************************************************************" << endl;
				startNum = 100;
			}
			else {
				vector <double> vdouble = {};
				vector <int > vint = {};
				int end1;
				int wordnum=0;
				for (int i = 0; i < findWord2; i++) {
					cout << endl;
					cout << i+1 << " 번째 글자 를 입력하세요. : ";
					cin >> findWord1;
					cout << endl;
					map<string, vector<string>> ::iterator iter1 = word_map.find(findWord1);
					if (iter1 == word_map.end()) {
						cout << "찾고자 하는 단어의 결과가 없습니다." << endl;
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
							cout << floor(k) << "행 ";
						}
						cout << endl;
						
					}
					
				}


				clock_t tbegin, tend;

				tbegin = clock();

				quickSort(vdouble.begin(), vdouble.end());
				quickSort(vint.begin(), vint.end());
				cout << wordnum << "개의 글자에 대해서 점수를 찾습니다.\n" << endl;
				
				vector<double> compare;
				map<int, int>rowcount;
				pair<int, int> x;
				int maxsize = 1;
				for (int i = 0; i < vint.size(); i++) {
					map<int, int>::iterator it = rowcount.find(vint[i]); // v[*iter]값을 찾는데 찾았을 때의 반복수를 it으로 가정한다는 것이다.
					if (it != rowcount.end()) { //rowcount에서 v[*iter]에 해당하는 값을 찾았다는 뜻
						int b = rowcount[vint[i]]; // 기존의 v[*iter]값을 b로 받아와서
						rowcount[vint[i]] = b + 1; // +1을 해주겠다는 뜻이다.
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
					//std::cout << (rit)->first << "행이 " << (rit)->second << "개 있습니다.";
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
						//cout << (fit -> second)[j]<< "행이" << (fit->first) << "점입니다." << endl;
						vscore.push_back(fit->first);
						vrow.push_back((fit->second)[j]);
					}
					
				}

				cout << endl;
				int k = 1;
				for (int i = vrow.size()-1; i >= vrow.size() - 10; i--) {
					cout << "    " << k << "등은 " << vrow[i] << "행이 "<< vscore[i]<< "점입니다." << endl;
					k++;
				}

				cout << endl;
				for (map<int, vector<int>>::iterator mit = maximumcount.begin(); mit != maximumcount.end(); mit++)
				{
					cout << "    ";
					std::cout << (mit)->first << "개를 가진 행 : ";
					for (int i = 0; i < maximumcount[(mit)->first].size(); i++) {
						cout << ((mit)->second)[i] << "행 ";
					}
					cout << endl;
				}

				tend = clock();
				cout << endl;
		
				cout << "    ";
				cout << "입력 단어조합 중 행에 포함된 최대 단어 개수 : " << maxsize << "개 이다."<< endl;
				cout << endl;
				cout << "    단어 선택을 제외한 총 수행 시간은 : " << (double)(tend - tbegin) / CLOCKS_PER_SEC<<"초이다."<<endl;
				

				


				cout << "  처음으로 돌아갑니다.\n" << "******************************************************************" << endl;
				
			}
		}
	} while (startNum != 0);
}


