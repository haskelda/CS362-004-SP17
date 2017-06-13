/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   
	   //test standard sites
	   System.out.println(urlVal.isValid("http://www.amazon.com")+" http://www.amazon.com Expected: True");
	   System.out.println(urlVal.isValid("http://www.google.com")+" http://www.google.com Expected: True\n");
	   
	   
	   //test random non valid site
	   System.out.println(urlVal.isValid("http://sd432.tea")+" http://sd432.tea Expected: False");
	   System.out.println(urlVal.isValid("http://cake.tea")+" http://cake.tea Expected: False");
	   System.out.println(urlVal.isValid("http://www.sd432.tea")+" http://www.sd432.tea Expected: False\n");
	   
	   //test www component of a site
	   System.out.println(urlVal.isValid("http://www.teamliquid.net")+" http://www.teamliquid.net Expected: True");
	   System.out.println(urlVal.isValid("http://ww.teamliquid.net")+" http://ww.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("http://w.teamliquid.net")+" http://w.teamliquid.net Expected: False\n");
	   
	   //test http component of a site
	   System.out.println(urlVal.isValid("abc://www.teamliquid.net")+" abc://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("abcdefgh://www.teamliquid.net")+" abcdefgh://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("abca//www.teamliquid.net")+" abca//www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("abcad/www.teamliquid.net")+" abcad//www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("abcadfwww.teamliquid.net")+" abcadfwww.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("://www.teamliquid.net")+" ://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("h://www.teamliquid.net")+" h://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("a://www.teamliquid.net")+" a://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("a:/./www.teamliquid.net")+" a:/./www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("abcadf:///www.teamliquid.net")+" abcadf:///www.teamliquid.net Expected: False\n");
	  
	   //test site region
	   System.out.println(urlVal.isValid("https://www.google.co.au")+" https://www.google.co.au Expected: True");
	   System.out.println(urlVal.isValid("https://www.google.et")+" https://www.google.et Expected: True");
	   System.out.println(urlVal.isValid("https://www.google.cn")+" https://www.google.cn Expected: True");
	   System.out.println(urlVal.isValid("https://www.google.uk")+" https://www.google.uk Expected: True");
	   System.out.println(urlVal.isValid("https://www.google.ca")+" https://www.google.ca Expected: True\n");
	   System.out.println(urlVal.isValid("https://www.amazon.uk")+" https://www.amazon.uk Expected: True\n");
	   System.out.println(urlVal.isValid("https://www.google.co.jp/?hl=en")+" https://www.google.co.jp/?hl=en Expected: True\n");
	   System.out.println(urlVal.isValid("https://www.amazon.co.jp/")+" https://www.amazon.co.jp/ Expected: True\n");
	   
	   
	   //test range of network addresses and random characters
	   System.out.println(urlVal.isValid("http://125.125.125.125")+" http://125.125.125.125 Expected: True");
	   System.out.println(urlVal.isValid("http://380.390.400.420")+" http://380.390.400.420 Expected: False");
	   System.out.println(urlVal.isValid("\n\0/0/")+"\\n\0/0/ Expected: False\n");
	   
	   //test of different suffix
	   System.out.println(urlVal.isValid("hpeepee://www.teamliquid.net")+" hpeepee://www.teamliquid.net Expected: False");
	   System.out.println(urlVal.isValid("hpeepee://www.teamliquid.club")+" hpeepee://www.teamliquid.club Expected: False");
	   System.out.println(urlVal.isValid("hpeepee://www.teamliquid.biz")+" hpeepee://www.teamliquid.biz Expected: False");
	   System.out.println(urlVal.isValid("hpeepee://www.teamliquid.edu")+" hpeepee://www.teamliquid.edu Expected: False");
	   
   }
   
   
   public void testYourFirstPartition() // Using symbols other than those allowed: alphanumeric characters and !$-_+*'(),
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUsing symbols other than those allowed: alphanumeric characters and !$-_+*'(),");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path"));
	   System.out.println(urlVal.isValid("http://www.abc().com/path$,()/path_!-+*"));
	   System.out.println(urlVal.isValid("http://www.abc^.com/path/path"));
	   System.out.println(urlVal.isValid("http://www.abc.com/^path/path"));
	   System.out.println(urlVal.isValid("http://www.abc^.com/path/=path"));
	   System.out.println(urlVal.isValid("http://www.abc.com/path /path"));
   }
   
   public void testYourSecondPartition() // Use of the double slash after http and https
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of the double slash after http and https");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path"));
	   System.out.println(urlVal.isValid("http:/www.abc.com/path/path"));	   
   }
   
   public void testYourThirdPartition() // Use and non-use of hostnames/IP addresses
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse and non-use of hostnames/IP addresses");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path"));
	   System.out.println(urlVal.isValid("ftp://abc.com/path/path"));
	   System.out.println(urlVal.isValid("http://abc.com/path/path"));
	   System.out.println(urlVal.isValid("http://path/path"));	   
   }
   
   public void testYourFourthPartition() // Use of IPv4 addresses
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of IPv4 addresses");
	   System.out.println(urlVal.isValid("https://255.255.128.45/path/path"));
	   System.out.println(urlVal.isValid("https://255.255.128.345/path/path"));
	   System.out.println(urlVal.isValid("https://255.255.128.128.12/path/path"));
	   System.out.println(urlVal.isValid("https://255.255.128.245.144/path/path"));	   
   }
   
   public void testYourFifthPartition() // Use of IPv6 addresses
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of IPv6 addresses");
	   System.out.println(urlVal.isValid("https://[2001:0db8:0000:0000:0000:ff00:0042:8329]/path/path"));
	   System.out.println(urlVal.isValid("https://[2001:db8:0:0:0:ff00:42:8329]/path/path"));
	   System.out.println(urlVal.isValid("https://[2001:db8::ff00:42:8329]/path/path"));
	   System.out.println(urlVal.isValid("https://[2001:db8::ff00:h42:8329]/path/path"));   
   }
   
   public void testYourSixthPartition() // Use of port numbers
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of port numbers");
	   System.out.println(urlVal.isValid("https://255.255.128.45:80/path/path"));
	   System.out.println(urlVal.isValid("https://255.255.128.45:abc/path/path"));
	   
   }
   
   public void testYourSeventhPartition() // Use of (/) and (//) in the Path component
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of (/) and (//) in the Path component");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path"));
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path/"));
	   System.out.println(urlVal.isValid("http://www.abc.com/path//path"));	   
   }
   
   public void testYourEighthPartition() // Use of Query with the leading (?)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of Query with the leading (?)");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path?query"));	   
   }
   
   public void testYourNinthPartition() // Use of Fragments with the leading (#)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nUse of Fragments with the leading (#)");
	   System.out.println(urlVal.isValid("http://www.abc.com/path/path#fragment"));	   
   }

   public void testIsValid() {
       testIsValid(urlComponents, UrlValidator.ALLOW_ALL_SCHEMES);
  }
   
   public void testIsValid(Object[] testObjects, long options) {
	   //for(int i = 0;i<10000;i++) {}
	   /*Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};*/
	   int i = 0;
		UrlValidator urlString = new UrlValidator(null, null, options);
		String testUrl;
		boolean expected = true;
		boolean actual = true;
		for (int a = 0; a < 9; a++){
			ResultPair[] partA = (ResultPair[]) testObjects[0];
			for(int b = 0; b < 19; b++){
				ResultPair[] partB = (ResultPair[]) testObjects[1];
				for(int c = 0; c < 7; c++){
					ResultPair[] partC = (ResultPair[]) testObjects[2];
					for(int d = 0; d < 10; d++){
						ResultPair[] partD = (ResultPair[]) testObjects[3];
						for(int e = 0; e < 3; e++){
							ResultPair[] partE = (ResultPair[]) testObjects[4];
							
							expected = partA[a].valid && partB[b].valid && partC[c].valid && partD[d].valid && partE[e].valid;
							testUrl = partA[a].item + partB[b].item + partC[c].item + partD[d].item + partE[e].item;
							actual = urlString.isValid(testUrl);
							
							if(expected != actual){
								System.out.print(++i);
								System.out.print(" Expected:" + expected + " Actual:" + actual); 
								System.out.print(" FAILED: " + testUrl);
								System.out.println();
							} else {
								System.out.print(" PASSED: " + testUrl);
								System.out.println();
							}						
						}
					}
				}
			}
		}   
	}
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] schemes = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false),
                               new ResultPair("", true)};

   ResultPair[] authorities = {new ResultPair("www.google.com", true),
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
                                  new ResultPair("", false)
   };
   ResultPair[] ports = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair(":-1", false),
                             new ResultPair(":65636", true),
                             new ResultPair(":65a", false),
                             new ResultPair("", true)
   };
   ResultPair[] paths = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false),
                          new ResultPair("", true)
   };

   ResultPair[] queries = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] urlComponents = {schemes, authorities, ports, paths, queries};
}
