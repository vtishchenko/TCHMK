
class Big_integer
{
private:
	int size; // размер числа
	unsigned char* digs; // знаки числа
	int sign; //знак - 0 положительный , 1 - отрицательный

public:
	//Конструкторы
	Big_integer();
	Big_integer(const char* inputstr);
	Big_integer(const Big_integer& RValue);
	Big_integer(int RValue);

	~Big_integer(); // деструктор

	char* GetString(); // функция получения строки в 10-й записи

	// Операции с файлами
	bool ReadFromTextFile(const char* FileName);
	bool WriteToTextFile(const char* FileName);
	bool ReadFromBin(const char* FileName);
	bool WriteToBin(const char* FileName);



	//Операторы сравнения
	bool operator>(const Big_integer& Y);
	bool operator>=(const Big_integer& Y);
	bool operator<(const Big_integer& Y);
	bool operator<=(const Big_integer& Y);
	bool operator==(const Big_integer& Y);
	bool operator!=(const Big_integer& Y);







	//Операторы инкриментирования и декриментирования
	Big_integer operator++();
	Big_integer operator++(int);
	Big_integer operator--();
	Big_integer operator--(int);





	//Арифметические операторы
	Big_integer& operator=(const Big_integer& RValue);
	Big_integer operator+(const Big_integer& RValue) const;
	Big_integer operator-() const;
	Big_integer operator-(const Big_integer& RValue) const;
	Big_integer operator*(const Big_integer& RValue) const;
	Big_integer operator/(const Big_integer& RValue) const;
	Big_integer operator%(const Big_integer& RValue) const;
	Big_integer operator^(const Big_integer& RValue) const;

private:
	void Set_size(int size); // устанавливает размер
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void RemoveForwardZero(); // Название функции говорит само за себя
	int cmp(const Big_integer& Y);
	void Shift(int s);

	Big_integer SummOrSub(const Big_integer& LValue, const Big_integer& RValue) const;
	Big_integer Mul(const Big_integer X, const Big_integer Y) const;
	Big_integer Div(const Big_integer& X, const Big_integer& Y, Big_integer &rem) const;

};

Big_integer Pow(const Big_integer& X, const Big_integer& Y, Big_integer& M);
