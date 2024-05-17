.SUFFIXES: .c .cpp .o .x .h .pdf

#---------------------------------------------------#
#                      Makefile                     #
#       Cezary924_Projekt_AISDII_Skarbonki       #
#---------------------------------------------------#

DIR = PROJEKT
NAME1 = Cezary924_Projekt_AISDII_Skarbonki

.PHONY: run

run:
	clear
	g++ -std=c++17 $(NAME1).cpp -o $(NAME1)
	./$(NAME1)

clean:
	rm -f $(NAME1)
	rm  -f *.o
	rm  -f *~	

tar: clean
	(cd ../; tar -cvzf $(NAME1).tar.gz  $(DIR) )