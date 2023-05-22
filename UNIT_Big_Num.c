#include <stdio.h>
#include "RSA.h"
#include <check.h>
void init(struct bigNum * x, struct bigNum * y, struct bigNum * check,int v1,int v2, struct bigNum * v3);

int mod_test(struct bigNum x,struct bigNum y);

int equals_test(struct bigNum x,struct bigNum y);

int sub_test(struct bigNum x, struct bigNum y, struct bigNum check);

int add_test(struct bigNum x, struct bigNum y, struct bigNum check);

int multi_test(struct bigNum x, struct bigNum y, struct bigNum check);

int div_test(struct bigNum x, struct bigNum y, struct bigNum check);

int pow_test(struct bigNum x, int y, struct bigNum check);

int prime_test(struct bigNum x);
//write prime test

int main(){
  //init setup
  int passed = 0;
	int skipped = 0;
	int failed = 0;
		
	struct bigNum x = {" "};// " " value is 64
  char t = (char)64;
  set_val(&x,&t,1);
  t = (char)32;
	struct bigNum y = {"@"};// @ value is 32
  set_val(&y,&t,1);
  //mod test
	if(mod_test(x,y)==1){
    printf("passed mod \n");
		passed++;
	}else{
    printf("failed mod \n");
		failed++;
	}
  //equals test
	set_val(&x,"123456789",9);
	set_val(&y,"123456789",9);
	//printf("%s == %s \n",x.num,y.num);
	if(equals_test(x,y)==1){
		printf("passed equals \n");
    passed++;
	}else{
    printf("failed equals \n");
		failed++;
	}
  //add test
	set_val(&x,"1",1); //49
	set_val(&y,"2",1); //50
	struct bigNum check = {"c"}; //99
	if(add_test(x,y,check)==1){
		printf("passed add \n");
    passed++;
	}else{
    printf("failed add \n");
		failed++;
	}
  //sub test
  t = 255;
	set_val(&x,&t,1); //50
  x = fastmult(x,x);
  t = 49;
	set_val(&y,&t,1); //49
  y = fastmult(y,y);
  t = (char) 1;
  char t2 [2] = {(char)160,(char)244};
  set_val(&check,(char*)&t2,2);
	//printBigNum(check);
  if(sub_test(x,y,check)==1){
		printf("passed sub\n");
    passed++;
	}else{
    printf("failed sub \n");
		failed++;
	}

  //multiplication test
  t = (char) 2;
  set_val(&x,&t,1);
  set_val(&y,&t,1);
  t = (char) 4;
  set_val(&check,&t,1);
  //printBigNum(check); 
	if(multi_test(x,y,check)==1){
		printf("passed multiplication \n");
    passed++;
	}else{
    printf("failed multiplication \n");
		failed++;
	}
  //div test
  init(&x,&y,&check,250,50,&check);
  t = (char) 5;
  set_val(&check,&t,1);
	if(div_test(x,y,check)==1){
		printf("passed division \n");
    passed++;
	}else{
    printf("failed division \n");
		failed++;
	}
  //pow test
  t = 3;
  set_val(&x,&t,1); 
  set_val(&check,&t,1);
  //printf("%s\n",fastpow(x,100).num);
  for (int i = 0; i < 511; i++) {
    check = fastmult(check,x);
  }
  if(pow_test(x,512,check)==1){
		printf("passed pow \n");
    passed++;
	}else{
    printf("failed pow \n");
		failed++;
	}
  //rand test
  printf("random number:");
  generate_random(&x);
  printBigNum(x);

  //prime test
  t = (char) 5;
  set_val(&x,&t,1);
  if(prime_test(x)==1){
    printf("passed prime\n");
    passed++;
  }else{
    printf("failed prime\n");
    failed++;
    return 0;
  }
  
  //results
	printf("passed %d \n",passed);
	printf("failed %d \n",failed);
  
  //prime find test
  printf("starting search\n");
  x = gen_prime();
  printf("found!\n");
  printBigNum(x);

}

void init(struct bigNum * x, struct bigNum * y, struct bigNum * check,int v1,int v2,struct bigNum * v3){
  char tmp = (char) v1;
  set_val(x,&tmp,1);
  tmp = (char)v2;
  set_val(y,&tmp,1);
  set_val(check,(char*)v3->num,num_size);
}

int mod_test(struct bigNum x,struct bigNum y){
	struct bigNum zero = {"\0"};
  //printBigNum(mod(x,y));
	struct powMap * m = malloc(sizeof *m);
  pow_Map_init(m); 
  printf("mod test\n");
  if(equals(mod(x,y,m),zero)){
		return 1;
	}
  free (m);
	return 0;
}


int equals_test(struct bigNum x,struct bigNum y){
	if(equals(x,y)==1){
		return 1;
	}
	return 0;
}

int add_test(struct bigNum x, struct bigNum y, struct bigNum check){
	if(equals(add(x,y),check)==1){
		return 1;
	}
	return 0;
}

int sub_test(struct bigNum x, struct bigNum y,struct bigNum check){
  printBigNum(sub(x,y));
  return equals(sub(x,y),check);
}

int multi_test(struct bigNum x, struct bigNum y, struct bigNum check){
  if(equals(fastmult(x,y),check)){
    return 1;
  }
  return 0;
}

int div_test(struct bigNum x, struct bigNum y, struct bigNum check){
  if(equals(fastdiv(x,y),check)){
    return 1;
  }
  return 0;
}

int pow_test(struct bigNum x, int y, struct bigNum check){
  return (equals(check,fastpow(x,y)));
}
int primecheck(int x){
  int tmp = x/2;
  for (int i = 2; i < tmp; i++) {
    if(x%i==0){
      return 0;
    }
  }
  return 1;
}
int prime_test(struct bigNum x){
  printf("starting test with: \n");
  //printBigNum(x);
  struct bigNum diff;
  big_num_init(&diff);
  printf("line 216\n");
  char t = (char) 2;
  set_val(&diff,&t,1);
  /*t = (char)11;
  set_val(&x,&t,1);*/
  //printf("line 218\n");
  for (int i = 0; i <10000; i++) {
    if(primeTest(x)!=primecheck((i*2)+5)){
      printf("error!!!! @%d",(i*2)+5);
      return 0;
    } 
    set_val(&x,(char *)add(x,diff).num,num_size);
  }
  return 1; //primeTest(x);
}

void finish(){
 return;
}


