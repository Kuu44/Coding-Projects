      program GudGud
      implicit none
      real a,b,c,d,e,r1,r2,rel,cmp
      write(*,*)'Enter the coefficients in order'
      read(*,*)a,b,c
      if (a .eq. 0) then
        print *,'The coefficient of square cant be zero'
        goto 999
      endif
      d=((b**2)-4*a*c)
      e=b/(2*a)
      if (d .eq. 0) then
        write(*,*)'Roots are real and equal'
        r1=e
        write(*,*)'They are both:',r1
       elseif (d .gt. 0) then
         write(*,*)'Roots are real and unequal'
         r1=e+(sqrt(d)/(2*a))
         r2=e-(sqrt(d)/(2*a))
         write(*,*)'They are',r1,'and',r2
       else
         write(*,*)'Roots are imaginary'
         rel=e
         cmp=(sqrt(abs(d))/(2*a))
         write(*,100)1,rel,cmp,2,rel,(0-cmp)
100   format('Root ',I1,' is',2x,f6.3,1x,f6.3,'i')
      endif
999   continue
      stop
      end program GudGud