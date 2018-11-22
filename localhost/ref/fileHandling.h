#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#define TEMP_DIR "/tmp/upload"
#define TEMP_SHRED_COUNT_FILE TEMP_DIR"/shredCount"
#define TEMP_ENCRYPT_COUNT_FILE TEMP_DIR"/encryptCount"
#define TEMP_SHRED_FILESLIST TEMP_DIR"/shredFilesList"
#define TEMP_ENCRYPTED_FILESLIST TEMP_DIR"/encryptFilesList"
#define TEMP_JOIN_FILELIST TEMP_DIR"/joinFileList"
#define TEMP_JOIN_COUNT TEMP_DIR"/joinCount"
#define TEMP_ENCRYPTED_FILENAMEHASH TEMP_DIR"/encryptedFileNameHash"
#define TEMP_ENCRYPTED_COUNT TEMP_DIR"/encryptedCount"

#define FILE_SPLIT_SEPARATOR "??"
#define FILE_ENCRYPT_SEPARATOR "."
#define DOT "."

#define FILE_SPLIT_MAX 4

#define ZERO 0

#define FILENAME "FN"
#define FILE_ABSOLUTE_LOCATION "FAL"
#define FILE_SPLIT_STATE "FSS"
#define FILE_SPLIT_NAME "FSN"
#define FILE_DECRYPTED_NAME "FDN"
#define FILE_SPLIT_ABSOLUTE_LOCATION "FSAL"
#define FILE_SPLIT_ENCRYPTED_STATE "FSES"
#define ENCRYPTED_SPLIT_NAME "ESN"
#define ENCRYPTED_ABSOLUTE_LOCATION "EAL"
#define FILE_DECRYPTED_JOINED_STATE "FDJS"
#define FILE_DECRYPTED_STATE "FDS"

unsigned long long int fileHandling_GetSizeInBytes(char *fileLocation);
int fileHandling_CreateDir(char *userId);
char *fileHandling_GetShredSuffix(int i);
char *fileHandling_GetSHA256Hash(char *fileAbsLoc);
int fileHandling_DeleteShreds(char *splitFileName, char *userId);
char *fileHandling_EncryptShreds(char *fileName, char *type, char *userId, char *originalFileNameHash, int totalLinkedAccounts);
char *fileHandling_DecryptShreds(char *fileName, char *userId, char *type);
char *fileHandling_JoinShreds(char *fileName, char *type, char *userId);
char *fileHandling_SplitFile(char *fileAbsLoc, char *fileName, char *type, char *userId, char *brewScore);

#endif /* FILE_HANDLING_H */
