# 1sDZ2
19.12.2021
    Домашнее задание № 2
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
