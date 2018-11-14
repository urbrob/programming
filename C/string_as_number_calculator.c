#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int log_error(char *text ,int error) {printf("%s", text);return error;}

void remove_minus(char *chr){
    int len = strlen(chr), i;
    if(*chr != '\0')for(i = 0;i < len; i++) *(chr + i) = *(chr + i + 1);
}


void remove_zeros(char *chr){
    while(*chr == '0' && *(chr + 1) !='\0') remove_minus(chr);
}

int is_sign(const char a){if(a == '-' || a == '+' || a == '*') return 1; return 0;}
int is_number(const char a){if(a >='0' && a<= '9') return 1; return 0;}
int is_zero(const char *chr){if(*chr =='0' && *(chr + 1) == '\0') return 1; return 0;}

int validate_expression(const char *expr){
    if(expr == NULL) return 2;
    if (*expr == '\0') return 1;
    int i;
    if(is_sign(*expr) == 1 && *expr != '-') return 1;
    for(i = 0; *(expr + i) != '\0'; i++){
        char pom = *(expr + i);
        if(is_number(pom) == 0 && is_sign(pom) == 0) return 1;
        if(is_sign(pom) == 1 && *(expr + i + 1) == '\0') return 1;
        if(is_sign(pom) == 1 && is_sign(*(expr + i + 1)) == 1 && *(expr + i + 1) != '-') return 1;
    }
    return 0;
}

int fetch_number(const char *src, char *dest){
    int size = 0;
    if(*src == '-'){
        *dest = *src;
        size++;
    }
    for(;is_number(*(src + size)) == 1; size++ ) *(dest + size) = *(src + size);
    *(dest + size) = '\0';
    return size;
}

int find_longer(char *max, char *min, const char *number1, const char *number2){
    unsigned int i, swap = 0;
    strcpy(max, number1);strcpy(min, number2);
    if (*max == '-') remove_minus(max);
    if (*min == '-') remove_minus(min);
    if(strlen(max) > strlen(min)) {
        strcpy(max, number1);strcpy(min, number2);
    }else if(strlen(max) < strlen(min)){
        strcpy(max, number2);strcpy(min, number1); swap = 1;
    }else{
        for(i = 0; i <= strlen(max); i++){
            if(*(max + i) > *(min + i)){
                strcpy(max, number1);strcpy(min, number2);
                break;
            }
            if(*(max + i) < *(min + i)){
                strcpy(max, number2);strcpy(min, number1); swap = 1;
                break;
            }
            if(i >= strlen(max)){
                strcpy(max, number1);strcpy(min, number2);
            }
        }
    }
    return swap;
}

void add_char(char *chr, char znak){
    int len = strlen(chr) + 1;
    for(;len >= 0; len--) *(chr + len + 1) = *(chr + len);
    *chr = znak;
}

char subtract_chars(const char a, const char b, int *mem){
    int num = a - b - *mem;
    *mem = 0;
    if(num < 0){
        *mem = 1;
        return '9' + 1 + num;
    }else return (char)(num + '0');
}

void subtract_base(const char* number1, const char* number2, char *res){
    int len1 = strlen(number1), len2 = strlen(number2), mem = 0, len_pom_1 = len1, len_pom_2 = len2;
    *(res + len_pom_1--) = '\0';
    for(len_pom_2 = len_pom_2 - 1; len_pom_2 >= 0; len_pom_2--, len_pom_1--){
        *(res + len_pom_1) = subtract_chars(*(number1 + len_pom_1), *(number2 + len_pom_2), &mem);
    }
    for(;len_pom_1 >= 0  && *(number1 + len_pom_1) != '-'; len_pom_1--) {
        *(res + len_pom_1) = subtract_chars(*(number1 + len_pom_1), '0', &mem);
    }
    remove_zeros(res);
}

char add_chars(const char a, const char b, int *mem){
    int num = a - '0' + b - '0' + *mem;
    *mem = 0;
    if(num > 9){
        *mem = 1;
        return '0' + num - 10;
    }else return (char)(num + '0');
    
}

void add_base(const char* number1, const char* number2, char *res){
    int len1 = strlen(number1), len2 = strlen(number2), mem = 0, len_pom_1 = len1, len_pom_2 = len2;
    *(res + len_pom_1--) = '\0';
    for(len_pom_2 = len_pom_2 - 1; len_pom_2 >= 0; len_pom_2--, len_pom_1--){
        *(res + len_pom_1) = add_chars(*(number1 + len_pom_1), *(number2 + len_pom_2), &mem);
    }
    for(;len_pom_1 >= 0 && *(number1 + len_pom_1) != '-'; len_pom_1--){
        *(res + len_pom_1) = add_chars(*(number1 + len_pom_1), '0', &mem);
    }
    if(mem == 1){
        add_char(res, '1');
    }
}

int subtract(const char* number1, const char* number2, char** result){
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    int size = strlen(number1) > strlen(number2) ? strlen(number1) + 5 : strlen(number2) +5;
    *result = (char*)malloc(50000);
    if (*result == NULL) return 3;
    char *max = (char*)malloc(size), *min = (char*)malloc(size);
    if(max == NULL){
        free(result);
        return 3;
    }
    if(min == NULL){
        free(result); free(max);
        return 3;
    }
    if(validate(number1) != 0 || validate(number2) != 0){
        free(*result); free(max); free(min);
        return 2;
    }
    int swap = 0;
    swap = find_longer(max, min, number1, number2);
    if (*max == '-' && *min == '-'){
        subtract_base((max + 1), (min + 1), *result);
        if(swap == 0 && **result != '0') add_char(*result, '-');
    } else if(*max == '-') {
        add_base((max + 1), min, *result);
        if (swap == 0 && **result != '0') add_char(*result, '-');
    } else if (*min == '-'){
        add_base(max, (min + 1), *result);
        if (swap == 1 && **result != '0') add_char(*result, '-');
    } else{
        subtract_base(max, min, *result);
        if (swap == 1 && **result != '0') add_char(*result, '-');
    }
    
    free(max); free(min);
    return 0;
}

int add(const char* number1, const char* number2, char** result){
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    *result = (char*)malloc(3000);
    if (*result == NULL) return 3;
    char *max = (char*)malloc(50000);
    if(max == NULL){
        free(result);
        return 3;
    }
    char *min = (char*)malloc(50000);
    if(min == NULL){
        free(result); free(max);
        return 3;
    }
    if(validate(number1) != 0 || validate(number2) != 0){
        free(max); free(min); free(*result);
        return 2;
    }
    
    find_longer(max, min, number1, number2);
    if (*max == '-' && *min == '-'){
        add_base((max + 1), (min + 1), *result);
        if(**result != '0') add_char(*result, '-');
    } else if(*max == '-'){
        subtract_base((max + 1), (min), *result);
        if(**result != '0') add_char(*result, '-');
    }else if (*min == '-') subtract_base(max, (min + 1), *result);
    else add_base(max, min, *result);
    free(max); free(min);
    return 0;
}

int validate(const char *number){
    int i = 0;
    if(number == NULL) return 2;
    if(*(number + i) == '-') i++;
    if(i == 1 && *(number + i) == 0) return 1;
    if(*(number + i) == '\0')return 1;
    while(*(number + i) != '\0') if(is_number(*(number + i++)) == 0) return 1;
    return 0;
}

int compare(const char* number1, const char* number2){
    unsigned int i;
    int wynik = 1;
    if(number1 == NULL || number2 == NULL) return 2;
    if(validate(number2) != 0 || validate(number1) != 0) return 3;
    if(*number1 == '0' && is_number(*(number1 + 1))) return 3;
    if(*number2 == '0' && is_number(*(number2 + 1))) return 3;
    if(*number1 == '-' && *number2 == '-') wynik = -1;
    if (*number1 != '-' && *number2 == '-') return 1 * wynik;
    if (*number1 == '-' && *number2 != '-') return -1 * wynik;
    if(strlen(number1) > strlen(number2)) {
        return 1;
    }else if(strlen(number1) < strlen(number2)){
        return -1;
    }else{
        i = wynik == -1 ? 1: 0;
        for(; i <= strlen(number1) ;i++){
            if(*(number1 + i) > *(number2 + i)) return 1 * wynik;
            if(*(number1 + i) < *(number2 + i)) return -1 * wynik;
            if(i == strlen(number1)) break;
        }
    }
    return 0;
}


int multiply_base(const char* number1, const char base, char* result){
    int i = strlen(number1) - 1, value = base - '0', mem = 0, size = 0;
    for(; i >= 0; i--){
        int val = (*(number1 + i) - '0') * value + mem;
        *(result + i) = val % 10 + '0';
        mem = val / 10;
        size ++;
    }
    while(mem != 0){
        add_char(result, '0' + mem % 10);
        mem /= 10;
        size ++;
    }
    *(result + size) = '\0';
    return size;
}

void fill_with_char(char *chr, char znak, int size){while(size >= 0) *(chr + size--) = znak;}
void remove_char_from_string(char *chr, char znak){
    int i = 0;
    while(*(chr + i) != '\0'){
        if(*(chr + i) == znak) remove_minus((chr + i));
        else i++;
    }
}

int multiply(const char* number1, const char* number2, char** result){
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if(validate(number1) !=0 || validate(number2) !=0) return 2;
    *result = (char*)malloc(50000);
    if (*result == NULL) return 3;
    if (is_zero(number1) || is_zero(number2)){
        **result = '0';
        *(*(result) + 1)= '\0';
        return 0;
    }
    char *pom = (char*)malloc(50000);
    if (pom == NULL){
        free(*result);
        return 3;
    }
    char *pom_res = (char*)malloc(50000);
    if (pom_res == NULL){
        free(pom);
        free(*result);
        return 3;
    }
    *pom_res = '0';
    *(pom_res + 1)= '\0';
    int i = strlen(number2) - 1, j, zeros = 0, minus_x = 0, minus_y = 0;
    if (*number1 == '-') minus_x++;
    if (*number2 == '-') minus_y++;
    char *res;
    
    for(;i >= 0 + minus_y; i--, zeros++){
        int size = multiply_base((number1 + minus_x), *(number2 + i), pom);
        for (j = 0 ; j < zeros; j++) add_char((pom + size + j), '0');
        if(add(pom_res, pom, &res) != 0){
            free(pom);
            free(pom_res);
            return 3;
        }else{
            strcpy(pom_res, res);
            if(i != 0 + minus_y) free(res);
        }
    }
    strcpy(*result, res);
    free(res);
    if((minus_x + minus_y) % 2 == 1) add_char(*result, '-');
    free(pom);
    free(pom_res);
    return 0;
}

void copy_without_terminator(char *dest, char *src){
    int size = 0;
    while(*(src + size) !='\0'){
        *(dest + size) = *(src + size);
        size++;
    }
}

int calculate(const char* expr, char **result){
    if (result == NULL || expr == NULL) return 1;
    if (validate_expression(expr) != 0) return 2;
    *result = (char*)malloc(50000); if (*result == NULL) return 3;
    char *expr_copy = (char*)malloc(50000); if (expr_copy == NULL){ free(*result); return 3;}
    char *expr_pom;
    strcpy(expr_copy, expr);
    char *number = (char*)malloc(50000); if (number == NULL){ free(*result); free(expr_copy); return 3;}
    char *number_2 = (char*)malloc(50000); if (number_2 == NULL) { free(*result); free(number);free(expr_copy); return 3;}
    int i, i_mem;
    for(i = 0; *(expr_copy + i) != '\0'; i++){
        i_mem = i;
        i += fetch_number((expr_copy + i), number);
        if(*(expr_copy + i) == '*'){
            i++;
            i += fetch_number((expr_copy + i), number_2);
            multiply(number, number_2, &expr_pom);
            fill_with_char((expr_copy + i_mem), '^', strlen(number)+ strlen(number_2));
            copy_without_terminator((expr_copy + i_mem), expr_pom);
            remove_char_from_string(expr_copy, '^');
            i=i_mem-1;
            free(expr_pom);
        }else if(*(expr_copy + i) == '+'){
            i++;
            i += fetch_number((expr_copy + i), number_2);
            if(add(number, number_2, &expr_pom) != 0){
                free(number);free(expr_copy);free(number_2);
                return 3;
            }
            fill_with_char((expr_copy + i_mem), '^', strlen(number)+ strlen(number_2));
            copy_without_terminator((expr_copy + i_mem), expr_pom);
            remove_char_from_string(expr_copy, '^');
            i=i_mem-1;
            free(expr_pom);
        }else if(*(expr_copy + i) == '-'){
            i++;
            i += fetch_number((expr_copy + i), number_2);
            subtract(number, number_2, &expr_pom);
            fill_with_char((expr_copy + i_mem), '^', strlen(number)+ strlen(number_2));
            copy_without_terminator((expr_copy + i_mem), expr_pom);
            remove_char_from_string(expr_copy, '^');
            i=i_mem - 1;
            free(expr_pom);
        }
    }
    strcpy(*result, expr_copy);
    free(number); free(number_2);free(expr_copy);
    return 0;
}

int main(){
    char *result, *expr;
    expr = (char*)malloc(502);
    if (expr == NULL) return log_error("Failed to allocate memory", 3);
    printf("Podaj wyrazenie:\n");
    scanf("%500s", expr);
    if (validate_expression(expr) != 0){
        free(expr);
        return log_error("Incorrect input", 2);
    }
    if (calculate(expr, &result) == 0){
        printf("%s", result);
        free(result);
    }
    else{
        free(expr);
        return log_error("Failed to allocate memory", 3);
    }
    free(expr);
    return 0;
}
