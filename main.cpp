#define CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "interface.hpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	Game test;

	test.session();
}