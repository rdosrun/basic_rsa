#include "NUMSTRUCT.h"


struct bigNum fastpow(struct bigNum x,int y);


int equals(struct bigNum x, struct bigNum y){
  for (int i = 0; i < num_size; i++) {
    if(x.num[i]==y.num[i]){
      continue;
    }
    return 0;//nums are not equal
  }
  return 1;//nums are equal
}

int comp(struct bigNum x, struct bigNum y){
  /*
   * if x > y
   *  return 1;
   * if x < y 
   *  return -1;
   * return 0;
   * */
  for(int i = num_size -1;i>=0;i--){
    if(x.num[i]>y.num[i]){
      return 1;//x is greater than y
    }else if(x.num[i]<y.num[i]){
      return -1;//y is greater than x
    }
  }
  return 0;
}

struct bigNum add (struct bigNum x,struct bigNum y){
	//printf("%s + %s",x.num,y.num);
	
  int length = x.length>y.length ? x.length : y.length;
  if(length<=0){
    length = num_size;
  } 
  if(length<0 || length>num_size){
    length = num_size;
  }
	struct bigNum total;
	big_num_init(&total);
  int sum = 0;
	int carry =0;
  for(int i =0;i<length || carry != 0;i++){
		sum = (x.num[i]+y.num[i]+carry);
		total.num[i] = sum>255? sum%256 : sum;
		carry = (int)( (sum-total.num[i])/256);
	}
	//printf("total = %d \n",(int)total.num[1]);
	return total;
}

struct bigNum sub (struct bigNum x, struct bigNum y){ 
	//printf("%s + %s",x.num,y.num);
  struct bigNum total;
  big_num_init(&total);
  int length = x.length>y.length ? x.length : y.length;
  if(length<=0){
    length = num_size;
  }
  int borrow = 0;
  int diff =0;
  if(length<0 || length>num_size){
    length = num_size;
  }
  //printf("length: %d",length);
  for (int i = 0; i < length || borrow == 1; i++) {
    diff = x.num[i] - y.num[i] - borrow;
    if(diff<0){
      diff += 256;
      borrow =1;
    }else{
      borrow =0;
    }
    total.num[i] =(unsigned char) diff;
  }

  return total;
}

struct bigNum fastmult(struct bigNum x, struct bigNum y) {
  struct bigNum result;
  big_num_init(&result);
  int count =0;
  while (comp(y, zero)==1) {
    if (y.num[0]%2==1) {
      set_val(&result,(char*)add(result, x).num,num_size);
    }
    bigNum_shift(&x,1,1);
    bigNum_shift(&y,1,-1);
    count++;
  }
  //printf("mult rounds: %d\n",count);
  return result;
}

struct bigNum fastdiv(struct bigNum x, struct bigNum y){
   // x/y
   /*
   *algorithm
   1. make a list
   2. double x until bigger than y
   3. store x in list
   4. sub x from y if x<y
   5. add ll(index-1) to result
   6. return result
   * */
  struct powList * ll = malloc(sizeof *ll);
  struct bigNum result;
  big_num_init(&result);
  struct bigNum two;
  big_num_init(&two);
  char t = (char) 2;
  set_val(&two,&t,1);
  int count =0;

  while(comp(y,x)!=1){
    add_val(ll,y);
    y = add(y,y);
    count++;
  }
  //printf("count=%d\n",count);
  for (int i = count-1; i >=0; i--) {
    if(comp(at(* ll,i),x)!=1){
      x = sub(x,at(*ll,i));
      result = add(result,fastpow(two,i));
  //    printBigNum(result);
    } 
  }
  free(ll);
  return result;
}

struct bigNum mod(struct bigNum x,struct bigNum y,struct powMap * m){
  int count = m->length;
  set_length(&y);
  int b = y.length;
  if(equals(m->table[0],zero)!=1){
    set_val(&y,(char*)at_map(m,count-1).num,num_size);
  }
  while(comp(y,x)!=1){
    set_length(&y);
    add_val_map(m,y);
    bigNum_shift(&y,1,1);    
  }
  //printf("y = %d, x = %d\n",y.length,x.length);
  count = m->length;
  int test_count =0;
  set_length(&x);
  int index =x.length - b;
  /*printf("**********\n\n\n\n\n\n---------------");
  printBigNum(x);
  printBigNum(m->table[0]);*/
  while (index>=0) {
    test_count++;
    if(test_count%10000==0){
      printf("help!!!\n");
      printf("count: %d\n",count);
      printf("index: %d\n",index);
    }
    if(index>=count){
      index = count-1;
      if(index<0){
        return x;//check
      }
    }
    long int tmpt =0;
    //needs optimization

        /*printf("x=%d\n",x.length);
        //printBigNum(x);
        printf("map=%d\n",b);*/
        //printBigNum(at_map(m,index));
    while(comp(x,at_map(m,index))==-1){
        index--;
        if(index<0){
          //printf("test count = %d\n",test_count);
          return x;
        }
        count = index;
        tmpt++;
        if(tmpt%4==0){
          //printf("tmpt: %d",tmpt);
        }
    }
    if(tmpt>5000){
      printf("tmp test count =%d\n",tmpt);
    }
    set_val(&x,(char*)sub(x,at_map(m,index)).num,num_size);
    //test_count++;
    set_length(&x);
    //printBigNum(x);
    index = x.length-b;
    //printf("index: %d \n",index);
  }
  //printBigNum(x);
  //printf("test count = %d\n",test_count);
  return x; 
}


struct bigNum fastpow(struct bigNum x,int y){
	struct bigNum result;
	big_num_init(&result);
  result.num[0] = (char) 1;
	//printf("start pow");
  while(y>0){
    if(y%2==1){
      result = fastmult(result,x);
      y--;
    }
    x = fastmult(x,x);
    y= y/2;

	}
  return result;//replace
}





