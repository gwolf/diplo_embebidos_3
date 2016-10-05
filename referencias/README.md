# Documentos y ligas

## Linux: Espacio de usuario

### Comunicación entre procesos

- [socat — Handling all kinds of sockets](http://www.dest-unreach.org/socat/doc/linuxwochen2007-socat.pdf)

### Sistema Buildroot

- [Manual de usuario de Buildroot](https://buildroot.uclibc.org/downloads/manual/manual.html);
  la sección 17.* habla acerca de cómo agregar paquetes nuevos al árbol
- [Using Buildroot for real projects](http://elinux.org/images/2/2a/Using-buildroot-real-project.pdf)

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

### Arranque de Linux

- Video de Martin Michlmayr en DebConf16:
  [Debian on ARM devices, subtitulado en amara.org](http://www.amara.org/en/videos/ITAyeVQIwOPr/info/debian_on_arm_devices_2webm/?tab=video);
  [únicamente video](http://meetings-archive.debian.net/pub/debian-meetings/2016/debconf16/Debian_on_ARM_devices_2.webm)
- [How Linux boots](http://troubleshooters.com/linux/diy/howboot.htm),
  de Steve Litt, 2015. Descripción detallada y actualizada del proceso
  de arranque en Linux. Un poco centrado en x86, pero un buen
  documento en general.
- [A Handy U-Boot Trick](https://www.linuxjournal.com/content/handy-u-boot-trick)
  Artículo de Bharath Bhushan, 2013. Justifica por qué conviene
  levantar un SoC en la etapa de desarrollo con un núcleo provisto
  desde la red, y hace una buena revisión de la configuración
  necesaria para u-boot

### Sistemas de inicio en Linux

- [A history of modern init systems (1992-2015)](http://blog.darknedgy.net/technology/2015/09/05/0/)
  Desarrollo histórico de los sistemas que ocupan el PID 1
- [Wiki de Ubuntu: initramfs](https://wiki.ubuntu.com/Initramfs)
  Descripción sencilla y bastante completa de cómo se conforma y cómo
  se genera un initramfs
