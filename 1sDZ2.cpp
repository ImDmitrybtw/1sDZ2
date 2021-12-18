#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<cctype>

using namespace std;

/*  Домашнее задание № 2
	Разработать программу для реализации алгоритма
шифрования и расшифрования данных, используя метод
гаммирования и поразрядного циклического сдвига. Алгоритм: для
блока данных заданного размера берется такого же размера
фрагмент гаммы и выполняется операция поразрядного
исключающего «ИЛИ», далее, выполняется операция поразрядного
циклического сдвига на заданное число бит влево или вправо с
полученным новым блоком. Расшифрование выполняется в
обратном порядке, вначале циклический сдвиг в противоположную
сторону, а затем операция поразрядного исключающего «ИЛИ» с
блоками той же самой гаммы.
Программа может запускаться в двух режимах: шифрование и
расшифрование.
Режим шифрование: на вход программы поступают два
параметра (параметры функции main): encryption и имя файла, в
котором сохраняются зашифрованные данные. Далее пользователь
вводит по запросу строку текста, которая должна шифроваться,
пароль (целое число), зашифрованные данные сохраняются в файле.
Режим расшифрование: на вход программы поступают два
параметра (параметры функции main): decryption и имя файла, в
котором хранятся зашифрованные данные (файл должен
существовать). Далее пользователь по запросу вводит пароль (целое
число), расшифрованные данные из файла выводятся на консоль.

	Пауль Дмитрий ИУ8-13
	Вариант 17
	Циклический сдвиг вправо на 2
	Размер обрабатываемого блока данных = 2 байта
*/
bool check_key(string key) {
	if (key.empty())
		return false;
	if (static_cast<int>(key.size()) > 9)
		return false;
	for (int i = 0; i != static_cast<int>(key.size()); ++i) {
		if (!('0' <= key[i] && '9' >= key[i]))
			return false;
	}
	return true;
}

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		cerr << "Error: Use three parameters\n";
		return 5;
	}
	const string mode(argv[1]); // Режим работы
	const string file_name(argv[2]); // Имя файла
	//const string mode = "decryption";
	//const string file_name = "C:\\Users\\79166\\Desktop\\txt4.txt"; // Имя файла
	unsigned int shift = 2; //Циклический сдвиг вправо
	string key;

	if (mode != "encryption" && mode != "decryption") {
		cerr << "Error: Invalid mode\n";
		return 9;
	}

	if (mode == "encryption") { // Режим шифрование
		std::ofstream out(file_name, ios_base::binary);
		if (!out.is_open()) {
			cerr << "Error: File doesn't exist\n";
			return 1;
		}
		string text_input;
		cout << "Enter a text\n";
		getline(cin, text_input);
		cout << "Enter a key (an integer from 0 to 10^9 - 1)\n";
		getline(cin, key);
		if (!check_key(key)) {
			cerr << "Error: Invalid key\n";
			return 6;
		}
		srand(static_cast<unsigned int>(stoi(key)));
		vector<char> symbs(text_input.size());
		for (int i = 0; i != text_input.size(); ++i) {
			symbs[i] = text_input[i];
		}

		for (int i = 0; i < symbs.size(); i += 2) {
			unsigned int gamma = rand();
			unsigned int block;
			if (i + 1 < symbs.size())
				block = (static_cast<unsigned int>(symbs[i]) << 8) | (static_cast<unsigned int>(symbs[i + 1]));
			else
				block = (static_cast<unsigned int>(symbs[i]) << 8);
			unsigned int block_gamma = block ^ gamma;
			unsigned int block_encrypt = ((block_gamma >> shift) & 0xFFFF) | (block_gamma << (16 - shift) & 0xFFFF); // Сдвиг с наложением маски
			unsigned char a = block_encrypt >> 8;
			unsigned char b = block_encrypt;
			out << a << b;
		}
		out.close();
		cout << "The text was successfully encrypted\n";
	}

	if (mode == "decryption") { // Режим расшифрования

		std::ifstream in(file_name, ios_base::binary);
		if (!in.is_open()) {
			cerr << "Error: File doesn't exist\n";
			return 1;
		}
		cout << "Enter a key (an integer from 0 to 10^9 - 1)\n";
		getline(cin, key);
		if (!check_key(key)) {
			cerr << "Error: Invalid key\n";
			return 6;
		}
		srand(static_cast<unsigned int>(stoi(key)));
		string str;
		getline(in, str);
		vector<unsigned char> symbs(str.size());
		for (int i = 0; i != str.size(); ++i)
			symbs[i] = str[i];
		for (int i = 0; i < symbs.size(); i += 2) {
			unsigned int gamma = rand();
			unsigned int block_encrypt;
			if (i + 1 < symbs.size())
				block_encrypt = (static_cast<unsigned int>(symbs[i]) << 8u) | (static_cast<unsigned int>(symbs[i + 1]));
			else
				block_encrypt = (static_cast<unsigned int>(symbs[i]) << 8u);
			unsigned int block_gamma = ((block_encrypt << shift) & 0xFFFF) | ((block_encrypt >> (16 - shift)) & 0xFFFF); // Сдвиг с наложением маски
			unsigned int block = block_gamma ^ gamma;
			unsigned char a = block >> 8u;
			unsigned char b = block;
			cout << a << b;
		}
		in.close();
		cout << "\nThe text was decrypted\n";
	}
	return 0;
}