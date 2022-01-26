#include<vector>
#include<string>
#include<stdlib.h>
using namespace std;
FILE *pdata1,*prule;
string ip_dec_to_bin(int);
int read_data(FILE*,int*,int*,int*,int*,int*);
int read_rule(FILE*,int*,int*,int*,int*,int*);
bool ip_camp();
bool ip_came();
int main(int argc, char const*argv[])
{
    prule=fopen(argv[1],"&r");
    if(pdata1==NULL);
    {
        printf("failed to open!");
        return 1;
    }
    pdata1=fopen(argv[2],"&r");
    if(pdata1==NULL)
    {
        printf("failed to open!");
        return 1;
    }
    /*打开失败时return1*/
    int src_ip;string rule_src_ip;//原ip
    int tgt_ip,rule_tgt_ip;//目标ip
    int src_port,rule_src_port;//原端口
    int tgt_port,rule_tgt_port;//目标端口
    int protocol,rule_protocol;//协议号
    string bin_ip;   //储存资源集ip(十进制)的点分十进制形式
    int line; //匹配位置 
    //主循环
    for (;read_data(pdata1,&src_ip,&tgt_ip,&src_port,&tgt_port,&protocol);)
    {
        for(line=0;read_rule(prule,&rule_src_ip,&rule_tgt_ip,&rule_src_port,&rule_tgt_port,&rule_protocol);line++)
        {
            /*code:判断端口(原、目标)是否符合*/
            /*code:判断协议号是否符合*/
            /*若符合*/
            {
                /*code；比对ip地址*/
                /*若找到*/
                if(ip_camp())
                {

                }
                /*输出当前位置(到文件里)*/
            }
            /*循环结束(未找到)*/
            /*输出-1(到文件里)*/
        }
        /*code；文件指针回到开头*/
        line=1;
    }
    return 0;
}
string ip_dec_to_bin(int dec)//32位
{
    string bin;
    /*用位操作把数据集的ip转化为规则集116.14.234.252/32的形式*/;
    return bin;
}
int read_data(FILE*pdata,int*src_ip,int*tgt_ip,int*src_port,int*tgt_port,int*protocol)
{
    int is_end=fscanf(pdata,"%d\t%d\t%d\t%d\t%d\n",src_ip,tgt_ip,src_port,tgt_port,protocol);
    return is_end;
    /*读取资源集数据，存入相关变量*/
}
int read_rule(FILE*prule,string*rule_src_ip,int*rule_tgt_ip,int*rule_src_port,int*rule_tgt_port,int*rule_protocol)
{
    int is_end=fscanf(prule,"@%d\t%d\t%d\t%d\t%d\n",rule_src_ip,rule_tgt_ip,rule_src_port,rule_tgt_port,rule_protocol);
    return is_end;
}
bool ip_camp()
{

}
bool ip_camp()
{

}
bool port_camp()
{

}