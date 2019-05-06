#include "my_string.h"

int main(){
    My_String ms1("hello world");
    My_String ms2("hello world22");
    My_String ms3(ms1);
    ms3.show();
    ms3=ms2;
    ms3.show();

    return 0;
}