#include <iostream>
#include<string>
#include<chrono>
#include<functional>
#include <cmath>
#include <vector>
using namespace std;

class LibrFunc
{
public:
	int m = 281;
	string a;
	string b;
	string n;
	string null;
	string one;
	int matrix[281][281];

	LibrFunc(string s1, string s2, string s3);

	bool Check(int m);

	void Print(string s);

	void MultiMatrix();

	string Add(string a, string b);

	string Mul(string a, string b);

	int Trace(string a);

	string Square(string a);

	string Pow(string a, string n);

	string Inverse(string a);
};

LibrFunc::LibrFunc(string s1, string s2, string s3)
{
	if (Check(m))
	{
		cout << "The optimal normal basis for the expansion of the field " << m << " exists!" << endl;
	}
	else cout << "There is no optimal normal basis for expanding the field " << m << endl;
	a = s1;
	b = s2;
	n = s3;
	string null(m, '0');
	this->null = null;
	string one(m, '1');
	this->one = one;
	MultiMatrix();
};

bool LibrFunc::Check(int m)
{
	int p = 2 * m + 1;
	for (int i = 2; i <= sqrt(p); i++)
	{
		if (p % i == 0) return false;
	}
	int n = 2;
	for (int k = 1; k < m; k++)
	{
		if (n == 1) return false;
		n = (n * 2) % p;
	}
	if (n == p - 1) return true;
	if (n == 1 && p % 4 == 3) return true;
	return false;
}

void LibrFunc::Print(string s)
{
	cout << s << endl;
};

void LibrFunc::MultiMatrix()
{
	int x, y, k;
	int p = 2 * m + 1;
	vector<int> q(m, 1);
	for (int i = 1; i < m; i++)
	{
		q[i] = (q[i - 1] * 2) % p;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = i; j < m; j++)
		{
			x = q[i];
			y = q[j];
			if ((x + y) % p == 1) k = 1;
			else if ((p + (x - y) % p) % p == 1) k = 1;
			else if ((p + (-x + y) % p) % p == 1) k = 1;
			else if ((p + (-x - y) % p) % p == 1) k = 1;
			else k = 0;
			matrix[i][j] = k;
			matrix[j][i] = k;
		}
	}
};

string LibrFunc::Add(string a, string b)
{
	string c = null;
	for (int i = 0; i < m; i++)
	{
		c[i] = ((a[i] - '0') ^ (b[i] - '0')) + '0';
	}
	return c;
};

string LibrFunc::Mul(string a, string b)
{
	string c = null;
	string str = null;
	int sum;
	for (int i = 0; i < m; i++)
	{
		for (int l = 0; l < m; l++)
		{
			sum = 0;
			for (int j = 0; j < m; j++)
			{
				sum = (sum + ((a[j] - '0') & matrix[j][l])) & 1;
			}
			str[l] = sum + '0';
		}
		sum = 0;
		for (int j = 0; j < m; j++)
		{
			sum = (sum + (str[j] & b[j] - '0')) & 1;
		}
		c[i] = sum + '0';
		a = a.substr(1) + a.substr(0, 1);
		b = b.substr(1) + b.substr(0, 1);
	}
	return c;
};

int LibrFunc::Trace(string a)
{
	int count = 0;
	for (int i = 0; i < a.length(); i++)
	{
		count = (count + (a[i] - '0' & 1)) & 1;
	}
	return count;
};

string LibrFunc::Square(string a)
{
	a = a.substr(a.length() - 1) + a.substr(0, a.length() - 1);
	return a;
};

string LibrFunc::Pow(string a, string n)
{
	string c = one;
	reverse(n.begin(), n.end());
	for (int i = m - 1; i >= 0; i--)
	{
		if (n[i] == '1') c = Mul(c, a);
		if (i != 0) c = Square(c);
	}
	return c;
};

string LibrFunc::Inverse(string a)
{
	string n = "100011000";
	string b = a;
	int k = 1;
	string c;
	for (int i = 1; i < n.length(); i++)
	{
		c = b;
		for (int j = 0; j < k; j++)
		{
			c = Square(c);
		}
		b = Mul(b, c);
		k = (k * 2) % m;
		if (n[i] == '1')
		{
			b = Mul(Square(b), a);
			k = (k + 1) % m;
		}
	}
	return Square(b);
};

double MeasureTime(function<void()> operation) {
	auto start_time = chrono::high_resolution_clock::now();

	operation();

	auto end_time = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed_time = end_time - start_time;

	return elapsed_time.count();
}

int main()
{
	string s1, s2, s3, str;
	s1 = "10101110001100111011100010000011101110111111110001100000000101111011000100010101011001010101001011011111100110010111111010101010011110001100011000101110000100111111010111110001111001000001100110110001010110010100001011101011010111110010001011010100110000011010010000100101011010101";
	s2 = "00010001101001010001001100101101110111001001011110110010101011110110000011101011101001101010100001010000000001010100001010111110101101001100000111101010101001010011101101000010010010011001001010111111011011111100011001101111110101000101011100001001111000001001000111111110101011111";
	s3 = "10101011111101101100001000001010011100011110100100011110000010011011100000010011100000110110111100011100010110001101110100101011011010000100101101111100101010100101011010011001101001011101001111000011101110011000100011011000011001011100111110000010010100000010011101000000011000101";

	LibrFunc A(s1, s2, s3);

	double time_add = MeasureTime([&]() {
		cout << "\nA+B: ";
		A.Print(A.Add(A.a, A.b));
		});
	cout << "Time taken for addition: " << time_add << " seconds" << endl;

	double time_mul = MeasureTime([&]() {
		cout << "\nA*B: ";
		A.Print(A.Mul(A.a, A.b));
		});
	cout << "Time taken for multiplication: " << time_mul << " seconds" << endl;

	double time_trace = MeasureTime([&]() {
		cout << "\nTrace(A): ";
		cout << A.Trace(A.a) << endl;
		});
	cout << "Time taken to calculate the trace: " << time_trace << " seconds" << endl;

	double time_square = MeasureTime([&]() {
		cout << "\nA^2: ";
		A.Print(A.Square(A.a));
		});
	cout << "Time taken to calculate the square: " << time_square << " seconds" << endl;

	double time_power = MeasureTime([&]() {
		cout << "\nA^n: ";
		A.Print(A.Pow(A.a, A.n));
		});
	cout << "Time taken for exponentiation: " << time_power << " seconds" << endl;

	double time_inv = MeasureTime([&]() {
		cout << "\nA^(-1): ";
		A.Print(A.Inverse(A.a));
		});
	cout << "Time taken to calculate the inverse: " << time_inv << " seconds" << endl;

	cout << "\n(a + b) * c = a * c + b * c: ";
	string w = A.Mul(A.Add(A.a, A.b), A.n);
	string u = A.Add(A.Mul(A.a, A.n), A.Mul(A.b, A.n));

	if (u.compare(w) == 0) {
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}

	cout << "\n a^(2^m - 1):";
	A.Print(A.Mul(A.a, A.Inverse(A.a)));
	if ((A.one).compare(A.Pow(A.a, A.one)) == 0) {
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}
}
