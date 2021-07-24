/**********************************************************************************
 ____  _                 _      ____  ____  
/ ___|(_)_ __ ___  _ __ | | ___|  _ \| __ ) 
\___ \| | '_ ` _ \| '_ \| |/ _ \ | | |  _ \ 
 ___) | | | | | | | |_) | |  __/ |_| | |_) |
|____/|_|_| |_| |_| .__/|_|\___|____/|____/ 
                  |_|  
Copyright (c) 2021 P K Navin Shrinivas
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**********************************************************************************/

#include<stdio.h>
#include<string.h>
#if _WIN32
#include"curl\curl.h"
#else
#include<curl/curl.h>
#endif
#include<ctype.h>

void dbread(char* host , char* username, char* password , char* file)
{
    CURL *curl;
    FILE* f=fopen("new.txt","w+");
    curl = curl_easy_init(); 
    CURLcode res;
    char link[10000];
    strcat(link,host);
    strcat(link,"read/");
    strcat(link,username);
    strcat(link,"/");
    strcat(link,password);
    // printf("%s",link);
    curl_easy_setopt(curl,CURLOPT_URL,link);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
    res = curl_easy_perform(curl);
    fclose(f);
    if(strcmp(file,"STDOUT")==0)
    {
        char a[100000];
        FILE* f1=fopen("new.txt","r");
        char data[1000];
        fscanf(f1,"%[^EOF]%*c",data);
        char* split=data;
        char* token1=strtok_r(split,"\n",&split);
        while(token1!=NULL)
        {
            if(strcmp(token1,"<pre>")!=0 && strcmp(token1,"</pre>")!=0)
            {
                printf("%s\n",token1);
            }
            token1=strtok_r(split,"\n",&split);
        }
        fclose(f1);
    }
    else{
        char a[100000];
        FILE* f1=fopen("new.txt","r");
        FILE* f2=fopen(file,"w+");
        char data[1000];
        fscanf(f1,"%[^EOF]%*c",data);
        char* split=data;
        char* token1=strtok_r(split,"\n",&split);
        while(token1!=NULL)
        {
            if(strcmp(token1,"<pre>")!=0 && strcmp(token1,"</pre>")!=0)
            {
                fprintf(f2,"%s",token1);
                fprintf(f2,"%s","\n");
            }
            token1=strtok_r(split,"\n",&split);
        }
        fclose(f2);fclose(f1);
    }
    curl_easy_cleanup(curl);remove("new.txt");
}

void dbwrite(char* host , char* username, char* password , char* data)
{
    CURL *curl;
    CURLcode res;
    FILE* f=fopen("new.txt","w+");
    curl = curl_easy_init(); 
    int i=0;
    while (data[i])
    {
        if (isspace(data[i])) 
            data[i]='_';
        i++;
    }

    char link[10000];
    strcat(link,host);
    strcat(link,"write/");
    strcat(link,username);
    strcat(link,"/");
    strcat(link,password);
    strcat(link,"/");
    strcat(link,data);
    curl_easy_setopt(curl,CURLOPT_URL,link);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    printf("Test data successfully written to database!\n");
    res=curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return;

}