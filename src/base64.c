#include "base64.h"

static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int base64_index(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

char* encode_to_base64(const unsigned char* input, size_t input_len, size_t* output_len) {
    size_t output_length = 4 * ((input_len + 2) / 3);
    char* encoded = (char*)malloc(output_length + 1);
    if (!encoded) return NULL;
    
    size_t j = 0;
    for (size_t i = 0; i < input_len; i += 3) {
        uint32_t octet_a = input[i];
        uint32_t octet_b = (i + 1 < input_len) ? input[i + 1] : 0;
        uint32_t octet_c = (i + 2 < input_len) ? input[i + 2] : 0;
        
        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        
        encoded[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded[j++] = (i + 1 < input_len) ? base64_chars[(triple >> 6) & 0x3F] : '=';
        encoded[j++] = (i + 2 < input_len) ? base64_chars[triple & 0x3F] : '=';
    }
    
    encoded[output_length] = '\0';
    *output_len = output_length;
    return encoded;
}

unsigned char* decode_from_base64(const char* input, size_t input_len, size_t* output_len) {
    if (!output_len) {
        return NULL;
    }
    *output_len = 0;

    if (!input || input_len == 0) {
        unsigned char* decoded = (unsigned char*)malloc(1);
        if (!decoded) {
            return NULL;
        }
        decoded[0] = '\0';
        return decoded;
    }

    size_t cleaned_len = 0;
    char* cleaned = (char*)malloc(input_len + 1);
    if (!cleaned) {
        return NULL;
    }

    for (size_t i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (c == '\n' || c == '\r' || c == '\t' || c == ' ' || c == '\f' || c == '\v') {
            continue;
        }
        cleaned[cleaned_len++] = (char)c;
    }
    cleaned[cleaned_len] = '\0';

    size_t max_decoded_len = (cleaned_len * 3u) / 4u + 1u;
    unsigned char* decoded = (unsigned char*)malloc(max_decoded_len);
    if (!decoded) {
        free(cleaned);
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i + 3 < cleaned_len; i += 4) {
        int values[4];
        int valid_group = 1;

        for (int k = 0; k < 4; k++) {
            char c = cleaned[i + k];
            if (c == '=') {
                values[k] = -1;
                continue;
            }

            values[k] = base64_index(c);
            if (values[k] < 0) {
                valid_group = 0;
                break;
            }
        }

        if (!valid_group) {
            continue;
        }

        if (values[2] < 0 && values[3] < 0) {
            decoded[j++] = (unsigned char)((values[0] << 2) | (values[1] >> 4));
        } else if (values[2] >= 0 && values[3] < 0) {
            decoded[j++] = (unsigned char)((values[0] << 2) | (values[1] >> 4));
            decoded[j++] = (unsigned char)(((values[1] & 0x0F) << 4) | (values[2] >> 2));
        } else {
            decoded[j++] = (unsigned char)((values[0] << 2) | (values[1] >> 4));
            decoded[j++] = (unsigned char)(((values[1] & 0x0F) << 4) | (values[2] >> 2));
            decoded[j++] = (unsigned char)(((values[2] & 0x03) << 6) | values[3]);
        }
    }

    decoded[j] = '\0';
    *output_len = j;
    free(cleaned);
    return decoded;
}
