main: main.o libisentlib.a
	gcc -Wall main.o -o main -lm libisentlib.a
# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall exemple.o -o exemple -lm libisentlib.a -framework OpenGL -framework GLUT

main.o: main.c  BmpLib.h imageIO.h 
	gcc -Wall -O2 -c main.c

libisentlib.a: BmpLib.o OutilsLib.o imageIO.o
	ar r libisentlib.a BmpLib.o OutilsLib.o 
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c BmpLib.c

imageIO.o: imageIO.c imageIO.h BmpLib.h OutilsLib.h
	gcc -Wall -O2 -c imageIO.c

# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c GfxLib.c -Wno-deprecated-declarations

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc -Wall -O2 -c OutilsLib.c

# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

clean:
	rm -f *~ *.o

deepclean: clean
	rm -f exemple libisentlib.a
