#define _DEFAULT_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

int main(int argc, char* argv[]){
    for (int i = 0; i < argc; i++){
        char path[256];
        if (i == 0 && argc != 1) continue;

        if (argc == 1) path[0] = '.';
        else strcpy(path, argv[i]);

        struct stat state;
        if (access(path, F_OK) == 0 || argc == 1){
            stat(path, &state);
            mode_t mode = state.st_mode;

            printf("%c", (mode & S_IFREG) ? '-' : (mode & S_IFDIR) ? 'd' : '?');
            printf("%c", (mode & S_IRUSR) ? 'r' : '-');
            printf("%c", (mode & S_IWUSR) ? 'w' : '-');
            printf("%c", (mode & S_IXUSR) ? 'x' : '-');

            printf("%c", (mode & S_IRGRP) ? 'r' : '-');
            printf("%c", (mode & S_IWGRP) ? 'w' : '-');
            printf("%c", (mode & S_IXGRP) ? 'x' : '-');

            printf("%c", (mode & S_IROTH) ? 'r' : '-');
            printf("%c", (mode & S_IWOTH) ? 'w' : '-');
            printf("%c", (mode & S_IXOTH) ? 'x' : '-');

            printf(" %d ", (int)state.st_nlink);
            struct passwd *owner_pw = getpwuid(state.st_uid);
            struct group *group_gr = getgrgid(state.st_gid);
            printf("%s ", owner_pw->pw_name);
            printf("%s ", group_gr->gr_name);
            printf("%*ld ", 7, state.st_size);

            char date[20];
            struct tm time;
            localtime_r(&state.st_mtime, &time);
            strftime(date, sizeof(date), "%b %d  %H:%M", &time);
            printf(" %s %s\n", date, path);
        }
        else printf("File %s doesnt exist in directory :(\n)", path);
    }
    return 0;
}