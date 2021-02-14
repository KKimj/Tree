#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

int* array_key;
Avltree avltree;

int main()
{
    char filename[110] = "test.in";
    int data_n, i, key, value;
    printf("file name�� �Է����ּ���. 100�� �̳�.\n");
    scanf(" %s", filename);
    printf("�������� ������ �Է��ϼ���. 0�Է½� 100����.\n");
    scanf("%d", &data_n);
    data_n = data_n == 0 ? 1000000 : data_n;

    printf("stdin�� ����˴ϴ�..\n");
    freopen(filename, "r", stdin);

    array_key = (int*)malloc(data_n * sizeof(int));

    for (i = 0; i < data_n; i++)
    {
        scanf("%d %d", &key, &value);
        //scanf("%d", &key);

        array_key[i] = avltree.Insert(key);
    }
    printf("������ �Ϸ��߽��ϴ�..\n");


    FILE* search_out = fopen("search.csv", "w");
    for (i = 0; i < data_n; i++)
    {
        fprintf(search_out, "%d\n", avltree.Search(array_key[i]));
    }
    fclose(search_out);
    printf("�˻��� �Ϸ��߽��ϴ�..\n");


    for (i = 0; i < (data_n + 1) / 2; i++)
    {
        avltree.Delete(array_key[i]);
    }
    printf("������ �Ϸ��߽��ϴ�..\n���� ������ ���� %d\n", avltree.count);
    // FILE* delete_out = fopen("delete.out", "w");
    char delete_file[] = "delete.csv";
    avltree.Print(delete_file);
    // tree Ž��..
    printf("���� ��� ���� �Ϸ��߽��ϴ�..\n");

    printf("����۾��� �Ϸ��߽��ϴ�..\n");

    return 0;
}