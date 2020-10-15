import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
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
        
        Scanner oscanner = new Scanner(System.in); //added by Kuu
        System.out.println("Enter output file name: "); //added by Kuu
        String ofileName = oscanner.nextLine(); //added by Kuu
        File outputFile = new File(ofileName); //added by Kuu
        PrintWriter pw = new PrintWriter(outputFile);

        Project0Helper helper = new Project0Helper();
        
        MailAddressInterface[] myList = new ConcreteMailAddress[100];
        int size = 0;        
//        Project0Helper helper = new Project0Helper();
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
                size++; //added by Kuu
                //                System.out.println(myList[i]);                
            }
        } catch (NoSuchElementException e) {
            // end of input?
        }        
        
        helper.checkStartingOrder(myList); //added by Kuu
        
        //Sort
        RadixSort rs = new RadixSort(); //added by Kuu
        rs.radixSort(myList, size);   //added by Kuu            
       
        for (int i = 0; i <= myList.length; i++) {
            try {            	
                pw.println(myList[i].getName());
                pw.println(myList[i].getAddressLine1());
                pw.println(myList[i].getAddressLine2());
                pw.println(myList[i].getCity());
                pw.println(myList[i].getState());                
                String zipCodeStr = String.format("%05d", myList[i].getZipCode()); //added by Kuu
            	pw.println(zipCodeStr); //added by Kuu
            } catch (NullPointerException e) {
//                System.out.println("Write to output file success !!.");
                break;
            }
        }
        pw.close();   
        
        System.out.println("Name of input file: "+fileName); //added by Kuu

        helper.checkFinalOrder(myList); //added by Kuu
        
        System.out.println("Name of ouput file: "+ofileName); //added by Kuu
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

    
