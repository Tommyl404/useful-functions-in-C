#include <stdbool.h>

typedef struct int64x2_t{
	uint64_t val[2];
} int64x2_t;

typedef struct {
	int64x2_t data;
} block_t;

void buffer_to_bool_array(const uint8_t* buffer, size_t numValues, bool* bool_array) {
    for (size_t i = 0; i < numValues; ++i) {
        bool_array[i] = (buffer[i / 8] & (1 << (i % 8))) != 0;
    }
}

void uint8_to_bool_array(uint8_t byte, bool* bool_array) {
    for (size_t i = 0; i < 8; ++i) {
        bool_array[i] = (byte & (1 << i)) != 0;
    }
}


void uint64_to_uint8_array(uint64_t num, uint8_t arr[8]) {
    for (int i = 0; i < 8; ++i) {
        arr[i] = (num >> (8 * i)) & 0xFF; // Isolate each byte
    }
}

int64x2_t pack_128_bits_into_int64x2_t(uint8_t* data) {
    int64x2_t result;

    // Adjusting for the updated Convert_to_double_word which assumes big-endian input
    // Load the first 64 bits (MSB) into the first element of the array within the struct
    result.val[0] = Convert_to_double_word(data);

    // Load the next 64 bits into the second element of the array within the struct
    result.val[1] = Convert_to_double_word(data + 8);

    return result;
}

uint64_t Convert_to_double_word(uint8_t array_of_bytes[])
{
	uint64_t temp = 0x00;

		for (int index = 0; index < 8; index++)
			temp +=  (uint64_t)array_of_bytes[index]<<(index*8);


	return temp;
}
