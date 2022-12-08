#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "initialization.hpp"
#include "quick_game.hpp"
#include "offline_mode.hpp"

using namespace std;

class Universe {
public:
	int height, width;
	string name, vers, gamemode;
	vector<int> birthRate, surviveRate, x, y;
	vector<string> un;
};

class inputData: public Universe {
private:
	ifstream fun, fru, fhe, fmo;

	void format_error() {
		cout << "Файл со вселенной повреждён или отсутствует. Проверьте его формат записи или наличие и повторите сессию" << endl;
		exit(1);
	}

public:
	string readHelp() {
		string help = "";

		fhe.open("./help.txt");

		while (!fhe.eof()) help += fhe.get();

		help.pop_back();

		fhe.close();

		return help;
	}

	string readModes() {
		string modes = "";

		fmo.open("./modes.txt");

		while (!fmo.eof()) modes += fmo.get();

		modes.pop_back();

		fmo.close();

		return modes;
	}

	void readUn(string filename) {
		string command, arg;

		fun.open("./" + filename);

		fun >> command;
		fun >> arg;

		if (command == "#Life") {
			vers = arg;

			arg = "";

			fun >> command;

			arg += fun.get();
			while (arg[arg.length() - 1] != '\n') arg += fun.get();
			arg.pop_back();
			std::reverse(arg.begin(), arg.end());
			arg.pop_back();
			std::reverse(arg.begin(), arg.end());

			if (command == "#Name") {
				name = arg;

				fun >> command;
				fun >> arg;

				if (command == "#R") {
					for (int i = 0; i < arg.length(); i++) {
						if (arg[i] != 'B' && arg[i] != 'S' && arg[i] != '/' and !isdigit(arg[i])) format_error();
					}

					bool slash = false, S = false, B = false;
					for (int i = 0; i < arg.length(); i++) {
						if (arg[i] == '/') {
							slash = true;
							continue;
						}

						if (!slash) {
							if (isdigit(arg[i])) {
								string temp = string(1, arg[i]);
								birthRate.push_back(stoi(temp));
							}
							else {
								if (arg[i] == 'B' && !B) {
									B = true;
									continue;
								}
								else format_error();
							}
						}
						else {
							if (isdigit(arg[i])) {
								string temp = string(1, arg[i]);
								surviveRate.push_back(stoi(temp));
							}
							else {
								if (arg[i] == 'S') {
									S = true;
									continue;
								}
								else format_error();
							}
						}
					}

					fun >> command;
					fun >> arg;

					if (command == "#S") {
						for (int i = 0; i < arg.length(); i++) {
							if (!isdigit(arg[i]) && arg[i] != '/') format_error();
						}

						bool slash = false;

						string temp = "";

						for (int i = 0; i < arg.length(); i++) {
							if (arg[i] == '/') {
								slash = true;
								width = stoi(temp);
								temp = "";
								continue;
							}

							if (!slash) {
								if (isdigit(arg[i])) temp += arg[i];
								else format_error();
							}
							else {
								if (isdigit(arg[i])) temp += arg[i];
								else format_error();
							}
						}

						height = stoi(temp);

						while (!fun.eof()) {
							fun >> command;
							fun >> arg;

							x.push_back(stoi(command));
							y.push_back(stoi(arg));
						}

						un.push_back(string(width + 2, 'X'));

						for (int i = 1; i <= height; i++) {
							un.push_back("X");
							un[i] += string(width, '*');
							un[i] += 'X';
						}

						un.push_back(string(width + 2, 'X'));

						for (int i = 0; i < x.size(); i++) un[x[i]][y[i]] = '^';
					}
					else format_error();
				}
				else format_error();
			}
			else format_error();
		}
		else format_error();
	}
	
	string readRules() {
		string rules = "";

		fru.open("./rules.txt");

		while (!fru.eof()) rules += fru.get();

		rules.pop_back();

		fru.close();

		return rules;
	}

	void show() {
		for (int i = 0; i < height + 2; i++) cout << un[i] << endl;
	}
};

class Game : private inputData, public Initialization, public Quick_game, public Offline_mode {
private:
	void start() {
		string command;

		cout << "Добро пожаловать в игру 'Жизнь'" << endl;
		cout << "По ходу игры вам будет предлагаться набор команд, которые вы будете вводить через консоль\n" << endl;

		cout << "start - начать игру" << endl;
		cout << "rules - правила игры" << endl;
		cout << "help - помощь" << endl;
		cout << "exit - выход из игры (будет доступна в любой момент игры)" << endl;

		while (true) {
			cin >> command;

			if (command == "start") {
				cout << "Начать игру с заранее заданной вселенной? y/n (да/нет)" << endl;

				while (true) {
					cin >> command;

					if (command == "y") {
						cout << "Введите имя файла, с которой считаете вселенную" << endl;
						cout << "Внимание! Обязательно указание расширения!" << endl;

						string filename;
						cin >> filename;
						if (filename == "exit") exit(0);

						readUn(filename);
						break;
					}
					if (command == "n") {
						while (true) {
							vers = initVers();
							if (vers == "") continue;

							name = initName();
							if (name == "") continue;

							vector<vector<int>> rates = initRules();
							if (rates.size() == 0) continue;
							else birthRate = rates[0], surviveRate = rates[1];

							vector<int> size = initSize();
							if (size.size() == 0) continue;
							else width = size[0], height = size[1];

							vector<vector<int>> pairs = coordinates(width, height);
							if (pairs.size() == 0) continue;
							else {
								un = initUn(width, height);

								for (int i = 0; i < pairs[0].size(); i++) un[pairs[0][i]][pairs[1][i]] = '^';

								break;
							}
						}

						break;
					}

					if (command == "exit") exit(0);

					cout << "Команда '" << command << "' не поддерживается на данном этапе игры" << endl;
				}

				break;
			}

			if (command == "rules") {
				cout << readRules() << endl;
				continue;
			}

			if (command == "help") {
				cout << inputData::readHelp() << endl;
				continue;
			}

			if (command == "exit") exit(0);

			cout << "Команда '" << command << "' не поддерживается на данном этапе игры." << endl;
		}

		cout << "Отлично! Ваша вселенная выглядит вот так:" << endl;
		show();

		cout << "Введите одну из следующих команд:" << endl;
		cout << "quick_game - быстрая игра" << endl;
		cout << "offline_mode - 'оффлайн' режим" << endl;
		cout << "help - подробнее о режимах игры" << endl;

		while (true) {
			cin >> command;

			if (command == "quick_game") {
				gamemode = command;
				break;
			}
			if (command == "offline_mode") {
				gamemode = command;
				break;
			}
			if (command == "help") {
				cout << readModes() << endl;
				continue;
			}

			if (command == "exit") exit(0);

			cout << "Команда '" << command << "' не поддерживается на данном этапе игры." << endl;
		}
	}

	void gameplay() {
		if (gamemode == "quick_game") Quick_game::play(un, birthRate, surviveRate, vers, name, width, height);
		if (gamemode == "offline_mode") Offline_mode::play(un, birthRate, surviveRate, vers, name, width, height);
	}
public:
	void session() {
		start();
		gameplay();
	}
};