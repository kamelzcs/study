/*
 * string.cpp
 * Copyright (C) 2015 zhao <zhao@kamel-Desktop>
 *
 * Distributed under terms of the MIT license.
 */

#include<vector>
#include<algorithm>
#include<iostream>
#include<memory.h>

class String{
    public:
        String(): data(new char[1]){
            data[0] = '\0';
        }
        String(char *str): data(new char[strlen(str) + 1]){
            strcpy(data, str);
        }
        String(const String& rhs): data(new char[rhs.size() + 1]){
            strcpy(data, rhs.data);
        }
        String& operator=(String s){
            swap(s);
            return *this;
        }
        ~String(){
            delete[] data;
        }
        char* c_str() const{
            return data;
        }
        int size() const{
            return strlen(data);
        }
        void swap(String &rhs){
            std::swap(data, rhs.data);
        }
    private:
        char *data;
};

void foo(String x)
{
}

void bar(const String& x)
{
}

String baz()
{
  String ret("world");
  return ret;
}

int main()
{
  String s0;
  String s1("hello");
  String s2(s0);
  String s3 = s1;
  s2 = s1;

  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  String s4 = baz();

  std::vector<String> svec;
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(baz());
  svec.push_back("good job");
  for(String str: svec){
      std::cout<<str.c_str()<<std::endl;
  }
}


