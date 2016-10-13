# Corriendo un userland nuevo sobre un kernel conocido

Tengo una computadora ARM con la que puedo arrancar un kernel dado de
Linux, pero quiero usar otra distribución sobre de éste. Por ejemplo,
tengo una Raspberry Pi 3, pero quiero lanzar una instalación de
OpenWRT o de Buildroot, y no tiene soporte para éste. ¿Cómo hago?

1. Elimino la partición `root` (típicamente la 2) de la tarjeta SD
   donde está la instalación funcionando (emplear `fdisk`). Me quedo
   con un sistema inútil.
2. Del sistema para una plataforma *similar*, extraigo la partición de
   espacio de usuario que *quiero* tener. Ejemplo:  (como root)
        # losetup -f -P instalacion.img
		# dd if=/dev/loop0p2 of=/tmp/nuevo_root.img
		# losetup -D
   **ojo:** ¡Verifiquen qué es lo que hace y cómo opera `losetup`!
3. En la tarjeta SD, creo nuevamente la partición 2, y le "vuelco" la
   partición que acabo de extraer
        # fdisk /dev/sdb     # ¿Verificaste que sea sdb?
		(... crear la partición como sdb2 ...)
		# dd if=/tmp/nuevo_root.img of=/dev/sdb2
    1. En realidad, podría no haberla borrado, y seguir usando la
       anterior — Pero asumiendo que quieren una partición destino más
       chica que la original, lo hacemos de este modo.
4. En caso de ser necesario, ajusten los parámetros de inicio del
   `UBoot` (o del gestor de arranque de la Raspberry, de ser el caso).

A entregar: Un documento de *texto* indicando la distribución origen y
destino que emplearon, cualquier cosa que se tuviera que desviar de
estas instrucciones, grado de éxito.

¡No se rindan a la primera! Me gustaría que me muestren un sistema que
incia *bien*.
