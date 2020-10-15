

/**
 *
 */

import java.util.*;
import java.io.*;
/**
 * @author Jerry Heuring
 *  Test class for the Project 0
 */
public class Project0Helper {
    protected ArrayList<Integer> zipList;
    long startTime, endTime;
    int outOfOrder, missingZip;
    /**
     * Constructor -- does initial setup and initialization.
     */
    public Project0Helper() {
        zipList = new ArrayList<Integer> (100);
        startTime = 0;
        endTime = 0;
        outOfOrder = 0;
        missingZip = 0;
    }

    /**
     * This checks the initial group of addresses and starts the
     * timer for the run.
     * @param mailingList  The list of addresses in their original order.
     */
    public void checkStartingOrder(MailAddressInterface mailingList[]) {
        for (int i = 0; i < mailingList.length; i++) {
            if (mailingList[i] != null) {
                zipList.add(mailingList[i].getZipCode());
            }
        }
        startTime = System.currentTimeMillis();
    }

    /**
     * This method will check for some error conditions in the data
     * such as addresses not in ascending order and mismatches in terms
     * of zip codes.
     * It also outputs the time for the sort.
     *
     * @param mailingList  The list of addresses in sorted order.
     */
    public void checkFinalOrder(MailAddressInterface mailingList[]) {
        int finalListSize = mailingList.length;

        endTime = System.currentTimeMillis();
        for (int i = 0; i < mailingList.length; i++) {
            if (mailingList[i] == null) {
                finalListSize = i;
                break;
            }
        }

        if (zipList.size() != finalListSize) {
            System.out.println("Final list size does not match initial list size!");
            System.out.println("Initial List Size = " + zipList.size() );
            System.out.println("Final List Size = " + finalListSize);
        } else {
            System.out.println("Initial and Final list sizes match.");
        }

        for (int i=1; i < finalListSize; i++) {
            if (mailingList[i-1].getZipCode() > mailingList[i].getZipCode()) {
                System.out.println("Zip Code Out of Order");
                System.out.println("Address " + (i-1));
                System.out.println(mailingList[i-1]);
                System.out.println("Address " + (i));
                System.out.println(mailingList[i]);
                outOfOrder++;
            }
        }

        zipList.sort(null);
        for (int i = 0; i < finalListSize; i++) {
            if (mailingList[i].getZipCode() != zipList.get(i).intValue()) {
                System.out.println("Expecting to see zip code "+zipList.get(i).intValue());
                System.out.println("Found: ");
                System.out.println(mailingList[i]);
                missingZip++;
            }
        }

        System.out.println("Time Taken = "+(endTime - startTime)+" msec");
    }
    /**
     * Main program reads in a test file and uses it.  The class
     * ConcreteMailClass implements the MailAddressInterface.  The
     * ConcreteMailClass is NOT supplied -- you need to make your
     * own implementation of the ConcreteMailAddress class and then
     * you can substitute it in here if you wish.
     * @param args  command line arguments -- not used.
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        MailAddressInterface myList[] = new ConcreteMailAddress[100];
        Project0Helper helper = new Project0Helper();
        Scanner myscanner;
        try {
            myscanner = new Scanner(new File("test.txt") );
            try {
                for (int i= 0; i < 100; i++) {
                    String name = myscanner.nextLine();
                    String address1 = myscanner.nextLine();
                    String address2 = myscanner.nextLine();
                    String city = myscanner.nextLine();
                    String state = myscanner.nextLine();
                    int zipcode = myscanner.nextInt();
                    myscanner.nextLine();  // get rid of the rest of the line after the zip code
                    myList[i] = new ConcreteMailAddress(name, address1, address2, city, state, zipcode);
                    System.out.println(myList[zipcode]);
                }
            } catch(NoSuchElementException e) {
                // end of input?
            }

            helper.checkStartingOrder(myList);

            helper.checkFinalOrder(myList);
            myscanner.close();
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.exit(0);
    }

}
