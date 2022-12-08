#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

class Initialization {
private:
	string count(int n) {
		if ((n - 1) % 10 == 0 && n != 11) return "раза";
		else return "раз";
	}
protected:
	ifstream fhe;
	string help = "";

	string initVers() {
		if (help == "") {
			fhe.open("./help.txt");

			while (!fhe.eof()) help += fhe.get();

			help.pop_back();
			cout << help << endl;
			cout << "¬ведите команду 'help' в консоль, чтобы ознакомитьс€ с правилами инициализации ещЄ раз" << endl;
		}

		while (true) {
			string command, arg;

			cin >> command;

			if (command == "#Life") {
				cin >> arg;

				return arg;
			}

			if (command == "help") {
				cout << help << endl;
				continue;
			}

			if (command == "exit") exit(0);

			cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
			return "";
		}
	}

	string initName() {
		string command, arg;

		cin >> command;

		if (command == "#Name") {
			cin.ignore();

			getline(cin, arg);

			return arg;
		}

		if (command == "exit") exit(0);

		cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
		return "";
	}

	vector<vector<int>> initRules() {
		vector<vector<int>> rates;
		string command, arg;

		cin >> command;

		if (command == "#R") {
			cin >> arg;

			for (int i = 0; i < arg.length(); i++) {
				if (arg[i] != 'B' && arg[i] != 'S' && arg[i] != '/' && !isdigit(arg[i])) {
					cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
					return rates;
				}
			}

			if (arg.find("/") == string::npos || arg.find("B") == string::npos || arg.find("S") == string::npos) {
				cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
				return rates;
			}
			else {
				bool slash = false, B = false, S = false;
				rates.push_back(vector<int>());
				rates.push_back(vector<int>());
				for (int i = 0; i < arg.length(); i++) {
					if (arg[i] == '/') {
						slash = true;
						continue;
					}

					if (!slash) {
						if (isdigit(arg[i])) rates[0].push_back(stoi(string(1, arg[i])));
						else {
							if (arg[i] == 'B' && !B) {
								B = true;
								continue;
							}
							else {
								cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
								rates.resize(0);
								return rates;
							}
						}
					}

					if (slash) {
						if (isdigit(arg[i])) rates[1].push_back(stoi(string(1, arg[i])));
						else {
							if (arg[i] == 'S' && !S) {
								S = true;
								continue;
							}
							else {
								cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
								rates.resize(0);
								return rates;
							}
						}
					}
				}

				return rates;
			}
		}

		if (command == "exit") exit(0);

		cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
		return rates;
	}

	vector<int> initSize() {
		vector<int> size;
		string command, arg;

		cin >> command;

		if (command == "#S") {
			cin >> arg;

			for (int i = 0; i < arg.length(); i++) {
				if (!isdigit(arg[i]) && arg[i] != '/') {
					cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
					return size;
				}
			}

			if (arg.find("/") == string::npos) {
				cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
				return size;
			}
			else {
				string temp = "";
				bool slash = false;
				for (int i = 0; i < arg.length(); i++) {
					if (arg[i] == '/') {
						slash = true;
						size.push_back(stoi(temp));
						temp = "";
						continue;
					}

					if (!slash) temp += arg[i];
					if (slash) temp += arg[i];
				}

				size.push_back(stoi(temp));

				return size;
			}
		}

		if (command == "exit") exit(0);

		cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
		return size;
	}

	vector<vector<int>> coordinates(int width, int height) {
		vector<vector<int>> pairs(2);

		cout << "¬ы можете задать координаты до " << width * height << ' ' << count(width * height) << endl;
		cout << "¬ведите в консоль команду ready, чтобы закончить инициализацию живых клеток самосто€тельно" << endl;
		cout << "¬ качестве координат система принимает только пары целочисленных значений, разделЄнных пробелом" << endl;

		for (int i = 0; i < width * height; i++) {
			string arg1, arg2;
			int x, y;

			try {
				cin >> arg1;
				if (arg1 == "ready") break;
				if (arg1 == "exit") exit(0);
				cin >> arg2;

				x = stoi(arg1);
				y = stoi(arg2);
			}
			catch(exception) {
				cout << "¬селенна€ задана в неправильном формате. ѕовторите инициализацию" << endl;
				pairs.resize(0);
				return pairs;
			}

			pairs[0].push_back(x), pairs[1].push_back(y);
		}

		return pairs;
	}

	vector<string> initUn(int width, int height) {
		vector<string> un;

		un.push_back(string(width + 2, 'X'));

		for (int i = 1; i <= height; i++) {
			un.push_back("X");
			un[i] += string(width, '*');
			un[i] += 'X';
		}

		un.push_back(string(width + 2, 'X'));

		return un;
	}
};