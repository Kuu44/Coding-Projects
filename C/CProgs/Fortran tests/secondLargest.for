      program GudGud
      !to find largest, second largest and smallest number
      implicit none
      integer a(100),i,j,n,temp
      write(*,*)'Enter total number of values to compare(<100)'
      read(*,*)n
      do 100, i=1,n
        write(*,*)'Enter the ',i,'th value'
        read(*,*)a(i)
100   continue
      do 200, i=1,(n-1)
        do 300, j=i+1,n
          if (a(i) .lt. a(j)) then
            temp=a(i)
            a(i)=a(j)
            a(j)=temp
            !print *,temp
          endif
300   continue
200   continue
      print *,'The second largest number is',a(2)
      print *,'The largest number is',a(1)
      print *,'The smallest number is',a(n)
      !write(*,*)a(2)
      end program GudGud