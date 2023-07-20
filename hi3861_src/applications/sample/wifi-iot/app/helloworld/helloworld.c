#include <stdio.h>
#include "ohos_init.h"

void HelloWorld(void)
{
    //打印一下helloworld!的字符串
    printf("helloworld!\r\n");

}
// APP_FEATURE_INIT()是openharmony封装好的函数入口，实现main函数的功能
APP_FEATURE_INIT(HelloWorld);