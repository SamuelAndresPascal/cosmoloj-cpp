## Développement

### Réinitialisation du projet, génération de la configuration CodeBlocks et du Makefile, et compilation:

```bash
cd learning-ri
rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
```

### Tests

```bash
cd learning-ri
bin/test
# ou bien 
make test
# ou bien 
ctest -V
```

### Build et test en un script (GNU/Linux)

```bash
cd learning-ri
. build.sh
```
