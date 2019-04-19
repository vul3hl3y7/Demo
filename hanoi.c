#include <stdio.h>
#include <stdlib.h>

int time = 0;

int hanoit(int num, char start, char temp, char end ){

   if( num > 0 )
    {
   hanoit ( num-1 , start , end , temp );
 //  printf("%c -> %c  \n" , start , end ); /* ��ܲ��ʪ��p */
   hanoit ( num-1 , temp , start , end);
   time++;
  }
    return time;
}

void hanoi (int num, char start, char temp, char end ){

   if( num > 0 )
    {
   hanoi ( num-1 , start , end , temp );
   printf("%c -> %c  \n" , start , end ); /* ��ܲ��ʪ��p */
   hanoi ( num-1 , temp , start , end);
   time++;
  }
}

int main(){

    time = hanoit ( 3 , 'A' , 'B' ,'C' );    /*�T�ӽL�l�A�HA���_�l�W�A�HC���ؼЬW�A�HB���Ȧs�W*/
    printf("%d\n", time);
    hanoi ( 3 , 'A' , 'B' ,'C' );    /*�T�ӽL�l�A�HA���_�l�W�A�HC���ؼЬW�A�HB���Ȧs�W*/
    return 0;

}
