#include <stdio.h>
#include <string.h>
// Copyrights restricted to Robert Urbaniak
struct bits{
    unsigned char a:1;
    unsigned char b:1;
    unsigned char c:1;
    unsigned char d:1;
    unsigned char e:1;
    unsigned char f:1;
    unsigned char g:1;
    unsigned char h:1;
};

union byte{
    unsigned char letter;
    struct bits bit_set;
};

int my_len(const char* string){
    const char *letter = string;
    for( ; *letter;++letter);
    return letter-string;
}

int save(FILE *f, FILE *g, int x){
    int pom; 
    char n;
    union byte byte_save;
    if((fscanf(f,"%d", &pom) != 1))  return 0;
    byte_save.letter = pom;
    byte_save.bit_set.a = x;
    fprintf(g, "%d ", byte_save.letter);
    if((fscanf(f, "%c", &n)) != 1) return 0;
    if(n == ' '){
       if((fscanf(f, "%c", &n)) != 1) return 0;
       if(n == '\n') fprintf(g, "\n");
       else fseek(f, -1, SEEK_CUR);
    }   
    return 1;
}

int encode(const char *input, char *txt, const char *output){
    if (input == NULL || txt == NULL || output == NULL) return 4;
    FILE *f ,*g;
	if((f = fopen(input, "r")) == NULL) return 1;  
    if((g = fopen(output, "w")) == NULL){
        fclose(f); return 2;
    }
    union byte byte_pom;
    int x = 0, i = 0;
    for(;!x && !feof(f); i++){
        if(i < my_len(txt)){
                byte_pom.letter = *(txt+i);
                if(save(f, g, byte_pom.bit_set.h) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.g) == 0){
					fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.f) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.e) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.d) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.c) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.b) == 0){
                    fclose(f); fclose(g); return 3;
                }
                if(save(f, g, byte_pom.bit_set.a) == 0){
                    fclose(f); fclose(g); return 3;
                }
            }
        else if(save(f, g, 0) == 0) x++;
    }
    fclose(g); fclose(f); return 0;
}

int decode(const char * filename, char *txt, int size){
    if(size <= 0 || filename == NULL || txt == NULL) return 2;
    FILE *f1;
    union byte byte_load, byte_save;
    int i = 0, a, b, c, d, e, f, g, h;
    if((f1 = fopen(filename, "r")) == NULL) return 1;
    for(;i < size; i++){
        if(fscanf(f1, "%d %d %d %d %d %d %d %d", &h, &g, &f, &e, &d, &c, &b, &a) != 8){
            fclose(f1); return 3;
        }
        if(d == EOF || c == EOF || b == EOF || a == EOF || h == EOF || g == EOF || f == EOF || e == EOF) break;
        byte_load.letter = h;
        byte_save.bit_set.h = byte_load.bit_set.a;
        byte_load.letter = g;
        byte_save.bit_set.g = byte_load.bit_set.a;
        byte_load.letter = f;
        byte_save.bit_set.f = byte_load.bit_set.a;
        byte_load.letter = e;
        byte_save.bit_set.e = byte_load.bit_set.a;
        byte_load.letter = d;
        byte_save.bit_set.d = byte_load.bit_set.a;
        byte_load.letter = c;
        byte_save.bit_set.c = byte_load.bit_set.a;
        byte_load.letter = b;
        byte_save.bit_set.b = byte_load.bit_set.a;
        byte_load.letter = a;     
        byte_save.bit_set.a = byte_load.bit_set.a;
        *(txt + i) = byte_save.letter;  
    }
    fclose(f1);
    return 0;
}


int main() {
	int i = 1;
    char znak[1], *ptr_char = znak, text[1010], *ptr_text = text, image[30], *ptr_image = image, tab[30], *ptr_tab = tab;
    printf("Choose: e/d:\n");
    scanf("%c", ptr_char);
	if(*ptr_char == 'E' || *ptr_char == 'e'){
	        printf("Podaj text do ukrycia:\n");
	        char z;
	        scanf("%*c%c", &z);
	        *ptr_text = z;
	        for(; i < 1010; i++){
	            scanf("%c", &z);
	            if(z == '\n') break;
	            *(ptr_text + i) = z;
	            *(ptr_text + i + 1) = '\0';
	        }
	        printf("Podadj nazwe pliku:\n");
	        scanf("%29s", ptr_image);
	        printf("Podaj nazwe pliku zakodowanego:\n");
	        scanf("%29s", ptr_tab);
	        FILE *f, *f2;
	        if(( f = fopen(ptr_image, "r")) == NULL){
	            printf("File not found");
	            return 1;
	        }
	        if(( f2 = fopen(ptr_tab, "w")) == NULL){
	            fclose(f);
	            printf("Couldn't create file");
	            return 2;
	        }
	        fclose(f);
	        fclose(f2);
	        int error = encode(ptr_image, ptr_text, ptr_tab);
	        
	        if(error == 0) printf("File saved");
	        else if(error == 1) printf("File not found");           
	        else if (error ==2 )printf("Couldn't create file");
	        else if(error == 3) printf("File corrupted");
	} else if(*ptr_char == 'D' || *ptr_char == 'd'){
	    printf("Podaj nazwe pliku:\n");
	    scanf("%29s", ptr_image);
	    FILE *f;    
	    if((f = fopen(ptr_image, "r")) == NULL){
	        printf("File not found");
	        return 1;
	    }
	    fclose(f);   
	    if(decode(ptr_image, ptr_text, 1010) == 0){
	        printf("%s", ptr_text);
	        return 0;
	    }else {
	        printf("File corrupted");
	        return 3;
	    }
	}
	else{
	        printf("Incorrect input"); return 0;
	}
	    return 0;
}
