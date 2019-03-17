import static org.junit.Assert.*;

import junit.framework.TestCase;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;

import java.lang.annotation.Repeatable;
import java.util.Random;

public class UrlValidatorRandomTest {
	private static final String NULL = null;
	static UrlValidator randomUrl;
	static Random rand;
	

	
	@BeforeClass
	public static void setUpBeforeClass(){
		randomUrl = new UrlValidator();
		rand = new Random();
	}
	
	@Test
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

	@Test
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
	
	@Test
	public void testIsValidRandom() {
		int pool;
		int n;
		boolean tally = true;
		boolean falseFlag, result, valid;
		
		System.out.println("\nRandom Testing of urls");
		
		for(int i = 0; i < 1000; i++)
		{
			falseFlag = true;
			StringBuilder testString = new StringBuilder();
			//Randomly choose the Scheme
			pool = testUrlScheme.length;
			n = rand.nextInt(pool);
			testString.append(testUrlScheme[n].item);
			if(testUrlScheme[n].valid == false)
			{
				falseFlag = false;
			}
			//Randomly choose the Authority
			pool = testUrlAuthority.length;
			n = rand.nextInt(pool);
			testString.append(testUrlAuthority[n].item);
			if(testUrlAuthority[n].valid == false)
			{
				falseFlag = false;
			}
			//Randomly choose the Port
			pool = testUrlPort.length;
			n = rand.nextInt(pool);
			testString.append(testUrlPort[n].item);
			if(testUrlPort[n].valid == false)
			{
				falseFlag = false;
			}
			//Randomly choose the Path
			pool = testPath.length;
			n = rand.nextInt(pool);
			testString.append(testPath[n].item);
			if(testPath[n].valid == false)
			{
				falseFlag = false;
			}
			//Randomly choose the Query
			pool = testUrlQuery.length;
			n = rand.nextInt(pool);
			testString.append(testUrlQuery[n].item);
			if(testUrlQuery[n].valid == false)
			{
				falseFlag = false;
			}
			
			
			String url = testString.toString();
			valid = randomUrl.isValid(url);
			result = compareResults(url, falseFlag, valid);
			tally &= result;	
		}
		
		assertTrue(tally);
	}
	
	public boolean compareResults(String url, boolean expected, boolean result) 
	{
		String pass = expected?" should pass":" should fail";
		if (expected == result)
		{   
			System.out.println("CORRECT: " + url + pass);
			return true;
		}
		else
		{
			System.out.println("INCORRECT: " + url + pass);
			return false;
		}
	}


/* I reused test values from Apache Commons UrlValidatorTest *
 * Didn't seem like a good use of time or wise to create new *
 * ones and possibly introduce a bug in to the test itself   */
ResultPair[] testUrlScheme = {new ResultPair("http://", true),
new ResultPair("ftp://", true),
new ResultPair("h3t://", true),
new ResultPair("3ht://", false),
new ResultPair("http:/", false),
new ResultPair("http:", false),
new ResultPair("http/", false),
new ResultPair("://", false),
new ResultPair("http", true),
new ResultPair("chrome://", true),
new ResultPair("fish://", true),
new ResultPair("gopher", true),
new ResultPair("g0-to+.", true),
	new ResultPair("not_valid", false), // underscore not allowed
	new ResultPair("HtTp", true),
	new ResultPair("telnet", false)
};

ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
new ResultPair("www.google.com.", true),
new ResultPair("go.com", true),
new ResultPair("go.au", true),
new ResultPair("0.0.0.0", true),
new ResultPair("255.255.255.255", true),
new ResultPair("256.256.256.256", false),
new ResultPair("255.com", true),
new ResultPair("1.2.3.4.5", false),
new ResultPair("1.2.3.4.", false),
new ResultPair("1.2.3", false),
new ResultPair(".1.2.3.4", false),
new ResultPair("go.a", false),
new ResultPair("go.a1a", false),
new ResultPair("go.cc", true),
new ResultPair("go.1aa", false),
new ResultPair("aaa.", false),
new ResultPair(".aaa", false),
new ResultPair("aaa", false),
new ResultPair("", false),
new ResultPair(NULL, false)
};
ResultPair[] testUrlPort = {new ResultPair(":80", true),
	new ResultPair(":65535", true), // max possible
	new ResultPair(":65536", false), // max possible +1
	new ResultPair(":0", true),
	new ResultPair("", true),
	new ResultPair(":-1", false),
	new ResultPair(":65636", false),
	new ResultPair(":999999999999999999", false),
	new ResultPair(":65a", false)
};
ResultPair[] testPath = {new ResultPair("/test1", true),
new ResultPair("/t123", true),
new ResultPair("/$23", true),
new ResultPair("/..", false),
new ResultPair("/../", false),
new ResultPair("/test1/", true),
new ResultPair("", true),
new ResultPair("/test1/file", true),
new ResultPair("/..//file", false),
new ResultPair("/test1//file", false)
};
//Test allow2slash, noFragment
ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
new ResultPair("/t123", true),
new ResultPair("/$23", true),
new ResultPair("/..", false),
new ResultPair("/../", false),
new ResultPair("/test1/", true),
new ResultPair("/#", false),
new ResultPair("", true),
new ResultPair("/test1/file", true),
new ResultPair("/t123/file", true),
new ResultPair("/$23/file", true),
new ResultPair("/../file", false),
new ResultPair("/..//file", false),
new ResultPair("/test1//file", true),
new ResultPair("/#/file", false)
};

ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
new ResultPair("?action=edit&mode=up", true),
new ResultPair("", true)
};

}
