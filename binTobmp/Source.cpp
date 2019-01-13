#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


const char *byte_to_binary(int x)
{
	static char b[9];
	b[0] = '\0';

	int z;
	for (z = 128; z > 0; z >>= 1)
	{
		strcat(b, ((x & z) == z) ? "1" : "0");
	}

	return b;
}



int leArquivo(char *nome){
	FILE *src;
	uint8_t vetor[320 * 240];
	src = fopen("3.bmp", "rb"); // CAMINHO PARA O .bmp
	if (src == NULL){
		printf("Nao foi possivel abrir o arquivo\n\n");
		return(1);
	}
	else
		printf("Arquivo aberto c sucessp \n");




}



int main(){

	int w = 320;
	int h = 240;
	int x, y, i, j, k;
	
	unsigned char * img = NULL;
	unsigned char * text = NULL;
	unsigned char r, g, b, byte, y0,u,y1,v;
	int filesize = 54 + 3 * w*h;  //w is your image width, h is image height, both int
	long lSize;

	FILE *dst, *src;
	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
	unsigned char bmppad[3] = { 0, 0, 0 };

	// Aloca tamanho da imagem em memoria
	img = (unsigned char *)malloc(3 * w*h);
	// Limpa a memoria alocada
	memset(img, 0, 3 * w*h);

	// Abre o arquivo em texto
	src = fopen("3.bmp", "rb"); // CAMINHO PARA O .bmp
	if (src == NULL){
		printf("Nao foi possivel abrir o arquivo\n\n");
		return(1);
	}
		
	// Resolve o tamanho da imagem
	fseek(src, 0, SEEK_END);
	lSize = ftell(src);
	rewind(src);
	text = (unsigned char*)malloc(sizeof(unsigned char)*lSize);

	//Le o arquivo para a memoria
	fread(text, 1, lSize, src);

	for (i = 0; i<w; i++)  // Para cada linha
	{
		for (j = 0; j<h; j++)  // Para cada coluna
		{
			
			
			x = i; y = (h - 1) - j; // Coordenadas do pixel
			byte = text[j * w + i]; // Byte correspondente a esse pixel no texto
			
			
			r = (byte) ;  // Canal vermelho do pixel
			g = (byte);// Canal verde do pixel
			b = (byte);   // Canal azul do pixel
			//            printf("R is %s\n", byte_to_binary(r));
			// g = green[i][j]*255;
			// b = blue[i][j]*255;
			// if (r > 255) r=255;
			// if (g > 255) g=255;
			// //f (b > 255) b=255;
			img[(x + y*w) * 3 + 2] = (unsigned char)(r); // Atribui na imagem o valor do pixel
			img[(x + y*w) * 3 + 1] = (unsigned char)(g); // Atribui na imagem o valor do pixel
			img[(x + y*w) * 3 + 0] = (unsigned char)(b); // Atribui na imagem o valor do pixel
		}
	}
	printf("Done creating the img! %d %d\n", i, j);


	// Cuida do cabecalho e dos padroes estruturais do formato BMP
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	// Escreve a imagem em disco
	dst = fopen("img.bmp", "wb");
	fwrite(bmpfileheader, 1, 14, dst);
	fwrite(bmpinfoheader, 1, 40, dst);
	for (i = 0; i<h; i++)
	{
		fwrite(img + (w*(h - i - 1) * 3), 3, w, dst);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, dst);
	}

	// Libera a memoria
	free(img);
	//  Fecha o arquivo
	fclose(dst);

	return 0;
}
