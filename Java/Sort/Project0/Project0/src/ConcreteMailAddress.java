public class ConcreteMailAddress implements MailAddressInterface {

    private String name;
    private String address1;
    private String address2;
    private String city;
    private String state;
    private int zipcode;

    public ConcreteMailAddress(String name, String address1, String address2, String city, String state, int zipcode) {
        // TODO Auto-generated constructor stub
        this.name = name;
        this.address1 = address1;
        this.address2 = address2;
        this.city = city;
        this.state = state;
        this.zipcode = zipcode;

    }
    public String toString()
    {
        return name + "\n" + address1 + "\n" + address2 + "\n" + city + "\n" + state + "\n" + zipcode + "\n";
    }

    @Override
    public String getName() {
        // TODO Auto-generated method stub
        return  this.name;
    }

    @Override
    public String getAddressLine1() {
        // TODO Auto-generated method stub
        return this.address1;
    }

    @Override
    public String getAddressLine2() {
        // TODO Auto-generated method stub
        return this.address2;
    }

    @Override
    public String getCity() {
        // TODO Auto-generated method stub
        return this.city;
    }

    @Override
    public String getState() {
        // TODO Auto-generated method stub
        return this.state;
    }

    @Override
    public int getZipCode() {
        // TODO Auto-generated method stub
        return this.zipcode;
    }

    @Override
    public int getZipCodeDigit(int digit) {
        // TODO Auto-generated method stub
        String zipCodeStr = String.format("%05d", zipcode);
        return Integer.parseInt(Character.toString(zipCodeStr.charAt(zipCodeStr.length() - digit)));
    }

}

