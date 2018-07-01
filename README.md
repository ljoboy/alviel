# ALVIEL
un logiciel de gestion d'une boutique fait en C avec Glade 3
##how to compile
gcc -export-dynamic -Wall `pkg-config --cflags --libs gtk+-3.0` ALVIEL.c -o ALVIEL `pkg-config --cflags --libs gtk+-3.0`
