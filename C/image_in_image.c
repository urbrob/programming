#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct image_t {
	char type[3];
	int **ptr;
	int width;
	int height;
};

void destroy_image(struct image_t **m){
	int i;
	if (m == NULL || (*m)->height < 1 || (*m)->width < 1 || (*m)->ptr == NULL) return;
	for (i = 0; i < (*m)->height; i++){
		if (*((*m)->ptr + i) == NULL) return;
		free(*((*m)->ptr + i));
	}
	if ((*m)->ptr != NULL) free((*m)->ptr);
	free(*m);
}

struct image_t* load_image_t(const char *filename, int *err_code){
	FILE *f;
	int i, max, j;
	struct image_t *img;
	if (err_code != NULL) *err_code = 0;
	if (filename == NULL){
		if (err_code != NULL) *err_code = 1;
		return NULL;
	}
	f = fopen(filename, "r");
	if (f == NULL){
		if (err_code != NULL) *err_code = 2;
		return NULL;
	}
	img = (struct image_t*)malloc(sizeof(struct image_t));
	if (img == NULL){
		if (err_code != NULL) *err_code = 4;
		fclose(f);
		return NULL;
	}
	fscanf(f, "%2s", img->type);
	if (*(img->type + 1) != '2' || (*(img->type) != 'P')){
		free(img);fclose(f);
		if (err_code != NULL) *err_code = 3;
		return NULL;
	}
	if (fscanf(f, "%d %d", &img->width, &img->height) != 2){
		free(img);fclose(f);
		if (err_code != NULL) *err_code = 3;
		return NULL;
	}
	img->ptr = (int**)malloc(sizeof(int*)*img->height);
	if (img->ptr == NULL){
		fclose(f);free(img);
		if (err_code != NULL) *err_code = 4;
		return NULL;
	}
	for (i = 0; i<img->height; i++){
		*(img->ptr + i) = (int*)malloc(sizeof(int)*img->width);
		if (*(img->ptr + i) == NULL){
			for(j = 0; j <= i; j++) free(*(img->ptr + j));
			free(img->ptr);free(img);fclose(f);
			if (err_code != NULL) *err_code = 4;
			return NULL;
		}
	}
	if (fscanf(f, "%d", &max) != 1){
		destroy_image(&img);fclose(f);
		if (err_code != NULL) *err_code = 3;
		return NULL;
	}
	for (i = 0; i < img->height; i++)
		for (j = 0; j < img->width; j++){
			if (fscanf(f, "%d", (*(img->ptr + i) + j)) != 1){
				fclose(f);
				destroy_image(&img);
				if (err_code != NULL) *err_code = 3;
				return NULL;
			}
		}
	fclose(f);
	return img;
}

int save_image_t(const char * filename, const struct image_t *m1){
	int i, j;
	if (filename == NULL || m1 == NULL || m1->ptr == NULL || m1->height < 1 || m1->width < 1) return 1;
	FILE *f;
	f = fopen(filename, "w");
	if (f == NULL) return 2;
	fprintf(f, "P2\n%d %d\n%d\n", m1->width, m1->height, 255);
	for (i = 0; i < m1->height; i++){
		for (j = 0; j < m1->width; j++) fprintf(f, "%3d ", *(*(m1->ptr + i) + j));
		fprintf(f, "\n");
	}
	fclose(f);return 0;
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty){
	if (img == NULL || src == NULL || src->ptr == NULL || img->ptr == NULL || destx < 0 || desty < 0) return 1;
	if (src->height + desty > img->height || src->width + destx > img->width) return 1;
	int x = 0, y = 0, i, j;
	for (i = desty; i < (desty + src->height); i++){
		for (j = destx; j < (destx + src->width); j++){
			*(*(img->ptr + i) + j) = *(*(src->ptr + y) + x++);
		}
		x = 0;
		y++;
	}
	return 0;
}

int log_error(char *txt, int error){ printf("%s", txt); return error;}

int main(){
	char *filename1, *filename2;
	int err, i;
	struct image_t *img1, *img2;
	filename1 = (char*)malloc(30 * sizeof(char));
	if (filename1 == NULL){
		printf("Failed to allocate memory");
		return 4;
	}
	printf("nazwa pliku: ");
	scanf("%29s", filename1);
	img1 = load_image_t(filename1, &err);
	switch(err){
		case 2:
			printf("File not found");
			free(filename1);
			return 2;
		case 3:
			printf("File corrupted");
			free(filename1);
			return 3;
		case 4:
			printf("Failed to allocate memory");
			free(filename1);
			return 4;
	}	
	int photos;
	printf("podaj photos plikow: ");
	if (scanf("%d", &photos) != 1 || photos < 1){
		printf("Incorrect input");
		destroy_image(&img1);
		free(filename1);
		return 1;

	}
	filename2 = (char*)malloc(30 * sizeof(char));
	if (filename2 == NULL)	{
		printf("Failed to allocate memory");
		free(filename1);
		destroy_image(&img1);
		return 4;
	}
	int destx, desty;
	for (i = 0; i < photos; i++){
		printf("nazwa pliku narysowanego: ");
		scanf("%29s", filename2);
		img2 = load_image_t(filename2, &err);
		switch(err){
			case 2:
				printf("File not found\n");
				continue;
			case 3:	
				printf("File corrupted\n");
				continue;
			case 4:
				printf("Failed to allocate memory");
				free(filename1);
				free(filename2);
				destroy_image(&img1);
				return 4;
		}
		printf("x i y: ");
		if (scanf("%d %d", &destx, &desty) != 2) printf("Incorrect input\n");
		if (draw_image(img1, img2, destx, desty) == 1) printf("Incorrect input\n");
		destroy_image(&img2);
	}

	for (i = 0; *(filename1 + i) != 0; i++){
		*(filename2 + i) = *(filename1 + i);
		if (*(filename1 + i + 1) == '.' && *(filename1 + i + 3) == 'x' && *(filename1 + i + 4) == 't' && *(filename1 + i + 2) == 't'){
			*(filename2 + i + 1) = '\0';
			strcat(filename2, "_modified.txt"); 
			break;
		}
	}
	if (save_image_t(filename2, img1) == 0) printf("File saved");
	else{
		printf("Couldn't save file");
		destroy_image(&img1);
		free(filename1);
		free(filename2);
		return 2;
	}
	destroy_image(&img1);
	free(filename1);
	free(filename2);
	return 0;
}
