      program GudGud
      !to print (1)+(1+2)+(1+2+3)...
      implicit none
      integer a,n,i,j
      a=0
      write(*,*)'Enter no of repetitions of pattern'
      read(*,*)n
      do 100, i=1,n
        do 200,j=1,i
          a=a+j
200   continue
100   print *,a
      end program GudGud