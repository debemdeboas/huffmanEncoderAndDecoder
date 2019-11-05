#!/bin/bash

currentver="$(g++ -dumpversion)"
requiredver="6"

if [ "$(printf '%s\n' "$requiredver" "$currentver" | sort -V | head -n1)" = "$requiredver" ]; then
	tr -d '\015' <king_james.txt >king_james_UNIX.txt
	mkdir obj
	g++ -pthread -std=c++17 -O -Wall -c Node.cpp -o obj/Node.o
	g++ -pthread -std=c++17 -O -Wall -c HuffmanUtils.cpp -o obj/HuffmanUtils.o
	g++ -pthread -std=c++17 -O -Wall -c EncoderUtils.cpp -o obj/EncoderUtils.o
	g++ -pthread -std=c++17 -O -Wall -c DecoderUtils.cpp -o obj/DecoderUtils.o
		
	echo "Would you like to [E]ncode the file, [D]ecode the file or [B]oth?"
	read -n1 -p "[E/D/B] " choice
	echo
	case $choice in
		e|E)
			g++ -pthread -std=c++17 -O -Wall obj/* Encode.cpp -o Encode
			./Encode
			;;
		d|D)
			g++ -pthread -std=c++17 -O -Wall obj/* Decode.cpp -o Decode
			./Decode
			;;
		b|B)
			g++ -pthread -std=c++17 -O -Wall obj/* EntryPoint.cpp -o EncodeAndDecode
			./EncodeAndDecode
			;;
		*)
			echo
			echo "Error: Invalid operation. Please select a valid option."
			;;
	esac
	rm -rf obj
else
	echo "This script requires g++6!"
fi
