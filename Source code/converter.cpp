# define _CRT_SECURE_NO_WARNINGS
# include "iGraphics.h"
# include <stdio.h>
# include <windows.h>
# include <string.h>
# pragma pack(2)

# define MAX_WIDTH 512
# define MAX_HEIGHT 620

void drawBMP(void);
void drawgrayBMP(void);

int filemanage(void);

char str[200], str2[200]; //str, directory of original image; str2, directory of grayscale image
unsigned char len = 0;
unsigned int pic_width, pic_height;
char mode = -3, filedone = 0, file_operation = 1, size_ok = 1;
unsigned char graycolor[MAX_WIDTH][MAX_HEIGHT], pixelcolor[MAX_WIDTH][MAX_HEIGHT][3];

/* filedone: used to check if the function 'filemanage' has been executed
file_operation: used to see if the function 'filemanage' has been executed suuccefully;
0, if successful;
otherwise, if unsuccessful.
size_ok: used to check if the image fits in the screen.
graycolor: saves the pixel info for grayscale image
pixelcolor: saves the pixel info of the original image. */

void drawTextBox(void)  //draws the text box to take the directory of the original image as input.
{
	iSetColor(0, 0, 0);
	iRectangle(250, 400, 800, 100);
}

void ConvertDesign(void)  //draws the arrow shaped 'convert button'.
{
	iLine(570, 330, 670, 330);
	iLine(670, 330, 670, 310);
	iLine(670, 310, 730, 350);
	iLine(730, 350, 670, 390);
	iLine(670, 390, 670, 370);
	iLine(670, 370, 570, 370);
	iLine(570, 370, 570, 330);
}

void iDraw()
{
	iClear();
	iShowBMP(0, 0, "background.bmp");

	if (mode == -3){       //Greetings
		iSetColor(0, 0, 0);
		iShowBMP(0, 0, "background_initial.bmp");
		mode = -2;
	}

	else if (mode == -2){   //showtime of 3 seconds
		iDelay(3);
		mode = -1;
	}

	else if (mode == -1){	//shows information about how to use the program
		iShowBMP(0, 0, "rules.bmp");
	}

	else if (mode == 0 || mode == 1){
		iSetColor(250, 250, 250);
		iText(350, 650, "Please enter the address of the BMP image you want to convert", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(15, 580, "Sample: If you want to convert a bmp image named 'image.bmp' in a folder named 'Pics' located in another folder named 'User'", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(15, 550, "in 'D' Drive, the address will be of the format - D:\\\\User\\\\Pics\\\\image.bmp", GLUT_BITMAP_TIMES_ROMAN_24);
		drawTextBox();
		if (mode == 1)  //Textbox activated
		{
			iText(260, 445, str, GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(255, 255, 255);
			iText(550, 350, "Text Box Activated", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(255, 255, 255);
		iText(250, 150, "Click in the box to activate, press ENTER to finish. Press END if you want to exit", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else if (mode == 2 || mode == 3){ //mode 2 means directory of original image is available
		if (!filedone) {
			filemanage();
			filedone = 1;
		}
		if (file_operation){  //execution status of 'filemanage' function checked
			if (file_operation == -2) iText(400, 400, "Sorry only BMP files are supported by this program.", GLUT_BITMAP_TIMES_ROMAN_24);
			else if (file_operation == -3) iText(400, 400, "Sorry, only 24 bit BMP images are supported by this program.", GLUT_BITMAP_TIMES_ROMAN_24);
			else if (file_operation == -4) iText(350, 400, "Sorry, the image is compressed. Only uncompressed images are supported by this program.", GLUT_BITMAP_TIMES_ROMAN_24);
			else if (file_operation == -1) iText(400, 400, "Sorry, image does not exist. Please recheck the address", GLUT_BITMAP_TIMES_ROMAN_24);
			mode = 3;
		}
		else if (!size_ok){ //image bigger than screen size.
			iText(500, 400, "Sorry, too large image to be shown.", GLUT_BITMAP_TIMES_ROMAN_24);
			iText(280, 350, "However, the grayscale version of the image has been created in the specified directory.", GLUT_BITMAP_TIMES_ROMAN_24);
			mode = 3;
		}
		else{
			drawBMP(); //original image drawn using pixel info from array pixelcolor
			iSetColor(0, 0, 0);
			ConvertDesign();
			iText(585, 345, "Convert", GLUT_BITMAP_TIMES_ROMAN_24);
			if (mode == 3){  //mode 3 means 'convert' button is clicked
				iSetColor(220, 20, 20);
				iText(585, 345, "Convert", GLUT_BITMAP_TIMES_ROMAN_24);
				//iShowBMP(1025 - pic_width / 2, 350 - pic_height / 2, str2);
				drawgrayBMP(); //grayscale image drawn using pixel info from array graycolor
			}
		}
		iSetColor(255, 255, 255);
		iText(20, 10, "Press END to exit", GLUT_BITMAP_HELVETICA_18);
		if (mode == 3) iText(530, 20, "Press Enter to convert another image", GLUT_BITMAP_HELVETICA_18);
	}
	else if (mode == 4) {  //mode 4 means end button pressed
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, 1300, 700);
		iShowBMP(1300-512, 700-573, "pol2.bmp");
		mode = 5;
	}
	else{
		iDelay(5);  //showtime of 7 seconds
		exit(0);
	}
}

void iMouseMove(int mx, int my)
{
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mx >= 250 && mx <= 1050 && my >= 400 && my <= 500 && mode == 0)
		{
			mode = 1;  //text box activation
		}
		if (mode == 2){
			if ((mx >= 570 && mx < 670 && my >= 330 && my <= 370) || (mx >= 670 && mx <= 730 && 2 * mx + 3 * my <= 2510 && 2 * mx - 3 * my <= 410))
			{
				mode = 3;  //convert button clicked
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void iKeyboard(unsigned char key)
{
	int i;
	if (mode == -1){
		if (key == '\r') mode = 0; //finished viewing rules page
	}
	if (mode == 1)
	{
		if (key == '\r'){      //setting directory for grayscale image
			i = strlen(str);
			strcpy(str2, str);
			str2[i - 4] = '2';
			str2[i - 3] = '.';
			str2[i - 2] = 'b';
			str2[i - 1] = 'm';
			str2[i] = 'p';
			str2[i + 1] = '\0';
			mode = 2;

		}
		else if (key == '\b' && len>0){  //activating backspace
			str[--len] = '\0';
		}
		else if (key != '\b'){
			str[len] = key;    //updating str
			len++;
		}
	}
	if (mode == 3){
		if (key == '\r'){   //user wants to re-execute the program
			for (unsigned char i = 0; i <= len; i++) str[i] = 0; //resetting 'str' for reusing
			len = 0;
			mode = 0;
			filedone = 0;
			file_operation = 1;   //resetting all the program controlling variables to initial value
			size_ok = 1;
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if ( mode > -1 && key == GLUT_KEY_END) mode = 4;  // terminate program
}

typedef struct
{
	char signature[2];
	unsigned int fileSize;
	unsigned int reserved;
	unsigned int offset;
} BmpHeader;     //File header of BMP file (14 bytes)

typedef struct
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planeCount;
	unsigned short bitDepth;
	unsigned int compression;
	unsigned int compressedImageSize;
	unsigned int horizontalResolution;
	unsigned int verticalResolution;
	unsigned int numColors;
	unsigned int importantColors;

} BmpImageInfo;  //image header of BMP file (40 bytes)

typedef struct   //used to extract pixel data from original image
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} Rgb;

int filemanage(void){
	FILE *inFile, *outfile;
	BmpHeader header;
	BmpImageInfo info;

	unsigned char color_table[256][4];    //color table for 8 bit image, total 256 combinations 
	for (int i = 0; i < 256; i++){
		for (int j = 0; j < 3; j++) color_table[i][j] = i;
		color_table[i][3] = 0;           //4th byte set to 0
	}
	if ((inFile = fopen(str, "rb")) == NULL){
		printf("File does not exist. Please recheck the given path.\n");
		return file_operation = -1;
	}
	
	if (fread(&header, sizeof(BmpHeader), 1, inFile) != 1) {
		printf("Error reading bmp header.\n");
		return errno;
	}

	if (header.signature[0] != 'B' || header.signature[1] != 'M'){
		fclose(inFile);
		return file_operation = -2;
	}

	if ((outfile = fopen(str2, "wb")) == NULL){
		printf("Error creating file.");
		return errno;
	}

	if (fwrite(&header, sizeof(BmpHeader), 1, outfile) != 1){
		printf("Error writng file.");
		return errno;
	}
	if (fread(&info, sizeof(BmpImageInfo), 1, inFile) != 1) {
		printf("Error reading image info.\n");
		return errno;
	}

	printf("\nBMP-Info (Original image):\n");
	printf("Width x Height: %u x %u\n", pic_width = info.width, pic_height = info.height);
	printf("Depth: %hd\n", info.bitDepth);
	printf("Number of Colors: %d\n", info.numColors);
	printf("Compression: %d\n", info.compression);

	if (pic_width > MAX_WIDTH || pic_height > MAX_HEIGHT) size_ok = 0;

	if (info.bitDepth != 24){
		fclose(inFile);
		fclose(outfile);
		remove(str2);
		return file_operation = -3;
	}
	if (info.compression){
		fclose(inFile);
		fclose(outfile);
		remove(str2);
		return file_operation = -4;
	}

	info.bitDepth = 8;            //creating 8 bit BMP image

	char padding = (pic_width % 4 != 0) ? (4 - pic_width % 4) : 0; //checking if padding is needed

	if (fwrite(&info, sizeof(BmpImageInfo), 1, outfile) != 1){
		printf("Error writing file.");
		return errno;
	}
	if ((fwrite(color_table, sizeof(color_table), 1, outfile)) != 1){
		printf("error writing color table.");
		return errno;
	}

	Rgb *pixel = (Rgb*)malloc(sizeof(Rgb));

	for (unsigned int j = 0; j<pic_height; j++) {
		int read = 0;
		for (unsigned int i = 0; i<pic_width; i++) {
			if (fread(pixel, sizeof(Rgb), 1, inFile) != 1) {
				printf("Error reading pixel!\n");
				return errno;
			}
			unsigned char gray;
			gray = 0.299*pixel->red + 0.587*pixel->green + 0.114*pixel->blue;
			if (size_ok){
				pixelcolor[i][j][0] = pixel->red;     //storing pixel data of original image 
				pixelcolor[i][j][1] = pixel->green;
				pixelcolor[i][j][2] = pixel->blue;
				graycolor[i][j] = gray;	   //storing pixel data of grayscale image
			}
			if ((fwrite(&gray, 1, 1, outfile)) != 1){
				printf("Error writing pixel.");
				return errno;
			}
			read += sizeof(Rgb);
			//printf( "Pixel %d: %3d %3d %3d\n", i+1, pixel->red, pixel->green, pixel->blue );
		}
		//printf("%d\n", read);
		if (read % 4 != 0) {
			read = 4 - (read % 4);
			//printf("Padding: %d bytes\n", read);
			fread(pixel, read, 1, inFile);    //reading the padding in original image
		}
		for (int k = 0; k < padding; k++){    //writing the padding in grayscale image
			unsigned char gray = 0;
			if ((fwrite(&gray, 1, 1, outfile)) != 1){
				printf("Error writing padding.");
				return errno;
			}
		}
	}

	printf("\nStatus: Conversion Completed.\n");
	free(pixel);
	fclose(inFile);
	fclose(outfile);
	return file_operation = 0;
}

void drawBMP(void){        //drawing original image
	for (unsigned int i = 0; i<pic_width; i++){
		for (unsigned int j = 0; j<pic_height; j++){
			iSetColor(pixelcolor[i][j][0], pixelcolor[i][j][1], pixelcolor[i][j][2]);
			iFilledRectangle(275 - pic_width / 2 + i, 350 - pic_height / 2 + j, 1, 1);
		}
	}
}

void drawgrayBMP(void){     //drawing grayscale image
	for (unsigned int i = 0; i<pic_width; i++){
		for (unsigned int j = 0; j<pic_height; j++){
			iSetColor(graycolor[i][j], graycolor[i][j], graycolor[i][j]);
			iFilledRectangle(1025 - pic_width / 2 + i, 350 - pic_height / 2 + j, 1, 1);
		}
	}
}


int main()
{
	iInitialize(1300, 700, "Grayscale Image Conversion");
	return 0;
}