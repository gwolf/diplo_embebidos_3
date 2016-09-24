# Instalación de paquetes en una máquina virtual con OpenWRT

Para esta práctica, bajen la
[imágen genérica de la versión actual](https://downloads.openwrt.org/chaos_calmer/15.05.1/x86/kvm_guest/openwrt-15.05.1-x86-kvm_guest-combined-ext4.img.gz)
de *OpenWRT*, e instálenle el
[módulo de kernel *e1000*](https://downloads.openwrt.org/chaos_calmer/15.05.1/x86/kvm_guest/packages/base/kmod-e1000_3.18.23-1_x86.ipk),
necesario para que reconozca la tarjeta de red de la máquina virtual
*KVM*.

Recuerden: Los módulos para el hardware que elijan están en el
directorio `packages`, dentro del mismo directorio de donde
descargaron su imágen.

Pasos a seguir:

1. Desde la computadora *anfitrión*, Bajar OpenWRT y el módulo
2. Crear un sistema de archivos adicional (un *disco adicional
   virtual*) para comunicar los contenidos. Para crear
   `/tmp/archivo.img` de 1MB y formatearlo como ext2:

		$ dd if=/dev/zero of=/tmp/archivo.img bs=1024 count=1024
		$ /sbin/mkfs.ext2 /tmp/archivo.img
3. Montar este sistema de archivos virtual. Como root:

        # mount /tmp/archivo.img /mnt
		# cp kmod_e1000_3.18.24-1_x86.ipk /mnt
		# umount /mnt
4. Lanzar la máquina virtual con este disco "insertado", montarlo, e
   instalar el paquete. Desde el anfitrión:

	    $ qemu-system-x86 -drive index=0,file=openwrt-15.05.1-x86-kvm_guest-combined-ext4.img -drive index=1,file=/tmp/archivo.img

   Esperar unos segundos a que arranque, y desde la máquina virtual:

        # mount /dev/sdb /mnt
		# opkg -i /mnt/kmod-e1000_3.18.23-1_x86.ipk

5. Configurar la red para recibir su configuración por DHCP. OpenWRT
   permite configurar el sistema por medio de su herramienta UCI:

        # uci set network.lan.proto=dhcp
		# uci delete network.lan.ifname
		# uci delete network.lan.netmask

6. Generen un archivo con *su nombre* en el directorio raiz, para que
   pueda identificar a cada una de las máquinas virtuales. En mi caso:

		# touch /GunnarWolf.txt

7. *Apaguen* la máquina virtual resultante, compriman el sistema de
   archivos, renómbrenlo con su nombre, y súbanlo a GitHub. En mi
   caso, por ejemplo, podría ser `openwrt_gunnar_wolf.img.gz`
