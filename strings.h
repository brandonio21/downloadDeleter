/*******************************************************************************
 * strings.h
 * Brandon Milton
 * brandonio21
 * http://brandonio21.com
 *
 * October 4, 2014
 *
 * Holds all of the strings that are used and displayed by downloadDeleter.c
 ******************************************************************************/

/* Standard Strings */
#define USAGE_STRING "Usage: %s <OPTIONS> <downloadDirectory>\n"

/* Verbose Strings */
#define SCANNING_DIR "Scanning Directory: %s\n"
#define STATTING_FILE "Getting Info (via stat) for file: %s\n"
#define TIME_DETAILS "\tLast Access: %ld\n\tTime Diff: %ld\n"
#define REMOVING_FILE "Removing: %s"

/* Error Strings */
#define ERR_OPENDIR "Error opening the directory for reading: "
#define ERR_CLOSEDIR "Error closing the directory: "
#define ERR_STAT_FILE "Error getting info of (statting) a file: "
#define ERR_STAT_DIR "Error getting info of (statting) a directory: "
#define ERR_NOT_A_DIR "Error: The specified directory is not a directory\n"

/* Prompt Strings */
#define PROMPT_REQUIRES_DIR "Option -%c requires a directoroy to scan.\n"
#define PROMPT_UNKNOWN_OPTION "Unknown Option '-%c'\n"
#define PROMPT_UNKNOWN_CHAR "Unknown Option Character '\\x%x'\n"

