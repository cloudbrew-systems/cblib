// The new version (src/cpp/FileHandling.cpp --> localhost/src/Files.cpp)
#include "Files.h"

/* Create the file handling directory */
int Files::createdir(std::string userid) {
    std::string cmd = "mkdir -p ";
    cmd += FILES_TEMPDIR + "/" + userid;
    system(cmd.c_str());
	return CB_SUCCESS;
}

/* Size of the file in bytes */
unsigned long long int Files::sizeinbytes(std::string fileabsloc)
{
	struct stat statbuf;
	stat(fileabsloc.c_str(), &statbuf);
	unsigned long long int size = statbuf.st_size;
	return size;
}

/* Get the appropriate suffix of the file shred */
std::string  Files::shredsuffix(int i)
{
	switch(i)
	{
		case 1:
			return "aa";
			break;
		case 2:
			return "ab";
			break;
		case 3:
			return "ac";
			break;
		case 4:
			return "ad";
			break;
		case 5:
			return "ae";
			break;
		case 6:
			return "af";
			break;
		case 7:
			return "ag";
			break;
		case 8:
			return "ah";
			break;
		case 9:
			return "ai";
			break;
		case 10:
			return "aj";
			break;
		case 11:
			return "ak";
			break;
		case 12:
			return "al";
			break;
		case 13:
			return "am";
			break;
		case 14:
			return "an";
			break;
		case 15:
			return "ao";
			break;
		case 16:
			return "ap";
			break;
		case 17:
			return "aq";
			break;
		case 18:
			return "ar";
			break;
		case 19:
			return "as";
			break;
		case 20:
			return "at";
			break;
		case 21:
			return "au";
			break;
		case 22:
			return "av";
			break;
		case 23:
			return "aw";
			break;
		case 24:
			return "ax";
			break;
		case 25:
			return "ay";
			break;
		case 26:
			return "az";
			break;
		case 27:
			return "ba";
			break;
		case 28:
			return "bb";
			break;
		case 29:
			return "bc";
			break;
		case 30:
			return "bd";
			break;
		case 31:
			return "be";
			break;
		case 32:
			return "bf";
			break;
		case 33:
			return "bg";
			break;
		case 34:
			return "bh";
			break;
		case 35:
			return "bi";
			break;
		case 36:
			return "bj";
			break;
		case 37:
			return "bk";
			break;
		case 38:
			return "bl";
			break;
		case 39:
			return "bm";
			break;
		case 40:
			return "bn";
			break;
		case 41:
			return "bo";
			break;
		case 42:
			return "bp";
			break;
		case 43:
			return "bq";
			break;
		case 44:
			return "br";
			break;
		case 45:
			return "bs";
			break;
		case 46:
			return "bt";
			break;
		case 47:
			return "bu";
			break;
		case 48:
			return "bv";
			break;
		case 49:
			return "bw";
			break;
		case 50:
			return "bx";
			break;
		case 51:
			return "by";
			break;
		case 52:
			return "bz";
			break;
		case 53:
			return "ca";
			break;
		case 54:
			return "cb";
			break;
		case 55:
			return "cc";
			break;
		case 56:
			return "cd";
			break;
		case 57:
			return "ce";
			break;
		case 58:
			return "cf";
			break;
		case 59:
			return "cg";
			break;
		case 60:
			return "ch";
			break;
		case 61:
			return "ci";
			break;
		case 62:
			return "cj";
			break;
		case 63:
			return "ck";
			break;
		case 64:
			return "cl";
			break;
		case 65:
			return "cm";
			break;
		case 66:
			return "cn";
			break;
		case 67:
			return "co";
			break;
		case 68:
			return "cp";
			break;
		case 69:
			return "cq";
			break;
		case 70:
			return "cr";
			break;
		case 71:
			return "cs";
			break;
		case 72:
			return "ct";
			break;
		case 73:
			return "cu";
			break;
		case 74:
			return "cv";
			break;
		case 75:
			return "cw";
			break;
		case 76:
			return "cx";
			break;
		case 77:
			return "cy";
			break;
		case 78:
			return "cz";
			break;
		case 79:
			return "da";
			break;
		case 80:
			return "db";
			break;
		case 81:
			return "dc";
			break;
		case 82:
			return "dd";
			break;
		case 83:
			return "de";
			break;
		case 84:
			return "df";
			break;
		case 85:
			return "dg";
			break;
		case 86:
			return "dh";
			break;
		case 87:
			return "di";
			break;
		case 88:
			return "dj";
			break;
		case 89:
			return "dk";
			break;
		case 90:
			return "dl";
			break;
		case 91:
			return "dm";
			break;
		case 92:
			return "dn";
			break;
		case 93:
			return "do";
			break;
		case 94:
			return "dp";
			break;
		case 95:
			return "dq";
			break;
		case 96:
			return "dr";
			break;
		case 97:
			return "ds";
			break;
		case 98:
			return "dt";
			break;
		case 99:
			return "du";
			break;
		case 100:
			return "dv";
			break;
	}
	return "zz"; /* Should not reach here */
}

/* Calculate the SHA256 hash */

// TODO: Work on this one and make it C++ standard by using the SHA256 algo directly
// std::string getsha256hash(std::string fileabsloc)
// {
// 	std::string cmd;
//     // char cmd[MAX_CMD_LEN*2] = {'\0'};
// 	FILE *fp;
// 	struct stat statbuf;
// 	// char *encryptedFisleNameHash = MEM_XMALLOC(MAX_LEN);
	
// 	snprintf(cmd, MAX_CMD_LEN*2, "sha256sum \"%s\" | awk {'print $1'} > %s", fileAbsLoc, TEMP_ENCRYPTED_FILENAMEHASH);
// 	system(cmd);

// 	if(stat(TEMP_ENCRYPTED_FILENAMEHASH, &statBuf) == 0)
// 	{
// 		fp = fopen(TEMP_ENCRYPTED_FILENAMEHASH, "r");
// 		if(fp)
// 		{
// 			if (fgets(encryptedFileNameHash, MAX_LEN, fp) != NULL)
// 				strtok(encryptedFileNameHash, "\n");/* Remove new line from end */
// 		}
// 		fclose(fp);
// 	}

// 	snprintf(cmd, MAX_CMD_LEN*2, "rm -f %s", TEMP_ENCRYPTED_FILENAMEHASH);
// 	system(cmd);

// 	return encryptedFileNameHash;
// }


// int main() {
//     std::unique_ptr<Files> fl(new Files("test"));
//     fl->createDir("1000");    

//     return 0;
// }
