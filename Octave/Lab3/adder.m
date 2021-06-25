function [s, c] = adder (n1, n2)
    c = 0;
    maxLength = max(length(n1),length(n2));
	  s = zeros(1, maxLength);
    n1=[zeros(1, maxLength-length(n1)),n1];
    n2=[zeros(1, maxLength-length(n2)),n2];
    for i = length(n1) : -1 : 1
		  [s(i), c] = FullAdder(n1(i), n2(i), c);
    endfor
endfunction
