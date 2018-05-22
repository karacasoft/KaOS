./iso.sh

#qemu-system-x86_64 -cdrom kaos.iso -hda kaos.img
qemu-system-x86_64 -cdrom kaos.iso -drive format=raw,file=kaos.img