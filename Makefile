
all: 
	gcc -I./ -O -o ./upload_reading ./upload_reading.c ./mysql_message.c  `mysql_config --cflags --libs`



debug:
	gcc -I./ -g -O0 -fbuiltin -o ./upload_reading ./upload_reading.c ./mysql_message.c `mysql_config --cflags --libs`


clean:
		rm -rf *o *.out upload_reading
