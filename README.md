# Keylogger con Capturas de Pantalla y Sincronización

Este programa es un keylogger diseñado específicamente para sistemas Linux, escrito en C y creado en Ubuntu. Su función principal es registrar las teclas presionadas en un archivo llamado `keylogger.txt`, el cual se genera automáticamente. Además, el programa captura la pantalla de la computadora cada minuto, guardando las imágenes en una carpeta dedicada. Cada 5 minutos, tanto el archivo de registro como las capturas de pantalla son enviadas automáticamente a un servidor remoto para su almacenamiento y análisis.

## Requisitos Previos a la Instalación

Antes de instalar y ejecutar este script, asegúrate de ejecutar los siguientes comandos los cuales contienen librerias y comandos necesarios para el script:

1. `sudo apt update`
2. `sudo apt install libinput-tools`
3. `sudo apt install sshpass`
4. `sudo apt install imagemagick`

- **libinput-tools:** Necesario para que el script pueda manejar los eventos de entrada de los dispositivos.
- **sshpass:** Permite ejecutar el comando `sshpass -p` para enviar la contraseña del servidor al comando `rsync`.
- **imagemagick:** Proporciona el comando `import` que permite capturar capturas de pantalla.

## Instalación y Ejecución

Para instalar este programa, puedes simplemente copiar y pegar el script en un archivo `.c` ya creado en tu computadora.

También puedes ejecutar el comando `git clone` en la ruta donde desees guardar este script.

Antes de ejecutar el script asegurate de haber modificado las lineas necesarias marcadas en el script para ajustarlo a tu computadora.

Para ejecutar el script, basta con compilarlo con el siguiente comando:

`gcc -o nombre_ejecutable_que_quieras keylogger.c`

Una vez compilado con GCC, iniciaremos el ejecutable **COMO USUARIO ROOT** con el comando:
`sudo ./nombre_ejecutable_que_quieras`

Con esto, el programa se estará ejecutando todo el tiempo hasta que nosotros lo detengamos con `CTRL + C`. El programa creará la carpeta de `Screenshots` y el archivo `keylogger.txt`, listos para recopilar los datos y enviarlos al servidor.

## Ejemplos de Casos de Uso LEGALES

1. **Supervisión de seguridad en redes empresariales:**
   Este script puede ser utilizado por administradores de sistemas en redes corporativas para monitorear las actividades de las estaciones de trabajo, asegurando que no se realicen acciones indebidas o no autorizadas dentro de la red. Todo esto debe realizarse bajo la autorización correspondiente y en cumplimiento de las políticas de privacidad y seguridad de la empresa.

2. **Monitoreo de uso en entornos educativos:**
   En centros educativos, este script puede ayudar a los administradores a supervisar el uso de computadoras por parte de los estudiantes, garantizando que se usen solo para fines académicos y evitando el acceso a contenido inapropiado. Este uso debe ser transparente y comunicado tanto a los estudiantes como a sus tutores, cumpliendo con las regulaciones de privacidad aplicables.
