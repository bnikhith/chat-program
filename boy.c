#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<pthread.h>
typedef struct blocky{
	int size;
	char msg[60];
};
pthread_cond_t cond_var;
pthread_mutex_t mutexlock;
void* send(void*args){
	struct blocky b;
	FILE* fp = fopen("D:\\nik1.bin", "rb+");
	while (1){

		printf("\nboy: ");
		fflush(stdin);
		gets(b.msg);
		//scanf("%[^\n]*c", b.msg);
		b.size = strlen(b.msg);
		fwrite(&b, sizeof(struct blocky), 1, fp);
		fflush(fp);
	}
	fclose(fp);
	return 0;
}
void* recieve(void*args){
	struct blocky b;
	//pthread_mutex_lock(&mutexlock);
	FILE* fs = fopen("D:\\nik.bin", "rb+");
	char ch;
	while (1){
		if ((ch = fgetc(fs)) == EOF){
			fseek(fs, -1, SEEK_CUR);
			continue;
		}
		else{
			fseek(fs, -1, SEEK_CUR);
		}
		fread(&b, sizeof(struct blocky), 1, fs);
		if (b.size < 0)
			continue;
		printf("girl: %s\n\n", b.msg);
		b.size = ((-1) * (b.size));
		fseek(fs, -64, SEEK_CUR);
		fwrite(&b, sizeof(struct blocky), 1, fs);

	}
	fclose(fs);
	//pthread_mutex_unlock(&mutexlock);
	return 0;
}
int main(){

	//FILE* fs = fopen("D:\\nik.bin", "rb+");
	//struct blocky b;
	pthread_t t0, t4;
	void*agrs;
	pthread_mutex_init(&mutexlock, NULL);
	pthread_cond_init(&cond_var, NULL);
	pthread_create(&t0, NULL, send, NULL);
	pthread_create(&t4, NULL, recieve, NULL);
	//pthread_join(t0, NULL);
	pthread_join(t0, NULL);
	pthread_join(t4, NULL);
	getchar();
	return 0;
}
