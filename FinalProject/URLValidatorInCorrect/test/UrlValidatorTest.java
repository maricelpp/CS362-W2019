

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator();
	   
	   
	   //Valid Scheme 
	   System.out.println("Testing: http://www.google.com");
	   System.out.println("Expecting: TRUE");
	   if (urlVal.isValid("http://www.google.com") == true)
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   else
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   
	   //Invalid Scheme
	   System.out.println("Testing: ht_tp://www.google.com");
	   System.out.println("Expecting: FALSE");
	   if (urlVal.isValid("ht_tp://www.google.com") == false)
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   else
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   
	   
	   
	   //Valid Port 
	   System.out.println("Testing: http://www.google.com:80");
	   System.out.println("Expecting: TRUE");
	   if (urlVal.isValid("http://www.google.com:80") == true)
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   else
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   
	   //Invalid Port
	   System.out.println("Testing: http://www.google.com:-1");
	   System.out.println("Expecting: FALSE");
	   if (urlVal.isValid("http://www.google.com:-1") == false)
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   else
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	  

	   //Valid Path 
	   System.out.println("Testing: http://www.google.com/images");
	   System.out.println("Expecting: TRUE");
	   if (urlVal.isValid("http://www.google.com/images") == true)
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   else
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   
	   //Invalid Path
	   System.out.println("Testing: http://www.google.com/../");
	   System.out.println("Expecting: FALSE");
	   if (urlVal.isValid("http://www.google.com/../") == false)
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   else
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   

	   //Valid Authority 
	   System.out.println("Testing: http://go.com");
	   System.out.println("Expecting: TRUE");
	   if (urlVal.isValid("http://go.com") == true)
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   else
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   
	   //Invalid Authority
	   System.out.println("Testing: http://1.2.3.4");
	   System.out.println("Expecting: FALSE");
	   if (urlVal.isValid("http://1.2.3.4") == false)
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   else
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   

	   //Valid Query 
	   System.out.println("Testing: https://www.google.com/webhp?hl=en&ictx=2&sa=X");
	   System.out.println("Expecting: TRUE");
	   if (urlVal.isValid("https://www.google.com/webhp?hl=en&ictx=2&sa=X") == true)
	   {
		   System.out.println("Observing: TRUE\n");
	   }
	   else
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   
	   //Invalid Query
	   System.out.println("Testing: https://www.google.com/webhp?hl=en&ictx=2&sa=X#&ved=0ahUKEwiQxrSA-_vgAhUBNX0KHfEnARUQPQgH");
	   System.out.println("Expecting: FALSE");
	   if (urlVal.isValid("https://www.google.com/webhp?hl=en&ictx=2&sa=X#&ved=0ahUKEwiQxrSA-_vgAhUBNX0KHfEnARUQPQgH") == false)
	   {
		   System.out.println("Observing: FALSE\n");
	   }
	   else
	   {
		   System.out.println("Observing: TRUE\n");
	   }

   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
