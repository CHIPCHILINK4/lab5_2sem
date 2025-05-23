#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Elem {
    char val;
    struct Elem* nx;
};

struct steck {
    struct Elem* top;
    size_t size;
};

void printiii(struct steck* St) {//прииииииииииииинннннннттттттттттиииииииииииии
    if (St) {
        struct Elem* ptr = St->top;
        if (ptr) {
            while (ptr) {
                printf("%c", ptr->val);
                ptr = ptr->nx;
            }
            printf("\n");
        }
    }
}

bool push(struct steck* St, char el) {// добавить
    if (St) {
        struct Elem* ptr = (struct Elem*)calloc(1, sizeof(struct Elem));
        if (ptr) {
            ptr->val = el;
            ptr->nx = St->top;
            St->top = ptr;
            St->size++;
            return true;
        }
        free(ptr);
    }
    return false;
}

bool pop(struct steck* St, char* value) {//достать
    if (St->top && value) {
        *value = St->top->val;
        struct Elem* tmp = St->top;
        St->top = St->top->nx;
        St->size--;
        free(tmp);
        return true;
    }
    return false;
}

void clear(struct steck* St) {//очистить
    if (St) {
        if (St->top) {
            while (St->top) {
                struct Elem* tmp = St->top;
                St->top = St->top->nx;
                free(tmp);
            }
            St->size = 0;
        }
    }
}

bool isEmpty(struct steck* St) {//пустой ли
    if (St) {
        if (St->top != NULL) {
            return false;
        }
    }
    return true;
}

char seeTop(struct steck* St) {// посмотреть вершину
    if (St&& St->top&& St->top->val) {
        char tmp = St->top->val;
        return tmp;
    }
    return '\0';
}
//
////add_str_to_steck() //можно реализовать но стоит ли
////check_v1_v2_v3()//можно но стоит ли
//
//
bool check(char* string) { //основная
    if (string && *string) {
        char* ptrIx = string;
        struct steck* Steckk = (struct steck*)calloc(1, sizeof(struct steck));
        int count = 0;
        if (Steckk) {
            for (; *ptrIx; ptrIx++) {
                if (*ptrIx != ' ') {
                    if ((*ptrIx == '(') && (count >= 0)) {
                        count++;
                    }
                    else if (*ptrIx == ')') {
                        count--;
                    }
                    else {
                        push(Steckk, *ptrIx);
                    }
                }
            }
            printf("_____________________________________________________________________________\n");
            printf("in Steckk: ");
            printiii(Steckk);
            if (count == 0) {
                while( Steckk->size > 1) {
                    char v1 = 0, v2 = 0, v3 = 0;

                    pop(Steckk, &v1);//тройку достал
                    pop(Steckk, &v2);
                    pop(Steckk, &v3);

                    if ((v1 >= 48 && v1 <= 57) || (v1 >= 97 && v1 <= 122) || (v1 == 82)) {
                        if ((v3 >= 48 && v3 <= 57) || (v3 >= 97 && v3 <= 122)) {
                            if (v2 == 42 || v2 == 43 || v2 == 45 || v2 == 47 || v2 == 61) {
                                push(Steckk, 'R');
                            }
                        }
                    }

                    printiii(Steckk);


                }
                if ((Steckk->size == 1) && (seeTop(Steckk) == 'R'))
                {
                    clear(Steckk);
                    return true;
                }
            }

        }
        clear(Steckk);
    }
    return false;
}


int main()
{
    char str[] = ")a+b(*3-3/9";
    //char str[] = "a+b*3-3/9";
    //char str[] = "";//ошибка
    //char str[] = "a";//ошибка
    //char str[] = "+a*b"//ошибка
    //char str[] = "+-*/"//ошибка
    //char str[] = "a+b*c/d-e+f/g*h-i/j+k*l/m-n+o/p*q-r/s+t/u*v-w/x+y/z";
    //char str[] = "2+b2*3-d/e";//ошибка
    //char str[] = "(a+b)*3-3/9)";//ошибка в скобках
    //bool check2 = check(NULL);//ошибка пустое
    //char str[] = "()";//ошибка скобочки
    //char str[] = "a + b * 3 - 3 / 9"; //пробелы
    //char str[] = "a+b$c";//ошибка плохой символ
    //char str[] = "((a+b)*(c-d))/(e+f)";// с вложенными скобками


    bool checkk = check(str);
    if (checkk) {
        printf("String is good\n");
    }
    else {
        printf("String is bad\n");
    }

    return 0;
}
