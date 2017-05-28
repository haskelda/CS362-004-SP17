CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)


# example tests

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

betterTestDrawCard: betterTestDrawCard.c dominion.o rngs.o
	gcc -o betterTestDrawCard -g  betterTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4ls -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)


testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)




# testing for Assignment-3

unittestresults.out: unittest1.c unittest2.c dominion.o rngs.o
	echo "Results from running function tests:" > unittestresults.out

	echo "---------------------------- unittest1.c ------------------------------------------" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	#gcov dominion.c >> unittestresults.out
	#cat dominion.c.gcov >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "---------------------------- unittest2.c ------------------------------------------" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "---------------------------- unittest3.c ------------------------------------------" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "---------------------------- unittest4.c ------------------------------------------" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

cardtest1.out: cardtest1.c dominion.o rngs.o
	echo "---------------------------- cardtest1.c ------------------------------------------" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

cardtest2.out: cardtest2.c dominion.o rngs.o
	echo "---------------------------- cardtest2.c ------------------------------------------" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

cardtest3.out: cardtest3.c dominion.o rngs.o
	echo "---------------------------- cardtest3.c ------------------------------------------" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

cardtest4.out: cardtest4.c dominion.o rngs.o
	echo "---------------------------- cardtest4.c ------------------------------------------" >> unittestresults.out
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b -f dominion.o >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out


# testing for Assignment-4

randomtestcard1.out: randomtestcard1.c dominion.o rngs.o 
	echo "Results from running randomtestcard1:" > randomtestcard1.out

	echo "---------------------------- randomtestcard1.c ------------------------------------------" >> randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o 
	echo "Results from running randomtestcard2:" > randomtestcard2.out

	echo "---------------------------- randomtestcard2.c ------------------------------------------" >> randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o 
	echo "Results from running randomtestadventurer:" > randomtestadventurer.out

	echo "---------------------------- randomtestadventurer.c ------------------------------------------" >> randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

cleanall:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out
