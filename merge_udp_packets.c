#include <stdio.h>
#include <stdlib.h>

void merge_files(const char *output_filename, const char *files[], int num_files) {
    FILE *outfile = fopen(output_filename, "wb");
    if (outfile == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    for (int i = 0; i < num_files; i++) {
        FILE *infile = fopen(files[i], "rb");
        if (infile == NULL) {
            perror("Error opening input file");
            fclose(outfile);
            exit(1);
        }

        // Copy file content to the output file
        char buffer[1024];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), infile)) > 0) {
            fwrite(buffer, 1, bytes_read, outfile);
        }

        fclose(infile);
    }

    fclose(outfile);
    printf("Files have been merged into %s\n", output_filename);
}

int main() {
    // Array of upstream and downstream file paths
    const char *files[] = {
        "upstream1.bin", "upstream2.bin", "upstream3.bin", "upstream4.bin", "upstream5.bin",
        "downstream1.bin", "downstream2.bin", "downstream3.bin", "downstream4.bin", "downstream5.bin"
    };
    int num_files = sizeof(files) / sizeof(files[0]);

    // Merge files into a single binary file
    merge_files("merged_udp_packets.bin", files, num_files);

    return 0;
}
