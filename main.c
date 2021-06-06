#include <stdio.h>

#include "encr_mode.h"

int main() 
{
	uint8_t IV[] = 
	{
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c  
	}; 

	uint8_t key[] = 
	{
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c  
	}; 

	char string[] = {"asdasfgjhfsaasdadsffsa"};

	int numberofblocks;

	uint8_t **inputblocks = make_blocks_form_string (string, &numberofblocks);

	uint8_t **encrypted = encryption_decryptionCTR (inputblocks, numberofblocks, 1, key);

	uint8_t **decrypted = encryption_decryptionCTR (encrypted, numberofblocks, 1 , key);
	
	encrypted = encryption_CBC(decrypted, numberofblocks, IV, key);

	decrypted = decryption_CBC(encrypted, numberofblocks, IV, key);

	encrypted = encryption_decryptionOFB (decrypted, numberofblocks, IV, key);

	decrypted = encryption_decryptionOFB (encrypted, numberofblocks, IV, key);
	
	printf("%s", make_string_form_block (decrypted, numberofblocks));

	free(inputblocks);

	free(encrypted);

	free(decrypted);

	return 0;
}
