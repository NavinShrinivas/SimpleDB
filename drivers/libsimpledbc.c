#include<stdio.h>
#include<string.h>
#include<curl/curl.h>
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
    char a[100000];
    FILE* f1=fopen("new.txt","r");
    FILE* f2=fopen(file,"w+");
    char data[1000];
    fscanf(f1,"%[^NULL]%*c",data);
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
    fclose(f2);fclose(f1);remove("new.txt");
    curl_easy_cleanup(curl);
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
    // printf("%s",link);
    curl_easy_setopt(curl,CURLOPT_URL,link);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
    printf("Test data successfully written to database!\n");
    res=curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return;

}