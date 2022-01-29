#include<stdio.h>
#include<string>
#include <stdlib.h>
#include <string.h>

using namespace std;

FILE *pdata1, *prule , *ans;

/*string ip_translate(unsigned long int,char *);*/
unsigned long int ip_translate(char * ,unsigned long int,const char*);
int read_data(FILE *, unsigned int *, unsigned int *, int *, int *, int *);
int read_rule(FILE *, char *, char *, int *, int *, int *, int *, int *, int *, int *);
bool ip_camp(unsigned int ,char*);

unsigned long int ip_translate(char *bin_ip ,const char * digit_str)
{
    short int digit;
    unsigned long int dec;
    unsigned long int bin1,bin2,bin3,bin4;
    sscanf(digit_str,"/%hd",&digit);

    if(digit==32)
    {
    sscanf(bin_ip,"%lu.%lu.%lu.%lu/32",&bin1,&bin2,&bin3,&bin4);
    dec = (bin1<<24)^(bin2<<16)^(bin3<<8)^(bin4);
    }

    return dec;
}

/*string ip_translate(unsigned long int dec,char bin_ip[]) //(32位)将十进制ip转化为点分十进制
{
    string temp;
    unsigned long int bin1, bin2, bin3, bin4;
    bin1 = dec >> 24;
    bin2 = (dec >> 16) & 255ul;
    bin3 = (dec >> 8) & 255ul;
    bin4 = dec & 255ul;
    temp.append(to_string(bin1)+".");
    temp.append(to_string(bin2)+".");
    temp.append(to_string(bin3)+".");
    temp.append(to_string(bin4)+"/32");
    
    return temp;
}*/

/*读取资源集数据，存入相关变量*/
int read_data(FILE *pdata,unsigned int *src_ip,unsigned int *tgt_ip, int *src_port, int *tgt_port, int *protocol)
{
    int is_end = fscanf(pdata, "%d\t %d\t %d\t %d\t %d\n", src_ip, tgt_ip, src_port, tgt_port, protocol);
    return is_end;
    
}

/*读取规则集*/
int read_rule(FILE *prule, char *rule_src_ip, char *rule_tgt_ip, int *rule_src_port_min,int *rule_src_port_max, int *rule_tgt_port_min,int *rule_tgt_port_max, int *rule_protocol_min,int *rule_protocol_max)
{
    int is_end = fscanf(prule, "@%s\t %s\t %d : %d\t %d : %d\t %x/%x\n", rule_src_ip, rule_tgt_ip, rule_src_port_min , rule_src_port_max , rule_tgt_port_min , rule_tgt_port_max, rule_protocol_min ,rule_protocol_max);
    //读入的rule_src_ip不带'@'
    return is_end;
}

bool ip_camp(unsigned int data_ip,char* rule_ip)
{
    int i,j;
    char mod[4];
    for(i=0;rule_ip[i]!='/';++i)
    {}
    for(j=0;rule_ip[i]!='\0';++i)
        mod[j++] = rule_ip[i];
    mod[j]='\0';

    return data_ip==ip_translate(rule_ip,mod);
}



int main(int argc, char const *argv[])
{

    prule = fopen(argv[1], "r");
    if (prule == NULL)
    {
        printf("failed to open the rule!");
        return 1;
    }
    pdata1 = fopen(argv[2], "r");
    if (pdata1 == NULL)
    {
        printf("failed to open the data!");
        return 1;
    }
    /*格式化生成ans文件名*/
    char ans_file_name[10];
    int ans_num=1;
    sscanf(argv[2],"packet%d",&ans_num);
    sprintf(ans_file_name,"ans%d.txt",ans_num);
    ans = fopen(ans_file_name,"w+");

    if (ans == NULL)
    {
        printf("failed to open ans!");
        return 1;
    }
    /*打开失败时return1*/

    unsigned int src_ip; char rule_src_ip[20]; //原ip
    unsigned int tgt_ip; char rule_tgt_ip[20]; //目标ip
    int src_port, rule_src_port_min ,rule_src_port_max;  //原端口
    int tgt_port, rule_tgt_port_min ,rule_tgt_port_max;  //目标端口
    int protocol, rule_protocol_min ,rule_protocol_max;  //协议号
    int line;                     //匹配位置
    
    printf("Writing...\n");
    //主循环
    for (;EOF != read_data(pdata1, &src_ip, &tgt_ip, &src_port, &tgt_port, &protocol);)
    {
        for (line = 1;;line++)
        {
            if(EOF == read_rule(prule, rule_src_ip, rule_tgt_ip, &rule_src_port_min , &rule_src_port_max, &rule_tgt_port_min , &rule_tgt_port_max, &rule_protocol_min , &rule_protocol_max))
                {
                fprintf(ans,"%d\n",-1);//没找到，输出-1
                break;
                }

            /*判断端口(原、目标)是否符合*/
            if(src_port > rule_src_port_max || src_port < rule_src_port_min)
                continue;//不输出，进入下一循环
            if(tgt_port > rule_tgt_port_max || tgt_port < rule_tgt_port_min)
                continue;//不输出，进入下一循环
            
            /*判断协议号是否符合*/
            if(protocol> rule_protocol_max || protocol < rule_protocol_min)
                continue;//不输出，进入下一循环

            
            /*比对ip地址*/
            if (ip_camp(src_ip ,rule_src_ip) && ip_camp(tgt_ip , rule_tgt_ip))//若找到
                {
                fprintf(ans,"%d\n",line);//输出当前位置(到文件里)
                break;
                }
                
            
        }
        
        /*文件指针回到开头*/
        rewind(prule);
        
        line = 1;
    }

    printf("Finished.");
    return 0;
}
