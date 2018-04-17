#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
    red=`tput setaf 1`;
    green=`tput setaf 2`;
    blue=`tput setaf 4`;
    bg_blue=`tput setab 4`;
    reset=`tput sgr0`;
    bold=`tput setaf bold`;


#------------------------------------------------------
# VARIABLES GLOBALES
#------------------------------------------------------
proyectoActual="$(pwd)";
proyectos="/home/andrew/Documents/repo_GitLab/repos.txt";

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
    
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver estado del proyecto";
    echo -e "\t\t\t b.  Subir el proyecto al repositorio Git (PUSH)";
    echo -e "\t\t\t c.  Actualizar proyecto en la PC (PULL)";
    echo -e "\t\t\t d.  Verificar si tengo una aplicacion instalada";
    echo -e "\t\t\t e.  Buscar archivos por directorio, extension y nombre"; 
    echo -e "\t\t\t f.  Busqueda y concatenado de strings";
    echo -e "\t\t\t g.  Canto Marado";
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}-------------------------------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue} ${red} ${bold}-------------------------------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
    echo $1;
    while true; do
        echo "desea ejecutar? (s/n)";
            read respuesta;
            case $respuesta in
                [Nn]* ) break;;
                   [Ss]* ) eval $1
                break;;
                * ) echo "Por favor tipear S/s ó N/n.";;
            esac
    done
}

notificar () {
	notify-send "Deberia verificar si el proyecto esta actualizado con la opcion A."
}

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------

a_funcion () {
	imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
	decidir "cd $proyectoActual; git status";
}


b_funcion () {
	imprimir_encabezado "\tOpción b.  Subir el proyecto al repositorio Git (PUSH)";
	decidir "cd $proyectoActual; git add -A";
	read -p "Ingrese un mensaje para su Commit: " Mensaje
	decidir "cd $proyectoActual; git commit -m "$Mensaje"";
	decidir "cd $proyectoActual; git push origin master";
}



c_funcion () {
	imprimir_encabezado "\tOpción c.  Actualizar el proyecto en la PC (PULL)";
	decidir "cd $proyectoActual; git pull origin master";
}



d_funcion () {
	imprimir_encabezado "\tOpción d.  Verificar si tengo una aplicacion instalada";

	echo "Introduzca aplicacion a verificar?"
	read app

	dpkg --get-selections > Copia
	resultado=$( grep -wc "^$app" Copia );

	if [ "$resultado" != "0" ];
		then
			echo "El programa esta instalado"
		else
			echo "El programa no esta instalado"
	fi
}



e_funcion () {
    imprimir_encabezado "\tOpción e.  Buscar archivos por directorio, extension y nombre";

read -p "Ingrese path a verificar -> " directorio
read -p "Ingrese el extension del archivo -> " extension
read -p "Ingrese el nombre o parte del nombre del archivo -> " nombre

find $directorio -name "*.$extension" | grep -i "$nombre" > Copia

resultado=$( grep -c "$nombre" Copia );
if [ "$resultado" != "0" ];
	then
		echo "Con Directorio: $directorio y Extension $extension existen los siguientes archivos:"
		echo "";
		cat Copia
	else
		echo "";
		echo "No existen Archivos asociados con el directorio y el extension"
	fi
rm Copia

}



f_funcion () {
	imprimir_encabezado "\tOpción f. Busqueda y concatenado de strings";

read -p "Ingrese el path completo incluyendo el archivo -> " archivo
read -p "Ingrese un String para buscar en el archivo -> " string

grep -i  "$string"  $archivo >> salida.out

}

g_funcion () {
	imprimir_encabezado "\tOpción g. Canto Marado";

}


#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    notificar;
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done


