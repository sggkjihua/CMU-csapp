#include "cachelab.h"
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<limits.h>
#include<getopt.h>
#include<string.h>


int help_mode, verbose_mode, s, E, b, S,number_hits, number_miss, number_eviction;

//S is the number of sets, E is the associativity, b is number of block bits
char filename[1000];//The file name
char buffer[1000];//The buffer of input

typedef struct 
{
	int valid_bit, tag, stamp;//cold miss
}cache_line;

cache_line **cache = NULL;


void update(unsigned int address){
    int set, tag ;
	set = (address >> b) & ((-1U) >> (32 - s));//use bit manipulation to get s_address, -1U equals to INT_MAX
	tag = address >> (s + b);
    //set = (address >> b) & ((2^s)-1); 

    // load 如果 hit了就直接返回，并且把那个stamp 设置成 0，意即最近的那个 time
    for(int i=0;i<E;i++){
        if(cache[set][i].tag == tag){
            cache[set][i].stamp = 0;
            number_hits ++;
            return ;
        }
    }
    // if there is no hits, check if needs to evicts
    // 如果是 modify 或者是 store, m 包括 store 还有 load
    number_miss ++ ;

    int toReplace = 0;
    int maxTimeStamp = 0;
    for(int i=0;i<E;i++){
        if(cache[set][i].valid_bit == 0){
            toReplace = i;
            cache[set][i].tag = tag;
            cache[set][i].stamp = 0;
            cache[set][i].valid_bit = 1;
            // find an empty slot, no need to evicts
            return;
        }
        if(cache[set][i].stamp>maxTimeStamp){
            maxTimeStamp = cache[set][i].stamp;
            toReplace = i;
        }
    }

    number_eviction ++;
    cache[set][toReplace].tag = tag;
    cache[set][toReplace].stamp = 0;
}

void update_time(){
	for(int i = 0; i < S; i++)
		for(int j = 0; j < E; j++)
			if(cache[i][j].valid_bit == 1)//if valid
				cache[i][j].stamp++;
}


int main(int argc,char* argv[])
{
    int opt, temp;//The getopt return value
    char type;//type of a single trace record
    unsigned int address;//address of memory
    number_hits = number_miss = number_eviction = 0;//initialization
    while(-1 != (opt = (getopt(argc, argv, "hvs:E:b:t:"))))
    {
        switch(opt)
        {
            case 'h':help_mode = 1;
                    break;
            case 'v':verbose_mode = 1;
                    break;
            case 's':s = atoi(optarg);
                    break;
            case 'E':E = atoi(optarg);
                    break;
            case 'b':b = atoi(optarg);
                    break;
            case 't':strcpy(filename, optarg);
                    break;
        }
    }
    if(help_mode == 1)
    {
        system("cat help_info");//"help_info" is a text file containing help information
        exit(0);
    }
    FILE* fp = fopen(filename,"r");
    if(fp == NULL)
    {
        fprintf(stderr,"The File is wrong!\n");
        exit(-1);
    }
    S = (1 << s); // S equals to 2^s, 总set数
    cache = (cache_line**)malloc(sizeof(cache_line*) * S);
    for(int i = 0; i < S; i++)
        cache[i] = (cache_line*)malloc(sizeof(cache_line) * E);//Important! malloc each row of cache，每个 set 里面的总行数
    for(int i = 0; i < S; i++)
        for(int j = 0; j < E; j++)
        {
            cache[i][j].valid_bit = 0;
            cache[i][j].tag = cache[i][j].stamp = -1;
        }//initialization
    while(fgets(buffer,1000,fp))//get a whole line
    {
        sscanf(buffer," %c %xu,%d", &type, &address, &temp);//hexdecimal
        switch(type)
        {
            case 'L':update(address);// load data
                    break;
            case 'M':update(address);// just let it fall through, do twice，load followed by store
            case 'S':update(address);// data store
                    break;
        }
        update_time();
    }
    for(int i = 0; i < S; i++)
        free(cache[i]);//free allocated space first
    free(cache);
    fclose(fp);
    printSummary(number_hits, number_miss, number_eviction);
    return 0;
}
