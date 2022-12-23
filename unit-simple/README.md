
Bibliothèques nécessaires pour faire tourner les tests:

```
sudo apt-get install libcppunit-dev libcppunit-1.15-0
```

Réinitialisation du projet, génération de la configuration CodeBlocks et du Makefile, et compilation:

```
cd simple-unit
rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
```
