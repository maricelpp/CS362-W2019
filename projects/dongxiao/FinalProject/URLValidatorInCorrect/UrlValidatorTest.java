

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
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean tally = true;
	   System.out.println("\nTesting basic urls");
	   // base cases
	   String [] base_urls = {"http://www.google.com", "http://www.google.com/", "http://localhost/"};
	   boolean valid, result;
	   int i;
	   for (i=0; i<3; i++) {
		   valid = urlVal.isValid(base_urls[i]);
		   result = compareResults(base_urls[i], true, valid);
		   tally &= result;
	   }
	   
	   // Null URL should be false
	   String url = "";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	   // URL with scheme only should be false
	   System.out.println("\nTesting different schemes");
	   String [] scheme_urls = {"https:", "http:", "ftp:", "h3t:", "http://"};
	   for (i=0; i<5; i++) {
		   valid = urlVal.isValid(scheme_urls[i]);
		   result = compareResults(scheme_urls[i], false, valid);
		   tally &= result;
	   }
	   
	   
	   // testing URL with different schemes
	   url = "http://www.google.com";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "2://google.com";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	   // testing different domains
	   System.out.println("\nTesting different domains");
	   url = "http://go.com";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://225.255.255.255/";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://255.com";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://225.255.255.256/";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	   // testing different paths
	   System.out.println("\nTesting different paths");
	   url = "http://www.google.com/test1";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com/test1/file";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com/ae(ge)";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com/#";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com/..";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	   url = "http://www.google.com/../file";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	// testing different ports
	   System.out.println("\nTesting different ports");
	   url = "http://www.google.com:80";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com:65536";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	   url = "http://www.google.com:6e6";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, false, valid);
	   tally &= result;
	   
	// testing different queries
	   System.out.println("\nTesting different queries");
	   url = "http://www.google.com?action=view";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   url = "http://www.google.com?action=view&test=true";
	   valid = urlVal.isValid(url);
	   result = compareResults(url, true, valid);
	   tally &= result;
	   
	   assertTrue(tally);
   }
   
   public boolean compareResults(String url, boolean expected, boolean result) {
	   String pass = expected?" should pass":" should fail";
	   if (expected == result) {   
		   System.out.println("CORRECT: " + url + pass);
		   return true;
	   } else {
		   System.out.println("INCORRECT: " + url + pass);
		   return false;
	   }
   }
   
}
