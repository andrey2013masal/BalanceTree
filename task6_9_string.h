#include <iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
using namespace std;

class Str
{
private:
    char *str;
public:
    Str(){ str = NULL; }

    Str(const char *s){
   	 str = new char[strlen(s)+1];
   	 strcpy(str, s);
	}

    ~Str() { delete[] str; }

    Str &operator=(const Str &s){
	    if (&s == this)
	        return *this;
	    delete[] str;
		str=NULL;
	    str = new char[strlen(s.str)+1];
	    strcpy(str, s.str);
	    return *this;
	}
	
    Str &operator=(Str &&s){
	    if (&s == this)
	        return *this;
        delete[] str; 
	    str = s.str;
	    s.str = nullptr;

	    return *this;
	}
        friend bool operator==(const Str &s1, const Str &s2) { return  strlen(s1.str)==strlen(s2.str);}
//	friend bool operator<(const Str &s1, const Str &s2) { return (strcmp(s1.str, s2.str) < 0);}
	friend bool operator<(const Str &s1, const Str &s2) { return strlen(s1.str)<strlen(s2.str);}
	friend bool operator>(const Str &s1, const Str &s2) {  return strlen(s1.str)>strlen(s2.str); }
//	friend bool operator==(const Str &s1, const Str &s2) { return strcmp(s1.str, s2.str) == 0; }
	friend bool operator!=(const Str &s1, const Str &s2) { return !(s1 == s2); }
	friend ostream &operator<<(ostream &out, const Str &s1) { out<< s1.str; return out;}
};



	