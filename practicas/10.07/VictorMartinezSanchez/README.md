# Running a new inte galileo userland on a known kernel

I finally succedded on my adventure to run a new userland partition on an existing one. I tried with other images and rootfs partitions but I could not make it work until a finally make it.

I worked with the intel Galileo Gen2 board, and to begin with I had already a partitio on a SD card, that was taken from [this](https://software.intel.com/en-us/iot/hardware/galileo/downloads) webpage, and the new userland I used was taken from this other [page](https://sourceforge.net/projects/galileodebian/files/).

I can upload the linux images because they are so big that my internet connection will fail if I try, so I upload some images:

![initial_content](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/initial_content.png)
	This is the initial content of the sdcard partition.

![new_content](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/new_rootfs_content.png)
	This is the content of the image partition.

![create_partition](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/create_partition.png)
	This shows how a format the image.

![copy_content](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/copy_content.png)
	This shows the copy of the content from the image to the sdcard.

![files_copied](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/test_files_copied.png)
	This is the new content on the sdcard.

![kernel_panic](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/kernel_panic.png)
	This is the kernel panic I got

![error_login](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/error_login.png)
	Once I fix the error (linux kernel parameters) I could not login in, the password ant the user never let me login.

![success](https://github.com/MASVictor/diplo_embebidos_3/blob/10.07-new-userland/practicas/10.07/VictorMartinezSanchez/img/success.png)
	Finally I could with the help of `init=/bin/bash`.

