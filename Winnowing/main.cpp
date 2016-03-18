#include <stdio.h>
#include <stdlib.h>

void winnow(int w /*size of window*/ )
{
    FILE *fp; // hash.txt file pointer
    if((fp = fopen("hash.txt","r")) == NULL)
    {
        perror("fail to read hash.txt");
        exit (1);
    }
    FILE *fpfinger=fopen("fingerprints.txt","w+");
    int *h=new int[w];  //存放哈希值的窗口，窗口是循环使用的
    int min=0;     //记录当前最小值在窗口中的位置
    int pos=min;     //记录最小值在原序列中出现的位置
    // init h array
    for(int i=0; i<w; i++)
    {
        int fs = fscanf(fp,"%d",&h[i]);
        if(fs==EOF)        //当窗口值大于指纹总数时执行
        {
            fprintf(fpfinger,"[%d, %d]\n",h[min],pos+1);
            delete h;
            return;
        }
        else
        {
            if(h[min] > h[i])
            {
                min = i;
                pos = min;
            }
        }
    }
    fprintf(fpfinger,"[%d, %d]\n",h[min],pos+1);

    int r=w-1;     //循环遍历数组h，按顺序将原序列的哈希值添加到数组中
    int hv = 0; // temp hash value that read from hash.txt
    while(fscanf(fp,"%d",&hv)!=EOF)
    {
        r=(r+1)%w; // 滑动到下一个窗口
        h[r]=hv;   //添加下一个哈希值
        if(min==r) //如果条件成立，说明前一个窗口的最小值将被移除窗口
        {
            pos+=w;
            for(int i=(r-1+w)%w; i!=r; i=(i-1+w)%w)   //向后循环查找最小值，选取窗口中最小且最右的哈希值
            {
                if(h[i]<h[min])
                {
                    pos-=(min+w-i)%w;
                    min=i;
                }
            }
            fprintf(fpfinger,"[%d, %d]\n",h[min],pos+1);
        }
        else //min!=r就说明当前最小的哈希值依然包含在窗口中
        {
            if(h[r]<h[min]) //那么只需要比较新添加进的哈希值即可，条件中不能含有等于号，否则不是健壮的winnowing方法。
            {
                pos+=(r+w-min)%w;
                min=r;
                fprintf(fpfinger,"[%d, %d]\n",h[min],pos+1);
            }
        }
    }
    delete h;
    fclose(fp);
    fclose(fpfinger);
}

int main()
{
    winnow(30);
    return 1;
}
