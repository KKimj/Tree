#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

int* array_key;
Avltree avltree;

int main()
{
    char filename[110] = "test.in";
    int data_n, i, key, value;
    printf("file name을 입력해주세요. 100자 이내.\n");
    scanf(" %s", filename);
    printf("데이터의 개수를 입력하세요. 0입력시 100만개.\n");
    scanf("%d", &data_n);
    data_n = data_n == 0 ? 1000000 : data_n;

    printf("stdin이 변경됩니다..\n");
    freopen(filename, "r", stdin);

    array_key = (int*)malloc(data_n * sizeof(int));

    for (i = 0; i < data_n; i++)
    {
        scanf("%d %d", &key, &value);
        //scanf("%d", &key);

        array_key[i] = avltree.insert(key);
    }
    printf("삽입을 완료했습니다..\n");


    FILE* search_out = fopen("search.csv", "w");
    for (i = 0; i < data_n; i++)
    {
        fprintf(search_out, "%d\n", avltree.search(array_key[i]));
    }
    fclose(search_out);
    printf("검색을 완료했습니다..\n");


    for (i = 0; i < (data_n + 1) / 2; i++)
    {
        avltree.deleteNode(array_key[i]);
    }
    printf("삭제를 완료했습니다..\n현재 데이터 개수 %d\n", avltree.count);
    // FILE* delete_out = fopen("delete.out", "w");
    char delete_file[] = "delete.csv";
    avltree.print(delete_file);
    // tree 탐색..
    printf("삭제 결과 저장 완료했습니다..\n");

    printf("모든작업을 완료했습니다..\n");

    return 0;
}