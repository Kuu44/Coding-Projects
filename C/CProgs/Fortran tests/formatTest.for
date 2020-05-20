      program start
      implicit none
      integer a
      real r
      character name*10
      double precision d
      !complex x

      read *,a,r,name,d
!1     format(I3,F5.2,A10,D11.6)
      !read *,x
      write(*,100) a,r,name,d
100   format(1x,'Int=',2x,I4,/,'Real=',F6.2,/,
     c'Name=',A,/,'Precise=',D11.8)
      stop
      end program start   