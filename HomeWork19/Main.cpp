# include <iostream>
#include<string>
#include<ctime>
#include<cstdlib>

void array_Filling(int arr[], const short length) { // Процедура заполнения массива (для задач 1)
	for (short i = 0; i < length; i++) {
		std::cout << "Enter the number N " << i + 1 << " -> ";
		std::cin >> arr[i];
	}
}

int divisor_Max(int arr[], const short length, int divisor) { // Рекурсивная функция поиска максимального общего делителя (для задачи 1)
	for (short i = 0; i < length; i++)
		if (arr[i] % divisor && divisor) 
			return divisor_Max(arr, length, divisor - 1);		
	return divisor;
}

void array_Print(int arr[],const short length) { // Процедура вывода массива в консоль (для задач 1, 3)
	for (short i = 0; i < length; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\b\b ";
}

long long mirror_Number(long long number) { // Функция зеркалирования числа (для обоих варинтов задачи 2)
	short length_number = std::to_string(number).length(); // Определяем длину введённого пользователем числа в кол-ве символов
	std::string number_Text = std::to_string(number); // Переводим введённое пользователем число в текстовую строку
	short* arr = new short[length_number]; // Выделяем память под динамический массив типа данных short
	for (short i = 0; i < length_number; i++) { // Формируем динамический массив чисел из массива string с учётом зеркалирования
		arr[i] = number_Text[length_number - i - 1];
	}
	for (short i = 0; i < length_number; i++) // Цикл перезаписи отзеркалированного массива в массив string
		number_Text[i] = arr[i];
	delete [] arr; // Чистим память от динамического массива
	return stoll(number_Text); // Возвращаем отзеркалированное число 
}

short array_Sort(int arr[], const short length, int n) { // Функция нахождения в массиве числа n с последующей сортировкой массива с числа n (для задачи 3)
	short index = -1; // Переменная для хранения индекса первого элемента массива, равного числу n, введённому пользователем. Инициализируем переменную
						// значением, которое не может быть у индекса массива	
	for(short i = 0; i < length; i++) // Цикл поиска элемента массива, равного n
		if (arr[i] == n) { // Если такой элемент найден, то
			index = i; // записываем индекс в переменную
			break; // прекращаем поиски (первый элемент найден)
		}
	if (index >= 0) { // Если есть, что сортировать, то 
		if (index == length)
			std::cout << "\033[92mUnable to sort array! Number "<< n <<" is last\033[0m";
		else
			if (index == length - 1)
				std::cout << "\033[92mUnable to sort array! Number " << n << " is penultimate\033[0m";
			else {
				char my_Choise; // Локальная переменная для хранения вабора пользователя
				int tmp; // Локальная временная переменная для реализации механизма сортировки
				std::cout << "\nSpecify how to sort the array: \npress \'1\' to sort in ascending order or press any other key to sort descending\nYour choise -> ";
				std::cin >> my_Choise;
				switch (my_Choise) { // Конструкция для сортировки массива с числа n в соответствии с выбором пользователя
				case '1':
					for (short i = length - 1; i > index; i--) // Цикл сортировки массива по возрастанию
						for (short j = index + 1; j < length - 1; j++)
							if (arr[j] > arr[j + 1]) {
								tmp = arr[j];
								arr[j] = arr[j + 1];
								arr[j + 1] = tmp;
							}
					break;
				default:
					for (short i = length - 1; i > index; i--) // Цикл сортировки массива по убыванию
						for (short j = index + 1; j < length - 1; j++)
							if (arr[j] < arr[j + 1]) {
								tmp = arr[j];
								arr[j] = arr[j + 1];
								arr[j + 1] = tmp;
							}
				}
			}		
	}
	return index;
}

void range(int arr[], const short length, int a, int b) { // Процудера заполнения массива случайными числами (для задач 3 и 4)
	while (b < a) { // Цикл проверки введённого пользователем диапазона
		std::cout << "Input error! The end of the range cannot be less than the start of the range!\nEnter the start of the range = ";
		std::cin >> a;
		std::cout << "Enter the end of the range = ";
		std::cin >> b;
	}
	srand(time(NULL));
	for (short i = 0; i < length; i++) // Цикл заполнения массива случайными числами [a...b]
		arr[i] = rand() % (b - a + 1) + a;
}

int main() {

	// Задача 1. Наибольший общий делитель
	std::cout << "\033[91mTask 1. Greatest common divisor\033[0m\n\n";
	const short length = 2; // Размер массива (можно менять, задача будет работать)
	int array_Divisor[length]{}; // Числа для массовости (не только 2, как в условии задачи, но и большее кол-во чисел) будут храниться в массиве
	array_Filling(array_Divisor, length);
	int divisor = array_Divisor[0]; // Объявляем и инициализируем переменную для хранения максимального общего делителя
	for (short i = 1; i < length; i++) // Цикл определения минимального из введённых чисел
		divisor = divisor > array_Divisor[i] ? array_Divisor[i] : divisor; // Находим наименьшее из чисел, принимаем это число за максимальный общий делитель
	std::cout << "\n\033[092mMaximum common divisor of numbers ";
	array_Print(array_Divisor, length);
	std::cout << "is " << divisor_Max(array_Divisor, length, divisor) << "\033[0m\n\n";

	// Задача 2. Зеркальное отражение числа
	std::cout << "\033[91mTask 2. Mirroring a number\033[0m\n\nEnter a positive integer number -> ";

	//Вариант решения 1 (через string с проверками на корректность ввода)
	std::string my_Text;
	std::cin >> my_Text;
	bool key_Mistake = false; // Вводи переменную для хранения кода ошибки
	short size = std::size(my_Text); // Находим длину введённой строки
	for (short i = 0; i < size; i++) { // Цикл проверки введёной пользователем строки
		short symbol = int(my_Text[i]); // В локальную переменную записываем код по ASCII-таблице текущего значения символа строки
		if (symbol < 48 || symbol > 57) {
			std::cout << "\n\033[92mInput error! The entered value is not a positive integer!\033[0m\n\n";
			key_Mistake = true;
			break; // Если текущий элемент строки не цифра, то нет смысла дальше крутить цикл
		}
	}
	if (key_Mistake == false) { // Если введённая пользователем строка число, то
		long long number = stoll(my_Text); // Объявляем и инициализируем переменную для хранения введённого пользователем числа
		std::cout << "\033[92m\nReflected entered number is " << mirror_Number(number) << "\033[0m\n\n";
	}

	// Варинт решения 2 (через простой ввод числа) 
	/*long long num;
	std::cin >> num;
	while (num < 0) {
		std::cout << "Input error! The entered value is not a positive integer!\nEnter a positive integer number -> ";
		std::cin >> num;
	}
	std::cout << "\033[92m\nReflected entered number is " << mirror_Number(num) << "\033[0m\n\n";*/

	// Задача 3. Число N в массиве
	const short length_Array = 10;
	int array_N[length_Array]{};
	int n; // Переменная для хранения числа N
	char my_Choise; // Переменная для хранения выбора пользователя
	std::cout << "\033[91mTask 3. Number N in array\033[0m\n\nChoose how to fill the array:\npress \'1\' to manual entry of array elements or press any other key for random array filling\nYour choise -> ";
	std::cin >> my_Choise;
	switch (my_Choise) { // Конструкция для заполнения массива в соответствии с выбором пользователя
	case '1':
		for (short i = 0; i < length_Array; i++) { // Цикл ручного заполнения массива
			std::cout << "Enter array element N " << i << " -> ";
			std::cin >> array_N[i];
		}
		break;
	default:
		int a, b; // локальные переменные для хранения начала и конца диапазона 
		std::cout << "\nSpecify a range of random numbers:\nEnter the start of the range = ";
		std::cin >> a;
		std::cout << "Enter the end of the range = ";
		std::cin >> b;
		range(array_N, length_Array, a, b);		
	}
	std::cout << "\n\033[92mSource array is: \033[0m\n";
	array_Print(array_N, length_Array);
	std::cout << std::endl;
	std::cout << "\nEnter a number from which to start sorting the array N = ";	
	std::cin >> n;
	short result = array_Sort(array_N, length_Array, n); // Переменная для хранения индекса элемента массива, равного введённому пользователем числу
	if (result > -1) { // Если индекс найден (число n пользователя есть в массиве)
		std::cout << "\n\033[92mThe number " << n << " first occurs in the array by index " << result << "\n\nFinal array is: \033[0m";
		array_Print(array_N, length_Array);
	}
	else // Если в массиве нет элемента, равного ввдённому пользоателем числу
		std::cout << "\n\033[92mThere is no element in the array equal to the number " << n << "\033[0m";	
	std::cout << "\n\n";

	// Задача 4. Заполнение массива случайными числами из диапазона пользователя
	std::cout << "\033[91mTask 4. Filling an array with random numbers from a range\033[0m\n";
	const short size_Array_Range = 10;
	int array_Range[size_Array_Range];
	int start_Range, end_Range; // локальные переменные для хранения начала и конца диапазона 
	std::cout << "\nSpecify a range of random numbers:\nEnter the start of the range = ";
	std::cin >> start_Range;
	std::cout << "Enter the end of the range = ";
	std::cin >> end_Range;
	range(array_Range, size_Array_Range, start_Range, end_Range);
	std::cout << "\n\033[92mFinal array is: \033[0m";
	array_Print(array_Range, size_Array_Range);
	std::cout << "\n\n";

	return 0;
}