function credit_line() {
	echo -n "const unsigned char credits_$1[] = ";
	echo "$2" | python string.py
}


#              "                            "
credit_line 0  "          SplatooD"
credit_line 1  "      a Splatoon demake"
credit_line 2  "        Project Lead"
credit_line 3  "      John Carmackeral"
credit_line 4  "           Music"
credit_line 5  "     Nobuo Squidimatsu"
credit_line 6  "      Title & Postgame"
credit_line 7  "        Koji Ikarashi"
credit_line 8  "        Game Design"
credit_line 9  "       Squideo Kojima"
credit_line 10 "          Graphics"
credit_line 11 "         Squid Meier"
credit_line 12 "        Game Mechanics"
credit_line 13 "        American McGill"
credit_line 14 "      Splatoon (C) 2015"
credit_line 15 "          Nintendo"
credit_line 16 "     Thanks for playing!"

echo "const unsigned char * credits[] = {" credits_{0..16}, zero, zero, zero "};"
