#include <stdio.h>
#include <time.h>

#include "NUMMATH.h"

/*Reason for making this 
 * this will allow for end users of your landing page to send credentials securely
 * wrap request in server public key with client private key
 * */
/*
 * TO-DO
 * Generate random number 
 * Check if prime move on +2 (find better alg) think +6+-2
 *
 *
 * */

int primeTest(struct bigNum x){
  struct bigNum result;
  big_num_init(&result);
  char tmp = (char) 2;
  set_val(&result,&tmp,1); 
  struct bigNum x_copy = x;
  struct bigNum carry;
  big_num_init(&carry);
  carry.num[0] = (char) 1;
  set_val(&x,(char *)(sub(x,one).num),num_size);
  int step =0;
  //result = fastpow(result,512);
  struct powMap * m = malloc(sizeof *m);
  pow_Map_init(m);
  while(comp(x,one)==1){
    step++;
    if(step%1000==0){
      //printf("m length: %d\n",m->length);
      printf("multiply round %d\n",step);
      /*printBigNum(result);
      printBigNum(x_copy);*/
    }
    //printf("line 39\n");
    if(x.num[0]%2==1){
      //printf("line 44\n");
      printf("carry::::\n");
      printBigNum(result);
      printf("*");
      printBigNum(carry);
      set_val(&carry,(char*)fastmult(result,carry).num,num_size);
      if(comp(carry,x_copy)==1){
        set_val(&carry,(char*)mod(carry,x_copy,m).num,num_size); 
      }
      printf("=");
      printBigNum(carry);
      //  printf("line 46\n");
    }
    //printf("line 46\n");
    set_val(&result,(char*)fastmult(result,result).num,num_size);
    //printBigNum(result);
    if(comp(result,x_copy)==1){
      set_val(&result,(char*)mod(result,x_copy,m).num,num_size); 
    }
    //printf("line 51\n");
    bigNum_shift(&x,1,-1);
  }
  //printf("line 52\n");
  printf("--------result----------");
  //printBigNum(result);
  if(equals(carry,zero)==0){
    printf("combine\n");
    //this doesn't seem to be changing results value
    printf("before:");
    printBigNum(result);
    printf("*");
    printBigNum(carry);
    set_val(&result,(char*)fastmult(result,carry).num,num_size);
    printf("after mult:");
    printBigNum(result);
    set_val(&result,(char*)mod(result,x_copy,m).num,num_size);
    printf("after mod:");
    printBigNum(result);
  }
  printBigNum(x_copy);
  printBigNum(result);
  printBigNum(carry);
  printf("--------finish----------\n");
  for (int i = 0; i < m->length; i++) {
    printf("index: %d",i);
    printBigNum(m->table[i]);
  } 
  free(m);

  if(equals(result,one)){
    return 1;
  }
  return 0;
}

struct bigNum gen_prime(){
 struct bigNum x;
 big_num_init(&x);
 generate_random(&x);
 /*char t = (char) 5;
 set_val(&x,&t,1);*/
 if(x.num[0]%2==0){
   x = add(x,one);
 }
 /*printBigNum(x);*/
 primeTest(x);
 struct bigNum two = add(one,one);
 int count =0;
 while(primeTest(x)!=1){
   x = add(x,two);
   count++;
   if(count%2==0){
     printf("count = %d\n",count);
   }
 }
 return x;
}
