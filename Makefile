# -Wall: 	zet de meeste warnings aan
# -Wextra: 	zet extra warnings aan
# -Werror: 	zorg dat warnings worden behandeld als errors (d.w.z. programma kan niet worden gecompiled als er warnings/errors zijn)
# -O3: 		optimizatie level 3 (zorget er onder andere voor dat de data sneller kan worden gelezen)
CFLAGS = -Wall -Wextra -Werror -O3

# Naam van executable
EXE = main

# Directory voor source code
SRC_DIR = src
# Directory voor object files
OBJ_DIR = obj

# Alle source code bestanden:
# wildcard zorgt ervoor dat alle bestanden die een .cpp extensie hebben en in de directory SRC_DIR zitten worden toegevoegd aan SRC
SRC = $(wildcard $(SRC_DIR)/*.cpp)
# Alle object files:
# TODO magie
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target $(EXE) / main:
$(EXE): $(OBJ)
	# g++ src1.o src2.o src3.o -o main
	# Linkt alle object files tot een executable
	$(CXX) $^ -o $@

# Target clean:
clean:
	# rm/del src1.o src2.o src3.o
	# Verwijdert de gegenereerde object files
	$(RM) $(OBJ)

# Target voor alle object files:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	# g++ -Wall -Wextra -Werror -O3 -o src1.cpp -o src1.o
	# Compilet een .cpp bestand in een .o bestand met de flags gespecificeerd in $(CFLAGS)
	$(CXX) $(CFLAGS) -c $< -o $@

# $(CXX) en $(RM) zijn ingebouwde variabelen:
# $(CXX): C++ compiler (g++/c++)
# $(RM):  Bestanden verwijderen (rm op *nix, del op NT)
