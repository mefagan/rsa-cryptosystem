//MaryEileen Fagan
//Cryptography Final Project

#include <iostream>

using namespace std;


//MODULUS FUNCTION
int mod (int value, int divisor){

	if (divisor==0) 
		return 0;
	else
		while (value>=divisor){
		value = value-divisor;
	}
	return value;
}

//PRINTS 32 BIT INTEGERS AS BITS
void bit_32converter(int x){
        for (int i = 31; i>=0; i--){
                int bit = mod((x>>i), 2);
		cout << bit;
        }
}

//function to print 8 bit integers as bits
void bit_8converter(int x){
        for (int i = 7; i>=0; i--){
                int bit = mod((x>>i), 2);
                cout << bit;
        }
}


//PRINT PRIME TRACi
//prints out arrays of random numbers and the extracted bits for each number
//shows which each bit of prime number is set to
void primeTrace(int (&randArray)[5], int (&bitArray)[5], int prime){
	cout << "Trace for " << prime << " (";
	bit_32converter(prime);
	cout << "):"<<endl;
	cout << "Bit 0: set as 1"<<endl;
	for (int i =0; i<5; i++){
		cout << "Bit " << i+1 << " number ";
		bit_32converter(randArray[i]);
		cout << " extracts " << bitArray[i] << endl;
	}
	cout << "Bit 6: set as 1" << endl;
}


//POWER FUNCION
double power(double base, double exponent) {
        double result = 1;
        while (exponent !=0){
                result = result * base;
                exponent --;
        }
        return result;
}

//Function updates 2 arrays, one for random numbers and one for bits derived from the random numbers
void chooseRandomBits(int (&randArray)[5], int (&bitArray)[5]) {
	for (int i=0; i<5; i++){
		randArray[i] = rand();
		bitArray[i] = mod(randArray[i], 2);
        }
}

//Function pads 5 random bits with 1's and leading zeros
void padPrime(int &prime, int (&bitArray)[5]){	
	int prime1 = 1<<6 | 1;
        int prime2 = (bitArray[0] << 4 | bitArray[1] << 3 | bitArray[2] << 2 | bitArray [3] << 1 | bitArray[4]);
        int leadingZeroes = 0 << 31;
        prime = (prime1 | (prime2 << 1)) | leadingZeroes;
}

//prints trace of miller rabin algorithm
void print_isPrime(int prime, int &a) {
        cout << "Trace: n = " << prime << "   a = " << a << endl;
        double n = prime;
        int x = prime -1;
        int y1 = 1;
        int y2 = 1;
        int z = 1;
        for (int i=6; i>=0; i--){
                z = y2;
                int xi = mod((x>>i), 2);
                y1 = mod((power(y2, 2)), n);

                if (xi==1)
                y2 = mod((y1*a), n);
                else
                y2 = y1;
                cout << "i = " << i << "   xi = " << xi << "   z = "  << z
                << "   y1 = " << y1 << "   y2 = " << y2 << endl;
                 }
}

//tests if number is prime using miller rabin algorithm
bool isPrime(int prime, int &a) {
        bool isPrimeNumber = false;
        int counter =0;
        while (counter<20) {
        	int n = prime;
        	int x = prime -1;
        	int random = rand() + 1;
        	while(a==0){
			a = mod(random, prime);
        	}
		int y1 = 1;
        	int y2 = 1;
        	int z = 1;
        	for (int i = 6; i>=0; i--){
                	z = y2;
                	int xi = mod ((x>>i), 2);
                	y1 = mod((power(y2, 2)), n);

                	if ((y1==1) && (z!= 1) && (z!=(x))){
               			return false;
               		}

                if (xi==1) y2 = mod((y1*a), n);
                else y2 = y1;
        	}

        	if (y1!=1) {
        	return false;
        }


        	else{
        	counter++;
        	if (counter==20)return true;
        	}
	}	
        return true;
}

//runs extended euclidean algorithm to find if one number is relatively prime with another
//does this by finding whether the gcd of both numbers is 1
//The algorithm does not say whether the two numbers are relatively prime; rather, the 
//algorithm increments the e value by 1 until one of the e values is relatively prime with theta n
void extended_euclidean(int &ri1, int &ri2, int &d, int &thetaN, int &e) {
	e++;
	ri1 = thetaN;
        ri2 = e;
        cout << endl << endl;
	cout << "line 145" << endl;
	cout << "Try e = " << e << endl;
        int s[10];
        int t[10];
        int q[10];
        int i = 1;
        q[i] = ri1/ri2;
        int ri3 = mod(ri1, ri2);
        s[i] = 1;
        t[i] = 0;
        cout << "i = " << i << " qi = " << q[i] << " ri =  " << ri1 << " r(i+1) =  " << ri2 << " r(i+2) =  " << ri3 << " si = " << s[i] << " ti =  " << t[i]<< endl;	
	
	i = 2;
        ri1 = ri2;
        ri2 = ri3;
	if (ri2==0){
                cout << "i = " << i << " ri = " << ri1 << " si = " << s[i] << " ti = " << t[i] << endl;
        	}
	else {
	q[i] = ri1/ri2;
	ri3 = mod(ri1, ri2);
        s[i] = 0;
        t[i] = 1;
        cout << "i = " << i << " qi = " << q[i] << " ri =  " << ri1 << " r(i+1) =  " << ri2 << " r(i+2) =  " << ri3 << " si = " << s[i] << " ti =  " << t[i]<< endl;
	}
	
	while (ri2 > 0){
        i++;
        ri1 = ri2;
        ri2 = ri3;
	s[i] = s[i-2]  - (s[i-1]*q[i-2]);
        t[i] = t[i-2]- (t[i-1]*q[i-2]);
	 if (ri2==0){
                cout << "i = " << i << " ri = " << ri1 << " si = " << s[i] << " ti = " << t[i] << endl;
        }
	
	else
	{
	q[i] = ri1/ri2;
        ri3 = mod(ri1, ri2);
                cout << "i = " << i << " qi = " << q[i] << " ri =  " << ri1 << " r(i+1) =  " << ri2 << " r(i+2) =  " << ri3 << " si = " << s[i] << " ti =  " << t[i]<< endl;
        }
	}
	d = t[i];
        if (t[i]<0)
        d = t[i] + thetaN;
	
}

//does the same thing as extended euclidean algorithm above, but doesn't print a trace
void noprint_extended_euclidean(int &ri1, int &ri2, int &d, int &thetaN, int &e) {
        e++;
        ri1 = thetaN;
        ri2 = e;
        int s[10];
        int t[10];
        int q[10];
        int i = 1;
        q[i] = ri1/ri2;
        int ri3 = mod(ri1, ri2);
        s[i] = 1;
        t[i] = 0;

        i = 2;
        ri1 = ri2;
        ri2 = ri3;
        if (ri2>0){
        q[i] = ri1/ri2;
        ri3 = mod(ri1, ri2);
        s[i] = 0;
        t[i] = 1;
        }

        while (ri2 > 0){
        i++;
        ri1 = ri2;
        ri2 = ri3;
        s[i] = s[i-2]  - (s[i-1]*q[i-2]);
        t[i] = t[i-2]- (t[i-1]*q[i-2]);

        if (ri2>0)
        {
        q[i] = ri1/ri2;
        ri3 = mod(ri1, ri2);
        }
        }
        d = t[i];
	if (t[i]<0)
        d = t[i] + thetaN;
}


//creates a prime number candidate by using the chooserandombits and padprime functions
int createPrime(){
	int prime = 0;
	int randArray[5];
	int bitArray[5];
	chooseRandomBits(randArray, bitArray);
	padPrime(prime, bitArray);
	return prime;
}

//finds and prints a candidate that does not pass the test for prime
void findNotPrime(){
	int a = 0;
	int notPrime = createPrime();
	while (isPrime(notPrime, a)==true){
		notPrime = createPrime();
        }
        int x = notPrime-1;
        cout << "line 122" << endl;
        cout << notPrime  << " is not a prime because " << a << "^" << x << " mod " << notPrime << " != 1" << endl;
        print_isPrime(notPrime, a);
}

//finds a candidate that passes the prime test, called p
void findP (int &p, int &a)
{
	p = createPrime();
        while (isPrime(p, a)==false){
                p = createPrime();
        }
}

//finds another candiate that does pass test for prime, called q
void findQ (int &p, int &q)
{
	int a = 0;
	q = createPrime();
	while ((isPrime(q, a)==false) || (p==q)) {
		q = createPrime();
        }
}

//This function produces the variables for Alice's rsa cryptosystem, p, q, n, e, and d.
void alice_cryptosystem(int &aliceP, int &aliceQ, int &aliceN, int &aliceE, int &aliceD)
{
        cout << endl << endl;
	int a=0;
	//find a prime number, p
	findP(aliceP, a);
	cout << "line 126" << endl;
        cout << "Prime number p = " << aliceP << "  may be a prime" << endl;
        //prints prime number trace
	print_isPrime(aliceP, a);
	//find another prime number, q, but doesn't print trace
	findQ(aliceP, aliceQ);
	aliceN = aliceP * aliceQ;
	int thetaN = (aliceQ-1) * (aliceP-1);
	//e value is incremented by one at start of the extended euclidean algorithm 
	//function so the value e is initiated to 2 here so that it will 
	//test e=3 in the function
	aliceE = 2;
	int ri2 = aliceE;
	int ri1 = thetaN;
	//runs extended euclidean until an e value is found such that r1 ==1 a
	//meaning that e and theta n are relatively prime
        while (ri1 != 1) {
        extended_euclidean(ri1, ri2, aliceD, thetaN, aliceE);
        }
	cout << endl;
        cout << "line 155" << endl;
        cout << "d = " << aliceD << endl;
        cout << endl << endl;
	cout << "line 159" << endl;
	cout << "Integer:"<< endl;
	cout << "p = " << aliceP << ", q = " << aliceQ << ", n = "<< aliceN << ", e = "<< aliceE << ", d = " << aliceD << endl;
	cout << "Bits:" << endl;
	cout << "p = ";
	bit_32converter(aliceP);
	cout << endl << "q = ";
	bit_32converter(aliceQ);
	cout << endl << "n = ";
	bit_32converter(aliceN);
	cout << endl << "e = ";
	bit_32converter(aliceE);
	cout << endl << "d = ";
	bit_32converter(aliceD);
	//Alice's public key is <n, e>
	//Alice's private key is <n, d>
}

//Trent's rsa cryptosystem runs the same as Alice's above, but doesn't print a trace
void trent_cryptosystem(int &trentP, int &trentQ, int &trentN, int &trentE, int &trentD)
{
        int a =0;
	findP(trentP, a);
        findQ(trentP, trentQ);
        trentN = trentP * trentQ;
        int thetaN = (trentQ-1) * (trentP-1);
        trentE = 2;
        int ri2 = trentE;
        int ri1 = thetaN;
        while (ri1 != 1) {
        	noprint_extended_euclidean(ri1, ri2, trentD, thetaN, trentE);
        }
}

//function produces r and h(r) through bit manipulation
//it produces the individual bytes of r and then performs
//exclusive or on the bytes to find the hash, h(r)
void certificate(int n, int e, int &hr) {
        int bytes1 = (0<<8);
        int bytes2 = 'A';
        int bytes3 = 'l';
        int bytes4 = 'i';
        int bytes5 = 'c';
        int bytes6 = 'e';
        int bytes7to10 = n;
        int bytes7 = (0<<8);
        int bytes8 = (0<<8);
        int bytes9to10 = n;
        int bytes9 = (bytes9to10>>8);
        int bytes10 = (bytes9to10&255);
        int bytes11 = (0<<8);
        int bytes12 = (0<<8);
        int bytes13 = (0<<8);
        int bytes14 = e;

        cout << "r = ";
        bit_8converter(bytes1);
        bit_8converter(bytes2);
        bit_8converter(bytes3);
        bit_8converter(bytes4);
        bit_8converter(bytes5);
        bit_8converter(bytes6);
        bit_8converter(bytes7);
        bit_8converter(bytes8);
        bit_8converter(bytes9);
        bit_8converter(bytes10);
        bit_8converter(bytes11);
        bit_8converter(bytes12);
        bit_8converter(bytes13);
        bit_8converter(bytes14);
        cout << endl;

        hr  = (bytes1^bytes2^bytes3^bytes4^bytes5^bytes6^bytes7^bytes8^bytes9^bytes10^bytes11^bytes12^bytes13^bytes14);
	cout << "h(r) = ";
	bit_32converter(hr);
	cout << endl;
        }

//function receives an integer n, partitions it into separate bytes
//function then produces a hash of the integer by performing exlcusive
//or on all of the bytes
//function will receive integer u in main() and find h(u)
void hashInt(int n, int &hu)
{
	int byte1 = n>>24;
	int byte2 = (n>>16)^(byte1<<8);
	int byte3 = (n>>8)^(byte1<<16)^(byte2<<8);
	int byte4 = (byte1<<24)^(byte2<<16)^(byte3<<8)^n;
	hu = (byte1^byte2^byte3^byte4);
}

//function to perform fast exponentiation algorithm
int fast_exponentiation(int a, int x, int n){
        int y = 1;
        int counter = 0;
	 //finds how many bits there are exluding the padding zeros
        for (int i=31; i>=0; i--) {
                if ((mod((x>>i), 2))==0)
                counter++;
                else
                break;
        }
        int k = 31-counter;
        for (int i = k; i>=0; i--){
                y = mod((y*y), n);
                int xi = mod ((x>>i), 2);
                if (xi==1){
                       y = mod((y*a), n);
                }
        }
return y;
}


//function to perform fast exponentiation algorithm and print a trace of the exponentiation
int print_fast_exponentiation(int n, int a, int x){
	cout << endl <<  "line 226" << endl;
	cout << "Trace:  " <<  "n  = " << n << "   a = " << a << "   x = " << x << endl;
        int y = 1;
	int counter = 0;
	//finds how many bits there are exluding the padding zeros
	for (int i=31; i>=0; i--) {
                if ((mod((x>>i), 2))==0)
                counter++;
                else
                break;
        }
        int k = 31-counter;
        for (int i = k; i>=0; i--){	
		cout << "i = " << i << "   ";
                y = mod((y*y), n);
                int xi = mod ((x>>i), 2);
		cout << "x = " << xi << "   ";
		cout << "y = " << y << "   ";
                if (xi==1){
                        y = mod((y*a), n);
			cout << "y2 = " << y << endl;
                }
		else cout << "y2 = " << y << endl;
        }
return y;
}

//creates U as described in project outline
void uCreator (int aliceN, int &u) {
	//first finds first occurence of 1 and sets k to index value
	int counter = 0; 
	for (int i=31; i>=0; i--) {
                if ((mod((aliceN>>i), 2))==0)
                counter++;
                else
                break;
        }
	int k = 31-counter;
	int m = k-1;
	int uarray[m];
	//creates k-1 random bits as an array
	int randomBits=0;
	for (int i =m; i>=0; i--){
		uarray[i] = mod(rand(),2);
		//concatenates the m random bits
		randomBits = randomBits | (uarray[i]<<i);
        }
	//creates 32-k 0 bits followed by a 1 at index k 
	int padder = (1<<k) ^ (0<<31);
	u = randomBits | padder;
	cout << endl <<  "line 214" << endl;
	cout << "integers: " << endl << "k = " << k << endl;
        cout << "u = " << u << endl << endl;
        cout << "line 216" << endl;
	cout << "u =  ";
        bit_32converter(u);
        cout << endl;
}

	
int main() 
{
	srand(time(0));
	int a = 0;
	int prime = 0;
	int randArray[5];
	int bitArray[5];
	//finds 5 random numbers and extracts least significant bits
	//places numbers into array randArray and bits into array bitArray
	chooseRandomBits(randArray, bitArray);
	padPrime(prime, bitArray);
	cout << endl << "line 106" << endl;
	primeTrace(randArray, bitArray, prime);
	cout << endl << endl;
	findNotPrime();
	int aliceP, aliceQ, aliceN, aliceE, aliceD;
	int trentP, trentQ, trentN, trentE, trentD;
	alice_cryptosystem(aliceP, aliceQ, aliceN, aliceE, aliceD);
	trent_cryptosystem(trentP, trentQ, trentN, trentE, trentD);
	int hr;
	cout << endl << endl << "line 188"<< endl;
	certificate(aliceN, aliceE, hr);
	int s = fast_exponentiation(hr, trentD, trentN);
	cout << "s = ";
	bit_32converter(s);
	cout << endl << endl << "line 190" << endl;
	cout << "h(r) = " << hr << endl;
	cout << "s = " << s << endl;
	int u;
	uCreator(aliceN, u);
	int hu;
	hashInt(u, hu);
	int v = fast_exponentiation(hu, aliceD, aliceN);
	int huu = fast_exponentiation(v, aliceE, aliceN);
	cout << endl << "line 222" << endl;
	cout << "u = " << u << endl;
	cout << "h(u) = " << hu << endl;
	cout << "v = D(d, h(u)) = " << v << endl;
	cout << "E(e,v) = " << huu << endl; 
	print_fast_exponentiation(aliceN, v, aliceE);
	//Bob knows he is talking to someone who knows Alice's private key
	//if th encrypted v value is equal to the hash of the u value
	return 0;
}
