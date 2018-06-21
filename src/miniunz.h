#ifndef MINIUNZ_H
#define MINIUNZ_H

//! Look for possible filename in zip archive
char *find_possible_filename_in_zip (char *zipfilename, const char* extstr);

//! Extract file content from zip archive
int extract_file_in_memory (char *zipfilename, char *archivedfile,
			    size_t * unzipped_size);

#endif
