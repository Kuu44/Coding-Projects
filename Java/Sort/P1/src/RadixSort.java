import java.util.Arrays;

class RadixSort {
	//Kuu's code starts 
	// Using counting sort to sort the elements in the basis of significant places
	  void countingSort(MailAddressInterface myList[], int size, int place) {
		MailAddressInterface[] output = new MailAddressInterface[size + 1];
	    
	    int max = myList[0].getZipCode();
	    for (int i = 1; i < size; i++) {
	      if (myList[i].getZipCode() > max)
	        max = myList[i].getZipCode();
	    }
	    int[] count = new int[max + 1];

	    for (int i = 0; i < max; ++i)
	      count[i] = 0;

	    // Calculate count of elements
	    for (int i = 0; i < size; i++)
	      count[(myList[i].getZipCode() / place) % 10]++;

	    // Calculate cummulative count
	    for (int i = 1; i < 10; i++)
	      count[i] += count[i - 1];

	    // Place the elements in sorted order
	    for (int i = size - 1; i >= 0; i--) {
	      output[count[(myList[i].getZipCode() / place) % 10] - 1] = myList[i];
	      count[(myList[i].getZipCode() / place) % 10]--;
	    }

	    for (int i = 0; i < size; i++)
	      myList[i] = output[i];
	  }


//Function to get the largest element from an myList
  int getMax(MailAddressInterface myList[], int size) {
    int max = myList[0].getZipCode();
    for (int i = 1; i < size; i++)
      if (myList[i].getZipCode() > max)
        max = myList[i].getZipCode();
    return max;
  }

  // Main function to implement radix sort
  void radixSort(MailAddressInterface myList[], int size) {
	    // Get maximum element
	    int max = getMax(myList, size);

	    // Apply counting sort to sort elements based on place value.
	    for (int place = 1; max / place > 0; place *= 10)
	      countingSort(myList, size, place);
  }  	 
}
