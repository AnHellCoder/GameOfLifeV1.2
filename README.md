# GameOfLifeV1.2
Лабораторная №2 по ООП

Реализация игры "Жизнь".
Игра разделена на 10 файлов (5 исполнительных, 5 текстовых).
В файле main.cpp одна переменная типа Game - игровая сессия.
В хедере interface.hpp 3 класса - Game - администрирующий класс,
модифицирующий дальнейший ход игры,
inputData - класс, отвечающий за работу с текстовыми файлами в директории (чтение и вывод правил игры и режимов, считывание вселенной из файла),
Universe - класс, хранящий информацию о вселенной (версия игры, имя вселенной, карта, координаты живых клеток и правила перехода).
В файле initialization.hpp присутствует только класс Initialization, он необходим для ручного считывания вселенной.
В файле quick_game.hpp находится одноимённый класс, в котором происходит быстрая игра.
Там же в private есть методы countGen и countCell, но они нужны только в конце игры, чтобы вывести слова "поколение" и "клетка" в правильных для опр. числа ходов форме.
Функционал класса Offline_mode в одноимённом .hpp файле аналогичен.
