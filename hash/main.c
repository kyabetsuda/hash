//
//  main.c
//  hash
//
//  Created by 津田準 on 2017/12/10.
//  Copyright © 2017 津田準. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "MT.h"

#define BUCKET_SIZE 100
#define KEY_SIZE 10

typedef char KEY;
typedef int DATA;

struct ALPHABET {
    char alphabet;
    int code;
} alphabets[26];

struct CELL {
    KEY key[KEY_SIZE];
    DATA data;
    struct CELL *next;
};
//ポインタの配列を宣言
struct CELL *table[BUCKET_SIZE];

void initialize(){
    char letters[26] = "abcdefghijklmnopqrstuvwxyz";
    init_genrand((unsigned)time(NULL));
    for(int i = 0; i < 26; i++){
        alphabets[i].alphabet = letters[i];
        alphabets[i].code = genrand_int32() % 100;
    }
    
    for(int i = 0; i < BUCKET_SIZE; i++){
        table[i] = NULL;
    }
}

int hash(KEY key[KEY_SIZE]){
    int sum = 0;
    for(int i = 0; i < KEY_SIZE; i++){
        for(int j = 0; j < 26; j++){
            if( key[i] == alphabets[j].alphabet ){
                sum += alphabets[j].code;
            }
        }
    }
    return sum % 100;
}

int keyequals(KEY key1[KEY_SIZE], KEY key2[KEY_SIZE]){
    if( hash(key1) == hash(key2) )
        return 1;
    
    return 0;
}

DATA* find(KEY key[KEY_SIZE]){
    struct CELL *p;
    
    for(p = table[hash(key)]; p != NULL; p = p -> next){
        if(keyequals(key, p -> key))
            return &p -> data;
    }
    
    return NULL;
}

int insert(KEY key[KEY_SIZE], DATA data){
    struct CELL *p;
    int h;
    
    if(find(key) != NULL)
        return 0;
    if( (p = malloc(sizeof(struct CELL))) == NULL)
        exit(2);
    h = hash(key);
    strcpy(p -> key, key);
    p -> data = data;
    p -> next = table[h];
    table[h] = p;
    return 1;
}

void listData(){
    struct CELL *p;
    for(int i = 0; i < BUCKET_SIZE; i++){
        if(table[i] == NULL)
            continue;
        printf("%s : %d\n", table[i] -> key, table[i] -> data);
        p = table[i] -> next;
        while( p != NULL ){
            printf("%s : %d\n", p -> key, p -> data);
            p  = p -> next;
        }
    }
}



int main(int argc, const char * argv[]) {
    initialize();
    int flg = 1;
    while(flg){
        int a = 0;
        char key[KEY_SIZE] = "";
        int value = 0;
        printf("リストに値を追加 : 1\n");
        printf("リストの一覧を表示 : 2\n");
        printf("終了 : 3\n");
        scanf("%d", &a);
        switch(a){
            case 1:
                printf("キーとなる文字を入力してください\n");
                scanf("%s", key);
                printf("値を入力してください\n");
                scanf("%d", &value);
                insert(key, value);
                printf("値が挿入されました\n");
                break;
            case 2:
                printf("リストの一覧は以下の通りです\n");
                listData();
                break;
            case 3:
                flg = 0;
                break;
            default:
                flg = 1;
                break;
        }
    }
    
    return 0;
}
