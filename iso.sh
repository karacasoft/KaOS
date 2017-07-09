set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/kaos.kernel isodir/boot/kaos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "KaOSVengeance" {
	multiboot /boot/kaos.kernel
}
EOF
grub-mkrescue -o kaos.iso isodir
