#include <iostream>
using namespace std;

class AudioPlayer
{
public:
	AudioPlayer() {}
	virtual ~AudioPlayer() {}

	virtual void play() {
		cout << "Playing audio" << endl;
	}
};

class VideoPlayer
{
public:
	VideoPlayer() {}
	virtual ~VideoPlayer() {}

	virtual void play() {
		cout << "Playing video" << endl;
	}
};

class MediaPlayer : public AudioPlayer, public VideoPlayer
{
private:
	static inline unsigned count {};
	friend unsigned get_counter(const MediaPlayer&);
public:
	MediaPlayer() { this->count++; } 
	virtual ~MediaPlayer() {}
	void play() {
		AudioPlayer::play();
		VideoPlayer::play();
	}
};

unsigned get_counter(const MediaPlayer& player) {
	return player.count;
}


///////////////////////////////////////////////////////////

class Shape
{
private:
	virtual void draw() { cout << "Drawing shape" << endl; }
};

class Circle : public Shape
{
public:
	void draw() override { cout << "Drawing circle" << endl; }
};

void call_draw(Shape* shape) {
	dynamic_cast<Circle*> (shape)->draw();
}


///////////////////////////////////////////////////////////

class Matrix
{
private:
	int **matrix;
	size_t m, n;
public:
	Matrix(size_t n, size_t m) : n{n}, m{m} {//: matrix{new int*[n]} {
		matrix = new int*[n];
		for (size_t i = 0; i < n; i++) {
			matrix[i] = new int[m];
		}
	}

	Matrix(Matrix& matrix_old) : n{matrix_old.get_n()}, m{matrix_old.get_m()} {
		matrix = new int*[n];
		for (size_t i = 0; i < n; i++) {
			matrix[i] = new int[m];
		}

		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < m; j++) {
				matrix[i][j] = matrix_old.get_element(i, j);
			}
		}
	};
	
	void write(size_t r, size_t c, int val) {
		if (r < this->n and c < this->m)
			matrix[r][c] = val;
		else
			throw std::out_of_range("Index out of bounds");
	
	}

	int get_element(size_t r, size_t c) {
		if (r < this->n and c < this->m)
			return matrix[r][c];
		else
			throw std::out_of_range("Index out of bounds");
	}

	size_t get_n() { return n; }
	size_t get_m() { return m; }

	void full() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				matrix[i][j] = i;
			}
		}
	}

	void print() {
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < m; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	~Matrix() {
		for (size_t i = 0; i < n; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	friend class MatrixOperations;
};

class MatrixOperations
{
public:

	Matrix addition(Matrix& mat1, Matrix& mat2) {
		Matrix matrix_new(mat1.get_n(), mat1.get_m());

		for(size_t i = 0; i < mat1.get_n(); i++) {
			for(size_t j = 0; j < mat1.get_m(); j++) {
				matrix_new.write(i, j, mat1.get_element(i, j) + mat2.get_element(i, j));
			}
		}
		return matrix_new; //it works because it uses previously created copy constructor to keepp this matrix in memory 
	}

	Matrix multiply(Matrix& mat1, Matrix& mat2) {
		Matrix matrix_new(mat1.get_n(), mat2.get_m());
		int value;
		for (int i = 0; i < mat1.get_n(); i++) {
			for (int j = 0; j < mat2.get_m(); j++) {
				value = 0;
				for (int k = 0; k < mat1.get_m(); k++) {
 					value += mat1.get_element(i, k) * mat2.get_element(k, j);
				}
				matrix_new.write(i, j, value);
			}
		}
		return matrix_new; //it works because it uses previously created copy constructor to keepp this matrix in memory 
	}
};

int main() {
	MediaPlayer audio;
	MediaPlayer audio1;
	MediaPlayer audio2;
	audio.play();
	cout << "Number of objects: " << get_counter(audio) << endl;

	Circle circle;
	Circle* ref_circle = &circle;
	call_draw(dynamic_cast<Shape*> (ref_circle));

	Matrix mat(2, 3);
	mat.full();
	mat.print();
	mat.write(1, 2, 5);
	mat.print();
	
	//Matrix mat1(mat);
	Matrix mat1(3, 2);
	mat1.full();
	mat1.write(2, 1, 5);
	mat1.print();

	MatrixOperations op;
	Matrix mat2 = op.multiply(mat, mat1);
	mat2.print();

}
