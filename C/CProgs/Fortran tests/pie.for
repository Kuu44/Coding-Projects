      program GudGud
      implicit none
      real n,b,c
      integer a
      n=0
      do 100, a=0,24
        b=((-1)**a)
        c=(2.0*a+1.0)
        n=n+4*(b/c)
100   continue
      print *,n
      end program GudGud