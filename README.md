downloadDeleter.c
=================

This program is meant to be run periodically (generally on a cron job) and point
to the user's download directory. By default, this will automatically delete 
files that haven't been accessed in more than 30 days. This allows the user
to conserve space on their harddrive by getting rid of those nasty XGB large
.ISO files and other extremely large download files.

### Compiling ###
In order to compile, use the following command
```
make
```

If you cannot use makefiles, simply compile the `downloadDeleter.c` file using
your favorite C compiler.


### Usage ###
In order to use the program, simply make the following call:
```
./downloadDeleter <downloadDirectory>
```

The following options are also available:  
`-r` - Recursively search directories, deleting files that are in any 
subdirectories as well.  
`-v` - Verbose: Display any debug messages that will allow the user to see
what exactly is going on.  
`-t <days>` - Specify how old files have to be before they are deleted (default
is 30).

By default, this program does not delete any directories, just their contents.




#### Systemd Integration ####
After running `make`, .service and .timer files are populated within the 
working directory. These files can then be moved into the systemd service
directory and daily operation can then be enabled.

For example,
```
make
sudo cp downloadDeleter.service /etc/systemd/system
sudo cp downloadDeleter.timer /etc/systemd/system
sudo systemctl enable downloadDeleter.timer
```
The download deleter should then run daily!

