#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int* array_key;
Btree * btree;

int main()
{
    char filename[110] = "input.csv";
    int data_n, i, key, value, order;
    while (1)
    {
        int mode;
        printf("1.insertion 2.deletion. 3.quit\n");
        scanf("%d", &mode);

        if (mode == 3)
        {
            /*free(btree->root);
            btree->root = NULL;
            delete(btree);
            btree = NULL;*/
            break;
        }
        else if (mode == 1)
        {
#ifdef RELEASE
            printf("file name�� �Է����ּ���. 100�� �̳�.\n");
            scanf(" %s", filename);
            data_n = 1000000;
            order = 3;
            btree = new Btree(order);

#else
            printf("file name�� �Է����ּ���. 100�� �̳�.\n");
            scanf(" %s", filename);
            printf("�������� ������ �Է��ϼ���. 0�Է½� 100����.\n");
            scanf("%d", &data_n);
            data_n = data_n == 0 ? 1000000 : data_n;
            printf("B-tree�� order�� �Է��ϼ���.\n");
            scanf("%d", &order);
            btree = new Btree(order);
#endif

            

            FILE* input = fopen(filename, "r");

            array_key = (int*)malloc(data_n * sizeof(int));

            for (i = 0; i < data_n; i++)
            {
                fscanf(input, "%d %d", &key, &value);
                array_key[i] = btree->Insert(key, value);
            }
            fclose(input);
            printf("������ �Ϸ��߽��ϴ�..\n");


            FILE* search_out = fopen("insert_result.csv", "w");
            for (i = 0; i < data_n; i++)
            {
                fprintf(search_out,"%d\t%d\n", array_key[i], btree->Search(array_key[i]));
            }
            fclose(search_out);
            printf("�˻��� �Ϸ��߽��ϴ�..\n");
        }
        else if (mode == 2)
        {
            FILE* input = fopen("delete.csv", "r");
            char print_file[] = "print_delete.csv";
            for (i = 0; i < (data_n + 1) / 2; i++) // (data_n + 1) / 2
            {
                fscanf(input, "%d %d", &key, &value);
                if (btree->count == 1)
                {
                    printf("check\n");
                }
                btree->Delete(key);
                btree->Print(print_file);
                if (i % 5 == 0)
                {
                    printf("%d : %d check\n", i, btree->count);
                }
            }
            fclose(input);
            printf("������ �Ϸ��߽��ϴ�..\n���� ������ ���� %d\n", btree->count);
            char delete_file[] = "delete_result.csv";
            //btree->Print(delete_file);
            FILE* delete_out = fopen(delete_file, "w");
            for (i = 0; i < data_n; i++)
            {
                int tmp = btree->Search(array_key[i]);
                if (tmp != NULL)
                {
                    fprintf(delete_out, "%d\t%d\n", array_key[i], tmp);
                }
                else
                {
                    fprintf(delete_out, "%d\tNF\n", array_key[i]);
                }
            }
            fclose(delete_out);
            // tree Ž��..
            printf("���� ��� ���� �Ϸ��߽��ϴ�..\n");
        }
        else if (mode == 4)
        {
            char print_file[] = "print.csv";
            btree->Print(print_file);
        }
    }
    return 0;
}