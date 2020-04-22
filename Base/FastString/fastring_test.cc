/*
 * @Author: haha_giraffe
 * @Date: 2020-04-17 10:22:56
 * @Description: file content
 */
#include <stdio.h>
#include "fastring.h"

int main(){
    fastring fs("sdweqeq");
    printf("%d, %s\n", fs.size(), fs.toupper());
    fs.strip("sdqwae", 'l');
    printf("%d\n", fs.size());

}

