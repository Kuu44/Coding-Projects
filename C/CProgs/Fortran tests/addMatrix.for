      program GudGud
      implicit none
      integer mat1(50,50),mat2(50,50),res(50,50)
      integer i,j,m,n
      write(*,*)'Enter Size of matrix(rows,columns)'
      read(*,*)m,n
      do 100, i=1,m
        do 200, j=1,n
        write(*,800)i,j
       read(*,*)mat1(i,j)
200   continue
100   continue
      do 300, i=1,m
        do 400, j=1,n
        write(*,800)i,j
800     format('Enter the',1x,I2,1x,'x',1x,I2,1x,'element')
        read(*,*)mat2(i,j)
400   continue
300   continue
      do 500, i=1,m
        do 600, j=1,n
        res(i,j)=mat1(i,j)+mat2(i,j)
600   continue
500   continue
      write(*,*)'The result is'
      do 700, i=1,m
        write(*,*)(res(i,j),j=1,n)
700   continue
      end program GudGud