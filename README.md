# Defendiendo-las-Torres

[75.40]Algoritmos y Progamacion I-Catedra mendez-TP Final

Es una conjunto de tps que se fueron agregando cosas al programa

## Enunciados

- [TP1](2020_1C_TP1)
- [TP2](2020_1C_TP2)
- [TP3](2020_1C_TP3)

## Objetivos

### TP3

- Se familiarice con el manejo de archivos en C.
- Utilice las funciones acordes al tipo de archivo y/o forma de acceso.
- Realice apropiadamente las operaciones con archivos.
- Ponga en práctica el uso de argumentos por línea de comando.

## **Comandos**

### **Mostrar Ranking**

Listará todos los jugadores con los puntajes obtenidos al terminar las partidas.
Habrá un ranking por cada configuración ya que dependiendo de ella variará la dificultad del juego.
Queda a criterio del alumno como y que información visualizar en el listado.

#### **Comando: ranking**

Recibirá como parámetro la cantidad de jugadores a mostrar y el archivo de configuración para el cual se quiere ver el ranking.

Un ejemplo de este comando es:

```txt
./defendiendo ranking listar=25 config=mi_configuración.txt
```

- Ambos parámetros son opcionales.
  - **listar=num**: Listara la cantidad de jugadores puestos en num
    - En caso de no recibir la cantidad de jugadores a mostrar, se mostrarán todos.
  - **config=mi_configuracion.txt** listara el ranking de esa configuracion
    - En caso de no recibir el archivo de configuración se mostrará el ranking de la configuración por defecto.

### **Crear Camino**

Permitirá crear los caminos para utilizar durante las partidas

#### **Comando: crear_camino**

Recibirá como parámetro el nombre del archivo.Le permitirá al jugador crear los caminos para utilizar luego.

Un ejemplo de este comando es:

```txt
./defendiendo crear_camino mis_caminos.txt
```

- En caso de no ingresar nombre de archivo, el comando no será válido y no se realizará ninguna acción.
- En caso de existir un archivo de caminos con ese nombre, el archivo se sobreescribirá.

### **Crear Configuracion**

Los archivos de configuración permitirán jugar con mayor flexibilidad.

En características que no se deseen configurar se les asignará el valor -1.
Se deben poder configurar las siguientes características del juego:

- Resistencia de las torres: `RESISTENCIA_TORRES=<puntos de la torre 1>,<puntos de la torre 2>`
- Cantidad de enanos al iniciar cada nivel: ` ENANOS_INICIO=<enanos nivel 1>,<enanos nivel 2>,<enanos nivel 3>,<enanos nivel 4> `
- Cantidad de elfos al iniciar cada nivel: `ELFOS_INICIO=<elfos nivel 1>,<elfos nivel 2>,<elfos nivel 3>,<elfos nivel 4>`
- Cantidad de enanos extra y el costo para cada torre:
`ENANOS_EXTRA=<cantidad de enanos extra>,<costo a la torre 1>,<costo a la torre2>`
- Cantidad de elfos extra y el costo para cada torre: `ELFOS_EXTRA=<cantidad de elfos extra>,<costo a la torre 1>,<costo a la torre 2>`
- Ánimo de los enanos: `ENANOS_ANIMO=<Fallo de los enanos>,<Crítico de los enanos>`
- Ánimo de los elfos: `ELFOS_ANIMO=<Fallo de los elfos>,<Crítico de los elfos>`
- Velocidad del juego: `VELOCIDAD=<Tiempo que se detendrá cada turno (float)>`
- Caminos: ` CAMINOS=<Ruta del archivo de caminos a utilizar en esta configuación `

#### **Comando: crear_configuracion**

Recibirá como parámetro el nombre del archivo. Le permitirá al jugador crear una configuración inicial para utilizar luego.

Un ejemplo de este comando es:

```txt
./defendiendo crear_configuracion mi_configuracion.txt
```

- En caso de no ingresar nombre de archivo, el comando no será válido y no se realizará ninguna acción.
- En caso de existir un archivo de configuración con ese nombre, el archivo se sobreescribirá.

### **Ver Partida Grabada**

Le permitirá a los usuarios, ver una partida grabada anteriormente, la visualización es automática.

#### **Comando: poneme_la_repe**

Recibirá como parámetro el nombre del archivo con la partida y la velocidad de reproducción.

Un ejemplo de este comando es:

```txt
./defendiendo poneme_la_repe grabacion=mi_partida.dat velocidad=0.5
```

- En caso de no ingresar nombre de archivo, el comando no será válido y no se realizará ninguna acción.
- En caso de no ingresar velocidad de reproducción, por defecto se tomará velocidad 1.

### **Jugar Partida**

Permitirá jugar una partida utilizando configuraciones creadas por los usuarios. Adicionalmente el jugador podrá guardar la partida para verla luego.

#### **Comando: jugar**

Recibirá como parámetros el nombre del archivo de caminos a utilizar y, en casode querer grabar la partida, el nombre del archivo donde se grabará la partida.

Un ejemplo de este comando es:

```txt
./defendiendo jugar config=mi_configuracion.txt grabacion=mi_partida.dat
```

- Ambos parámetros son opcionales.
  - Si el archivo de configuración no existe o no fue ingresado, debe utilizarse la configuración por defecto.
  - Si el archivo de grabación ya existe, se sobreescribirá, si el parámetro grabación no fue ingresado, la partida no se grabará.

## Compilado

```bash
gcc *.c -o defendiendo -std=c99 -Wall -Werror -Wconversion
```

o con makefile:

```mkaefile
make
```
