#!/bin/bash

fichas=""
tps=""

for arg in "$@"
do
    case $arg in
        -fichas=*)
            fichas="${arg#*=}"
            ;;
        -tps=*)
            tps="${arg#*=}"
            ;;
        *)
            echo "Uso: ./agenteConnect6.sh -fichas=<blancas|negras> -tps=[segundos]"
            exit 1
            ;;
    esac
done

if [[ "$fichas" != "blancas" && "$fichas" != "negras" ]]; then
    echo "Error: -fichas debe ser 'blancas' o 'negras'"
    exit 1
fi

if ! [[ "$tps" =~ ^[0-9]+$ ]]; then
    echo "Error: -tps debe ser un número entero que representa los segundos"
    exit 1
fi

dir=$(dirname "$0")
if [[ ! -f "$dir/connect6" ]]; then
    echo "El archivo 'connect6' no se encontró. Ejecutando 'make'..."
    make
    if [[ $? -ne 0 ]]; then
        echo "Error: 'make' falló al compilar 'connect6'"
        exit 1
    fi
fi

exec "$dir/connect6" "$fichas" "$tps"
