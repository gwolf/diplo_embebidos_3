# Documentos y ligas

## Linux: Espacio de usuario

### Elementos de programación en general
- [Tips de estilo para la programación](./doc/tips_programacion.pdf):
  Tips para que tus programas sean legibles y mantenibles
- [POSIX threads programming](https://computing.llnl.gov/tutorials/pthreads/):
  Un texto que presenta claramente ilustrado con código y diagramas
  los muchos aspectos de la programación multihilos con `pthreads`.
- [Programación en shel (bash / Bourne)](./doc/tut_shell.pdf)
- [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Sets (No Excuses!)](http://www.joelonsoftware.com/articles/Unicode.html)

### Gestión de dispositivos
- [Writing udev rules](http://reactivated.net/writing_udev_rules.html)
  Muy buena y completa explicación acerca de la creación de reglas
  para udev

### Comunicación entre procesos

- [socat — Handling all kinds of sockets](http://www.dest-unreach.org/socat/doc/linuxwochen2007-socat.pdf)
- [Manejo de señales en Unix](./doc/senales.pdf)

### Vista del sistema como un todo

- [Filesystem Hierarchy Standard v3.0](http://refspecs.linuxfoundation.org/FHS_3.0/fhs-3.0.pdf)
  ¿Dónde debe ir cada parte del sistema? ¿Cuál es la lógica global de
  un sistema de archivos en Linux?

#### Debian
- [Empaquetamiento software para distribuciones basadas en Debian](./doc/paquetes_deb.pdf):
  Tutorial básico para la creación de paquetes `.deb` sencillos
- [Debian Policy](https://www.debian.org/doc/debian-policy/)
  Descripción y justificación detallada de todos los aspectos para que
  un paquete `.deb` sea válido y correcto

#### OpenWRT

#### Sistema Buildroot

- [Manual de usuario de Buildroot](https://buildroot.uclibc.org/downloads/manual/manual.html);
  la sección 17.* habla acerca de cómo agregar paquetes nuevos al árbol
- [Using Buildroot for real projects](http://elinux.org/images/2/2a/Using-buildroot-real-project.pdf)

### Sistemas de archivos

- [http://linux-mtd.infradead.org/](Memory Technology Devices
  subsystem for Linux): Mucha documentación relativa a las propiedades
  y manejo de los dispositivos de almacenamiento MTD (Memory
  Technology Devices), sistemas de archivos estructurados en bitácora,
  y servicios conexos

### Contenedores, *namespaces* y *cgroups*
- [Notes from a container](https://lwn.net/Articles/256389/), artículo
  de Jonathan Corbet de 2007 que explica el concepto de *CGroups* y de
  *Namespaces*, y de cómo entre ambos implementan la infraestructura
  de contenedores. Ha habido un muy fuerte avance desde hace nueve
  años, pero el fundamento de los *Linux Containers* (`lxc`) es el
  mismo.

## Arranque del sistema

### Arranque temprano

- [How computers boot up (Gustavo Duarte)](http://duartes.org/gustavo/blog/post/how-computers-boot-up/),
  muy buen resumen con algunos esquemas interesantes acerca del
  proceso de arranque, algo enfocado en la arquitectura x86.
- [How your computer boots (O'Reilly: Understanding the Linux kernel)](http://www.linuxdevcenter.com/pub/a/linux/excerpts/linux_kernel/how_computer_boots.html)
- [Intel 64 and IA-32 architectures software developers manual](https://www-ssl.intel.com/content/www/us/en/processors/architectures-software-developer-manuals.html)
  Tres volúmenes de más de 500 páginas cada uno con información
  detallada de la familia de procesadores x86; particularmente el
  primer volumen incluye información específica del inicio de
  ejecución del sistema
- [OSDEV: Rolling your own bootloader](http://wiki.osdev.org/Rolling_Your_Own_Bootloader):
  ¿Qué hace falta para iniciar la carga de un sistema operativo? Si
  bien esta página está orientada al mundo x86, pero aún así, es clara
  e interesante.
- [OSDEV: Boot sequence](http://wiki.osdev.org/Boot_Sequence)
  Simple y clara explicación esquemática de lo que hace un sistema
  (tipo x86, basado en BIOS) conforme arranca, y hasta cargar el
  sistema operativo

#### U-boot
- [OSDEV: ARM overview](http://wiki.osdev.org/ARM_Overview): Dado que
  el mundo de los embebidos está dominado por la arquitectura ARM,
  vale la pena revisar cómo está estructurada esta arquitectura. Esta
  página da un muy buen vistazo inicial.
- [The DENX U-Boot and Linux Guide (DULG)](http://www.denx.de/wiki/DULG/WebHome)
- [A Handy U-Boot Trick](https://www.linuxjournal.com/content/handy-u-boot-trick)
  Artículo de Bharath Bhushan, 2013. Justifica por qué conviene
  levantar un SoC en la etapa de desarrollo con un núcleo provisto
  desde la red, y hace una buena revisión de la configuración
  necesaria para u-boot
- [U-Boot on i.MX6](https://boundarydevices.com/u-boot-on-i-mx6/) Otro
  vistazo al aranque empleando U-boot en una subarquitectura de ARM,
  cubriendo aspectos como los argumentos para la carga de Linux y el
  arranque desde red.
- [U-Boot quick reference for the Lite5200B development platform](https://www.lysator.liu.se/~kjell-e/embedded/U-boot-quick-reference-LITE5200BUBPG.pdf)
  El gestor de arranque más común en el mundo ARM (y en varias otras
  arquitecturas) es U-boot. Esta página presenta una buena
  introducción a la forma de interactuar con él; si bien es
  específico a una plataforma en particular, es suficientemente
  general para servir de referencia.

#### GRUB
- [OSDEV: GRUB](http://wiki.osdev.org/GRUB): El gestor de arranque
  GRUB, con su reescritura para la versión 2, se volvió prácticamente
  un sistema operativo completo. Esta página cuenta las
  características principales y algunas herramientas para creación de
  imágenes instaladas con GRUB2.

#### UEFI
- [UEFI boot: how does that actually work, then?](https://www.happyassassin.net/2014/01/25/uefi-boot-how-does-that-actually-work-then/)

### Arranque de Linux

- Video de Martin Michlmayr en DebConf16:
  [Debian on ARM devices, subtitulado en amara.org](http://www.amara.org/en/videos/ITAyeVQIwOPr/info/debian_on_arm_devices_2webm/?tab=video);
  [únicamente video](http://meetings-archive.debian.net/pub/debian-meetings/2016/debconf16/Debian_on_ARM_devices_2.webm)
- [The many methods of building a Debian image](http://people.linaro.org/~riku.voipio/debian-images/#/):
  Comentamos en clase la importancia de confiar en lo que tenemos
  instalado en nuestro entorno embebido, y en las alternativas que hay
  a descargar un archivo ya instalado. En esta ponencia (presentada en
  el DebConf15), Riku Voipio presenta varias estrategias para generar
  imágenes de sistema operativo. Principalmente orientado a
  proveedores de infraestructura (*la nube*), pero perfectamente
  aplicable a nuestro tema de interés.
- [Inicio del sistema](./doc/inicio_del_sistema.pdf), presentación que
  explica los mensajes de carga temprana del sistema Linux, tal cual
  aparecen en la bitácora.
- [How Linux boots](http://troubleshooters.com/linux/diy/howboot.htm),
  de Steve Litt, 2015. Descripción detallada y actualizada del proceso
  de arranque en Linux. Un poco centrado en x86, pero un buen
  documento en general.
- [Inicio del sistema](./doc/proceso_arranque_kernel.pdf): Seguimiento
  comentado de los mensajes a bitácora que presenta el núcleo de Linux
  al arrancar
- [ARM en QEMU](https://people.debian.org/~aurel32/qemu/armel/): Si no
  tienen una ARM a la mano, pueden emularlo en su x86 usando
  `qemu`. Esta página tiene (muy) breves instrucciones e imágenes
  listas para hacerlo.
- [System emulation using QEMU](https://gmplib.org/~tege/qemu.html):
  Más información acerca del uso de QEMU como emulador; incluye
  imágenes de arranque con Linux para distintas arquitecturas.

#### Ramdisk de inicio

- [Wiki de Ubuntu acerca del initramfs](https://wiki.ubuntu.com/Initramfs)

### Sistemas de inicio en Linux

- [A history of modern init systems (1992-2015)](http://blog.darknedgy.net/technology/2015/09/05/0/)
  Desarrollo histórico de los sistemas que ocupan el PID 1
- [Wiki de Ubuntu: initramfs](https://wiki.ubuntu.com/Initramfs)
  Descripción sencilla y bastante completa de cómo se conforma y cómo
  se genera un initramfs
- [systemd](./doc/systemd.es.pdf): Presentación que explica el sistema
  de gestión de arranque y de monitoreo de sistema (y de mucho más)
  `systemd`. La presentación es de Lucas Nussbaum (ex-líder del
  proyecto Debian), traducida por Gunnar Wolf
