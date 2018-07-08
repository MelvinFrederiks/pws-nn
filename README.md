# PROFIELWERKSTUK NEURALE NETWERKEN

##### door Melvin Frederiks



### Vereisten

Voor het uitvoeren van het programma zijn geen 3rd-party libraries nodig. Om het programma op je eigen machine van source te builden, zijn de volgende benodigdheden nodig:

* GNU C++ Compiler (g++)
* GNU make (make)

Deze zijn te installeren met:

```
sudo apt-get install g++ make
```

op Debian en Debian-afgeleide distros.

Op Windows kunnen g++ en make gerund worden met behulp van [MinGW](http://www.mingw.org)

### Installatie

Download de repository:

```
wget https://github.com/MelvinFrederiks/pws-nn/archive/master.zip
```

Unzip de repository:

```
unzip master.zip
```

Ga naar de root directory:

```
cd pws-nn-master
```

Verplaats de bestanden `train-images-idx3-ubyte` en `train-labels-idx1-ubyte` van de [dataset](http://yann.lecun.com/exdb/mnist/) naar de ./data directory


Run de Makefile

```
make main
```

Dit maakt een executable genaamd `main` die kan worden uitgevoerd met 

```
./main
```
