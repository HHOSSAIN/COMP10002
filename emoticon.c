/* Emoticon message cleanser:
 *
 * Further completed by student name:HASNE HOSSAIN *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* library below included by Hasne */
#include <string.h>

#define STAGE_NUM_ONE 1							/* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_MSG_LENGTH 280						/* maximum message length */
#define MAX_NUM_MSGS 100						/* maximum number of messages */
#define MAX_EMTCN_LENGTH 50						/* maximum emot. line length */
#define MAX_NUM_EMTCN 50						/* maximum number of emot. */

typedef char msg_t[MAX_MSG_LENGTH+1];			/* a message */
typedef char emtcn_t[MAX_EMTCN_LENGTH+1];		/* an emoticon */

/****************************************************************/

/* function prototypes */
void read_one_msg(msg_t one_msg, int max_len);
void print_stage_header(int stage_num);
int count_tokens(msg_t one_msg);

void stage_one(msg_t one_msg);
void stage_two(msg_t msgs[], int *num_msgs);
void stage_three(msg_t msgs[], int num_msgs);
void stage_four(emtcn_t emtcns[], int *num_emtcns);
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns);

/* add your own function prototypes here */
void print(msg_t A[], int rows);
void copy_array(msg_t A[], msg_t B[], int rows);
void copy_array2(emtcn_t A[],emtcn_t B[], int rows);
int my_strcmp(const char *a, const char *b);
int my_strlen(char *s);
char *my_strcat(char *dest, char *src) ;
int row_count(msg_t filter[]);
/****************************************************************/

/* main function controls all the action */
int
main(int argc, char *argv[]) {
	/* to hold all input messages */
	msg_t msgs[MAX_NUM_MSGS];	
	/* to hold the number of input messages */
	int num_msgs = 0;	
	/* to hold all input emoticons in the dictionary */
	emtcn_t emtcns[MAX_NUM_EMTCN];
	/* to hold the number of emoticons in the dictionary */
	int num_emtcns = 0;	
	
	/* stage 1: reading the first message */
	stage_one(msgs[num_msgs]);  //num_msgs is row number 
	num_msgs++;
	
	/* stage 2: removing alphanumeric characters */
	stage_two(msgs, &num_msgs);

	/* stage 3: removing extra commas */ 
	stage_three(msgs, num_msgs);
	
	/* stage 4: reading the dictionary and finding the longest emoticon */
	stage_four(emtcns, &num_emtcns);
	
	/* stage 5: removing invalid emoticons with the help of the dictionary */
	stage_five(msgs, num_msgs, emtcns, num_emtcns);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_msg */
void
read_one_msg(msg_t one_msg, int max_len) {
	int i = 0, c;
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_msg[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_msg[i] = '\0';
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);  //STARGE_HEADER = "Stage %d\n==========\n"
}

/****************************************************************/

/* scan a message and count the number of tokens (separated by commas) in it */
int count_tokens(msg_t one_msg) { 
	/* add code here to count the number commas in one_msg,
	   and return the count + 1 */
	   int length = strlen(one_msg);
	   int commas=0;
       for (int i=0; i<length; i++){
		   if (one_msg[i] == ','){
               commas += 1;
		   }
	   }
	   return commas + 1;
}
/* print array rows */
void print(msg_t A[], int rows){
	for(int k=0; k < rows; k++){
		printf("%s", A[k]);
        if(k<(rows-1)){
			printf("\n");
		}
	}
}
/* copy of A[] into B[] for messages*/
void copy_array(msg_t A[], msg_t B[], int rows){
    int i=0,j=0;
	for (i=0; i<rows; i++){
        int length = strlen(A[i]);
        for (j=0; j <= length; j++){     //want '\0' copied as well
			B[i][j] = A[i][j];
		}
		
	}
}

/* copy A into B for dictionary */
void copy_array2(emtcn_t A[],emtcn_t B[], int rows){
    int i=0,j=0;
	for (i=0; i<rows; i++){
		int length = strlen(A[i]);
        for (j=0; j <= length; j++){    //want '\0' copied as well
			B[i][j] = A[i][j];
		}	
	}
}
/* comparing if 2 strings are identical or not*/
int my_strcmp(const char *arr1, const char *arr2){
    while (*arr1 && *arr1 == *arr2) { 
        ++arr1; 
        ++arr2; 
    }
    return (int)(unsigned char)(*arr1) - (int)(unsigned char)(*arr2);
}
/* strlen() substitute for stage_five */
int my_strlen(char *s){
    int len = 0;
    while(*s != 0) {
        s += 1;
        len += 1;
    }
    return len;
}
/* concatenation of strings for stage_five */
char *my_strcat(char *dest, char *src) {
    size_t i = my_strlen(dest);
    size_t j = my_strlen(src);
    for (size_t k = 0; k <= j; k++) {
        dest[k + i] = src[k];    
    }
    return dest;
}
/* count number of rows in the array*/
int row_count(msg_t filter[]){
	int rows=0;
    while (my_strcmp(filter[rows], "\0") != 0){
		rows +=1;
	}
	return rows;
}	

/* stage 1: reading the first message */
void stage_one(msg_t one_msg) {
	/* add code for stage 1 */
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	
	/* read the first message */
	read_one_msg(one_msg,  MAX_MSG_LENGTH);
	
	/* count and print the number of tokens */
	printf("Number of tokens: %d\n\n", count_tokens(one_msg));
}

/* stage 2: removing alphanumeric characters */
void stage_two(msg_t msgs[], int *num_msgs) {
	/* add code for stage 2 */
	/* print stage header */
	msg_t filter[MAX_NUM_MSGS]; int pos=0; //initialising rectifying array
	print_stage_header(STAGE_NUM_TWO);
	int i=0, j=0;
	while((strcmp(msgs[i], "###")) != 0){
		pos = 0;
		for (j = 0; j < MAX_MSG_LENGTH && msgs[i][j] != '\0'; j++){ 
		    if (!isalnum(msgs[i][j])){
                filter[i][pos] = msgs[i][j];
			    pos += 1;
			}
		}
		i += 1;
		read_one_msg(msgs[i],  MAX_MSG_LENGTH);
	}
    
	*num_msgs=i;
    print(filter, i);        //i=total rows=*num_msgs at this stage
	printf("\n\n");
	copy_array(filter,msgs,i);   //msgs array updated
}

/* stage 3: removing extra commas */ 
void stage_three(msg_t msgs[], int num_msgs) {
	/* add code for stage 3 */
	/* print stage header */
	print_stage_header(STAGE_NUM_THREE);
	msg_t final_filter[MAX_NUM_MSGS]; 
	int i=0;
	for (i=0; i < num_msgs; i++){  //i=row number
		int len=0;int a;
		for(a=0; msgs[i][a] == ',' && msgs[i][a] != '\0'; a++){
			//j += 1;
		}
        final_filter[i][len++] = msgs[i][a];
        int length2 = strlen(msgs[i]);
		for(a=a+1; a <= length2; a++){	
			if (msgs[i][a] == ',' && (msgs[i][a+1] == '\0' || 
                msgs[i][a+1] == ',')){
			}
			else{
				final_filter[i][len++] = msgs[i][a];
			}
		}
		printf("%s\n", final_filter[i]);		
	}
    
	printf("\n");
    copy_array(final_filter,msgs,i);
}
	
/* stage 4: reading the dictionary and finding the longest emoticon */ 
void stage_four(emtcn_t emtcns[], int *num_emtcns) {
	/* add code for stage 4 */
	/* print stage header */
	print_stage_header(STAGE_NUM_FOUR);
	int a=0; int length; int i=0;
    emtcn_t	filter[MAX_NUM_EMTCN]; int pos=0;
	for(a=0; a<MAX_NUM_EMTCN; a++){  //a=row number
        read_one_msg(emtcns[a], MAX_EMTCN_LENGTH);
		if ((strcmp(emtcns[a], "\0")) == 0){
			break;
		} 
		length = strlen(emtcns[a]);
        i=0, pos=0;
        for(i=0; i<length; i++){
            if(emtcns[a][i] == ','){
                break;
			}			
			else{
		       filter[a][pos++] = emtcns[a][i];
			}   
		}
        filter[a][pos++] = '\0';
	}
	int size =0, b=0, max_size=0, max_row=0;
	for(b=0; b<a; b++){
		size = strlen(filter[b]);
		if (size > max_size){
			max_size = size;
			max_row = b;  //rownumber of arr with max sized emoticon
		}
	}
    
    *num_emtcns = a;
	copy_array2(filter,emtcns,a);
    
	printf("Emoticon total: %d\n", a);
    printf("Longest: %s\n", filter[max_row]);
	printf("Length: %d\n", max_size);
	printf("\n");
}

/* stage 5: removing invalid emoticons with the help of the dictionary */
void stage_five(msg_t msgs[], int num_msgs, emtcn_t emtcns[], int num_emtcns) {	
	print_stage_header(STAGE_NUM_FIVE);
    int i=0, j=0, k=0, inum=0, found=0, rows=0;     //used i for rows,j for cols
	msg_t filter[MAX_NUM_MSGS]; int fil_pos=0;
	emtcn_t substr; int pos=0;
    filter[0][0]='\0';
    
	while ((my_strcmp(msgs[i],"\0")) != 0){ 
	    pos=0; substr[0]='\0';
	    for(j=inum;(msgs[i][j] != ',' && msgs[i][j] != '\0'); j++){
            substr[pos++] = msgs[i][j];
		}
		substr[pos++] = '\0';
		inum=j;  //points to ','s position
		found =0;
	    for(k=0; k<num_emtcns; k++){
			if(my_strcmp(emtcns[k], substr) == 0){
				found = 1;
				break;
			}
	    }
        
       	if(found){
		    my_strcat(filter[fil_pos], substr);
		    if(msgs[i][j] == '\0'){
			   i += 1;  //changing row
               fil_pos += 1;
			   inum = 0;
			}   
		    else{ 
			   my_strcat(filter[fil_pos], ",");
			   inum += 1;
		    }  
		}   
		else{
			if(msgs[i][j] == '\0'){
				i += 1;
				inum=0;
			}
			else{
				my_strcat(filter[fil_pos], ",");
				inum += 1;
			}
		}	
	}
    
    copy_array(filter,msgs,i);
    rows = row_count(filter);
    print(msgs, rows);
	printf("\n");
}

/* algorithms are fun */
