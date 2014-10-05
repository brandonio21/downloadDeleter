/******************************************************************************
 * downloadDeleter.c
 * Brandon Milton
 * brandonio21
 * http://brandonio21.com
 *
 * October 1, 2014
 *
 * The purpose of this quick program is to automatically remove any file in the 
 * specified directory that is older than 30 days. May be more extinsible in
 * the future.
 *****************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "strings.h"

#define DEFAULT_DAY_LIMIT 30

static int dayLimit = DEFAULT_DAY_LIMIT;
static int verbose = 0;

void displayArgMessage(const char* programArg)
{
  fprintf(stderr, USAGE_STRING, programArg);
}

void scanDirectory(const char *directoryToScan, int recursive)
{
  if (verbose == 1)
    fprintf(stderr, SCANNING_DIR, directoryToScan);

  /* Now let's get all of the files within the directory */
  DIR *directory = opendir(directoryToScan);
  if (directory == NULL) 
  {
    perror(ERR_OPENDIR);
    exit(EXIT_FAILURE);
  }

  /* The directory is valid and opened. Scan through files. */
  struct dirent *directoryItem;
  while ((directoryItem = readdir(directory)) != NULL)
  {
    char directoryToStat[BUFSIZ];
    memset(directoryToStat, 0, BUFSIZ);

    strcat(directoryToStat, directoryToScan);
    strcat(directoryToStat, "/");
    strcat(directoryToStat, directoryItem->d_name);

    /* Check to see if the file is a directory or not */
    if (directoryItem->d_type != DT_DIR)
    {
      /* Check to see if the file's last modify date is > limit */
      struct stat itemStat;

      if (verbose == 1)
        fprintf(stderr, STATTING_FILE, directoryToStat);

      if (stat(directoryToStat, &itemStat) == -1)
      {
        /* There was an error statting a specific file */
        perror(ERR_STAT_FILE);
        exit(EXIT_FAILURE);
      }

      time_t lastAccessTime = itemStat.st_atime;
      time_t now = time(NULL);
      if (verbose == 1)
        fprintf(stderr, TIME_DETAILS,
            lastAccessTime, (now - lastAccessTime));

      if ((now - lastAccessTime) > (dayLimit * 60 * 60))
      {
        if (verbose == 1)
          fprintf(stderr, REMOVING_FILE, directoryToStat);
        remove(directoryToStat);
      }
    }
    else if (recursive)
    {
      if (strcmp(directoryItem->d_name, "." ) != 0 &&
          strcmp(directoryItem->d_name, "..") != 0)
        scanDirectory(directoryToStat, recursive);
    }
  }

  /* We are done with the mentioned directory. Close it */
  if (closedir(directory) == -1)
  {
    perror(ERR_CLOSEDIR);
    exit(EXIT_FAILURE);
  }

}

int main(int argc,char* argv[])
{
  /* Check to see if the user provided the recursive argument */
  int option;
  int recursive = 0;
  char *directoryToScan = NULL;
  while ((option = getopt(argc, argv, "rt:v")) != -1)
  {
    switch (option)
    {
      case 'r':
        recursive = 1;
        break;
      case 't':
        dayLimit = (strtol(optarg, NULL, 10) * 24 * 60 * 60);
        break;
      case 'v':
        verbose = 1;
        break;
      case '?':
        if (optopt == 'r')
          fprintf(stderr, PROMPT_REQUIRES_DIR, optopt);
        else if (isprint(optopt))
          fprintf(stderr, PROMPT_UNKNOWN_OPTION, optopt);
        else
          fprintf(stderr, PROMPT_UNKNOWN_CHAR, optopt);
        exit(EXIT_FAILURE);
      default:
        displayArgMessage(argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  if (directoryToScan == NULL && (optind > 0 && optind < argc))
    directoryToScan = argv[optind];
  else if (directoryToScan == NULL)
  {
    displayArgMessage(argv[0]);
    exit(EXIT_FAILURE);
  }



  /* Verify that there is nothing wrong with the download dir */
  struct stat fileStat;
  if (stat(directoryToScan, &fileStat) == -1)
  {
    /* There was an error getting the stat of the specified downloads dir */
    perror(ERR_STAT_DIR);
    exit(EXIT_FAILURE);
  }

  /* There is nothing wrong with the download file. See if it is a dir */
  if (!S_ISDIR(fileStat.st_mode))
  {
    /* The download directory is not a directory at all. */
    fprintf(stderr, ERR_NOT_A_DIR);
    exit(EXIT_FAILURE);
  }
  scanDirectory(directoryToScan, recursive);
  return EXIT_SUCCESS;
}
