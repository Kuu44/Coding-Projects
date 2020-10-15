/**
 * @author Jerry Heuring
 * This is the MailAddressInterface you are to implement for 
 * Project 0.  You will need a class that implements this interface.
 *
 * Obviously, you will need to add classes beyond those described here.
 * Your class will need to support a Constructor (or Constructors) as
 * well as a toString method. 
 *
 * Revisions:
 *     None as of 9/3/2020
 *
 * Bugs:
 *
 */
public interface MailAddressInterface {
    /**
     * Get the name line for this address.
     * @return the name line for this address (Mr. John Doe)
     */
    public String getName();
    /**
     * Get the first address line for this address.
     * @return  First line of the street address for this address
     */
    public String getAddressLine1();
    /**
     * Get the second address line for this address (may be null or the
     * empty string if there is none).
     * @return  Second line of the street address (if any) for this address
     */
    public String getAddressLine2();
    /**
     * Get the city for this address.
     *
     * @return  The name of the city for this address.
     */
    public String getCity();
    /**
     * Get the name of the state or the state abbreviation for this address.
     * @return  The name of the state or the abbreviation of the state for this address.
     */
    public String getState();
    /**
     * Get the zip code for this address.
     * @return  The 5 digit zip code for this address.
     */
    public int getZipCode();
    /**
     * Get the n't digit of the zip code for this address.  Digit 1 is the units digit and
     * zip codes MUST be only 5 digits for this project.  If my zip code is 98765 then
     * digit 1 = 5
     * digit 2 = 6
     * digit 3 = 7
     * digit 4 = 8
     * digit 5 = 9
     *
     * @param digit  which digit of the zip code to return.  Digit 1 is the units digit.
     * @return  The n'th digit of the zip code.
     */
    public int getZipCodeDigit(int digit);
}