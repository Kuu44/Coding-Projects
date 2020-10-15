import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class MailSorter {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter file name: ");
        String fileName = scanner.nextLine();
        File file = new File(fileName);
// MailAddressInterface[] myList;
        try {
            scanner = new Scanner(file);
        } catch (FileNotFoundException e) {
            System.out.println("File not found!!");
        }

        File outputFile = new File("output.txt");
        PrintWriter pw = new PrintWriter(outputFile);

        MailAddressInterface[] myList = new ConcreteMailAddress[100];
        Project0Helper helper = new Project0Helper();
        try {
            for (int i = 0; i < 100; i++) {
                String name = scanner.nextLine();
                String address1 = scanner.nextLine();
                String address2 = scanner.nextLine();
                String city = scanner.nextLine();
                String state = scanner.nextLine();
                int zipcode = scanner.nextInt();
                scanner.nextLine();  // get rid of the rest of the line after the zip code
                myList[i] = new ConcreteMailAddress(name, address1, address2, city, state, zipcode);
                System.out.println(myList[i]);
            }
        } catch (NoSuchElementException e) {
            // end of input?
        }

        for (int i = 0; i <= myList.length; i++) {
            try {
                pw.println(myList[i].getName());
                pw.println(myList[i].getAddressLine1());
                pw.println(myList[i].getAddressLine2());
            } catch (NullPointerException e) {
                System.out.println("Write to output file success !!.");
                break;
            }
        }
        pw.close();
    }

  /* public static void radixSort(MailAddressInterface[] array) {
    RadixSort.sort(array,10);
    }
    public static void sort(int[] array, int radix) {
    	if (array.length == 0) {
    		return;
    	}
    	int minValue = array[0];
    	int maxValue = array[0];
    	final int RADIX = 10;
        ConcreteMailAddress[][] bins = new ConcreteMailAddress[10][100];
        // bin number: 1, 2, 3, 4, 5
        for (int i = 0; i <=5; i++) {
       
        	frequency[zipcode]++;
        }
        for (int i=1;i<RADIX;i++) {
        	frequency[i]+= frequency[i-1];
        }
           
      
        placement = placement*RADIX;
              }
       
       
            } */
}

    
