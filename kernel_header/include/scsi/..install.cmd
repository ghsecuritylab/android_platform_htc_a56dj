cmd_/home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi/.install := perl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/kernel/scripts/headers_install.pl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/kernel/include/scsi /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi arm scsi_bsg_fc.h scsi_netlink.h scsi_netlink_fc.h; perl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/kernel/scripts/headers_install.pl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/include/scsi /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi arm ; perl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/kernel/scripts/headers_install.pl /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/include/generated/scsi /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi/$$F; done; touch /home/aa/Project/A56DJDUGL_HTC_WWE_M601_CRC_Sense80GP_Stable_503111/out/target/product/htc_a56djdugl/obj/KERNEL_OBJ/usr/include/scsi/.install