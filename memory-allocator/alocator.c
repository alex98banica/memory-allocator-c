#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

unsigned char *vect; 
int n;
int spatiualocat[1000000];
int bloc=0;
int indexx[1000000];
int vectocupat[100000];



void INITIALIZE( int marime ){

vect=calloc( marime , sizeof( char* ) );
int i;
for(i=0;i<marime;i++){
	vect[i]=0;
	vectocupat[i]=0;
}
}

void FINALIZE(){

int i=0;

free(vect);

for(i=0;i<n;i++)
	vectocupat[i]=0;
for(i=0;i<bloc;i++){
	indexx[i]=0;
	spatiualocat[i]=0;
}

bloc=0;

}

void DUMP(){
int i = 0,j = 0 ;
while( j < n ) {
	if( j%16 == 0 ){
		printf("\n");
		printf("%08X\t",i);}
	if( j%8 == 0 && j%16 != 0 )
	printf(" ");
	printf("%02X ",vect[j]);
	j++;
	i++;
}
printf("\n");





}

void ALLOC(int spatiu){
int val1 = -12, val2 = 0;
int i = 0,j = 0;
int inainte,inapoi;
int Min,Max;

for(val2=0;val2<n;val2++){
	if(val1==spatiu)
		break;
	if(vectocupat[val2]==0)
		val1++;
	if(vectocupat[val2]!=0)
		val1=-12;

}


if( val1 == spatiu ){
	for(i=val2-spatiu-12;i<val2;i++)
		vectocupat[i]=1;
	spatiualocat[bloc]=spatiu;
	indexx[bloc]=val2-spatiu;
	bloc++;


	vect[indexx[bloc-1]-1] = (spatiu>>24) & 0xFF;
	vect[indexx[bloc-1]-2] = (spatiu>>16) & 0xFF;
	vect[indexx[bloc-1]-3] = (spatiu>>8) & 0xFF;
	vect[indexx[bloc-1]-4] = spatiu & 0xFF;
	
	if(bloc == 2){
		if( indexx[bloc-1] < indexx[0] ){
			inapoi=indexx[0];

			vect[indexx[bloc-1]-9] = (indexx[0]-12>>24) & 0xFF;
			vect[indexx[bloc-1]-10] = (indexx[0]-12>>16) & 0xFF;
			vect[indexx[bloc-1]-11] = (indexx[0]-12>>8) & 0xFF;
			vect[indexx[bloc-1]-12] = indexx[0]-12 & 0xFF;
	
			vect[indexx[0]-5] = (indexx[bloc-1]>>24) & 0xFF;
			vect[indexx[0]-6] = (indexx[bloc-1]>>16) & 0xFF;
			vect[indexx[0]-7] = (indexx[bloc-1]>>8) & 0xFF;
			vect[indexx[0]-8] = indexx[bloc-1] & 0xFF;
		}

		if( indexx[bloc-1] > indexx[0] ){
			inainte=indexx[0];
			
			vect[indexx[bloc-1]-5] = (indexx[0]-12>>24) & 0xFF;
			vect[indexx[bloc-1]-6] = (indexx[0]-12>>16) & 0xFF;
			vect[indexx[bloc-1]-7] = (indexx[0]-12>>8) & 0xFF;
			vect[indexx[bloc-1]-8] = indexx[0]-12 & 0xFF;
	
			vect[indexx[0]-9] = (indexx[bloc-1] -12 >>24) & 0xFF;
			vect[indexx[0]-10] = (indexx[bloc-1]-12>>16) & 0xFF;
			vect[indexx[0]-11] = (indexx[bloc-1]-12>>8) & 0xFF;
			vect[indexx[0]-12] = indexx[bloc-1]-12 & 0xFF;
		}
	}

	if(bloc > 2){



		Min=indexx[0];
		Max=indexx[0];
		for(j=1;j<bloc;j++){

			if(indexx[j]<Min ){
				Min=indexx[j];
				inapoi=spatiualocat[j];
			}
			if(indexx[j]>Max ){
				Max=indexx[j];
				inainte=spatiualocat[j];
			}
		}

		for(j=0;j<bloc;j++){

			if(indexx[bloc-1]-indexx[j]>0 && indexx[bloc-1]-indexx[j]<indexx[bloc-1]-Min ){
				Min=indexx[j];
				inapoi=spatiualocat[j];
			}
			if(indexx[j]-indexx[bloc-1]>0 && indexx[j]-indexx[bloc-1]<Max-indexx[bloc-1] ){
				Max=indexx[j];
				inainte=spatiualocat[j];
			}
		}
		if(Min<indexx[bloc-1]){
			vect[Min-9] = (indexx[bloc-1]-12 >>24) & 0xFF;
			vect[Min-10] = (indexx[bloc-1]-12>>16) & 0xFF;
			vect[Min-11] = (indexx[bloc-1]-12>>8) & 0xFF;
			vect[Min-12] = indexx[bloc-1]-12 & 0xFF;

			vect[indexx[bloc-1]-5] = (Min-12>>24) & 0xFF;
			vect[indexx[bloc-1]-6] = (Min-12>>16) & 0xFF;
			vect[indexx[bloc-1]-7] = (Min-12>>8) & 0xFF;
			vect[indexx[bloc-1]-8] = Min-12 & 0xFF;
		}
		
		
		if(Max>indexx[bloc-1]){	
			vect[indexx[bloc-1]-9] = (Max-12 >>24) & 0xFF;
			vect[indexx[bloc-1]-10] = (Max-12>>16) & 0xFF;
			vect[indexx[bloc-1]-11] = (Max-12>>8) & 0xFF;
			vect[indexx[bloc-1]-12] = Max-12 & 0xFF;

			vect[Max-5] = (indexx[bloc-1]-12>>24) & 0xFF;
			vect[Max-6] = (indexx[bloc-1]-12>>16) & 0xFF;
			vect[Max-7] = (indexx[bloc-1]-12>>8) & 0xFF;
			vect[Max-8] = indexx[bloc-1]-12 & 0xFF;
		}			
	
	}

printf("%d\n",(val2-spatiu));
}

else
	printf("0\n");

}

void FREE(int index){
int i=0,j,s=0,k1,k2;
int Min,Max,inainte,inapoi;
while(indexx[i]!=index)
	i++;

if(bloc-1==1){
	if(indexx[i-1]>indexx[i]){
		vect[indexx[i-1]-5]=0;
		vect[indexx[i-1]-6]=0;
		vect[indexx[i-1]-7]=0;
		vect[indexx[i-1]-8]=0;
	}
	if(indexx[i-1]<indexx[i]){
		vect[indexx[i-1]-9]=0;
		vect[indexx[i-1]-10]=0;
		vect[indexx[i-1]-11]=0;
		vect[indexx[i-1]-12]=0;
	}
	
}

if(bloc-1>=2){
	Min=indexx[0];
	Max=indexx[0];

	for(j=1;j<bloc;j++){
		if(indexx[j]<Min ){
			Min=indexx[j];
			inapoi=spatiualocat[j];
		}
		if(indexx[j]>Max ){
			Max=indexx[j];
			inainte=spatiualocat[j];
		}
	}

	for(j=0;j<bloc;j++){

		if(indexx[i]-indexx[j]>0 && indexx[i]-indexx[j]<indexx[i]-Min && j!=i){
			Min=indexx[j];
			inapoi=spatiualocat[j];
		}
		if(indexx[j]-indexx[i]>0 && indexx[j]-indexx[i]<Max-indexx[i] && j!=i){
			Max=indexx[j];
			inainte=spatiualocat[j];
		}
	}

	vect[Min-9] = (Max-12 >>24) & 0xFF;
	vect[Min-10] = (Max-12>>16) & 0xFF;
	vect[Min-11] = (Max-12>>8) & 0xFF;
	vect[Min-12] = Max-12 & 0xFF;
	
	vect[Max-5] = (Min-12>>24) & 0xFF;
	vect[Max-6] = (Min-12>>16) & 0xFF;
	vect[Max-7] = (Min-12>>8) & 0xFF;
	vect[Max-8] = Min-12 & 0xFF;
	


}

for(j=indexx[i]-12;j<indexx[i]+spatiualocat[i];j++){
	vect[j]=0;
	vectocupat[j]=0;
}

indexx[i]=0;
spatiualocat[i]=0;

for(j=i;j<bloc;j++){
	indexx[j]=indexx[j+1];
	spatiualocat[j]=spatiualocat[j+1];
}
bloc--;
}

void FILL(int index,int size,int value){
int i=0,j=0,k,s=0;
while(indexx[j]!=index)
	j++;
for(k=0;k<spatiualocat[j];k++){
	s++;
	vect[indexx[j]+k]=value;
	if(s>=size)
		break;
}

for(i=0;i<bloc;i++){
	if(indexx[i]!=indexx[j] && indexx[i]>indexx[j])
	for(k=0;k<spatiualocat[i];k++){
		s++;
		if(s>=size)
		break;
		vect[indexx[i]+k]=value & 0xFF;
	}
	if(s>=size)
		break;
}
}



void parse_command(char* cmd)
{
    const char* delims = " \n";

    char* cmd_name = strtok(cmd, delims);
    if (!cmd_name) {
        goto invalid_command;
    }

    if (strcmp(cmd_name, "INITIALIZE") == 0) {
        char* size_str = strtok(NULL, delims);
        if (!size_str) {
            goto invalid_command;
        }
        uint32_t size = atoi(size_str);
        // TODO - INITIALIZE
	INITIALIZE(size);
	n=size;

    } else if (strcmp(cmd_name, "FINALIZE") == 0) {
        // TODO - FINALIZE
	FINALIZE();
    } else if (strcmp(cmd_name, "DUMP") == 0) {
        // TODO - DUMP
	DUMP();
    } else if (strcmp(cmd_name, "ALLOC") == 0) {
        char* size_str = strtok(NULL, delims);
        if (!size_str) {
            goto invalid_command;
        }
        uint32_t size = atoi(size_str);
        // TODO - ALLOC
	ALLOC(size);
    } else if (strcmp(cmd_name, "FREE") == 0) {
        char* index_str = strtok(NULL, delims);
        if (!index_str) {
            goto invalid_command;
        }
        uint32_t index = atoi(index_str);
        // TODO - FREE
	FREE(index);
    } else if (strcmp(cmd_name, "FILL") == 0) {
        char* index_str = strtok(NULL, delims);
        if (!index_str) {
            goto invalid_command;
        }
        uint32_t index = atoi(index_str);
        char* size_str = strtok(NULL, delims);
        if (!size_str) {
            goto invalid_command;
        }
        uint32_t size = atoi(size_str);
        char* value_str = strtok(NULL, delims);
        if (!value_str) {
            goto invalid_command;
        }
        uint32_t value = atoi(value_str);
        // TODO - FILL
	FILL(index,size,value);

    } else if (strcmp(cmd_name, "ALLOCALIGNED") == 0) {
        char* size_str = strtok(NULL, delims);
        if (!size_str) {
            goto invalid_command;
        }
        uint32_t size = atoi(size_str);
        char* align_str = strtok(NULL, delims);
        if (!align_str) {
            goto invalid_command;
        }
        uint32_t align = atoi(align_str);
        // TODO - ALLOCALIGNED

    } else if (strcmp(cmd_name, "REALLOC") == 0) {
        printf("Found cmd REALLOC\n");
        char* index_str = strtok(NULL, delims);
        if (!index_str) {
            goto invalid_command;
        }
        uint32_t index = atoi(index_str);
        char* size_str = strtok(NULL, delims);
        if (!size_str) {
            goto invalid_command;
        }
        uint32_t size = atoi(size_str);
        // TODO - REALLOC

    } else {
        goto invalid_command;
    }

    return;

invalid_command:
    printf("Invalid command: %s\n", cmd);
    exit(1);
}

int main(void)
{
    ssize_t read;
    char* line = NULL;
    size_t len;

    /* parse input line by line */
    while ((read = getline(&line, &len, stdin)) != -1) {
        /* print every command to stdout */
        printf("%s", line);

        parse_command(line);
    }

    free(line);

    return 0;
}
