#ifndef ENCODE_H
#define ENCODE_H

#include "types.h" // Contains user defined types

/* Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _EncodeInfo
{
    /* Source Image info */
    char *src_image_fname;
    FILE *fptr_src_image;
    uint image_capacity;
    uint bits_per_pixel;
    char image_data[MAX_IMAGE_BUF_SIZE];

    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    char extn_secret_file[MAX_FILE_SUFFIX];
    char secret_data[MAX_SECRET_BUF_SIZE];
    long size_secret_file;
    uint file_size;

    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

} EncodeInfo;


/* Encoding function prototype */

/* Check operation type */
OperationType check_operation_type(char *argv[]);

/* Read and validate Encode args from argv */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);

/* Perform the encoding */
Status do_encoding(EncodeInfo *encInfo);

/* Get File pointers for i/p and o/p files */
Status open_files(EncodeInfo *encInfo);

/* check capacity */
Status check_capacity(EncodeInfo *encInfo);

/* Get image size */
uint get_image_size_for_bmp(FILE *fptr_image);

/* Get file size */
uint get_file_size(FILE *fptr);

/* Copy bmp image header */
Status copy_bmp_header(FILE * fptr_src_image, FILE *fptr_dest_image);

/*to check wheather encoding is possible or not */
Status check_encode(uint source_file_size,uint secret_file_size);

/* Store Magic String */
Status encode_magic_string(char *magic_string,FILE *fptr_src_image,FILE *fptr_stego_mage );

/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);

/* Encode secret file size */
Status encode_secret_file_size(long file_size,FILE *fptr_src_image,FILE *fptr_stego_image );

/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo);

/* Encode function, which does the real encoding */
uint encode_data_to_image(FILE *secret_file, FILE *fptr_src_image, FILE *fptr_stego_image,uint file_size);


/* Encode a byte into LSB of image data array */
uint encode_byte_tolsb(char data, FILE *fptr_src_image,FILE *fptr_stego_image);

/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest,uint seek);


/*decoding prototypes */

/*open the stego image for decoding*/
Status decode_open_files(EncodeInfo *encInfo);

/* check wheather the magic string there or not*/
Status check_if_encode(FILE *fptr_steg0_image);

/*password verification at decoding stage*/
Status password_verification(FILE *fptr_stego_image,char *password);

/* decoding the lsb bits */
char decode_lsb(FILE *fptr_stego_image);

/*decoding the data from the stego image file*/
Status decode_data(FILE *fptr_stego_image);




#endif
