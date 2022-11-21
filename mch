#!/bin/sh
# (M)y (C)/Cpp (H)elper
while test $# -gt 0
do
    case "$1" in
        --build) 
            echo "Building..."
            gcc main.c -lm -Wall -Wextra -pipe;
            ;;
        --build-release)
            echo "Building for release..."
            gcc main.c -lm -Wall -Wextra -pipe -Ofast;
            ;;
        --run)
            echo "Running..."
            if gcc main.c -lm -Wall -Wextra -pipe;
            then
                ./a.out;
            fi
            ;;
        --run-release)
            echo "Running release version..."
            if gcc main.c -lm -Wall -Wextra -pipe -Ofast;
            then
                ./a.out;
            fi
            ;;
    esac
    shift
done
echo "Finished :)"
exit 0
