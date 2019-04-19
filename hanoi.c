#include <stdio.h>
#include <stdlib.h>

int time = 0;

int hanoit(int num, char start, char temp, char end ){

   if( num > 0 )
    {
   hanoit ( num-1 , start , end , temp );
 //  printf("%c -> %c  \n" , start , end ); /* 顯示移動狀況 */
   hanoit ( num-1 , temp , start , end);
   time++;
  }
    return time;
}

void hanoi (int num, char start, char temp, char end ){

   if( num > 0 )
    {
   hanoi ( num-1 , start , end , temp );
   printf("%c -> %c  \n" , start , end ); /* 顯示移動狀況 */
   hanoi ( num-1 , temp , start , end);
   time++;
  }
}

int main(){

    time = hanoit ( 3 , 'A' , 'B' ,'C' );    /*三個盤子，以A為起始柱，以C為目標柱，以B為暫存柱*/
    printf("%d\n", time);
    hanoi ( 3 , 'A' , 'B' ,'C' );    /*三個盤子，以A為起始柱，以C為目標柱，以B為暫存柱*/
    return 0;

}
