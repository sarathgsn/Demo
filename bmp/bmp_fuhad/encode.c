#include <stdio.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
		uint width, height;
		// Seek to 18th byte
		fseek(fptr_image, 18, SEEK_SET);

		// Read the width (an int)
		fread(&width, sizeof(int), 1, fptr_image);
		printf("width = %u\n", width);

		// Read the height (an int)
		fread(&height, sizeof(int), 1, fptr_image);
		printf("height = %u\n", height);

		// Return image capacity
		return width * height * 3;
}

/* Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
		// Src Image file
		encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
		//Do Error handling
		if (encInfo->fptr_src_image == NULL)
		{
				perror("fopen");
				fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
				return e_failure;
		}

		// Secret file
		encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
		//Do Error handling
		if (encInfo->fptr_secret == NULL)
		{
				perror("fopen");
				fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);
				return e_failure;
		}

		// Stego Image file
		encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
		//Do Error handling
		if (encInfo->fptr_stego_image == NULL)
		{
				perror("fopen");
				fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
				return e_failure;
		}

		// No failure return e_success
		return e_success;
}



uint get_file_size(FILE *fptr)
{
		int count_size=0;
		int byte_read;
		char buff;
		while((byte_read=fread(&buff,sizeof(char),1,fptr))!=0)
		{
				count_size=count_size+1;

		}
		//		printf("counht=%d\n",count_size);
		return count_size;

}

Status check_encode(uint source_file_size,uint secret_file_size)
{
		if( ((54+3+1+secret_file_size)*8)<source_file_size)
		{
				printf("encoding is possible\n");
				return e_success;
		}
		else
		{
				printf("encoding cannot be done\n");
				return e_failure;
		}
}


Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image)
{
		int i;
		char buff;
		for(i=0;i<54;i++)
		{
				fseek(fptr_src_image,i,SEEK_SET);
				fread(&buff,sizeof(char),1,fptr_src_image);
				fseek(fptr_dest_image,i,SEEK_SET);
				fread(&buff,sizeof(char),1,fptr_dest_image);
		}
		return e_success;
}



Status encode_magic_string(char *magic_string,FILE *fptr_src_image,FILE *fptr_dest_image )

{
		int i,seek;
		char hash='#';

		seek=encode_byte_tolsb(hash,fptr_src_image,fptr_dest_image);
		printf("hash seek= %d\n",seek);



		for(i=0;i<3;i++)
		{
				seek=encode_byte_tolsb(magic_string[i],fptr_src_image,fptr_dest_image);
				printf("seek= %d\n",seek);
		}
}



uint encode_file_size(uint file_size,FILE *fptr_src_image,FILE *fptr_stego_image)
{
		encode_byte_tolsb(file_size,fptr_src_image,fptr_stego_image);
}



uint encode_data_to_image(FILE *fptr_secret_file,FILE *fptr_src_image,FILE *fptr_dest_image,uint file_size)
{
		char data;
		int i;
		uint seek;
		for(i=0;i<file_size;i++)
		{
				fseek(fptr_secret_file,i,SEEK_SET);
				fread(&data,sizeof(char),1,fptr_secret_file);
				seek=encode_byte_tolsb(data,fptr_src_image,fptr_dest_image);

				//	printf("inside seek %d\n",seek);
		}
		return seek;
}



uint encode_byte_tolsb(char data,FILE *fptr_src_image,FILE *fptr_dest_image)
{
		char buff;
		static uint seek=54;
		int i;
		for(i=0;i<8;i++)
		{
				fseek(fptr_src_image,seek,SEEK_SET);
				fread(&buff,sizeof(char),1,fptr_src_image);
				if(data&(1<<i))
				{
						buff=buff|1;
						fseek(fptr_dest_image,seek,SEEK_SET);
						fwrite(&buff,sizeof(char),1,fptr_dest_image);
						seek++;
				}
				else
				{
						buff=buff&(~1);
						fseek(fptr_dest_image,seek,SEEK_SET);
						fwrite(&buff,sizeof(char),1,fptr_dest_image);
						seek++;
				}
		}
		return seek;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest,uint seek)
{
		char buff;
		int byte_read;
		fseek(fptr_src,seek,SEEK_SET);
		fseek(fptr_dest,seek,SEEK_SET);


		while((byte_read=fread(&buff,sizeof(char),1,fptr_src))!=0)
		{
				fwrite(&buff,sizeof(char),1,fptr_dest);
		}

}



//decoding functions 

Status decode_open_files(EncodeInfo *encInfo)
{
		// stego Image file
		encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "r");
		//Do Error handling
		if (encInfo->fptr_stego_image == NULL)
		{
				perror("fopen");
				fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
				return e_failure;
		}

		return e_success;
}


Status check_if_encode(FILE *fptr_stego_image)
{
		char buff;
		buff=decode_lsb(fptr_stego_image);
		//printf("buff inside chek if encode is : %#x",buff);
		if(buff != '#')
		{
				return e_failure;
		}
		else
		{

				return e_success;
		}
}


Status password_verification(FILE *fptr_stego_image,char *password)
{
		int i;
		char buff;

		for(i=0;i<3;i++)
		{
				buff=decode_lsb(fptr_stego_image);
				if(buff != password[i])
						return e_failure;
		}
		return e_success;
}


char decode_lsb(FILE *fptr_stego_image)
{
		int i;
		int x;
		static uint seek=54;
		char buff;
		char dec=0x00;
		for(i=0;i<8;i++)
		{
				fseek(fptr_stego_image,seek,SEEK_SET);
				fread(&buff,sizeof(char),1,fptr_stego_image);
				x = (buff&1);
				if(x)
				{
						dec=dec|(1<<i);
				}
				seek;
		}
		return dec;
}

Status decode_data(FILE *fptr_stego_image)
{
		int i;
		uint file_size = decode_lsb(fptr_stego_image);

		for(i=0;i<file_size;i++)
		{
				printf("%c",decode_lsb(fptr_stego_image));
		}
}











