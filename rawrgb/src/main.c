#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct {
	uint32_t width,height,
		nr_channels;
	u_int8_t *image_data;
} Image;

int main(int argc,char **argv) {
	if(argc!=3) {
		printf("ERROR invalid argument count! \n");
		printf("usage: rawrgb image.jpg output_image.rgb \n");
		return EXIT_FAILURE;
	}
	char * input_file_path=argv[1];
	Image input_image={0};
	input_image.image_data=stbi_load(input_file_path,&input_image.width,&input_image.height,&input_image.nr_channels,3);
	
	*if(!input_image.image_data) {
		printf("Error on loading image.\n");
		return EXIT_FAILURE;
	}
	printf("%s, %u x %u - %u channels \n",input_file_path,input_image.width,input_image.height,input_image.nr_channels);
	printf("Writing bytes..\n");
	FILE *fp;
	fp=fopen(argv[2], "w+");
	fwrite(&input_image.width,sizeof(uint32_t),1,fp);
	fwrite(&input_image.height,sizeof(uint32_t),1,fp);
	fwrite(input_image.image_data,sizeof(u_int8_t),input_image.width*input_image.height*3,fp);
	fclose(fp);
	stbi_image_free(input_image.image_data);
	return EXIT_SUCCESS;
}

