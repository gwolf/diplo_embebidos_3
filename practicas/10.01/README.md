# Construcción de un paquete para buildroot

Podemos agregar nuestro propio software como un conjunto de recetas a
buildroot, para construir un sistema que cumpla con nuestros
requisitos. Esta práctica requiere que empaqueten *algo* — ¿Qué? No
importa. Encuentra un `.tar.gz` en la red o sube uno a un servidor que
controles, y trabaja con él para instalarlo en el sistema.

1. Instalación de un entorno local para Buildroot

   Clona el repositorio Git de buildroot en tu computadora:

        git clone git://git.buildroot.net/buildroot

   Te recomiendo instalar las bibliotecas de `ncurses`, para poder
   usar el sistema de construcción basado en menúes "amigables"; en
   las distribuciones derivadas de Debian, instalen el paquete
   `libncurses5`.

2. Construye un buildroot *pelón* — Entra a `make menuconfig`, acepta
   la configuración default, y construye con `make`.

3. Genera un directorio para tu paquete: dentro del depósito de
   buildroot, crea `packages/mipaquete` (donde *mipaquete* idealmente
   será le nombre del software que estás empaquetando). Genera dentro
   de éste directorio la declaración del paquete (`Config.in`) y la
   receta para construirlo (`mipaquete.mk`).

   Puedes encontrar un ejemplo de estos archivos en la práctica
   realizada en clase por Gunnar,
   [calculadora.diff](./gwolf/20161001-calculadora.diff)
4. Notifica a los Makefiles de buildroot acerca de tu paquete,
   editando `packages/Config.in`, agregando referencia al `Config.in`
   de tu directorio recién creado. Nuevamente, puedes ver esto en la
   práctica realizada en clase.
5. Entra por `make menuconfig`, entra a `Target packages`, a la
   categoría donde incluiste tu paquete, y actívalo.
6. Construye nuevamente tu imagen de buildroot. Verifica que los
   archivos que requieres estén incluídos
    1. ¿Dónde? La construcción se lleva a cabo dentro del directorio
       `output`; explora un poco sus subdirectorios para encontrar la
       lógica de construcción.
7. Haz el *commit* con tus cambios al repositorio local, y entrega
   *únicamente las diferencias* (puedes obtenerlas con `git diff
   HEAD~`).

Te recomiendo intentar comprender la razón de ser de las otras
opciones de configuración que ofrece buildroot. ¿Cuándo las usarías?
¿Para qué? ¿Cómo podrías agregar funcionalidad a ella?

Te recomiendo como referencia el [manual de Buildroot](https://buildroot.uclibc.org/downloads/manual/manual.html)
