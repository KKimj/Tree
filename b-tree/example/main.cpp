#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

#define RELEASE

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
            order = 200;
            btree = new Btree(order);

#else
            printf("file name�� �Է����ּ���. 100�� �̳�.\n");
            //scanf(" %s", filename);
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
            for (i = 0; i < (data_n + 1) / 2; i++) // (data_n + 1) / 2
            {
                if (i % 5 == 0)
                {
                    printf("%d : %d\n", i, btree->count);
                }
                if (fscanf(input, "%d %d", &key, &value) < 1)
                {
                    break;
                }

                btree->Delete(key);
            }
            fclose(input);
            printf("������ �Ϸ��߽��ϴ�..\n���� ������ ���� %d\n", btree->count);
               
            char delete_file[] = "delete_result.csv";
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
                    fprintf(delete_out, "%d\tN/A\n", array_key[i]);
                }
            }
            fclose(delete_out);
            // tree Ž��..
            printf("���� ��� ���� �Ϸ��߽��ϴ�..\n");
            

            FILE* delete_in = fopen(delete_file, "r");
            rewind(delete_in);

            char compare_file[] = "delete_compare.csv";
            FILE* compare_in = fopen(compare_file, "r");

            char str_compare[1000] = { '\0' };
            char str_delete[1000] = { '\0' };
            int line_count = 0;
            int diff_count = 0;
            while (fscanf(compare_in, " %[^\n]s", str_compare)>0 && fscanf(delete_in, " %[^\n]s", str_delete)>0)
            {
                //printf("%s\n", str_delete);
                if (strcmp(str_compare, str_delete) != 0)
                {
                    printf("%s\n", compare_file);
                    printf(">>> %s\n", str_compare);
                    printf("%s\n", delete_file);
                    printf("<<< %s\n", str_delete);
                    diff_count++;
                }
                line_count++;
            }
            fclose(delete_in);
            fclose(compare_in);
            if (diff_count == 0)
            {
                printf("%s �� %s�� �ٸ� �κ��� �����ϴ�.\n", delete_file, compare_file);
            }
            else
            {
                printf("%s �� %s�� %d���� ���� ���� �ٸ��ϴ�.\n", delete_file, compare_file, diff_count);
            }
            printf("%d ���� �񱳸� �Ϸ��߽��ϴ�.\n", line_count);
        }
        else if (mode == 4)
        {
            char print_file[] = "print.csv";
            btree->Print(print_file);
        }
    }
    return 0;
}