      program GudGud
      !to transpose a matrix and display
      implicit none
      integer mat1(50,50),tran(50,50)
      integer i,j,m,n
      write(*,*)'Enter Size of matrix(rows,columns)'
      read(*,*)m,n
      do 100, i=1,m
        do 200, j=1,n
        write(*,800)i,j
       read(*,*)mat1(i,j)
200   continue
100   continue
      do 500, i=1,m
        do 600, j=1,n
        tran(j,i)=mat1(i,j)
600   continue
500   continue
      write(*,*)'The transpose of'
      do 700, i=1,m
        write(*,*)(mat1(i,j),j=1,n)
700   continue
      write(*,*)'is'
      do 900, i=1,n
        write(*,*)(tran(i,j),j=1,m)
900   continue
800     format('Enter the',1x,I2,1x,'x',1x,I2,1x,'element')
      end program GudGud