#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "format_type.h"

struct statistic_t{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int log_error(char *chr, int error){printf("%s", chr); return error;}

int save(const char *filename, int **ptr, enum save_format_t format){
    int i, j;
    if (filename == NULL || ptr == NULL) return 1;
    if (format == fmt_text){
        FILE *f = fopen(filename, "w");
        if (f == NULL) return 2;
        for (i = 0; *(ptr + i) != NULL; i++){
            for (j = 0;; j++){
                if (*(*(ptr + i) + j) == -1) fprintf(f, "%d", *(*(ptr + i) + j));
                else fprintf(f, "%d ", *(*(ptr + i) + j));
                if (*(*(ptr + i) + j) == -1) break;
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
    else if (format == fmt_binary){
        FILE *f = fopen(filename, "wb");
        if (f == NULL) return 2;
        for (i = 0; *(ptr + i) != NULL; i++){
            for (j = 0;; j++){
                fwrite((*(ptr + i) + j), 4, 1, f);
                if (*(*(ptr + i) + j) == -1) break;
            }
        }
        fclose(f);
    }
    else return 1;
    return 0;
}

int load(const char *filename, int ***ptr, enum save_format_t format){
    if (filename == NULL || ptr == NULL) return 1;
    int counter = 0,liczba = 0, test = 0, i, j, k;
    char *fda = (char*)malloc(60); if (fda == NULL) return 4;
    free(fda);
    FILE *f;
    if (format == fmt_text){
        f = fopen(filename, "r");
        if (f == NULL) return 2;
        if (fscanf(f, "%d", &test) != 1){ fclose(f);return 3;}
        fseek(f, 0, SEEK_SET);
        for (i = 0; feof(f) == 0; i++){
        	liczba = 0;
            fscanf(f, "%d", &liczba);
            if (liczba == -1) counter++;
        }
        fseek(f, 0, SEEK_SET);
        *ptr = (int**)malloc(sizeof(int*) * (counter + 1));
        if (*ptr == NULL){
            fclose(f);
            return 4;
        }
        for (i = 0; i < counter; i++){
            for (j = 0;; j++){
                liczba = 0;
                if (fscanf(f, "%d", &liczba) != 1){
                    for (j = 0; j <= i; ++j) if(*((*ptr) + j) != NULL) free(*((*ptr) + j));
                    free(*ptr);
                    fclose(f);
                    return 3;
                }
                if (liczba == -1){
                    *((*ptr) + i) = (int*)malloc(sizeof(int) * (j + 1));
                    if (*((*ptr) + i) == NULL){
                        for (j = 0; j <= i; j++) free(*((*ptr) + j));
                        free(*ptr);
                        fclose(f);
                        return 4;
                    }
                    break;
                }
            }
        }
        fseek(f, 0, SEEK_SET);
        for (i = 0; i < counter; i++){
            for (j = 0; ;j++){
            	liczba = 0;
                if (fscanf(f, "%d", &liczba) == 1) *(*((*ptr) + i) + j) = liczba;
                else{
                    fclose(f);
                    for (k = 0; k < i; k++)free(*((*ptr) + k));
                    free((*ptr));
                    return 3;
                }
                if (liczba == -1) break;
            }
        }
        (*((*ptr) + counter)) = NULL;
        fclose(f);
    }
    else if (format == fmt_binary){
        test = 0;
        f = fopen(filename, "rb");
        if (f == NULL) return 2;
        int counter = 0, liczba;

        if (fread(&test, sizeof(int), 1, f) != 1){
            fclose(f);
            return 3;
        }
        fseek(f, 0, SEEK_SET);
        for (i = 0; feof(f) == 0; i++){
            liczba = 0;
            fread(&liczba, sizeof(int), 1, f);
            if (liczba == -1) counter++;
        }
        fseek(f, 0, SEEK_SET);
        *ptr = (int**)malloc(sizeof(int*) * (counter + 1));
        if (*ptr == NULL){fclose(f); return 4;}
        for (i = 0; i < counter; i++){
            for (j = 0; ;j++){
                liczba = 0;
                if (fread(&liczba, sizeof(int), 1, f) != 1){
                    for (j = 0; j <= i; j++)free(*((*ptr) + j));
                    free(*ptr);
                    fclose(f);
                    return 3;
                }
                if (liczba == -1){
                    *((*ptr) + i) = (int*) malloc(sizeof(int) * (j + 1));
                    if (*((*ptr) + i) == NULL){
                        for (j = 0; j <= i; j++)free(*((*ptr) + j));
                        free(*ptr);
                        fclose(f);
                        return 4;
                    }
                    break;
                }
            }
        }
        fseek(f, 0, SEEK_SET);
        for (i = 0; i < counter; i++){
            for (j = 0;; j++){
                if (fread(&liczba, sizeof(int), 1, f) == 1) *(*((*ptr) + i) + j) = liczba;
                else{
                    for (k = 0; k < i; k++) free(*((*ptr) + k));
                    free((*ptr));
                    fclose(f);
                    return 3;
                }
                if (liczba == -1) break;
            }
        }
        fclose(f);
        (*((*ptr) + counter)) = NULL;
    }
    else return 1;
    return 0;
}

int statistics(int **ptr, struct statistic_t **stats){
    if (ptr == NULL || stats == NULL) return 1;
    int i ,j, counter = 0;
    for (i = 0; *(ptr + i) != NULL; i++)for (j = 0; *(*(ptr + i) + j) != -1; j++)counter++;
    if (counter == 0) return 3;
    *stats = (struct statistic_t*) malloc(sizeof(struct statistic_t)); if (*stats == NULL) return 2;
    float min = 10000000, max = -99999999, avg = 0, sum = 0, ile = 0;
    
    for (i = 0; *(ptr + i) != NULL; i++){
        for (j = 0; *(*(ptr + i) + j) != -1; j++){
            avg += *(*(ptr + i) + j);
            max =  *(*(ptr + i) + j) > max ?  *(*(ptr + i) + j) : max;
            min =  *(*(ptr + i) + j) < min ?  *(*(ptr + i) + j) : min;
            ile++;
        }
    }
    avg /= ile;
    sum = 0;
    for (i = 0; *(ptr + i) != NULL; i++){
        for (j = 0; *(*(ptr + i) + j) != -1; j++){
            sum += (*(*(ptr + i) + j) - avg) * (*(*(ptr + i) + j) - avg);
        }
    }
    (*stats)->avg = avg;
    (*stats)->max = max;
    (*stats)->min = min;
    (*stats)->range = max - min;
    (*stats)->standard_deviation = sqrt(sum / ile);
    return 0;
}

int statistics_row(int **ptr, struct statistic_t **stats){
    int ile_wierszy = 0, i = 0, g, j;
    if (ptr == NULL || stats == NULL) return -1;
    for (; *(ptr + i) != NULL; i++) ile_wierszy++;
    *stats = (struct statistic_t*) malloc(sizeof(struct statistic_t)*ile_wierszy);
    if (*stats == NULL) return -2;
    float min, max, avg, st_dev, range, sum = 0, ile = 0;
    for (g = 0; g < ile_wierszy; g++){
        min = *(*(ptr + g)), max = *(*(ptr + g)), avg = 0, st_dev = 0, range = 0, sum = 0, ile = 0;
        for (j = 0; *(*(ptr + g) + j) != -1; j++){
            sum += *(*(ptr + g) + j);
            max =  *(*(ptr + g) + j) > max ?  *(*(ptr + g) + j) : max;
            min =  *(*(ptr + g) + j) < min ?  *(*(ptr + g) + j) : min;
            ile++;
        }
        if (ile == 0){(*stats + g)->avg = -1;(*stats + g)->max = -1;(*stats + g)->min = -1;(*stats + g)->range = -1;(*stats + g)->standard_deviation = -1;
        }
        else{

            avg = sum / ile;
            sum = 0;
            range = max - min;

            for (j = 0; *(*(ptr + g) + j) != -1; j++){
                sum += (*(*(ptr + g) + j) - avg)*(*(*(ptr + g) + j) - avg);
            }

            st_dev = sqrt(sum / ile);
            (*stats + g)->avg = avg;
            (*stats + g)->max = max;
            (*stats + g)->min = min;
            (*stats + g)->range = range;
            (*stats + g)->standard_deviation = st_dev;
        }
    }
    return ile_wierszy;
}

void destroy(int ***ptr){
    int i;
    for (i = 0;*((*ptr) + i) != NULL; i++) if (*((*ptr) + i) != NULL) free(*((*ptr) + i));
    free(*ptr);
}

void display(int **ptr){
    int i, j;
    if (ptr == NULL) return;
    for (i = 0; *(ptr + i) != NULL; i++){
        for (j = 0; *(*(ptr + i) + j) != -1; j++) printf("%3d ", *(*(ptr + i) + j));
        printf("\n");
    }
}

void cpystr(char *dest, char *src, char *add){
    int i = 0, j = 0;
    while(*(src + i) != '\0'){ *(dest + i) = *(src + i); i++;} 
    while(*(add + j) != '\0'){ *(dest + i) = *(add + j); i++; j++;}
    *(dest + i) = '\0';
}

int check_ext(char *filename){
    int i;
    while(*(filename + i) != '\0') i++;
    if(*(filename + i -4) == '.' &&*(filename + i -3  ) == 't' &&*(filename + i - 2) == 'x' &&*(filename + i - 1) == 't' &&*(filename + i) == '\0') return 1;
    if(*(filename + i -4) == '.' &&*(filename + i -3  ) == 'b' &&*(filename + i - 2) == 'i' &&*(filename + i - 1) == 'n' &&*(filename + i) == '\0') return 2;
    return 0;
}

int check_if_file(char *filename){
	int i =0, counter=0;
	for(; *(filename+i) !='\0'; i++){
		if(*(filename+i)  == '.') counter ++;
	}
	if(counter != 1) return 0;
	return check_ext(filename);
}

int main(){
	char* wsk = (char*)malloc(40);
    if(wsk == NULL) return log_error("Failed to allocate memory", 4);
    printf("Gibe plik pliaze: ");
    scanf("%39s", wsk);

    int i, ** ptr;
    
	switch(check_if_file(wsk)){
		case 1:
	        switch(load(wsk,&ptr,fmt_text)){
	        	case 1:
	        		printf("Couldn't open file");
	            	free(wsk);
	            	return 2;
	            case 2:
	            	printf("Couldn't open file");
		            free(wsk);
		            return 2;
		        case 3:
		        	printf("File corrupted");
		            free(wsk);
		            return 3;
		        case 4:
		            printf("Failed to allocate memory");
		            free(wsk);
		            return 4;
			}
	        break;
    	case 2:
	        switch(load(wsk,&ptr,fmt_binary)){
	        	case 1:
	        		printf("Couldn't open file");
	            	free(wsk);
	            	return 2;
	            case 2:
	            	printf("Couldn't open file");
		            free(wsk);
		            return 2;
		        case 3:
		        	printf("File corrupted");
		            free(wsk);
		            return 3;
		        case 4:
		            printf("Failed to allocate memory");
		            free(wsk);
		            return 4;
			}
	    	break;
		case 0:
	        printf("Wrong filename");
	        free(wsk);
	        return 1;
    }
    
    
    int stat_error;
    struct statistic_t *stats;
    stat_error = statistics_row(ptr,&stats);
    if(stat_error == -1){
        printf("Failed to allocate memory\n");
        destroy(&ptr);
        return 4;
    }
    else if(stat_error == -2){
        printf("Failed to allocate memory\n");
        destroy(&ptr);
        return 4;
    }
    free(wsk);

    for (i = 0; i <stat_error; i++) printf("%d %d %d %.2f %.2f\n", (stats+i)->min,(stats + i)->max,(stats + i)->range,(stats + i)->avg,(stats + i)->standard_deviation);
    

    free(stats);
    destroy(&ptr);

    return 0;
}

