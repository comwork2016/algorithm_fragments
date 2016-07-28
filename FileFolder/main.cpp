//LINUX/UNIX c获取某个目录下的所有文件的文件名

#include <stdio.h>
#include <iostream>
#include <dirent.h>

int main()
{
    struct dirent *ptr;
    DIR *dir;
    dir=opendir("./in");
    if(!dir)
    {
        printf("read dir error\n");
        return 1;
    }
    while((ptr=readdir(dir))!=NULL)
    {
        //跳过'.'和'..'两个目录
        if(ptr->d_name[0] == '.')
            continue;
        printf("%s\n",ptr->d_name);
    }
    closedir(dir);
    return 0;
}
