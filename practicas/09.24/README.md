# Creación de paquetes `.ipk`

El formato de paquetes que usa OpenWRT, así como otras distribuciones
orientadas a uso en entornos embebidos, es `ipk`. Este formato es
gestionado por la arquitectura `opkg`. Estos son paquetes muy
sencillos, y pueden verse como un *recorte* de los de Debian (`.deb`)

Para esta práctica, van a generar un paquete para un programa que
hayan escrito para alguna entrega previa de esta materia. Podemos
seguir como documentación mínima básica esta
[respuesta en StackOverflow](https://stackoverflow.com/questions/17369127/extracting-and-creating-ipk-files)
o este
[hilo en Vuplus](http://www.vuplus-community.net/board/threads/how-to-create-ipk-packages-bh-bp.9009/).

Pasos a seguir:

1. En el directorio donde tengas tu paquete, crea un `Makefile` para
   la creación del .ipk
    1. Considera que, en caso de que ya tengas un `Makefile` global,
       puedes crear uno con otro nombre, e invocarlo con `make -f
       mi_makefile`
    2. O, por otro lado, podrías crear dentro de tu `Makefile` global
       un objetivo `package` o `ipk`, que genere el paquete. Depende
       de tu estilo, y de la naturaleza del paquete en cuestión.
2. Genera la descripción y los metadatos en el archivo `control`:

		Package: mipaquete
		Version: 0.3.1
		Description: Paquete ejemplo para el diplomado de Linux embebido
		Section: extras
		Priority: optional
		Maintainer: Gunnar Wolf <gwolf@iiec.unam.mx>
		License: GPL3+
		Architecture: all
		Homepage: https://github.com/gwolf/diplo_embebidos_3/tree/master/practicas/09.09
		Source: https://github.com/gwolf/diplo_embebidos_3/practicas/09.09/minombre

Ojo: ¿Depende de la existencia de algún otro paquete? Si sí, deben
agregar el campo `Depends:` indicándolos.

3. Sugiero que definas como variables en tu `Makefile` la ubicación
   del paquete generado:

        PKG = mipaquete
		VERSION = 0.3.1
		PKGDIR = ../
        IPKDEST = $(PKGDIR)/$(PKG)_$(VERSION).ipk

4. El objetivo de tu Makefile debe depender del *binario* de tu
   programa. Puedes seguir pasos análogos a los siguientes:

	    ipk:
		        mkdir -p $(PKGDIR)/build/$(PKG)
				cp *.py $(PKGDIR)/build/$(PKG)
				tar czvf control.tar.gz control
				cd $(PKGDIR); tar czvf ../data.tar.gz .; cd ..
				echo 2.0 > debian-binary
				ar r $(PKG).ipk control.tar.gz data.tar.gz  debian-binary

		clean-ipk:
			    rm -f control.tar.gz data.tar.gz

5. Prueba la creación de tu paquete; debe quedar disponible en el
   directorio que indicaste como `PKGDIR` de tu `Makefile`. ¡Cópialo a
   la imágen de OpenWRT que empleaste para la práctica de ayer e
   intenta instalarlo!
