import java.util.Stack;
import java.util.ArrayList;
import java.util.List;

public class CustomStack {
	private List<Integer> intList = new ArrayList<>();

	public int pop() {
		return intList.remove(intList.size() - 1);
	}
	public void push(int value) {
		intList.add(value);
	}
	public int size() {
		return intList.size();
	}
	public Boolean items() {
		return intList.isEmpty();
	}
	public CustomStack getReverseStack() {
	CustomStack reverse = new CustomStack();	
	for(int i=intList.size()-1; i>=0;i--) {
		//System.out.println("Added Index:" + i);
		reverse.push(intList.get(i));
	}
	return reverse;
	}
}
