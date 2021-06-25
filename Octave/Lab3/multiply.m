function [result] = multiply (n1,n2)
  maxLength = max(length(n1),length(n2));
  sn1=[n1];
  sum = zeros(1,2*maxLength);
  for i= length(n2): -1: 1
    if(n2(1) == 1)
      [sum, carry]= adder(sum,sn1);
    endif
    sn1=[sn1,0];
  endfor
  result = sum;
endfunction
#[result]=multiply([1,0,1,0],[1,1])