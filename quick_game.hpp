#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Quick_game {
private:
	ifstream fmo;
	ofstream save;

	void readHelp() {
		cout << "dump <filename> - ��������� ��������� � ���� (��������! ����������� �������� ����������!)" << endl;
		cout << "tick <n = x> ��� t <n=x> -������ ������ �� ���������� x - �� ����.����� ��������� ��� ���������, ������� ��������, ����� �������� ���� � ���� � ������� ������������� ������." << endl;
		cout << "exit - ��������� ����" << endl;
		cout << "help - ������� ���������� ��� ���." << endl;
	}
protected:
	vector<string> turn(vector<string> un, vector<int> birthRate, vector<int> survivalRate, int width, int height) {
		vector<string> nextgen;

		nextgen.push_back(string(width + 2, 'X'));
		for (int i = 1; i <= width; i++) {
			nextgen.push_back("X");
			for (int j = 1; j <= height; j++) {
				int alive = 0;

				if (un[i][j] == '*') {
					if (un[i - 1][j - 1] == '^') alive++;
					if (un[i - 1][j] == '^') alive++;
					if (un[i - 1][j + 1] == '^') alive++;
					if (un[i][j - 1] == '^') alive++;
					if (un[i][j] == '^') alive++;
					if (un[i][j + 1] == '^') alive++;
					if (un[i + 1][j - 1] == '^') alive++;
					if (un[i + 1][j] == '^') alive++;
					if (un[i + 1][j + 1] == '^') alive++;

					bool birth = false;
					for (int k = 0; k < birthRate.size(); k++) {
						if (alive == birthRate[k]) {
							nextgen[i] += '^';
							birth = true;
							break;
						}
					}

					if (!birth) nextgen[i] += '*';
				}

				if (un[i][j] == '^') {
					if (un[i - 1][j - 1] == '^') alive++;
					if (un[i - 1][j] == '^') alive++;
					if (un[i - 1][j + 1] == '^') alive++;
					if (un[i][j - 1] == '^') alive++;
					if (un[i][j] == '^') alive++;
					if (un[i][j + 1] == '^') alive++;
					if (un[i + 1][j - 1] == '^') alive++;
					if (un[i + 1][j] == '^') alive++;
					if (un[i + 1][j + 1] == '^') alive++;

					bool survive = false;
					for (int k = 0; k < survivalRate.size(); k++) {
						if (alive == survivalRate[k]) {
							nextgen[i] += '^';
							survive = true;
							break;
						}
					}

					if (!survive) nextgen[i] += '*';
				}
			}
			nextgen[i] += 'X';
		}
		nextgen.push_back(string(width + 2, 'X'));

		return nextgen;
	}

	string countGen(int n) {
		if (n == 1 || (n - 1) % 10 == 0) {
			if (n % 100 != 11) return "���������";
			else return "���������";
		}
		if (((n % 10) >= 2 && (n % 10) <= 4)) {
			if (n % 100 >= 12 && n % 100 <= 14) return "���������";
			return "���������";
		}
		else return "���������";
	}

	string countCell(int n) {
		if (n == 1 || (n - 1) % 10 == 0) {
			if (n % 100 != 11) return "������";
			else return "������";
		}
		if ((n % 10) >= 2 && (n % 10) <= 4) {
			if (n % 100 >= 12 && n % 100 <= 14) return "������";
			return "������";
		}
		else return "������";
	}

	void play(vector<string> un, vector<int> birthRate, vector<int> survivalRate, string vers, string name, int width, int height) {
		vector<vector<string>> generation;
		string command, arg, tmp = "<n=>";
		int step = 1;

		readHelp();

		while (true) {
commandWait:
			cin >> command;
			if (command == "exit") exit(0);
			if (command == "help") {
				readHelp();
				continue;
			}
			cin >> arg;

			if (command == "tick" || command == "t") {
				string iter = "";
				int turns;

				int i = 0, j = 0;
				while (i != arg.length() && j != tmp.length()) {
					if (arg[i] == tmp[j] || isdigit(arg[i])) {
						if (isdigit(arg[i])) iter += arg[i], i++;
						else i++, j++;
					}
					else {
						cout << "�������� ����� � ������������ �������. ��������� �������." << endl;
						goto commandWait;
					}
				}

				turns = stoi(iter);

				for (i = 1; i <= turns; i++) {
					generation.push_back(un);

					un = turn(un, birthRate, survivalRate, width, height);

					for (j = 0; j < generation.size(); j++) {
						if (generation[j] == un) {
							if (j == generation.size() - 1) {
								cout << "������ " << step << ' ' << countGen(step) << " ��������� ������������ � ��������" << endl;
								exit(0);
							}
							else {
								cout << "������ " << step << ' ' << countGen(step) << " ��������� ����������� �� " << i << " ����" << endl;
								exit(0);
							}
						}
					}

					step++;
				}

				cout << "��� ���������: " << name << endl;
				cout << "��������� ������ �������� �� �����, ���� � ��������:" << endl;
				for (i = 0; i < birthRate.size(); i++) cout << birthRate[i] << ' ' << countCell(birthRate[i]) << endl;

				cout << "������ ������������ ����� ���������, ���� � ��������:" << endl;
				for (i = 0; i < survivalRate.size(); i++) cout << survivalRate[i] << ' ' << countCell(survivalRate[i]) << endl;

				cout << "� ������ ���� ������ " << step << ' ' << countGen(step) << endl;

				for (i = 0; i < un.size(); i++) cout << un[i] << endl;

				continue;
			}

			if (command == "dump") {
				if (arg[0] == '<' && arg[arg.length() - 1] == '>') {
					arg.pop_back();
					std::reverse(arg.begin(), arg.end());
					arg.pop_back();
					std::reverse(arg.begin(), arg.end());

					save.open("./" + arg);

					save << "#Life " << vers << endl;
					save << "#Name " << name << endl;
					save << "#R " << "B";

					for (int i = 0; i < birthRate.size(); i++) save << birthRate[i];
					save << "/S";

					for (int i = 0; i < survivalRate.size(); i++) save << survivalRate[i];
					save << endl;

					save << "#S " << width << '/' << height << endl;

					for (int i = 1; i <= height; i++) {
						for (int j = 1; j <= width; j++) {
							if (un[i][j] == '^') save << i << ' ' << j << endl;
						}
					}

					save.close();

					continue;
				}
				else {
					cout << "�������� ����� � ������������ �������. ��������� �������." << endl;
					continue;
				}
			}

			cout << "������� '" << command << "' �� �������������� �� ������ ����� ����." << endl;
		}
	}
};