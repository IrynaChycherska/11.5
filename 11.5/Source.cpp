#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Institute { NY, IF, KP, DP };
string instituteStr[] = { "Львівська політехніка", "Університет ім. Івана Франка", "Київська політехніка ", "Дніпровська політехніка" };
struct Student
{
	string prizv;
	int kurs;
	string group;
	string faculty;
	Institute institute;
	double bal;
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
double CountMarks(Student* p, const int N);
double physics_and_math_five(Student* p, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Institute institute);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
void CreateBIN(char* fname);
void PrintBIN(char* fname);
void ProcessBIN1(char* fname, char* gname);
void fWrite(fstream& f, const int i, const char x);
char fRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void SortBIN(char* fname);
void SortBIN(char* fname, char* gname);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть кількість інститутів N: "; cin >> N;

	Student* p = new Student[N];	double proc;
	int iinstitute;
	Institute institute;
	int kurs;
	string prizv;
	string group;
	string faculty;
	int found;
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [4] - фізичне впорядкування даних" << endl;
		cout << " [5] - бінарний пошук студента за курсом та групою" << endl;
		cout << " [6] - індексне впорядкування та вивід даних" << endl;
		cout << " [7] - Процент студентів, які отримали середній бал не менше 3.5:" << endl;
		cout << " [8] - Процент групи, де найбільше відмінників:" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			proc = physics_and_math_five(p, N);
			cout << " Процент студентів, які отримали середній бал не менше 3.5:  " << endl;
			cout << proc << "%" << endl;

		case 4:
			Sort(p, N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " інститут (0 -Львівська політехніка, 1- Університет ім.Івана Франка, 2-Київська політехніка, 3-Дніпровська політехніка): ";
			cin >> iinstitute;
			institute = (Institute)iinstitute;
			cin.get();
			cin.sync();

			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, institute)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 6:
			proc = CountMarks(p, N);
			cout << "Процент групи, де найбільше відмінників:" << endl;
			cout << proc << "%" << endl;

		case 7:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	char fname[100];
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname);
	PrintBIN(fname);
	char gname[100];
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname);
	SortBIN(fname, gname);
	PrintBIN(gname);
	SortBIN(fname);
	PrintBIN(fname);
	return 0;
}
void Create(Student* p, const int N)
{
	int faculty, kurs, institute;
	for (int i = 0; i < N; i++)
	{
		cout << " Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].kurs;
		cout << " група: "; cin >> p[i].group;
		cout << " факультет: "; cin >> p[i].faculty;
		cout << " інститут (0 -Львівська політехніка, 1- Університет ім.Івана Франка, 2-Київська політехніка, 3-Дніпровська політехніка): ";
		cin >> institute;
		p[i].institute = (Institute)institute;
		cout << endl;
	}
}
void Print(Student* p, const int N)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Група |  Факультет | Середній бал |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << right << p[i].prizv
			<< "| " << setw(4) << right << p[i].kurs << " "
			<< "| " << setw(8) << right << p[i].group << " "
			<< "| " << setw(11) << left << instituteStr[p[i].institute];
		switch (p[i].institute)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].bal << " |" << setw(13) << right << "|" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
double physics_and_math_five(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if (p[i].bal >= 3.5)
			k++;
	return 100.0 * k / N;

}
double CountMarks(Student* p, const int N)
{
	int k = 0;
	for (int i = 0; i < N; i++)
		if (p[i].bal == 5)
			k++;
	return 100.0 * k / N;

}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].institute > p[i1 + 1].institute)
				||
				(p[i1].institute == p[i1 + 1].institute &&
					p[i1].prizv > p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int BinSearch(Student* p, const int N, const string prizv, const Institute institute)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].institute == institute)
			return m;
		if ((p[m].institute < institute)
			||
			(p[m].institute == institute &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i;
	int i, j, value;
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].institute > p[value].institute) ||
				(p[I[j]].institute == p[value].institute &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "=========================================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Група |  Факультет | Середній бал |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << right << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(8) << right << p[i].group << " "
			<< "| " << setw(11) << left << instituteStr[p[i].institute];
		switch (p[i].institute)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].bal << " |" << setw(13) << right << "|" << endl;
			break;
		}
	}
	cout << "=================================================================================================================="
		<< endl;
	cout << endl;
}
void CreateBIN(char* fname)
{
	ofstream fout(fname, ios::binary);
	char ch;
	string s;
	do
	{
		cin.get();
		cin.sync();
		cout << "enter line: "; getline(cin, s);
		for (unsigned i = 0; i < s.length(); i++)
			fout.write((char*)&s[i], sizeof(s[i]));
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname)
{
	ifstream fin(fname, ios::binary);
	char c;
	while (fin.read((char*)&c, sizeof(c)))
	{
		cout << c << endl;
	}
	cout << endl;
}
void ProcessBIN1(char* fname, char* gname)
{
	ifstream f(fname, ios::binary);
	ofstream g(gname, ios::binary);
	char c;
	while (f.read((char*)&c, sizeof(c)))
	{
		if (c >= '0' && c <= '9')
			g.write((char*)&c, sizeof(c));
	}
}
void fWrite(fstream& f, const int i, const char x)
{
	f.seekp(i * (long)sizeof(char));
	f.write((char*)&x, sizeof(char));
}
char fRead(fstream& f, const int i)
{
	char x;
	f.seekg(i * (long)sizeof(char));
	f.read((char*)&x, sizeof(char));
	return x;
}
void fChange(fstream& f, const int i, const int j)
{
	char x = fRead(f, i);
	char y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}
void SortBIN(char* fname)
{
	fstream f(fname, ios::binary | ios::in | ios::out);

	f.seekg(0, ios::end);
	int size = f.tellg();
	f.seekg(0, ios::beg);
	for (int i0 = 1; i0 < size; i0++)
		for (int i1 = 0; i1 < size - i0; i1++)
		{
			char a = fRead(f, i1);
			char b = fRead(f, i1 + 1);
			if (a > b)
				fChange(f, i1, i1 + 1);
		}
	f.seekp(0, ios::end);
}
void SortBIN(char* fname, char* gname)
{
	ofstream g(gname, ios::binary);
	char s, mins, z = 0;
	int k;
	do
	{
		k = 0;
		ifstream f(fname, ios::binary);
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			mins = s;
			k++;
			break;
		}
		while (f.read((char*)&s, sizeof(char)))
		{
			if (s <= z)
				continue;
			if (s < mins)
			{
				mins = s;
				k++;
			}
		}

		z = mins;
		if (k > 0)
			g.write((char*)&z, sizeof(char));
		f.close();
	} while (k > 0);
}

