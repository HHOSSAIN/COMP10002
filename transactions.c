/* Processing credit card and transaction records and identifying
 * fraudulent transactions.
 * 
 * Coded by student name:HASNE HOSSAIN, ID:1102602 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define STAGE_H "=========================Stage %d=========================\n"
#define STAGE_NUM_ONE 1							/* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4

#define MAX_CARD_CHARS (8+1)
#define MAX_TRANSACTION_CHARS (12+1)
#define MAX_NUM_CARDS 100
#define MAX_NUM_CARDS2 1000
#define MAX_TRANSACTIONS 20
#define END_CARD "%%%%%%%%%%"

typedef struct{
    char card_id[MAX_CARD_CHARS]; 
    int daily_limit;
    int transaction_limit;
    int year,month,day;
    int sum;
}credit_card_t;

typedef struct{
    char transID[MAX_TRANSACTION_CHARS];
    char card_id[MAX_CARD_CHARS];
    int year,month,day,hours,mins,secs; 
    int transaction_amount;
}transaction_t;

typedef struct node node_t;

struct node {
	transaction_t *data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

/*...............function prototype.......................................*/
void stage_one (credit_card_t *cards, int num_card);
void stage_two (credit_card_t *cards, int *num_card);
void stage_three (list_t *trans,transaction_t *cards, int *num_card);
void stage_four(list_t *trans,credit_card_t *cards,int num_card, int num_card2);

void print_stage_header(int stage_num);
char *read_1_line(int len);
void all_records1(credit_card_t *cards, int i);
void all_records2(transaction_t *cards, int i);
int binary_search(credit_card_t *A, int lo, int hi, char *key, int *locn);
void validity_check(credit_card_t *cards, node_t *new, int locn);

list_t *make_empty_list(void);
list_t *insert_at_foot(list_t *list, transaction_t *value);

/*..................MAIN FUNCTION.............................................*/

int main(int argc, char* argv[]){
    credit_card_t *cards;
    transaction_t *cards2;
    list_t *trans = make_empty_list(); 

    int num_card = 0;
    int num_card2 = 0;
    
    cards = (credit_card_t*)malloc(MAX_NUM_CARDS * sizeof(credit_card_t));
    assert(cards != NULL);
    
    cards2 = (transaction_t*)malloc(MAX_NUM_CARDS2 * sizeof(transaction_t));

    stage_one(cards, num_card);
    num_card++;
    
    stage_two (cards, &num_card);
    
    stage_three (trans, cards2, &num_card2);
    
    stage_four(trans, cards, num_card, num_card2);
    
    free(cards);
    cards = NULL;
    free(cards2);
    cards2 = NULL;
    free(trans);
    trans = NULL;
    return 0;
}

/*...................FUNCTIONS USED IN THE STAGES.............................*/

/* prints stage header */
void print_stage_header(int stage_num) {
	printf(STAGE_H, stage_num); 
}

/* makes a string from 1 line of input until there is a space character */
char *read_1_line(int len) {
	int index=0;
    char c=0;
    char *id = malloc(len * sizeof(char));
    assert(id);
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r') && c != ' '){
        id[index++] = c;
	}
	id[index] = '\0';
    return id;
}

/* stores all details of one credit card */
void all_records1(credit_card_t *cards, int i) {
    int daily_l=0;
    int trans_l=0;
    char * result = read_1_line(MAX_CARD_CHARS);
    strcpy(cards[i].card_id, result);
  
    if (scanf("%d %d\n", &daily_l, &trans_l) == 2){
        cards[i].daily_limit = daily_l;
        cards[i].transaction_limit = trans_l;
    }
    cards[i].sum = 0;
    cards[i].year = 0;
    cards[i].month= 0;
    cards[i].day= 0;
}

/*stores all details of one transaction */
void all_records2(transaction_t *cards, int i) {

    int amount = 0, y=0,mon=0,d=0,h=0,min=0,sec=0;
    char * result1 = read_1_line(MAX_TRANSACTION_CHARS);
    strcpy(cards[i].transID, result1);
    char * result2 = read_1_line(MAX_CARD_CHARS);
    strcpy(cards[i].card_id, result2);
 
    if(scanf("%d:%d:%d:%d:%d:%d ", &y,&mon,&d,&h,&min,&sec) == 6){
        cards[i].year = y;
        cards[i].month = mon;
        cards[i].day = d;
        cards[i].hours = h;
        cards[i].mins = min;
        cards[i].secs = sec;
    }

    if (scanf("%d\n", &amount) == 1){
        cards[i].transaction_amount = amount;
    }
}

/* checks whether transactions are crossing any limit or not */
void validity_check(credit_card_t *cards, node_t *new, int locn){
    if( (cards[locn].sum > cards[locn].daily_limit) && 
       (new->data->transaction_amount > cards[locn].transaction_limit) ){
                
        printf("%s             OVER_BOTH_LIMITS\n",new->data->transID);
    }
    else if( (cards[locn].sum > cards[locn].daily_limit) && 
            (new->data->transaction_amount < cards[locn].transaction_limit) ){
    
            printf("%s             OVER_DAILY_LIMIT\n",new->data->transID);
    }
    else if( (cards[locn].sum < cards[locn].daily_limit) && 
            (new->data->transaction_amount > cards[locn].transaction_limit) ){
    
            printf("%s             OVER_TRANS_LIMIT\n",new->data->transID);
    }
    else{
            printf("%s             IN_BOTH_LIMITS\n",new->data->transID);
    }
}

/*........FUNCTIONS BELOW BY ALISTAIR MOFFAT,MODIFIED ACCORDING TO NEED.......*/

/*finds the location of a word from a list of words and tells if word found*/
int
binary_search(credit_card_t *A, int lo, int hi, 
		char *key, int *locn) {  
	int mid=0, outcome=0;
    
	if (lo>=hi) {
		return 0;
	}
	mid = (lo+hi)/2;
	if ((outcome = strcmp(key, A[mid].card_id)) < 0) {
		return binary_search(A, lo, mid, key, locn);
	} else if (outcome > 0) {
		return binary_search(A, mid+1, hi, key, locn);
	} else {
		*locn = mid;
		return 1;
	}
}

/*.......................NODE FUNCTIONS.......................................*/

/* inserts data at foot and helps to extend list structure */
list_t 
*insert_at_foot(list_t *list, transaction_t *value) {  
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	
	assert(list!=NULL && new!=NULL); 
	new->data = value;
	new->next = NULL;
    
	if (list->head==NULL) {
		/*  this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list; 
}

/* creates an empty list*/
list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}
/*...........END OF FUNCTIONS FROM ALISTAIR MOFFAT............................*/


/*......................STAGE FUNCTIONS...................................... */

/* reads and outputs one credit card record */
void stage_one (credit_card_t *cards, int num_card) {
    print_stage_header(STAGE_NUM_ONE);
    all_records1(cards, num_card); 
    printf("Card ID: %s\nDaily limit: %d\nTransaction limit: %d\n\n", 
    cards[num_card].card_id, cards[num_card].daily_limit, 
    cards[num_card].transaction_limit);
}

/* stores all the credit card records and outputs the number of records, average
   daily limit per card and credit card with largest transaction limit */
void stage_two (credit_card_t *cards, int *num_card) {
    print_stage_header(STAGE_NUM_TWO);

    int sum = cards[0].daily_limit, limit=0; 
   
    int i=0;
    while((((strcmp(cards[i].card_id, END_CARD)) != 0))&& 
        (*num_card <= MAX_NUM_CARDS)){
        
        all_records1(cards, *num_card);
        
        if ((strcmp(cards[*num_card].card_id, END_CARD)) != 0) {
            
            sum += cards[*num_card].daily_limit;
               
        }
        
        *num_card += 1; 
        i += 1;
    }
    
    *num_card = i; 
    float avg = (float)sum / *num_card;
    int max=0; char maxID[MAX_CARD_CHARS]; maxID[0]='\0';
    strcpy(maxID, cards[0].card_id);
    
    for(int k=0; k<*num_card; k++){
		
        limit = cards[k].transaction_limit;
		
        if ((limit > max) || (limit == max && 
            (strcmp(maxID,cards[k].card_id) > 0))){ 
			
            max = limit;                                                            
            strcpy(maxID, cards[k].card_id);
		}
	}
    
    printf("Number of credit cards: %d\n", *num_card);
    printf("Average daily limit: %.2f\n", avg);
    printf("Card with the largest transaction limit: %s\n", maxID);
    printf("\n");
}

/* reads the transactions, stores them in linked data structure and output their
   ids */
void stage_three (list_t *trans,transaction_t *cards, int *num_card) {
    print_stage_header(STAGE_NUM_THREE);

    all_records2(cards,*num_card);      
  
    while (cards[*num_card].transID[0] != '\0') {
        
        trans = insert_at_foot(trans, &(cards[*num_card])); 
        printf("%s\n", trans->foot->data->transID);
        *num_card += 1;
        all_records2(cards,*num_card);
    }
    
    printf("\n");
}

/* check whether a transaction may be fraudulent */
void stage_four(list_t *trans,credit_card_t *cards, int num_card, 
                int num_card2){
    
    print_stage_header(STAGE_NUM_FOUR);
    node_t *new; 
    new = trans->head; 
    int lo=0, locn=0,i=0;
    
    for(i=0;i<num_card2; i++){ 
        assert(binary_search(cards ,lo,num_card, new->data->card_id, &locn));
        
        if((new->data->year == cards[locn].year && 
            new->data->month == cards[locn].month && 
            new->data->day == cards[locn].day) || cards[locn].year==0 ) {
            
            if(cards[locn].year == 0){
                cards[locn].year = (new->data->year);
                cards[locn].month = (new->data->month);
                cards[locn].day = (new->data->day);
            }
            cards[locn].sum += (new->data->transaction_amount);
            
            validity_check(cards, new, locn);
            
        }
        
        else{
            cards[locn].year = (new->data->year);
            cards[locn].month = (new->data->month);
            cards[locn].day = (new->data->day);
            cards[locn].sum = (new->data->transaction_amount);
            
            validity_check(cards, new, locn);
            
        }
        new = new->next;
    }
}

/* In stage_four, it goes through n transactions, so, it passes through the 
for loop n times. At each loop, the location of the cardID is searched within 
m credit card records. Since this is done using binary search, the approximate 
time complexity of each binary search is O(logm). Therefore, the overall 
average approximate time complexity of stage_four is O(nlogm) as there are 
n binary searches*/

/*............................DONE............................................*/

/* algorithms are fun */