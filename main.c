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
    if (St && St->top && value) {
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
    if (St && St->top&& St->top->val) {
        char tmp = St->top->val;
        return tmp;
    }
    return '\0';
}


bool check_v1_v2_v3(struct steck* St) {
    if (St && St->size >= 3) {

        char v1 = 0, v2 = 0, v3 = 0;

        pop(St, &v1); // тройку достал
        pop(St, &v2);
        pop(St, &v3);
        if ((v1 >= '0' && v1 <= '9') || (v1 >= 'a' && v1 <= 'z') || (v1 == 'R')) {
            if ((v3 >= '0' && v3 <= '9') || (v3 >= 'a' && v3 <= 'z') || (v3 == 'R')) {
                if (v2 == '*' || v2 == '+' || v2 == '-' || v2 == '/' || v2 == '=') {
                    push(St, 'R');
                    printiii(St);
                    return true;
                }
            }
        }
        // Если не прошло то обратно
        push(St, v3);
        push(St, v2);
        push(St, v1);
    }
    return false;
}
//
////add_str_to_steck() //можно реализовать но стоит ли
//




bool check(char* string) { //основная
    if (string && *string) {
        char* ptrIx = string;
        struct steck* Steckk = (struct steck*)calloc(1, sizeof(struct steck));
        if (Steckk) {
            bool flag1 = true;
            for (; *ptrIx && flag1; ptrIx++) {
                if (*ptrIx != ' ') {
                    if (*ptrIx == ')') {

                        char tmp;
                        while (Steckk->size > 0 && seeTop(Steckk) != '(') {
                            if (!check_v1_v2_v3(Steckk)) {
                                if (seeTop(Steckk) != 'R')
                                {
                                    flag1 = false;
                                }
                                pop(Steckk, &tmp);
                            }
                        }


                        if (Steckk->size > 0 && seeTop(Steckk) == '(' && flag1) {
                            pop(Steckk, &tmp);
                            push(Steckk, 'R');
                        }
                        else {
                            flag1 = false;
                        }
                    }
                    else
                    {
                        push(Steckk, *ptrIx);
                    }
                }
                printf("for2   ");
                printiii(Steckk);
            }

            printf("_____________________________________________________________________________\n");
            printf("in Steckk: ");
            printiii(Steckk);
            bool flag = true;
            while ((Steckk->size > 1)&& flag1) {
                flag1 = check_v1_v2_v3(Steckk);
                printiii(Steckk);
            }
            if ((Steckk->size == 1) && (seeTop(Steckk) == 'R'))
            {
                clear(Steckk);
                return true;
            }
        }
        clear(Steckk);
    }
    return false;
}

int main()
{
    //char str[] = "a+b*3-(3/9)";
    //char str[] = "(a+b*3-)(3/9)";
    //char str[] = "(((a+b)*(c-d))/)(e+f)";// с вложенными скобками
    //char str[] = "( ( ( a + b ) * ( c - d ) ) / ) ( e + f )";// с вложенными скобками

    //char str[] = "a+b*3-3/9";
    //char str[] = "";//ошибка
    //char str[] = "a";//ош/ибка
    //char str[] = "+a*b";//ошибка
    //char str[] = "+-*/";//ошибка
    //char str[] = "a+b*c/d-e+f/g*h-i/j+k*l/m-n+o/p*q-r/s+t/u*v-w/x+y/z";
    //char str[] = "2+b2*3-d/e";//ошибка
    //char str[] = "(a+b)*3-3/9)";//ошибка в скобках
    //bool check2 = check(NULL);//ошибка пустое
    char str[] = "(a)";//ошибка скобочки
    //char str[] = "a + b * 3 - 3 / 9"; //пробелы
    //char str[] = "a+b$c";//ошибка плохой символ



    bool checkk = check(str);
    if (checkk) {
        printf("String is good\n");
    }
    else {
        printf("String is bad\n");
    }

    return 0;
}
