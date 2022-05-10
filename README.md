# Compo 2022

## MS-DOS

Para compilarlo para DOS necesitarás tener instalado [DJGPP] en tu equipo y una máquina virtual
de DOS con [DOSBox] o [DOSBox-X].

Desde la máquina DOS ejecuta:

```sh
make -f MAKEFILE.DOS
```

## Linux

Para compilarlo para Linux sólo tienes que llamar a:

```sh
make -f Makefile.linux
```

Necesitarás tener las librerías SDL2 instaladas, si utilizas Debian o un derivado (como Ubuntu),
puedes usar:

```sh
sudo apt-get install libsdl2-dev
```

## WebAssembly

Todavía estoy trabajando para tener una versión decente que funcione en WebAssembly pero
en principio bastaría con ejecutar (necesitarás tener instalado clang, llvm y lld):

```sh
make -f Makefile.wasm
```

> :bulb: Si no te compila comprueba que tengas al menos clang 12 y que esté disponible como 
> clang-12. Si no fuera el caso, siempre puedes reemplazarlo por `clang`.