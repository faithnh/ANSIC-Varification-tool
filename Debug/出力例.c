#include<stdio.h>
#include<stdlib.h>

#define SIZE 6

int main(void){
	int array[SIZE] = {1,5,8,1,2,-1};
	int *ptr;
	int tmp, num, count = 1,flag = 0;
	printf("�T������������: "); scanf("%d", num);
	for(ptr = array; *ptr != 0  ; ptr++){
		
		tmp = *ptr;
		
		if(tmp == num){
			flag = 1; break;
		}else{
			count++;
		}
	}
	if(flag) printf("%d��array��%d�Ԗڂɂ���܂��B\n", num, count);
	else printf("%d�͑��݂��܂���B\n", num);

	return 0;
}

�G���[�o�͗�F
array[SIZE] = {1,5,8,1,2,-1}	array => {:size => "6", :pointer => "0"}
int *ptr; 						*ptr => {:target => "null"}
int tmp;						tmp => null
int num;						num => null
int count=1;					count => 1
int flag=0;						flag => 0
printf("�T������������:");
scanf("%d", num);				num => {:value => 0}
for init: ptr = array;			ptr => {:size => "6", :pointer => "0"}
for branch: *ptr != 0;			branch => true
tmp = *ptr;						ptr => 1
if branch: tmp == num;			branch => false
count++;						count=> 1
for inc: ptr++;					ptr => {:size => "6", :pointer => "0"}
for branch: *ptr != 0;			ptr => {:size => "6", :pointer => "1"}
tmp = *ptr;						tmp => 5
if branch: tmp == num;			branch => false
count++;						count => 2
for inc: ptr++;					ptr => {:size => "6", :pointer => "2"}
�E�E�E
for branch: *ptr != 0;
tmp = *ptr; :error				ptr => {:size => "6", :pointer => "6"}