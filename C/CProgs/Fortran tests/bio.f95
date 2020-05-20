program Bio
implicit none
!program to ask people for their bio
real :: scoree, scorem, scores
integer :: age
character :: name*20
print *,'Enter your name, age and scores in english, maths and science'
read *,name,age,scoree,scorem,scores
print *,'Name:',name
print *,'Age:',age
print *,'Scores'
print *,'Maths:',scorem
print *,'Science',scores
print *,'English',scoree
end program Bio