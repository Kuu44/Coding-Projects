import java.util.Scanner;
public class Main {
public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	int initialVal = 0;
	int endVal = 0;
 
	boolean ValidInput = false;
	while(!ValidInput) 	{ //whole block changed by Kuu
		System.out.print("Range of Input: ");
		String input = in.nextLine();
		String[] inputArray = input.split(" "); 
		if (inputArray.length !=2) { 
			System.out.println("Invalid input, try again");			
		continue;
		}
		
		initialVal=Integer.parseInt(inputArray[0]);
		endVal=Integer.parseInt(inputArray[1]);
		
		if(initialVal<=0 || endVal<=0) {
			System.out.println("All values must be greater than zero. Try Again.");
			ValidInput = false;
		}
		else if(initialVal > endVal) {
			System.out.println("First number is larger than second number. Try Again.");
			ValidInput = false;
		}
		else { 
			ValidInput = true;
		}
	}
	
	 System.out.println("Palidromes");	 	
	 System.out.println("Decimal\tBinary");
	 for(int i=initialVal; i<=endVal; i++) {
		 if (palindrome(i,2) && palindrome(i,10)) { //changed by Kuu
			 System.out.print(i+"\t");
			 CustomStack binary=buildCustomStack(i,2);
			 while(!binary.items()) {
				 System.out.print(binary.pop());
			 }
			 System.out.print('\n');
		 }
	 }
}
private static boolean palindrome(int num, int base) {
	CustomStack stack = buildCustomStack(num,base);
	CustomStack reverse = stack.getReverseStack();
	int initialStackSize = stack.size();
	
for (int i=0; i<initialStackSize /2; i++) {
	if(stack.pop() != reverse.pop()) {
		return false;
	}
}
return true;
}

 private static CustomStack buildCustomStack(int i, int base) {
	CustomStack rem = new CustomStack();

	while (i>0) {
		rem.push(i % base);		
		i= i/base;
	}
	return rem;
 } 
}
