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
#oibf
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
    echo -e "\t\t\t b.  Actualizar el proyecto";
    echo -e "\t\t\t c.  Verificar aplicaciones instaladas";
    echo -e "\t\t\t d.  Buscar archivo por directorio, nombre y formato";        
    echo -e "\t\t\t e.  ";        
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
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
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

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion () {
        imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
        decidir "cd $proyectoActual; git status";
}

b_funcion () {
          imprimir_encabezado "\tOpción b";
#echo 

read -p "Ingrese el path del archivo a subir: " path
echo $1;
    while true; do
        echo "El path $path es correcto? (s/n)" ;
            read respuesta;
            case $respuesta in
                [Nn]* ) break;;
                   [Ss]* ) eval $1
		git add -A "$path"
		echo "El comando ingresado por la terminal fue: git add -A $path "
		echo 
                break;;
		* ) echo "Por favor tipear S/s ó N/n.";;
		esac
		
    done
#git add -A "$path"
#
read -p "Ingrese un comentario: " comment
git commit -m  "$comment"
echo "El comando ingresado por la terminal fue: git commit -m 'comentario' "
echo $1;
    while true; do
        echo "Desea subir el archivo? (s/n)";
            read respuesta;
            case $respuesta in
                [Nn]* ) break;;
                   [Ss]* ) eval $1
		git push origin master
		echo "El comando ingresado por la terminal fue: git push origin master"
		echo Subiendo...
                break;;
		* ) echo "Por favor tipear S/s ó N/n.";;
		esac
		
    done
  
    
}

c_funcion () {
	imprimir_encabezado "Verificar aplicaciones instaladas";

	#!/bin/bash
	echo "Introduzca aplicacion a verificar?"
	read app

	dpkg --get-selections > Copia && grep -wc "^$app" Copia

	resultado=$( grep -wc "^$app" Copia );

	if [ "$resultado" != "0" ];
	 then
		echo "El programa esta instalado"
	else
		echo "El programa no esta instalado"
	fi

}

d_funcion () {
    imprimir_encabezado "\tOpción d";

read -p "Ingrese path a verificar -> " direc
read -p "Ingrese el formato del archivo -> " format
read -p "Ingrese el nombre o parte del nombre del archivo -> " name
resultdirec=$( find "$direc" -type f -name "*.$format" | grep -i $name );
if [ "$resultdirec" != "0" ];then
	echo "El archivo $name.$format existe en el directorio $direc."
else
	echo "El archivo no existe en este directorio."
fi

}


e_funcion () {
    imprimir_encabezado "\tOpción e";        
    #completar
}


#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done
 

