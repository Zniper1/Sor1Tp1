#!/bin/bash
#---------------------------------------
while  true
do
	touch "$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"/SuperMenu.desktop
	echo "[Desktop Entry]" >> SuperMenu.desktop
	echo "Name= SuperMenu" >> SuperMenu.desktop
	echo "Comment= Acceso directo del Supermenu" >> SuperMenu.desktop
	echo "Exec= $(pwd)/supermenu.sh" >> SuperMenu.desktop
	echo "Icon= $(pwd)/Icono" >> SuperMenu.desktop
	echo "Terminal=true" >> SuperMenu.desktop
	echo "Type=Application" >> SuperMenu.desktop
	chmod 744 SuperMenu.desktop
	break;
done

