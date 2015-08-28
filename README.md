Integrantes
=========

- Mateo Carvaja Munoz
- Julian Andres Rodriguez

DESCRIPCION
----

Este programa modifica un sistema de ficheros
con formato:

```sh
MagicNumber[16bytes],na[8bytes],nb[8bytes],
indexa[na*8bytes],indexb[nb*8bytes],
data[na*24bytes + nb*16bytes]
```

FUNCIONAMIENTO
-----------

Para corre el programa haga uso del siguiente
formato:

```sh
upfsreg <nr> <tipo> <campo> <numero de veces> <valor> <fichero>
```

Donde:

- nr: Numero registro.
- tipo: Tipo de registro [a, b].
- campo: Campo del registro a modificar [a1, a1, a3, b1, b2].
- numero de veces: Cuantas veces se debe modificar el registro.
- valor: En cuanto se debe modificar el registro.
- fichero: Nombre del fichero a modificar.

Nota: Ejecute "make run" para ver un ejemplo.