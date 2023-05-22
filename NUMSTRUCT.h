#define num_size 2048 
#define key_size 512 
#define BLOCK_SIZE 8
#define table_size 6000
#include <stdlib.h>
#include <string.h>
struct bigNum{
	unsigned char num [num_size];
  long int length;
};
struct bigNum zero = {(char) 0};
struct bigNum one = {(char) 1};

struct bigNode{
	struct bigNum val;
	struct bigNode * next;
};
struct powList{
	struct bigNode * first;
	struct bigNode * curr;
  int length;
};
struct powMap{
  struct bigNum table[table_size];
  int length;
};

int comp(struct bigNum x, struct bigNum y);
void add_val(struct powList * l, struct bigNum x);
struct bigNum set_val(struct bigNum * x, char * y, int char_size);
void printBigNum(struct bigNum x);
//init
void big_num_init(struct bigNum* num) {
  memset(num->num, 0, num_size);
}
void pow_List_init(struct powList * ll){
  ll->length = 0;
}
void pow_Map_init(struct powMap * m){
  m->length =0;
  for (int i = 0; i < table_size; i++) {
    big_num_init(&m->table[i]);
  }
}
//powList functions
struct bigNum at(struct powList l, int index){
	l.curr = l.first;
	for(int i =0;i<index;i++){
		l.curr = l.curr->next;
	}
	return l.curr->val;
}

void add_val(struct powList * l, struct bigNum x){
  if(l->first == NULL){
  l->first = malloc(sizeof *l->first);
    set_val(&l->first->val,x.num,num_size);
    l->curr = l->first;
    l->length =1;
  }else{
    l->curr->next = malloc(sizeof *l->curr->next);
    set_val(&l->curr->next->val,x.num,num_size);
    l->curr = l->curr->next;
    l->length++;
  }
}
//powMap functions
void add_val_map(struct powMap * m, struct bigNum x){
  if(m->length == 0){
    set_val(&m->table[m->length++],(char*)x.num,num_size);
    m->table[m->length-1].length = x.length;
  }else if(comp(x,m->table[m->length-1])==1){
    set_val(&m->table[m->length++],(char*)x.num,num_size);
    m->table[m->length-1].length = x.length;
  }
}
struct bigNum at_map(struct powMap * m, int index){
  if(index>=m->length){
    big_num_init(&zero);
    return zero;
  }
  return m->table[index];
}

//bigNum functions
void generate_random(struct bigNum * x){
	//used to generate key uses key_size to allow for opperations 
  //checking purposes
  srand(time(NULL));
  for (int i = 0; i <=key_size; i++) {
	 x->num[i] = (char)(rand()%512);
	}
}

struct bigNum set_val(struct bigNum * x, char * y,int char_size){
  for(int i =0;i<num_size;i++){ 
    if(i<char_size){
			x->num[i] = y[i];
		}else{
      x->num[i] = 0;
			/*future
       * memset(y+i+1,(char)0,(num_size-(i+1))*sizeof(char));
      break;*/
		}
	}
	return *x;
}
void set_length(struct bigNum *x){
  int start = x->length/8;
  int end = -1;
  int diff = -1;
  for (int i = num_size-1; i > -1; i--) {
    if(x->num[i]!=0){
      int tmp =0;
      int x_tmp = x->num[i];
      for (int j = 7; j >=0; j--) {
        if(x_tmp!=0){
          x_tmp = x_tmp/2;
          tmp++;
        }
      }
      x->length = (i*8)+(tmp);
      return;
    }
  }
  if(x->num[0]==0){
    x->length = 0;
  }
}

void printBigNum(struct bigNum x){
  int lead = 0;
  for (int i = num_size-1; i >= 0; i--) {
    if(x.num[i]==0&&(lead==0)){

    }else{
      if(lead%2==0){
        printf(" ");
        if(lead%40==0){
          printf("\n");
        }
      }
      printf("%02x",x.num[i]);
      lead++;
    }
  }
  if(lead==0){
    printf("0");
  }
  printf("\n");
}

//could be wrong but should work
void bigNum_shift(struct bigNum *num, int bits, int shift_dir) {
  char carry =0;
  int start = shift_dir > 0 ? 0 : num_size - 1;
  int stop = shift_dir > 0 ? num_size : -1;
  //printf("%d,%d\n",start,stop);
  for (int i = start; i != stop; i = i+shift_dir) {
    char tmp = carry;
  if(shift_dir==-1){//shift right
      carry = num->num[i]<<(BLOCK_SIZE-bits);
      num->num[i]>>=bits;
      num->num[i] |= tmp;
    }else if(shift_dir == 1){//shift left 
      carry = num->num[i]>>(BLOCK_SIZE-bits);
      num->num[i]<<=bits;
      num->num[i] |=tmp;
    }
    
  }

}

