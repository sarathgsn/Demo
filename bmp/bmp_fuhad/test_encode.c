#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "encode.h"
#include "types.h"


int main()
{

		EncodeInfo encInfo;
		uint img_size;
		uint secret_file_size;
		char *password;
		char *decodepass;
		int seek;

		// Fill with sample filenames
		encInfo.src_image_fname = "beautiful.bmp";
		encInfo.secret_fname = "secret.txt";
		encInfo.stego_image_fname = "stego_img.bmp";

		// Test open_files
		if (open_files(&encInfo) == e_failure)
		{
				printf("ERROR: %s function failed\n", "open_files" );
				return 1;
		}
		else
		{
				printf("SUCCESS: %s function completed\n", "open_files" );
		}

		// Test get_image_size_for_bmp
		img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
		printf("INFO: Image size = %u\n", img_size);

		 encInfo.file_size=get_file_size(encInfo.fptr_secret);//secret file size
		 printf("INFO: SECRET file size : %u\n",encInfo.file_size);

		//cheak wheather encoding is possible or not

		check_encode(img_size,encInfo.file_size);
		//to copy the bmp header from sorce file to destination image file

		copy_bmp_header(encInfo.fptr_src_image,encInfo.fptr_stego_image);

		if((copy_bmp_header(encInfo.fptr_src_image,encInfo.fptr_stego_image)!=e_success))
		{
				return 1;
		}

		//to scan the password
scan_password :
		password=malloc(3*sizeof(char));
		printf("Enter the 3 letter password\n");
		__fpurge(stdin);
		scanf("%[^\n]",password);
		if(strlen(password)!=3)
		{
				goto scan_password;
		}


		//encode password with magic string char '#'
		encode_magic_string(password,encInfo.fptr_src_image,encInfo.fptr_stego_image);

		//encoding the file size
		encode_file_size(encInfo.file_size,encInfo.fptr_src_image,encInfo.fptr_stego_image);

		//encoding data to image
		if(seek=encode_data_to_image(encInfo.fptr_secret,encInfo.fptr_src_image,encInfo.fptr_stego_image,encInfo.file_size));
		{
				printf("data encoded\n");
		}
		

		//copy remaining data of the image
if( copy_remaining_img_data(encInfo.fptr_src_image, encInfo.fptr_stego_image,seek)==e_success)
{
		printf("encoding is complete\n");
}


//decoding 

		if (decode_open_files(&encInfo) == e_failure)
		{
				printf("ERROR: %s function failed\n", "open_files" );
				return 1;
		}
		else
		{
				printf("SUCCESS: %s function completed\n", "open_files" );
		}

		if(check_if_encode(encInfo.fptr_stego_image)==e_success)
		{
				printf("Please wait .....DECODING....\n");
		}
		else
		{
				printf("File does not contain the magic string  \n"); //where magic string given here is #
				return 1;
		}

		
		//to scan the password during decoding
scan_decodepassword :
		decodepass=malloc(3*sizeof(char));
		printf("Enter the 3 letter password\n");
		__fpurge(stdin);
		scanf("%[^\n]",decodepass);
		if(strlen(password)!=3)
		{
				goto scan_decodepassword;
		}

		if(password_verification(encInfo.fptr_stego_image,decodepass)==e_success)
		{
				printf("Entered password is correct\n.....DECODING....\n");
		}
		else
		{
				printf("Entered password is incorrect\n");
				return 1;
		}

		decode_data(encInfo.fptr_stego_image);






		return 0;
}
