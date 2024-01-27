//
// Created by CheeseIt on 24.01.2024.
//

#ifndef PHP_COMPILER_COMMANDS_H
#define PHP_COMPILER_COMMANDS_H

#include <vector>
#include <map>
#include "ValueAndBytes.h"
#include "code_generation/ConstantValue.h"

enum CodeCommandsNoParams {
    //Работа со стеком

    //iconst - однобайтовая комманда, загружает небольшое число на стек
    iconst_m1 = 0x2,
    iconst_0 = 0x3,
    iconst_1 = 0x4,
    iconst_2 = 0x5,
    iconst_3 = 0x6,
    iconst_4 = 0x7,
    iconst_5 = 0x8,

    // Забирает число с вершины стека
    pop = 0x57,
    //дублирует значение, лежащее на вершине стека
    dup = 0x59,

    // дублирует одно(для long и double) или два(для всего кроме long и double) значения лежащие на вершине стека.
    dup2 = 0x5C,

    //Арифметические операции

    // выполняет сложение двух целых чисел, лежащих на вершине стека(с их удалением оттуда) и помещает сумму на вершину стека.
    iadd = 0x60,
    // выполняет умножение двух целых чисел, лежащих на вершине стека
    imul = 0x64,
    // Выполняет вычитание двух целых чисел, лежащих на вершине стека
    isub = 0x68,
    // Выполняет деление двух целых чисел, лежащих на вершине стека
    idiv = 0x6C,

    //определяет длину массива
    //В случае, если ссылка на массив содержит null будет выброшено исключение NullPointerException
    arraylength = 0xBE,

    //загружают на стек целое число (iaload)из массива по индексу.
    iaload = 0x2E,
    //загружают на стек ссылку (aaload) из массива по индексу.
    aaload = 0x32,

    // сохраняют целое число (iastore) в массив по индексу.
    iastore = 0x4F,
    // сохраняют ссылку (aastore) в массив по индексу.
    aastore = 0x53,

    // Завершает выполнение текущего метода с возвращением целого числа (ireturn)
    ireturn = 0xAC,
    // авершает выполнение текущего метода с возвращением ссылки на объект (areturn)
    areturn = 0xB0,

    // завершает выполнение текущего метода. Метод должен иметь возвращаемый тип void.
    _return = 0xB1

};

enum CodeCommandsOneParam {
    //Работа со стеком

    // загружает на стек однобайтовую целую константу
    bipush = 0x10,

    //

    // Загружают на стек целую или дробную константу из таблицы констант класса как однобайтное число
    ldc = 0x12,

    //загружают на стек целое число
    iload = 0x15,

    aload = 0x19,

    // сохраняют из стека в локальную - целое
    istore = 0x36,
    // сохраняют из стека в локальную - ссылка
    astore = 0x3A,
};

enum CodeCommandsOneParamTwoBytes {

    // загружает на стек двухбатовую целую константу
    sipush = 0x11,

    // Загружают на стек целую или дробную константу из таблицы констант класса как двухбайтное
    ldc_w = 0x13,

    //Передача управления

    // Целые числа
    // =
    if_icmpeq = 0x9F,
    // !=
    if_icmpne = 0xA0,
    // <
    if_cmplt = 0xA1,
    // <=
    if_cmple = 0xA4,
    // >
    if_cmpgt = 0xA3,
    // >=
    if_cmpge = 0xA2,

    // = 0
    ifeq = 0x99,
    // != 0
    ifne = 0x9A,
    // <0
    iflt = 0x55,
    // <=0
    ifle = 0x9E,
    // > 0
    ifgt = 0x9D,
    // >= 0
    ifge = 0x9C,

    // Ссылки

    // Ссылка = Ссылка
    if_acmpeq = 0xA5,

    // !=
    if_acmpne = 0xA6,

    // безусловный переход на указанное смещение от текущей команды
    go_to = 0xA7,


    // создает массив заданного типа и размера в «куче» и помещает ссылку на него на вершину стека.
    // Тип массива определяется по таблице констант текущего класса. В таблице констант элемент с номером,
    // указанным в команде, должен содержать символическую ссылку на тип класса, массива или интерфейса.
    // При разрешении символической ссылки может быть выброшено любое из исключений классов и интерфейсов
    anewarray = 0xBE,

    // Создает объект заданного типа в области динамически выделяемой памяти («куче») и
    //помещает ссылку на него на вершину стека.
    _new = 0xBB,

    //получает значение поля объекта
    getfield = 0xB4,
    //устанавливает значение поля объекта
    putfield = 0xB5,

    // проверяет, является ли ссылка на объект экземпляром заданного класса.
    instanceof = 0xC1,
    // проверяет, является ли ссылка на объект экземпляром заданного класса.
    checkcast = 0xC0,

    // вызывает метод экземпляра класса
    invokevirtual = 0xB6,

    // вызывает специальный метод экземпляра класса: в частности, она должна
    //использоваться для вызовов конструкторов (метода с именем <init>, который необходимо вызвать после
    //выполнения команд типа new), а также при необходимости вызвать метод родительского класса, пере-
    //груженный в потомке для объекта-потомка (invokevirtual будет искать метод, соответствующий классу
    //текущего объекта, какой бы класс из его родителей не был указан в таблице констант). В остальном
    //функция аналогична invokevirtual.
    invokespecial = 0xB7,

    // вызывает статический метод класса.
    invokestatic = 0xB8
};

enum CodeCommandsTwoParams {

    // Прибавляет знаковое число размером 1 байт непосредственно к значению локальной переменной
    iinc = 0x84,

};

enum CodeCommandsSwitch {

    // Используется для реализации команды switch и используется в тех случаях,
    // когда ключи расположены достаточно близко друг к другу, так что они могут служить индексами масси-ва.
    // Поступающий индекс будет сравнен с верхней и нижней границами. Если он меньше нижней или
    // больше верхней, то будет произведен переход по сдвигу адрес команды + сдвиг по умолчанию. Иначе из
    // таблицы сдвигов извлечется сдвиг с индекс – нижняя граница и произойдет переход по нему
    tableswitch = 0xAA,

    // Используется для реализации команды switch и используется в тех случаях,
    //когда ключи являются произвольными целочисленными значениями. Поступивший на вход индекс будет
    //сравниваться со всему указанными ключами и если совпадет с одним из них, то произойдет переход по
    //соответствующему сдвигу. Если индекс не совпадет ни с одним ключом, то произойдет сдвиг по умолча-
    //нию
    lookupswitch = 0xAB
};

enum CodeCommandsArray {
    // Массивы

    // создает массив заданного типа и размера в области динамически выделяемойпамяти («куче») и помещает ссылку на него на вершину стека
    newarray = 0xBC,

};

class Commands {

public:

    // Функция для команд без параметров
    static void doCommand(CodeCommandsNoParams type, vector<ValueAndBytes *> *res) {
        res->push_back(new ValueAndBytes(type, 1));
    }

    // Функция для команд с одним однобайтовым параметром
    static void doCommand(CodeCommandsOneParam type, int param, vector<ValueAndBytes *> *res) {

        res->push_back(new ValueAndBytes(type, 1));

        res->push_back(new ValueAndBytes(param, 1));
    }

    // Функция для команд с одним двубайтовым параметром
    static void doCommandTwoBytes(CodeCommandsOneParamTwoBytes type, int param, vector<ValueAndBytes *> *res) {

        res->push_back(new ValueAndBytes(type, 1));

        res->push_back(new ValueAndBytes(param, 2));
    }

    // Функция для команды с двумя параметрами
    static void doCommand(CodeCommandsTwoParams type, int param1, int param2, vector<ValueAndBytes *> *res) {

        res->push_back(new ValueAndBytes(type, 1));

        res->push_back(new ValueAndBytes(param1, 1));

        res->push_back(new ValueAndBytes(param2, 1));

    }


    // Используется для реализации команды switch и используется в тех случаях,
    // когда ключи расположены достаточно близко друг к другу, так что они могут служить индексами масси-ва.
    // Поступающий индекс будет сравнен с верхней и нижней границами. Если он меньше нижней или
    // больше верхней, то будет произведен переход по сдвигу адрес команды + сдвиг по умолчанию. Иначе из
    // таблицы сдвигов извлечется сдвиг с индекс – нижняя граница и произойдет переход по нему
    static void
    doTableSwitchCommand(int zeroAmount, int defaultShift, int topBorder, int BottomBorder, const vector<int> &shifts,
                         vector<ValueAndBytes *> *res) {

        // Записываю код комманды
        res->push_back(new ValueAndBytes(tableswitch, 1));

        // Записываю вспомогательные нули
        for (zeroAmount; zeroAmount > 0; zeroAmount--) {
            res->push_back(new ValueAndBytes((int) 0x00, 1));
        }

        // Записываю сдвиг по умолчанию
        res->push_back(new ValueAndBytes(defaultShift, 4));

        // Записываю границы
        res->push_back(new ValueAndBytes(BottomBorder, 4));

        res->push_back(new ValueAndBytes(topBorder, 4));

        // Записываю сдвиги для каждого случая
        for (int shift: shifts) {
            res->push_back(new ValueAndBytes(shift, 4));
        }
    }

    // Используется для реализации команды switch и используется в тех случаях,
    //когда ключи являются произвольными целочисленными значениями. Поступивший на вход индекс будет
    //сравниваться со всему указанными ключами и если совпадет с одним из них, то произойдет переход по
    //соответствующему сдвигу. Если индекс не совпадет ни с одним ключом, то произойдет сдвиг по умолчанию
    static void doLookUpSwitchCommand(int zeroAmount, const map<int, int> &shifts, vector<ValueAndBytes *> *res) {
        // Записываю код комманды
        res->push_back(new ValueAndBytes(lookupswitch, 1));

        // Записываю вспомогательные нули
        for (zeroAmount; zeroAmount > 0; zeroAmount--) {
            res->push_back(new ValueAndBytes((int) 0x00, 1));
        }

        for (auto shift: shifts) {
            res->push_back(new ValueAndBytes(shift.first, 2));
            res->push_back(new ValueAndBytes(shift.second, 4));
        }

    }

    // создает массив заданного типа и размера в области динамически выделяемойпамяти («куче») и помещает ссылку на него на вершину стека
    static void doNewArrayCommand(ConstantType arrayItemsType, vector<ValueAndBytes *> *res) {

        res->push_back(new ValueAndBytes(newarray, 1));
        res->push_back(new ValueAndBytes(arrayItemsType, 1));
    }

};


#endif //PHP_COMPILER_COMMANDS_H
