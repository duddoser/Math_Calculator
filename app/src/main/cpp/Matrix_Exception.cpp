#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Exception: public exception{
 protected:
  //сообщение об ошибке
  char* str;
 public:
  Exception(const char* s){
    str = new char[strlen(s) + 1];
    strcpy_s(str, strlen(s) + 1, s);
  }
  Exception(char* s){
    str = new char[strlen(s) + 1];
    strcpy_s(str, strlen(s) + 1, s);
  }
  Exception(){
    str = NULL;
  }
  Exception(const Exception& e){
    str = new char[strlen(e.str) + 1];
    strcpy_s(str, strlen(e.str) + 1, e.str);
  }
  ~Exception(){
    delete[] str;
  }

  virtual void print(){
    cout << "Exception: " << str<< "; " << what();
  }
};

class IndexOutOfBounds : public Exception{
 protected:
  int row_index; int col_index;
 public:
  //конструктор
  IndexOutOfBounds(char* s, int RowIndex, int ColIndex) : Exception(s){
    row_index = RowIndex; col_index = ColIndex;
  }
  IndexOutOfBounds(const char* s, int RowIndex, int ColIndex) : Exception(s){
    row_index = RowIndex; col_index = ColIndex;
  }

  IndexOutOfBounds(const IndexOutOfBounds& e){
    str = new char[strlen(e.str) + 1];
    strcpy_s(str, strlen(e.str) + 1, e.str);
    row_index = e.row_index; col_index = e.col_index;
  }

  virtual void print(){
    cout << "IndexOutOfBounds: " << str << "; " << what();
  }
};

class TooWideIndex : public IndexOutOfBounds{
 public:
  //конструкторы
  TooWideIndex(char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex){}
  TooWideIndex(const char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex){}
  TooWideIndex(const TooWideIndex& e) : IndexOutOfBounds(e){}

  virtual void print(){
    cout << "TooWideIndex: " << str << row_index << " " << col_index << "; " << what();
  }

};

class NegativeIndex : public IndexOutOfBounds{
 public:
  //конструкторы
  NegativeIndex(char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex){}
  NegativeIndex(const char* s, int RowIndex, int ColIndex) : IndexOutOfBounds(s, RowIndex, ColIndex){}
  NegativeIndex(const NegativeIndex& e) : IndexOutOfBounds(e){}

  virtual void print(){
    cout << "NegativeIndex: " << str << row_index << " " << col_index << "; " << what();
  }

};

class WrongDimensions : public Exception{
 protected:
  int rows1; int cols1; int rows2; int cols2;

 public:
  //конструктор
  WrongDimensions(char* s, int Rows1, int Cols1, int Rows2, int Cols2) : Exception(s){
    rows1 = Rows1; cols1 = Cols1; rows2 = Rows2; cols2 = Cols2;
  }

  WrongDimensions(const char* s, int Rows1, int Cols1, int Rows2, int Cols2) : Exception(s){
    rows1 = Rows1; cols1 = Cols1; rows2 = Rows2; cols2 = Cols2;
  }

  WrongDimensions(const WrongDimensions& e){
    str = new char[strlen(e.str) + 1];
    strcpy_s(str, strlen(e.str) + 1, e.str);
    rows1 = e.rows1; cols1 = e.cols1; rows2 = e.rows2; cols2 = e.cols2;
  }

  virtual void print(){
    cout << "WrongDimensions: " << str << "; " << what();
  }
};

class WrongSize : public WrongDimensions{
 public:
  //конструкторы
  WrongSize(char* s, int Rows, int Cols) : WrongDimensions(s, Rows, Cols, 1, 1){}
  WrongSize(const char* s, int Rows, int Cols) : WrongDimensions(s, Rows, Cols, 1, 1){}
  WrongSize(const WrongSize& e) : WrongDimensions(e){}

  virtual void print(){
    cout << "WrongSize: " << str << "; " << what();
  }

};

// Добавим исключение, выпадающее в методах, которые написаны для матриц,
// сотстоящих из чисел
class NotANumber : public Exception{
 protected:
//  Название типа значений, которые лежат в многомерном массиве
  const char* TypeName;
 public:
  //конструктор
  NotANumber(char* s, const char* type) : Exception(s){
    TypeName = type;
  }
  NotANumber(const char* s, const char* type) : Exception(s){
    TypeName = type;
  }

  NotANumber(const NotANumber& e){
    str = new char[strlen(e.str) + 1];
    strcpy_s(str, strlen(e.str) + 1, e.str);
    TypeName = e.TypeName;
  }

  virtual void print(){
    cout << "NotANumber: " << str << "; " << what();
  }
};

