#include <iostream>
#include <stdexcept>
#include <iomanip>


using namespace std;
template <class T>
class Array2D
{
public:
	class ArraylD
	{
	private:
		int dim2;
		T* Array1;
	public:
		friend class Array2D;
		ArraylD() :Array1(NULL), dim2(0) {}
		T& operator[](int index);
		const T& operator[] (int index) const;
	}; //class ArraylD 
private:
	int dim1;
	ArraylD* Array2;
	void createObj(int d1, int& d2);
	void fromInitializer(std::initializer_list<std::initializer_list<T>>& value);
public:
	//constructors
	Array2D() :dim1(0), Array2(NULL) {};
	Array2D(int d1, int d2);
	Array2D(std::initializer_list<std::initializer_list<T>> value);	
	//business methods
	int getRowsCount() const;
	int getColumnsCount() const;
	//operators
	ArraylD& operator[] (int index) {
		return Array2[index];
	}
	const ArraylD& operator[] (int index) const {
		return Array2[index];
	}
	void operator = (std::initializer_list<std::initializer_list<T>> value);
	Array2D<T>& operator = (const Array2D<T>& other);
	Array2D<T> operator * (const Array2D<T>& other);
};

void printMatrix(const Array2D<double>& matrix, string msg) {
	cout << msg << endl;
	for (int i = 0; i < matrix.getRowsCount(); cout << endl, ++i) {
		for (int j = 0; j < matrix.getColumnsCount(); ++j) {
			cout << setw(7) << left << setprecision(4) << matrix[i][j] << '\t';
		}
	}
	cout << endl;
}

int main()
{
	Array2D<double> matrixA, matrixB, matrixC;

	matrixA = { {1.1, 1.2, 1.3},
				{2.1, 2.2, 2.3},
				{3.1, 3.2, 3.3} };

	matrixB = { {2.1, 2.2, 2.3},
				{2.4, 2.5, 2.6},
				{2.7, 2.8, 2.9} };

	matrixC = matrixA * matrixB;

	printMatrix(matrixA, "matrix A");
	printMatrix(matrixB, "matrix B");
	printMatrix(matrixC, "matrix C");
}


template <class T>
Array2D<T> Array2D<T>::operator * (const Array2D<T>& b) {
	Array2D<T> a = *this;
	Array2D<T> c(a.getRowsCount(), b.getColumnsCount());
	if (a.getRowsCount() == b.getColumnsCount()) {

		for (int i = 0; i < a.getRowsCount(); i++)
		{
			for (int j = 0; j < b.getColumnsCount(); j++)
			{
				c[i][j] = 0;
				for (int k = 0; k < a.getColumnsCount(); k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}
	else {
		cout << "Multiplication is not possible.";
	}
	return c;
}
template <class T>
Array2D<T>& Array2D<T>::operator = (const Array2D<T>& other) {
	if (this == &other) {
		return *this;
	}
	int d1 = other.getRowsCount();
	int d2 = other.getColumnsCount();
	createObj(d1, d2);

	for (int i = 0; i < d1; i++) {
		for (int k = 0; k < d2; k++) {
			Array2[i].Array1[k] = other[i][k];
		}
	}
	return *this;
}
template <class T>
void Array2D<T>::operator = (std::initializer_list<std::initializer_list<T>> value) {
	fromInitializer(value);
}
template <class T>
Array2D<T>::Array2D(std::initializer_list<std::initializer_list<T>> value) {
	fromInitializer(value);
}
template<class T>
void Array2D<T>::fromInitializer(std::initializer_list<std::initializer_list<T>>& value)
{
	//get arrays size from initialize list
	size_t d1 = value.size();
	size_t d2 = 0;
	for (auto it : value) {
		std::initializer_list<T> lst = it;
		d2 = lst.size();
		break;//getting first inner array list as second size
	}

	int dim1 = (int)d1;
	int dim2 = (int)d2;

	createObj(dim1, dim2);

	//populate
	int i = 0;
	for (auto it : value) {
		std::initializer_list<T> lst = it;
		int k = 0;
		for (auto inner : lst) {
			if (k >= d2) {
				throw std::invalid_argument("array size must be the same for all records");
			}
			Array2[i].Array1[k] = inner;
			k++;
		}
		i++;
	}
}
template <class T>
T& Array2D<T>::ArraylD::operator[](int index)
{
	return Array1[index];
}
template <class T>
const T& Array2D<T>::ArraylD::operator[](int index)const
{
	return Array1[index];
}
template <class T>
Array2D<T>::Array2D(int d1, int d2)
{
	createObj(d1, d2);
}
template<class T>
void Array2D<T>::createObj(int d1, int& d2)
{
	dim1 = d1;
	Array2 = new ArraylD[dim1];
	for (int i(0); i < d1; ++i)
	{
		Array2[i].dim2 = d2;
		Array2[i].Array1 = new T[d2];
	}
}
template <class T>
int Array2D<T> ::getRowsCount() const {
	return this->dim1;
}
template <class T>
int Array2D<T> ::getColumnsCount() const {
	return this->Array2->dim2;
}
